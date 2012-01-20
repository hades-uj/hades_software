/*
 * Author: Paweł Strzempek
 * Contact: pawel.strzempek@uj.edu.pl
 * Description: Program tworzy słowo sterujące na podstawie wyborów dokonanych w combobox-ach.
 * 		Następnie uruchamia inny program (jego nazwa wnna być wpisana do pliku config.txt)
 * 		z linii komend urzywając utworzonego słowa jako argumentu.
 */


#include "interface.h"


using namespace std;//std::string;

void send_function(GtkWidget *widget, int i);
void exit_function(GtkWidget *widget, int i);
void defaultValue_function(GtkWidget *widget, int i);

int main( int argc, char *argv[])
{
  GtkWidget *window;
  GtkWidget *send_button;
  GtkWidget *exit_button;
  GtkWidget *default_button;
  GtkWidget *frame;
//lables
  GtkWidget *preamplifier_gain_label;
  GtkWidget *preamplifier_time_constant_label;
  GtkWidget *rp_label;
  GtkWidget *cp_label;
  GtkWidget *tp_label;
  GtkWidget *tcmode_label;
  GtkWidget *rt1_label;
  GtkWidget *ct1_label;
  GtkWidget *rt2_label;
  GtkWidget *ct2_label;
  GtkWidget *blh_label;
  GtkWidget *pF_label[3];
  GtkWidget *kOhm_label[4];
  GtkWidget *bit_label[3];
  GtkWidget *mvfc_label;
  GtkWidget *ns_label;

//wczytanie z pliku nazwy programu do wywołania
//
  ifstream myfile ("config.txt");
  if (myfile.is_open())
     {
     if ( myfile.good() )
        {
        getline (myfile,nazwa_programu);
        }
     if( myfile.good() )
	{
	getline (myfile,cmd);
	}
     if( myfile.good() )
	{
	getline (myfile,cmd1);
	}
     if ( myfile.good() )
        {
        getline (myfile,zapamietane_wartosci);
        }
     if ( myfile.good() )
        {
        getline (myfile,domyslne_wartosci);
        }

     myfile.close();
     }
  else {cout << "Unable to open file: 'config.txt'\n"; return 0;}

system(nazwa_programu.c_str());//"stty -F /dev/ttyUSB0 speed 9600");
cout<<nazwa_programu.c_str()<<endl;
//
  gtk_init(&argc, &argv);
//inicjalizacja okna
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_resize( GTK_WINDOW(window), 560,520);

  gtk_widget_show(window);
//
  frame = gtk_fixed_new();
  gtk_container_add(GTK_CONTAINER(window), frame);

//Inicjalizacja przycisków
  send_button = gtk_button_new_with_label("send");
  gtk_widget_set_size_request(send_button, 100, 40);
  gtk_fixed_put(GTK_FIXED(frame), send_button, 190, 480);

  exit_button = gtk_button_new_with_label("exit");
  gtk_widget_set_size_request(exit_button, 100, 40);
  gtk_fixed_put(GTK_FIXED(frame), exit_button, 320, 480);
  
  default_button = gtk_button_new_with_label("default values");
  gtk_widget_set_size_request(default_button, 100, 40);
  gtk_fixed_put(GTK_FIXED(frame), default_button, 30, 480);
//Inicjalizacja wszystkich etykietek i umieszczenie ich na oknie
  preamplifier_gain_label = gtk_label_new("Preamplifier  gain");
  gtk_widget_set_size_request(preamplifier_gain_label, 240, 30);
  gtk_fixed_put(GTK_FIXED(frame), preamplifier_gain_label, 20, 40);

  preamplifier_time_constant_label = gtk_label_new("Preamp. time const");
  gtk_widget_set_size_request(preamplifier_time_constant_label, 240, 30);
  gtk_fixed_put(GTK_FIXED(frame), preamplifier_time_constant_label, 20, 80);

  rp_label = gtk_label_new("Rp");
  gtk_widget_set_size_request(rp_label, 240, 30);
  gtk_fixed_put(GTK_FIXED(frame), rp_label, 20, 120);

  cp_label = gtk_label_new("Cp");
  gtk_widget_set_size_request(cp_label, 240, 30);
  gtk_fixed_put(GTK_FIXED(frame), cp_label, 20, 160);

  tp_label = gtk_label_new("Tp");
  gtk_widget_set_size_request(tp_label, 240, 30);
  gtk_fixed_put(GTK_FIXED(frame), tp_label, 20, 200);

  tcmode_label = gtk_label_new("Tail cancelation");
  gtk_widget_set_size_request(tcmode_label, 240, 30);
  gtk_fixed_put(GTK_FIXED(frame), tcmode_label, 20, 240);
  
  rt1_label = gtk_label_new("Rt1");
  gtk_widget_set_size_request(rt1_label, 240, 30);
  gtk_fixed_put(GTK_FIXED(frame), rt1_label, 20, 280);

  ct1_label = gtk_label_new("Ct1");
  gtk_widget_set_size_request(ct1_label, 240, 30);
  gtk_fixed_put(GTK_FIXED(frame), ct1_label, 20, 320);

  rt2_label = gtk_label_new("Rt2");
  gtk_widget_set_size_request(rt2_label, 240, 30);
  gtk_fixed_put(GTK_FIXED(frame), rt2_label, 20, 360);
  
  ct2_label = gtk_label_new("Ct2");
  gtk_widget_set_size_request(ct2_label, 240, 30);
  gtk_fixed_put(GTK_FIXED(frame), ct2_label, 20, 400);

  blh_label = gtk_label_new("BLH");
  gtk_widget_set_size_request(blh_label, 240, 30);
  gtk_fixed_put(GTK_FIXED(frame), blh_label, 20, 440);

  for(int i=0; i<3;i++){
  pF_label[i] = gtk_label_new("pF");
  gtk_widget_set_size_request(pF_label[i], 40, 30);

  kOhm_label[i] = gtk_label_new("kOhm");
  gtk_widget_set_size_request(kOhm_label[i], 40, 30);

 // bit_label[i] = gtk_label_new("");
 // gtk_widget_set_size_request(bit_label[i], 40, 30);
  }
  
  kOhm_label[3] = gtk_label_new("kOhm");
  gtk_widget_set_size_request(kOhm_label[3], 40, 30);

  mvfc_label = gtk_label_new("mV/fC");
  gtk_widget_set_size_request(mvfc_label, 40, 30);

  ns_label = gtk_label_new("ns");
  gtk_widget_set_size_request(ns_label, 40, 30);
  
  
//koniec inicjalizacji wszytkich etykietek
//inicjalizacja wszystkich combobox

  preamplifier_gain_combobox = gtk_combo_box_new();
  preamplifier_gain_combobox = gtk_combo_box_new_text();
  gtk_combo_box_append_text(GTK_COMBO_BOX(preamplifier_gain_combobox) ,"0.5");gtk_fixed_put(GTK_FIXED(frame), mvfc_label, 510, 40);
  gtk_combo_box_append_text(GTK_COMBO_BOX(preamplifier_gain_combobox) ,"1");
  gtk_combo_box_append_text(GTK_COMBO_BOX(preamplifier_gain_combobox) ,"2");
  gtk_combo_box_append_text(GTK_COMBO_BOX(preamplifier_gain_combobox) ,"4");
  gtk_widget_set_size_request(preamplifier_gain_combobox, 240, 30);
  gtk_fixed_put(GTK_FIXED(frame),preamplifier_gain_combobox , 260, 40);
  gtk_combo_box_set_active(GTK_COMBO_BOX(preamplifier_gain_combobox),zapamietane_wartosci[0]-48);

  preamplifier_time_constant_combobox=gtk_combo_box_new();
  preamplifier_time_constant_combobox = gtk_combo_box_new_text();
  gtk_combo_box_append_text(GTK_COMBO_BOX(preamplifier_time_constant_combobox) ,"100");gtk_fixed_put(GTK_FIXED(frame), kOhm_label[3], 510, 80);
  gtk_combo_box_append_text(GTK_COMBO_BOX(preamplifier_time_constant_combobox) ,"200");
  gtk_combo_box_append_text(GTK_COMBO_BOX(preamplifier_time_constant_combobox) ,"300");
  gtk_combo_box_append_text(GTK_COMBO_BOX(preamplifier_time_constant_combobox) ,"400");
  gtk_widget_set_size_request(preamplifier_time_constant_combobox, 240, 30);
  gtk_fixed_put(GTK_FIXED(frame),preamplifier_time_constant_combobox , 260, 80);
  gtk_combo_box_set_active(GTK_COMBO_BOX(preamplifier_time_constant_combobox),zapamietane_wartosci[1]-48);

  rp_combobox=gtk_combo_box_new();
  rp_combobox = gtk_combo_box_new_text();
  gtk_combo_box_append_text(GTK_COMBO_BOX(rp_combobox) ,"5");gtk_fixed_put(GTK_FIXED(frame), kOhm_label[0], 510, 120);
  gtk_combo_box_append_text(GTK_COMBO_BOX(rp_combobox) ,"10");
  gtk_combo_box_append_text(GTK_COMBO_BOX(rp_combobox) ,"20");
  gtk_combo_box_append_text(GTK_COMBO_BOX(rp_combobox) ,"40");
  gtk_widget_set_size_request(rp_combobox, 240, 30);
  gtk_fixed_put(GTK_FIXED(frame),rp_combobox , 260, 120);
  gtk_combo_box_set_active(GTK_COMBO_BOX(rp_combobox),zapamietane_wartosci[2]-48);

  cp_combobox=gtk_combo_box_new();
  cp_combobox = gtk_combo_box_new_text();
  gtk_combo_box_append_text(GTK_COMBO_BOX(cp_combobox) ,"5");gtk_fixed_put(GTK_FIXED(frame), pF_label[0], 510, 160);
  gtk_combo_box_append_text(GTK_COMBO_BOX(cp_combobox) ,"7.5");
  gtk_combo_box_append_text(GTK_COMBO_BOX(cp_combobox) ,"10");
  gtk_combo_box_append_text(GTK_COMBO_BOX(cp_combobox) ,"20");
  gtk_widget_set_size_request(cp_combobox, 240, 30);
  gtk_fixed_put(GTK_FIXED(frame),cp_combobox , 260, 160);
  gtk_combo_box_set_active(GTK_COMBO_BOX(cp_combobox),zapamietane_wartosci[3]-48);

  tp_combobox=gtk_combo_box_new();
  tp_combobox = gtk_combo_box_new_text();
  gtk_combo_box_append_text(GTK_COMBO_BOX(tp_combobox) ,"11");//gtk_fixed_put(GTK_FIXED(frame), _label, 510, 200);
  gtk_combo_box_append_text(GTK_COMBO_BOX(tp_combobox) ,"10");
  gtk_combo_box_append_text(GTK_COMBO_BOX(tp_combobox) ,"01");
  gtk_combo_box_append_text(GTK_COMBO_BOX(tp_combobox) ,"00");
  gtk_widget_set_size_request(tp_combobox, 240, 30);
  gtk_fixed_put(GTK_FIXED(frame),tp_combobox , 260, 200);
  gtk_combo_box_set_active(GTK_COMBO_BOX(tp_combobox),zapamietane_wartosci[4]-48); 

  tcmode_combobox=gtk_combo_box_new();
  tcmode_combobox = gtk_combo_box_new_text();
  gtk_combo_box_append_text(GTK_COMBO_BOX(tcmode_combobox) ,"CR_RC");
  gtk_combo_box_append_text(GTK_COMBO_BOX(tcmode_combobox) ,"TC_1_on, TC_2_off");
  gtk_combo_box_append_text(GTK_COMBO_BOX(tcmode_combobox) ,"TC_1_off,TC_2_on");
  gtk_combo_box_append_text(GTK_COMBO_BOX(tcmode_combobox) ,"TC_on");
  gtk_widget_set_size_request(tcmode_combobox, 240, 30);
  gtk_fixed_put(GTK_FIXED(frame),tcmode_combobox , 260, 240);
  gtk_combo_box_set_active(GTK_COMBO_BOX(tcmode_combobox),zapamietane_wartosci[5]-48);

  rt1_combobox=gtk_combo_box_new();
  rt1_combobox = gtk_combo_box_new_text();
  gtk_combo_box_append_text(GTK_COMBO_BOX(rt1_combobox) ,"3");gtk_fixed_put(GTK_FIXED(frame), kOhm_label[1], 510, 280);
  gtk_combo_box_append_text(GTK_COMBO_BOX(rt1_combobox) ,"7");
  gtk_combo_box_append_text(GTK_COMBO_BOX(rt1_combobox) ,"11");
  gtk_combo_box_append_text(GTK_COMBO_BOX(rt1_combobox) ,"15");
  gtk_combo_box_append_text(GTK_COMBO_BOX(rt1_combobox) ,"19");
  gtk_combo_box_append_text(GTK_COMBO_BOX(rt1_combobox) ,"23");
  gtk_combo_box_append_text(GTK_COMBO_BOX(rt1_combobox) ,"27");
  gtk_combo_box_append_text(GTK_COMBO_BOX(rt1_combobox) ,"31");
  gtk_widget_set_size_request(rt1_combobox, 240, 30);
  gtk_fixed_put(GTK_FIXED(frame),rt1_combobox , 260, 280);
  gtk_combo_box_set_active(GTK_COMBO_BOX(rt1_combobox),zapamietane_wartosci[6]-48);
 
  ct1_combobox=gtk_combo_box_new();
  ct1_combobox = gtk_combo_box_new_text();
  gtk_combo_box_append_text(GTK_COMBO_BOX(ct1_combobox) ,"6");gtk_fixed_put(GTK_FIXED(frame), pF_label[1], 510, 320);
  gtk_combo_box_append_text(GTK_COMBO_BOX(ct1_combobox) ,"7.5");
  gtk_combo_box_append_text(GTK_COMBO_BOX(ct1_combobox) ,"9");
  gtk_combo_box_append_text(GTK_COMBO_BOX(ct1_combobox) ,"10.5");
  gtk_combo_box_append_text(GTK_COMBO_BOX(ct1_combobox) ,"12");
  gtk_combo_box_append_text(GTK_COMBO_BOX(ct1_combobox) ,"13.5");
  gtk_combo_box_append_text(GTK_COMBO_BOX(ct1_combobox) ,"15");
  gtk_combo_box_append_text(GTK_COMBO_BOX(ct1_combobox) ,"16.5");
  gtk_widget_set_size_request(ct1_combobox, 240, 30);
  gtk_fixed_put(GTK_FIXED(frame),ct1_combobox , 260, 320);
  gtk_combo_box_set_active(GTK_COMBO_BOX(ct1_combobox),zapamietane_wartosci[7]-48);

  rt2_combobox=gtk_combo_box_new();
  rt2_combobox = gtk_combo_box_new_text();
  gtk_combo_box_append_text(GTK_COMBO_BOX(rt2_combobox) ,"5");gtk_fixed_put(GTK_FIXED(frame), kOhm_label[2], 510, 360);
  gtk_combo_box_append_text(GTK_COMBO_BOX(rt2_combobox) ,"8");
  gtk_combo_box_append_text(GTK_COMBO_BOX(rt2_combobox) ,"11");
  gtk_combo_box_append_text(GTK_COMBO_BOX(rt2_combobox) ,"14");
  gtk_combo_box_append_text(GTK_COMBO_BOX(rt2_combobox) ,"17");
  gtk_combo_box_append_text(GTK_COMBO_BOX(rt2_combobox) ,"20");
  gtk_combo_box_append_text(GTK_COMBO_BOX(rt2_combobox) ,"23");
  gtk_combo_box_append_text(GTK_COMBO_BOX(rt2_combobox) ,"26");
  gtk_widget_set_size_request(rt2_combobox, 240, 30);
  gtk_fixed_put(GTK_FIXED(frame),rt2_combobox , 260, 360);
  gtk_combo_box_set_active(GTK_COMBO_BOX(rt2_combobox),zapamietane_wartosci[8]-48);

  ct2_combobox=gtk_combo_box_new();
  ct2_combobox = gtk_combo_box_new_text();
  gtk_combo_box_append_text(GTK_COMBO_BOX(ct2_combobox) ,"0.6");gtk_fixed_put(GTK_FIXED(frame), pF_label[2], 510, 400);
  gtk_combo_box_append_text(GTK_COMBO_BOX(ct2_combobox) ,"0.75");
  gtk_combo_box_append_text(GTK_COMBO_BOX(ct2_combobox) ,"0.9");
  gtk_combo_box_append_text(GTK_COMBO_BOX(ct2_combobox) ,"1.05");
  gtk_combo_box_append_text(GTK_COMBO_BOX(ct2_combobox) ,"1.2");
  gtk_combo_box_append_text(GTK_COMBO_BOX(ct2_combobox) ,"1.35");
  gtk_combo_box_append_text(GTK_COMBO_BOX(ct2_combobox) ,"1.5");
  gtk_combo_box_append_text(GTK_COMBO_BOX(ct2_combobox) ,"1.65");
  gtk_widget_set_size_request(ct2_combobox, 240, 30);
  gtk_fixed_put(GTK_FIXED(frame),ct2_combobox , 260, 400);
  gtk_combo_box_set_active(GTK_COMBO_BOX(ct2_combobox),zapamietane_wartosci[9]-48);
  
  blh_combobox=gtk_combo_box_new();
  blh_combobox = gtk_combo_box_new_text();
  gtk_combo_box_append_text(GTK_COMBO_BOX(blh_combobox) ,"on");
  gtk_combo_box_append_text(GTK_COMBO_BOX(blh_combobox) ,"off");
  gtk_widget_set_size_request(blh_combobox, 240, 30);
  gtk_fixed_put(GTK_FIXED(frame),blh_combobox , 260, 440);
  gtk_combo_box_set_active(GTK_COMBO_BOX(blh_combobox),zapamietane_wartosci[10]-48);

//koniec inicjalizacji combobox

//wczytanie z pliku nazwy programu do wywołania


  gtk_widget_show_all(window);

  g_signal_connect(window, "destroy",
  G_CALLBACK (gtk_main_quit), NULL);

  g_signal_connect(send_button, "clicked", 
  G_CALLBACK(send_function),0);

  g_signal_connect(exit_button, "clicked", 
  G_CALLBACK(exit_function),0);
 
  g_signal_connect(default_button, "clicked", 
  G_CALLBACK(defaultValue_function),0);
 
  gtk_main();
  return 0;
}

