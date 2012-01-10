/* Headers for Linux*/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <sys/select.h>

#include <iostream>
#include <string>
/* Definition of PS3000 driver routines on Linux */
#include <libps5000-1.3/ps5000Api.h>

enum BOOL {FALSE,TRUE};


#define __min(a,b) (((a) < (b)) ? (a) : (b))
#define __max(a,b) (((a) > (b)) ? (a) : (b))
#define Sleep(x) usleep(1000*(x))


#define BUFFER_SIZE     500000
#define MAX_CHANNELS 4
//#define QUAD_SCOPE 4
#define DUAL_SCOPE 2
//#define SEGMEM          10


using namespace std;


////////////////////////////////////////
///////////STRUKTURY
////////////////////////////////////////

typedef enum
{
        MODEL_NONE = 0,
        MODEL_PS5203 = 5203,
        MODEL_PS5204 = 5204
} MODEL_TYPE;

typedef struct
{
        short DCcoupled;
        PS5000_RANGE range;
        short enabled;
}CHANNEL_SETTINGS;

typedef struct
{
        short handle;
        MODEL_TYPE model;
        PS5000_RANGE firstRange;
        PS5000_RANGE lastRange;
        unsigned char signalGenerator;
        unsigned char external;
        short ChannelCount;
        CHANNEL_SETTINGS channelSettings [MAX_CHANNELS];
        PS5000_RANGE triggerRange;
}UNIT_MODEL;

typedef struct tTriggerDirections
{
        enum enThresholdDirection channelA;
        enum enThresholdDirection channelB;
        enum enThresholdDirection channelC;
        enum enThresholdDirection channelD;
        enum enThresholdDirection ext;
        enum enThresholdDirection aux;
}TRIGGER_DIRECTIONS;

typedef struct tPwq
{
        struct tPwqConditions * conditions;
        short nConditions;
        enum enThresholdDirection direction;
        unsigned long lower;
        unsigned long upper;
        enum enPulseWidthType type;
}PWQ;


/////////////////////////////////////////
/////////ZMIENNE GLOBALNE
/////////////////////////////////////////
unsigned long timebase = 8;
int         trigger = 200;
//int         trig_source = 1;
short       oversample = 1;
//int         min_ampl = 30;

unsigned short inputRanges [PS5000_MAX_RANGES] = {         10,
                                                           20,
                                                           50,
                                                           100,
                                                           200,
                                                           500,
                                                           1000,
                                                           2000,
                                                           5000,
                                                           10000,
                                                           20000,
                                                           50000 };//w jednoskach [mV]

short     g_ready = FALSE;
long long g_times [PS5000_MAX_CHANNELS];
short     g_timeUnit;
long      g_sampleCount;
unsigned long g_startIndex;
short         g_autoStop;
long timeInterval;
long maxSamples;






/////////////////////////////////////////
////////FUNKCJE
////////////////////////////////////////




/****************************************************************************
*  * dec_to_bin
*   *
*    * Convert a decimal number to binary which is put to string value
*     *
*      *  //it is used to convert dec valueof iterator in loop to string with bin used e.g. to name a file
*       ****************************************************************************/

string dec_to_bin (int input)
{
int i=0;
int por=1;
string output;

while (input >= (por*2))
{
	por = por*2;
	i++;
}
if(input==0)
{
output.append("0");
}else{
output.append("1");
}
input -= por;
i--;
por /=2;
while(i>=0)
{
	if(input == 0 || input<por )
	{
	output.append("0");
	por /=2;
	}
	else
	{
	output.append("1");
	input -= por;
	por /=2;
	}
i--;
}
return output;                                      
}

/****************************************************************************
*  * dec8_to_bin
*   *
*    * Convert a decimal number (max 8) to binary which is put to string value
*     *
*      *  //it is used to convert dec valueof iterator in loop to string with bin used e.g. to name a file
*       ****************************************************************************/
string dec8_to_bin (int input)
{
string output;
switch (input)
	{
	case 0: {output = "000";}; break;
	case 1: {output = "001";}; break;
	case 2: {output = "010";}; break;
	case 3: {output = "011";}; break;
	case 4: {output = "100";}; break;
	case 5: {output = "101";}; break;
	case 6: {output = "110";}; break;
	case 7: {output = "111";}; break;
 	default: {output = "000";}; break;	
	}
return output;
}

