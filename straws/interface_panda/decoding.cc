#include <iostream>
#include <cstdlib>
#include <string>



using namespace std;


int main(int argc, char** argv)
{

if(argc < 2)
  {
   cout<< "Usage: decoding binary_string\n";
   return 0;
  }

string input(argv[1]);
cout<<input<<endl;




string pre_amp_gain =  input.substr(0,2) ;
string pre_amp_time_const =  input.substr(2,2) ;
string rp=  input.substr(4,2) ;
string cp=  input.substr(6,2) ;
string tp=  input.substr(8,2) ;
string tail_cancel=  input.substr(10,2) ;
string rt1=  input.substr(12,3) ;
string rt2=  input.substr(15,3) ;
string ct1=  input.substr(18,3) ;
string ct2=  input.substr(21,3) ;
string blh=  input.substr(24,1) ;

/*
cout<<pre_amp_gain<<endl;
cout<<pre_amp_time_const <<endl;
cout<<rp <<endl;
cout<<cp <<endl;
cout<<tp <<endl;
cout<<tail_cancel <<endl;
cout<<rt1 <<endl;
cout<<rt2 <<endl;
cout<<ct1 <<endl;
cout<<ct2 <<endl;
cout<<blh <<endl;
*/

/*pre_amp_gain*/
cout<<"Preamplifier gain = ";
if(pre_amp_gain.compare("00") == 0)
	cout<<"4"<<endl;
else if (pre_amp_gain.compare("01") == 0)
	cout<<"1"<<endl;
else if ((pre_amp_gain.compare("10") == 0))
	cout<<"2"<<endl;
else if ((pre_amp_gain.compare("11") == 0))
        cout<<"0.5"<<endl;

/*pre_amp_time_const*/
cout<<"Preamplifier time constant = ";
if(pre_amp_time_const.compare("00") == 0)
	cout<<"400"<<endl;
else if (pre_amp_time_const.compare("01") == 0)
	cout<<"300"<<endl;
else if ((pre_amp_time_const.compare("10") == 0))
	cout<<"200"<<endl;
else if ((pre_amp_time_const.compare("11") == 0))
        cout<<"100"<<endl;

/*rp*/
cout<<"rp = ";
if(rp.compare("00") == 0)
	cout<<"5"<<endl;
else if (rp.compare("01") == 0)
	cout<<"10"<<endl;
else if ((rp.compare("10") == 0))
	cout<<"20"<<endl;
else if ((rp.compare("11") == 0))
        cout<<"40"<<endl;

/*cp*/
cout<<"cp = ";
if(cp.compare("00") == 0)
        cout<<"5"<<endl;
else if (cp.compare("01") == 0)
        cout<<"7.5"<<endl;
else if ((cp.compare("10") == 0))
        cout<<"10"<<endl;
else if ((cp.compare("11") == 0))
        cout<<"20"<<endl;

/*tp*/
cout<<"tp = ";
if(tp.compare("00") == 0)
        cout<<"00"<<endl;
else if (tp.compare("01") == 0)
        cout<<"01"<<endl;
else if ((tp.compare("10") == 0))
        cout<<"10"<<endl;
else if ((tp.compare("11") == 0))
        cout<<"11"<<endl;

/*tail cancel*/
cout<<"Tail cancellation  ";
if(tail_cancel.compare("00") == 0)
        cout<<"CR_RC"<<endl;
else if (tail_cancel.compare("01") == 0)
        cout<<"TC_1_on,TC_2_off"<<endl;
else if ((tail_cancel.compare("10") == 0))
        cout<<"TC_1_off,TC_2_on"<<endl;
else if ((tail_cancel.compare("11") == 0))
        cout<<"TC_on"<<endl;

/*rt1*/
cout<<"rt1 = ";
if(rt1.compare("000") == 0)
	cout<<"3"<<endl;
else if(rt1.compare("001") == 0)
	cout<<"7"<<endl;
else if(rt1.compare("010") == 0)
        cout<<"11"<<endl;
else if(rt1.compare("101") == 0)
        cout<<"23"<<endl;
else if(rt1.compare("011") == 0)
        cout<<"15"<<endl;
else if(rt1.compare("100") == 0)
        cout<<"19"<<endl;
else if(rt1.compare("110") == 0)
        cout<<"27"<<endl;
else if(rt1.compare("111") == 0)
        cout<<"31"<<endl;


/*ct1*/
cout<<"ct1 = ";
if(ct1.compare("000") == 0)
        cout<<"6"<<endl;
else if(ct1.compare("001") == 0)
        cout<<"7.5"<<endl;
else if(ct1.compare("010") == 0)
        cout<<"9"<<endl;
else if(ct1.compare("101") == 0)
        cout<<"13.5"<<endl;
else if(ct1.compare("011") == 0)
        cout<<"10.5"<<endl;
else if(ct1.compare("100") == 0)
        cout<<"12"<<endl;
else if(ct1.compare("110") == 0)
        cout<<"15"<<endl;
else if(ct1.compare("111") == 0)
        cout<<"16.5"<<endl;

/*rt2*/
cout<<"rt2 = ";
if(rt2.compare("000") == 0)
        cout<<"5"<<endl;
else if(rt2.compare("001") == 0)
        cout<<"8"<<endl;
else if(rt2.compare("010") == 0)
        cout<<"11"<<endl;
else if(rt2.compare("101") == 0)
        cout<<"20"<<endl;
else if(rt2.compare("011") == 0)
        cout<<"14"<<endl;
else if(rt2.compare("100") == 0)
        cout<<"17"<<endl;
else if(rt2.compare("110") == 0)
        cout<<"23"<<endl;
else if(rt2.compare("111") == 0)
        cout<<"26"<<endl;
/*ct2*/
cout<<"ct2 = ";
if(ct2.compare("000") == 0)
        cout<<"0.6"<<endl;
else if(ct2.compare("001") == 0)
        cout<<"0.75"<<endl;
else if(ct2.compare("010") == 0)
        cout<<"0.9"<<endl;
else if(ct2.compare("101") == 0)
        cout<<"1.35"<<endl;
else if(ct2.compare("011") == 0)
        cout<<"1.05"<<endl;
else if(ct2.compare("100") == 0)
        cout<<"1.2"<<endl;
else if(ct2.compare("110") == 0)
        cout<<"1.5"<<endl;
else if(ct2.compare("111") == 0)
        cout<<"1.65"<<endl;

/*blh*/
cout<<"BLH: ";
if(blh.compare("1") == 0)
	cout<<"on"<<endl;
else 
 	cout<<"off"<<endl;









return 0;
}