//fukcja jest wywoływana po naciśnięciu przycisku send. Ma za zadanie zebrać informacje z wszystkich combo
//boxów i utworzyć słowo sterujące. Na koniec wywołuje inną program do którego utworzone słowo podaje jako
//argument.
void send_function(GtkWidget *widget,int i )
{
gchar * zaznaczenia[11];
std::string slowo;
string instrukcja="";

zaznaczenia[0] = gtk_combo_box_get_active_text(GTK_COMBO_BOX(preamplifier_gain_combobox));
zaznaczenia[1] = gtk_combo_box_get_active_text(GTK_COMBO_BOX(preamplifier_time_constant_combobox));
zaznaczenia[2] = gtk_combo_box_get_active_text(GTK_COMBO_BOX(rp_combobox));
zaznaczenia[3] = gtk_combo_box_get_active_text(GTK_COMBO_BOX(cp_combobox));
zaznaczenia[4] = gtk_combo_box_get_active_text(GTK_COMBO_BOX(tp_combobox));
zaznaczenia[5] = gtk_combo_box_get_active_text(GTK_COMBO_BOX(tcmode_combobox));
zaznaczenia[6] = gtk_combo_box_get_active_text(GTK_COMBO_BOX(rt1_combobox));
zaznaczenia[7] = gtk_combo_box_get_active_text(GTK_COMBO_BOX(ct1_combobox));
zaznaczenia[8] = gtk_combo_box_get_active_text(GTK_COMBO_BOX(rt2_combobox));
zaznaczenia[9] = gtk_combo_box_get_active_text(GTK_COMBO_BOX(ct2_combobox));
zaznaczenia[10] = gtk_combo_box_get_active_text(GTK_COMBO_BOX(blh_combobox));



if(!string("0.5").compare(zaznaczenia[0]))
	slowo.append("11");//00
else if (!string("1").compare(zaznaczenia[0]))
	slowo.append("01");//01
else if (!string("2").compare(zaznaczenia[0]))
	slowo.append("10");//10
else if (!string("4").compare(zaznaczenia[0]))
	slowo.append("00");//11


if(!string("400").compare(zaznaczenia[1]))
	slowo.append("00");
else if (!string("300").compare(zaznaczenia[1]))
	slowo.append("01");
else if (!string("200").compare(zaznaczenia[1]))
	slowo.append("10");
else if (!string("100").compare(zaznaczenia[1]))
	slowo.append("11");

if(!string("5").compare(zaznaczenia[2]))
	slowo.append("00");
else if (!string("10").compare(zaznaczenia[2]))
	slowo.append("01");
else if (!string("20").compare(zaznaczenia[2]))
	slowo.append("10");
else if (!string("40").compare(zaznaczenia[2]))
	slowo.append("11");

if(!string("5").compare(zaznaczenia[3]))
	slowo.append("00");
else if (!string("7.5").compare(zaznaczenia[3]))
	slowo.append("01");
else if (!string("10").compare(zaznaczenia[3]))
	slowo.append("10");
else if (!string("20").compare(zaznaczenia[3]))
	slowo.append("11");

slowo.append(zaznaczenia[4]);

if(!string("CR_RC").compare(zaznaczenia[5]))
        slowo.append("00");
else if (!string("TC_1_on,TC_2_off").compare(zaznaczenia[5]))
        slowo.append("01");
else if (!string("TC_1_off,TC_2_on").compare(zaznaczenia[5]))
        slowo.append("10");
else if (!string("TC_on").compare(zaznaczenia[5]))
        slowo.append("11");

if(!string("3").compare(zaznaczenia[6]))
        slowo.append("000");
else if (!string("7").compare(zaznaczenia[6]))
        slowo.append("001");
else if (!string("11").compare(zaznaczenia[6]))
        slowo.append("010");
else if (!string("15").compare(zaznaczenia[6]))
        slowo.append("011");
else if (!string("19").compare(zaznaczenia[6]))
        slowo.append("100");
else if (!string("23").compare(zaznaczenia[6]))
        slowo.append("101");
else if (!string("27").compare(zaznaczenia[6]))
        slowo.append("110");
else if (!string("31").compare(zaznaczenia[6]))
        slowo.append("111");

if(!string("6").compare(zaznaczenia[7]))
        slowo.append("000");
else if (!string("7.5").compare(zaznaczenia[7]))
        slowo.append("001");
else if (!string("9").compare(zaznaczenia[7]))
        slowo.append("010");
else if (!string("10.5").compare(zaznaczenia[7]))
        slowo.append("011");
else if (!string("12").compare(zaznaczenia[7]))
        slowo.append("100");
else if (!string("13.5").compare(zaznaczenia[7]))
        slowo.append("101");
else if (!string("15").compare(zaznaczenia[7]))
        slowo.append("110");
else if (!string("16.5").compare(zaznaczenia[7]))
        slowo.append("111");

if(!string("5").compare(zaznaczenia[8]))
        slowo.append("000");
else if (!string("8").compare(zaznaczenia[8]))
        slowo.append("001");
else if (!string("11").compare(zaznaczenia[8]))
        slowo.append("010");
else if (!string("14").compare(zaznaczenia[8]))
        slowo.append("011");
else if (!string("17").compare(zaznaczenia[8]))
        slowo.append("100");
else if (!string("20").compare(zaznaczenia[8]))
        slowo.append("101");
else if (!string("23").compare(zaznaczenia[8]))
        slowo.append("110");
else if (!string("26").compare(zaznaczenia[8]))
        slowo.append("111");

if(!string("0.6").compare(zaznaczenia[9]))
        slowo.append("000");
else if (!string("0.75").compare(zaznaczenia[9]))
        slowo.append("001");
else if (!string("0.9").compare(zaznaczenia[9]))
        slowo.append("010");
else if (!string("1.05").compare(zaznaczenia[9]))
        slowo.append("011");
else if (!string("1.2").compare(zaznaczenia[9]))
        slowo.append("100");
else if (!string("1.35").compare(zaznaczenia[9]))
        slowo.append("101");
else if (!string("1.5").compare(zaznaczenia[9]))
        slowo.append("110");
else if (!string("1.65").compare(zaznaczenia[9]))
        slowo.append("111");

if(!string("on").compare(zaznaczenia[10]))
        slowo.append("1");
else if (!string("off").compare(zaznaczenia[10]))
        slowo.append("0");

//cout<<slowo<<endl;
//instrukcja += "./"+nazwa_programu+" "+slowo+" >/dev/ttyUSB0";


//instrukcja += "echo "+slowo+" >/dev/ttyUSB0";
//cmd += slowo + " >/dev/ttyUSB0";
system(string(cmd+" "+slowo+ " "+cmd1).c_str());
cout<<string(cmd+" "+slowo+ " "+cmd1).c_str()<<endl;
//std::cerr<<"\n\n"<<instrukcja<<endl;
}

