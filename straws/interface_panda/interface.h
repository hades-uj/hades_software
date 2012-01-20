#ifndef _interface_h_
#define _interface_h_

#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>



  GtkWidget *preamplifier_gain_combobox;
  GtkWidget *preamplifier_time_constant_combobox;
  GtkWidget *rp_combobox;
  GtkWidget *cp_combobox;
  GtkWidget *tp_combobox;
  GtkWidget *tcmode_combobox;
  GtkWidget *rt1_combobox;
  GtkWidget *ct1_combobox;
  GtkWidget *rt2_combobox;
  GtkWidget *ct2_combobox;
  GtkWidget *blh_combobox;
  std:: string nazwa_programu;
  std::string domyslne_wartosci;
  std::string zapamietane_wartosci;
  std::string cmd;
  std::string cmd1;

#endif