/****************************************************************************
 *  * adc_to_mv
 *   *
 *    * If the user selects scaling to millivolts,
 *     * Convert an 16-bit ADC count into millivolts
 *      ****************************************************************************/
int adc_to_mv(long raw, int ch)
{
        return  ( raw * inputRanges[ch] ) / PS5000_MAX_VALUE ;
}


/****************************************************************************
 *  * mv_to_adc
 *   *
 *    * Convert a millivolt value into a 16-bit ADC count
 *     *
 *      *  (useful for setting trigger thresholds)
 *       ****************************************************************************/
short mv_to_adc(short mv, short ch)
{
        return ( ( mv * PS5000_MAX_VALUE ) /inputRanges[ch] );
}


/****************************************************************************
 *  * Initialise unit' structure with Variant specific defaults
 *   ****************************************************************************/
void get_info(UNIT_MODEL * unit)
{
        char description [6][25]= { "Driver Version",
                                            "USB Version",
                                            "Hardware Version",
                                            "Variant Info",
                                            "Serial",
                                            "Error Code" };
        short i, r = 0;
        char line [80];
        int variant;

        if (unit->handle) {
                for (i = 0; i < 5; i++) {
                        ps5000GetUnitInfo(unit->handle, line, sizeof (line), &r, i);
                        if (i == 3) {
                                variant = atoi(line);
                        }
                        printf("%s: %s\n", description[i], line);
                }

                switch (variant) {
                        case MODEL_PS5203:
                                unit->model = MODEL_PS5203;
                                unit->external = TRUE;
                                unit->signalGenerator = TRUE;
                                unit->firstRange = PS5000_100MV;
                                unit->lastRange = PS5000_20V;
                                unit->ChannelCount = DUAL_SCOPE;
                                break;
                        case MODEL_PS5204:
                                unit->model = MODEL_PS5204;
                                unit->external = TRUE;
                                unit->signalGenerator = TRUE;
                                unit->firstRange = PS5000_100MV;
                                unit->lastRange = PS5000_20V;
                                unit->ChannelCount = DUAL_SCOPE;
                                break;
                        default:
                                break;
                }
        }
}       


/****************************************************************************
 *  * SetDefaults - restore default settings
 *   ****************************************************************************/
void SetDefaults(UNIT_MODEL * unit)
{
        int i;

        ps5000SetEts(unit->handle, PS5000_ETS_OFF, 0, 0, NULL); // Turn off ETS

     //   for (i = 0; i < unit->ChannelCount; i++) // reset channels to most recent settings
     //   {
                ps5000SetChannel(unit->handle, PS5000_CHANNEL_A /*+ i*/,
                                 unit->channelSettings[PS5000_CHANNEL_A/* + i*/].enabled,
                                 unit->channelSettings[PS5000_CHANNEL_A/* + i*/].DCcoupled,
                                 unit->channelSettings[PS5000_CHANNEL_A/* + i*/].range);
       // }
}

/****************************************************************************
 *  * Callback
 *   * used by PS5000 data block collection calls, on receipt of data.
 *    * used to set global flags etc checked by user routines
 *     ****************************************************************************/
void PREF4 CallBackBlock(short handle,PICO_STATUS status,void * pParameter)
{
        // flag to say done reading data
                g_ready = TRUE;
}


/****************************************************************************
 *  * SetTrigger 
 *   * This function sets proper trigger. It evokes other function to
 *    * set all needed parameters.
 *     ****************************************************************************/