void exit_function(GtkWidget *widget,int i )
{
fstream myfile;
myfile.open("config.txt",fstream::in | fstream::out | fstream::trunc);
if(myfile.good())//zapisywanie konfiguracji do pliku żeby po otwarciu programu znowu można było ją załadować
{
//myfile<<nazwa_programu;
//myfile<<cmd;
myfile<<nazwa_programu<<"\n"<<cmd<<"\n"<<cmd1<<"\n"<<gtk_combo_box_get_active(GTK_COMBO_BOX(preamplifier_gain_combobox))<<gtk_combo_box_get_active(GTK_COMBO_BOX(preamplifier_time_constant_combobox))<<gtk_combo_box_get_active(GTK_COMBO_BOX(rp_combobox))<<gtk_combo_box_get_active(GTK_COMBO_BOX(cp_combobox))<<gtk_combo_box_get_active(GTK_COMBO_BOX(tp_combobox))<<gtk_combo_box_get_active(GTK_COMBO_BOX(tcmode_combobox))<<gtk_combo_box_get_active(GTK_COMBO_BOX(rt1_combobox))<<gtk_combo_box_get_active(GTK_COMBO_BOX(ct1_combobox))<<gtk_combo_box_get_active(GTK_COMBO_BOX(rt2_combobox))<<gtk_combo_box_get_active(GTK_COMBO_BOX(ct2_combobox))<<gtk_combo_box_get_active(GTK_COMBO_BOX(blh_combobox))<<"\n"<<domyslne_wartosci;
}
else cout<<"File save error!\n";
myfile.close();

exit(0);
}


void defaultValue_function(GtkWidget *widget,int i )//po nacisnieciu przycisku wartosci domyslnych wszystkie comobo_box sa ustawiane na odpowiednie wartosci
{
  gtk_combo_box_set_active(GTK_COMBO_BOX(preamplifier_gain_combobox),domyslne_wartosci[0]-48);
  gtk_combo_box_set_active(GTK_COMBO_BOX(preamplifier_time_constant_combobox),domyslne_wartosci[1]-48);
  gtk_combo_box_set_active(GTK_COMBO_BOX(rp_combobox),domyslne_wartosci[2]-48);
  gtk_combo_box_set_active(GTK_COMBO_BOX(cp_combobox),domyslne_wartosci[3]-48);
  gtk_combo_box_set_active(GTK_COMBO_BOX(tp_combobox),domyslne_wartosci[4]-48); 
  gtk_combo_box_set_active(GTK_COMBO_BOX(tcmode_combobox),domyslne_wartosci[5]-48);
  gtk_combo_box_set_active(GTK_COMBO_BOX(rt1_combobox),domyslne_wartosci[6]-48);
  gtk_combo_box_set_active(GTK_COMBO_BOX(ct1_combobox),domyslne_wartosci[7]-48);
  gtk_combo_box_set_active(GTK_COMBO_BOX(rt2_combobox),domyslne_wartosci[8]-48);
  gtk_combo_box_set_active(GTK_COMBO_BOX(ct2_combobox),domyslne_wartosci[9]-48);
  gtk_combo_box_set_active(GTK_COMBO_BOX(blh_combobox),domyslne_wartosci[10]-48);
}