PICO_STATUS SetTrigger(short handle,
                       struct tTriggerChannelProperties * channelProperties,
                       short nChannelProperties,
                       struct tTriggerConditions * triggerConditions,
                       short nTriggerConditions,
                       TRIGGER_DIRECTIONS * directions,
                       struct tPwq * pwq,
                       unsigned long delay,
                       short auxOutputEnabled,
                       long autoTriggerMs)
{
        PICO_STATUS status;

        if ((status = ps5000SetTriggerChannelProperties(handle,
                                        channelProperties,
                                        nChannelProperties,
                                        auxOutputEnabled,
                                        autoTriggerMs)) != PICO_OK) {
                return status;
        }

        if ((status = ps5000SetTriggerChannelConditions(handle,
                                        triggerConditions,
                                        nTriggerConditions)) != PICO_OK) {
                return status;
        }

        if ((status = ps5000SetTriggerChannelDirections(handle,
                                        directions->channelA,
                                        directions->channelB,
                                        directions->channelC,
                                        directions->channelD,
                                        directions->ext,
                                        directions->aux)) != PICO_OK) {
                return status;
        }

        if ((status = ps5000SetTriggerDelay(handle, delay)) != PICO_OK) {
                return status;
        }

        status = ps5000SetPulseWidthQualifier(handle, pwq->conditions,
                                              pwq->nConditions, pwq->direction,
                                              pwq->lower, pwq->upper, pwq->type);
        return status;
}

/****************************************************************************
 *  * Change_config 
 *   * This function sends new configuration string on USB port 
****************************************************************************/
void Change_config(string input)
{
short unsigned diff;
string input_new="";
diff = 12 - input.length();
//sprawdzamy czy przychodzacy string ma dlugosc 12. Moze byc tak ze np liczba 8 to
//w bin 1000 a zatem pozostale miejsca wypelniamy 0 zeby otrzymac 0000 0000 1000
if(diff!=0)
{
for (int s=0; s<diff; s++){input_new+="0";}
}
input_new+=input;
system(string("echo 000001101111"+input_new+"1 >/dev/ttyUSB0").c_str());
cout<<string("echo 000001101111"+input_new+"1 >/dev/ttyUSB0")<<endl;
}


                    

//////////////////////////////////////////////
//////
//////
//////MAIN
//////
//////////////////////////////////////////////

int main()
{
        char ch;
        short i;
        PICO_STATUS status;
        UNIT_MODEL unit;


        int ch1_volt = 6; // 2V default range
        unsigned int Sample_Count=0;//ilosc sampli
        unsigned int Sample_Before_Trigger_Count=0;//ilosc sampli przed trygerem
	unsigned int trace_number=10;//ilosc przebiegow
        timebase = 1;//podstawa czasu (czyli co jaki czas wystepuje sampel) 
        trigger = 200;//tryger w mV - ta wartosc i tak bedzie zmieniana
	unsigned short iter_r1_min = 0;
	unsigned short iter_r1_max =7;
	unsigned short iter_c1_min = 0;
	unsigned short iter_c1_max =7;
	unsigned short iter_r2_min = 0;
	unsigned short iter_r2_max =7;
	unsigned short iter_c2_min = 0;
	unsigned short iter_c2_max =7;
	


        printf ("\n\nOpening configuration file ... \n");
        FILE *cfg_file = fopen ("param.txt","rt");
        char str_buf [25];
        int val;

        if (cfg_file == NULL) {
            printf ("No config file !\r\n");
            exit (0);
        }

        while (!feof(cfg_file)) {//////////////////////////////////////////wczytanie wartości z pliku konfiguracyjnego

            fscanf (cfg_file,"%s %d\n",str_buf,&val);
            if ( strcmp (str_buf,"CH1_VOLT") == 0 ) ch1_volt = val;
            if ( strcmp (str_buf,"TRIGGER") == 0 ) trigger = val;
            if ( strcmp (str_buf,"TIMEBASE") == 0 ) timebase = val;
            if ( strcmp (str_buf,"SAMPLE_COUNT") == 0 ) Sample_Count = val;
            if ( strcmp (str_buf,"SAMPLE_BEFORE_TRIGGER") == 0 ) Sample_Before_Trigger_Count = val;
            if ( strcmp (str_buf,"TRACE_NUMBER") == 0 ) trace_number = val;
            if ( strcmp (str_buf,"ITER_r1_min") == 0 ) iter_r1_min = val;
            if ( strcmp (str_buf,"ITER_r1_max") == 0 ) iter_r1_max = val;
            if ( strcmp (str_buf,"ITER_c1_min") == 0 ) iter_c1_min = val;
            if ( strcmp (str_buf,"ITER_c1_max") == 0 ) iter_c1_max = val;
            if ( strcmp (str_buf,"ITER_r2_min") == 0 ) iter_r2_min = val;
            if ( strcmp (str_buf,"ITER_r2_max") == 0 ) iter_r2_max = val;
            if ( strcmp (str_buf,"ITER_c2_min") == 0 ) iter_c2_min = val;
            if ( strcmp (str_buf,"ITER_c2_max") == 0 ) iter_c2_max = val;
            if ( strcmp (str_buf,"#####################") == 0 ) break;
        }

        fclose (cfg_file);////////////////////////////////////////////////////////

        printf("\n\nOpening the device...\n");
        status = ps5000OpenUnit(&(unit.handle));
        printf("Handle: %d\n", unit.handle);
        if (status != PICO_OK) {
                printf("Unable to open device\n");
                printf("Error code : %d\n", (int)status);
                exit(0);
        }
        printf("Device opened successfully \r\n");



        //setup device
        get_info(&unit);
        //set input ranges
        unit.channelSettings[PS5000_CHANNEL_A].range = (PS5000_RANGE) ch1_volt;
        unit.channelSettings[PS5000_CHANNEL_A].enabled = TRUE;
        unit.channelSettings[PS5000_CHANNEL_A].DCcoupled = FALSE;
        printf("Channel  A -> %d mV\n", inputRanges[ch1_volt]);


        short triggerVoltage = mv_to_adc(trigger,ch1_volt);//wartosc trygera w mV zostala wczytana z pliku param.txt. Tutaj jest zamieniana na skalę adc
	struct tTriggerChannelProperties sourceDetails = { triggerVoltage,
                                                                   triggerVoltage,
                                                                  128,// 256 * 10,//histereza
                                                                   PS5000_CHANNEL_A,
                                                                   LEVEL };
        struct tTriggerConditions conditions = {         CONDITION_TRUE,//tryger na kanale A
                                                         CONDITION_DONT_CARE,
                                                         CONDITION_DONT_CARE,
                                                         CONDITION_DONT_CARE,
                                                         CONDITION_DONT_CARE,
                                                         CONDITION_DONT_CARE,
                                                         CONDITION_DONT_CARE };
        struct tTriggerDirections directions = {         FALLING, //wyzwala zbocze rosnące
                                                         NONE,
                                                         NONE,
                                                         NONE,
                                                         NONE,
                                                         NONE };


        struct tPwq pulseWidth;				//szerokość impulsu potrzebne do tworzenia bardziej złożonych trygerów
        memset(&pulseWidth, 0, sizeof(struct tPwq));	//
        
	printf("Collects when value rises past %dmV\n",adc_to_mv(sourceDetails.thresholdMajor,ch1_volt));
        SetDefaults(&unit);

	/*Setting up trigger*/
	SetTrigger(unit.handle, &sourceDetails, 1, &conditions, 1, &directions,
                   &pulseWidth, 0, 0, 0);
	/*******************/
	
        int j;
        unsigned long sampleCount = Sample_Count;
        FILE * fp;
        short * buffers[PS5000_MAX_CHANNEL_BUFFERS * 2];
        long timeIndisposed;

        long nMaxSamples;
        unsigned long segmentIndex;
        unsigned long noOfSamples;

	//inicjalizacja buforów do przechowywania danych
        buffers[0] = (short*)malloc(sampleCount * sizeof(short));
        buffers[1] = (short*)malloc(sampleCount * sizeof(short));
        ps5000SetDataBuffers(unit.handle, PS5000_CHANNEL_A, buffers[0], buffers[1], sampleCount);




        /*  find the maximum number of samples, the time interval (in timeUnits),
 *           *               the most suitable time units, and the maximum oversample at the current timebase*/
        while (ps5000GetTimebase(unit.handle, timebase, sampleCount,
                                 &timeInterval, oversample,
                                 &maxSamples, 0))
        {
                timebase++;
        }

        printf("timebase: %lu\toversample:%hd\n", timebase-1, oversample);
        printf("interval %ld ns\r\n" ,timeInterval);

        long result_tables [Sample_Count];
        for (i = 0 ; i < Sample_Count  ; i++ ) result_tables [i] = 0;

	system("stty -F /dev/ttyUSB0 speed 9600");//potrzebne do configuracji FE

	int pass=0;
        int esc=0; 
	int pass_real=0;     
	string cmd = "";

for (int hr1= iter_r1_min; hr1<=iter_r1_max; hr1++)
{
  for (int hc1= iter_c1_min; hc1<=iter_c1_max; hc1++)
  {
    for (int hr2= iter_r2_min; hr2<=iter_r2_max; hr2++)
    {
      for (int hc2= iter_c2_min; hc2<=iter_c2_max; hc2++)
        {	
	
        for (i = 0 ; i < Sample_Count  ; i++ ) result_tables [i] = 0;//zerowanie tablicy
	//creating word for new configuration
	cmd="";
	cmd += dec8_to_bin(hr1) + dec8_to_bin(hc1) + dec8_to_bin(hr2) + dec8_to_bin(hc2);

	//changing configuration
	Change_config(cmd);
        usleep (50000);//odczekamy chwilę aby nowa konfiguracja się wgrała
	
	pass = 0;//do zbierania wielu przebieg
        pass_real=0;
        esc=0;
        
	while (pass<trace_number)
	{
            /* Start it collecting, then wait for completion*/
            g_ready = FALSE;

            status = ps5000RunBlock(unit.handle,Sample_Before_Trigger_Count, sampleCount, timebase, oversample,//drugi argument odpowiada za ilosc sampli przed trygerem
                                &timeIndisposed, 0, CallBackBlock, NULL);
            
            printf("Waiting for trigger...  x%d\r\n",pass+1);
            while (!g_ready && esc <5000)//kiedy runBlock zakończy zbieranie danych zmienia flage 
	    {
             usleep (1000);
	     esc++;
            }
            
            ps5000Stop(unit.handle);//powstrzymuje oscyloskop od dalszego zbierania danych

            if (g_ready) 
	    {
                    ps5000GetValues(unit.handle, 0, (unsigned long*) &sampleCount, 1, RATIO_MODE_NONE, 0 , NULL);
                    noOfSamples = sampleCount;
                    sampleCount = __min(sampleCount, BUFFER_SIZE);
                        for (i = 0; i < sampleCount ; i++) 
			{
                            result_tables [i] += buffers[0][i];
                        }
                        pass ++;
			if(esc<5000) pass_real++;//jesli pojawił się tryger to esc<5000 wtedy pass_real++
            } else {
                    printf("data collection aborted\n");
            }
        } //  trace_number loop end 
       
	 /*ZAPIS DANYCH DO PLIKU*/
        fp = fopen(string("./output/"+cmd).c_str(), "w");//nazwa pliku bedzie 12bit slowo konfiguracyjne
        printf("\nWriting data...\n");
        for (i = 0 ; i < Sample_Count ; i++)
        {
            fprintf (fp,"%d\t%d\n",i,adc_to_mv(  (long)  (result_tables[i]/pass_real), ch1_volt   ) );//usredniamy wartosci, konwert do mv i zapisujemy do pliku
        }
        fclose(fp);
        /*********************/
	}//hc2
      }//hr2
    }//hc1
  }//hr1
        
	free(buffers[0]);
	free(buffers[1]);
	
        printf("Closing unit...\n");
        ps5000CloseUnit(unit.handle);

return 0;
}
