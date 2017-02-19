// Seite 287 Aufgabenstellung

// nächste Schritte :Nachbarschaftslisten


#include <iostream>
#include <cstring>
#include <fstream>
#include <cmath>
#include "gnuplot.h"
#include "particle.h"
#include "verlet.h"
#include "runge_kutta.h"


using namespace std;


particle *Kugel;
int ntot;
double radius;
double length_x;
double height_y;

void init_struct(string dateiname); // liest Anfangsbedingung aus der Startdatei und erzeugt ein Feld für alle Kugeln
void init_force(particle *const p, const int nmax); // setzt alle Kräfte auf null
void save_result(particle *Kugel, int iteration, int ntot, int int_verfahren); // speichert die momentane Position als .dat ab
void plot_xy(Gnuplot &gpl, int timesteps, int int_verfahren);

int main(){
  
  
  // Initialisierung der Startkonfiguration
    string dateiname;
    double dt = 0;
    int timesteps = 0;
    double time = 0;
    
    
    dateiname = "start.dat";
    cout << endl;
    cout << "Startposition der Billardkugeln in der Datei: " << dateiname  << endl;
    
    cout << "Länge eines Zeitschritts: ";
    cin >> dt;
    cout << "Anzahl der Zeitschritte: ";
    cin >> timesteps;
    
    
    // Integrationsverfahren
   
    int int_verfahren;
    
    cout << "Wahl des Integrationsverfahrens" << endl;
    cout << "1: Störmer-Verlet" << endl;
    cout << "2: Runge Kutta 4. Ordung" << endl;
    cout << "3: Beide" << endl;
    cin >> int_verfahren;
    
    
    init_struct(dateiname);
    init_force(Kugel,ntot); 

    // Verlet_Störmer
    if((int_verfahren == 1) || (int_verfahren == 3)){ 
    
      for(int i=0; i<timesteps; i++){
	time += dt;
	update_positions(Kugel,ntot,dt);
	calc_force_verlet(Kugel, ntot, radius,length_x, height_y);
	update_velocities(Kugel,ntot,dt);
	save_result(Kugel,i,ntot,1);
      }
      ofstream ausgabedatei("Ergebnis_Verlet_Störmer.dat");
      for(unsigned int i=0; i<ntot; i++){
	ausgabedatei << Kugel[i].pos[0] << " " << Kugel[i].pos[1] << endl;
      }
      ausgabedatei.close();
    }
    
    delete Kugel;
    init_struct(dateiname);
    init_force(Kugel,ntot);
    
    // Runge_Kutta
    time = 0;
    if((int_verfahren == 2) || (int_verfahren == 3)){
      
      for(int i=0; i<timesteps; i++){
	time += dt;
	calc_force_runge_kutta(Kugel,ntot,radius,length_x, height_y);
	runge_kutta_step(Kugel,ntot,dt);
	save_result(Kugel,i,ntot,2);
      }
      ofstream ausgabedatei("Ergebnis_Runge_Kutta.dat");
	for(unsigned int i=0; i<ntot; i++){
	  ausgabedatei << Kugel[i].pos[0] << " " << Kugel[i].pos[1] << endl;
	}
      ausgabedatei.close();
    }
    
    
    // Plot
    
    Gnuplot gpl;
    int auswahl_1;
    
    cout << "Möchtens Sie das Ergebnis plotten?" <<  endl;
    cout << "1: Ja" << endl;
    cout << "2: Nein" << endl;
    cin >> auswahl_1;
    
    if(auswahl_1 == 1){
	if((int_verfahren == 1) || (int_verfahren == 2)){
	    plot_xy(gpl,timesteps,int_verfahren);
	}
	if(int_verfahren == 3){
	    int auswahl_2;
	    cout << "Welches Verfahren möchten Sie plotten?" << endl;
	    cout << "1: Verlet-Strörmer" << endl;
	    cout << "2: Runge-Kutta" << endl;
	    cin >> auswahl_2;
		plot_xy(gpl,timesteps,auswahl_2);
	}
    }
    
}



void init_struct(string dateiname){
  
  ifstream startdat;
  startdat.open(dateiname.c_str());
  
  if(startdat){
      startdat >> ntot;
      Kugel = new particle[ntot];
      startdat >> radius;
      startdat >> length_x;
      startdat >> height_y;
      for(unsigned int i=0; i<ntot; i++)
	  startdat >> Kugel[i].m >>Kugel[i].pos[0] >> Kugel[i].pos[1] >> Kugel[i].vel[0] >> Kugel[i].vel[1];
      startdat.close();
  }
  else {cout << "Datei nicht gefunden" << endl;} 
}


void init_force(particle *const p, const int nmax){
  // setze alle Kräfte auf Null:
  for(int i=0;i<nmax;i++)
    for(int n=0;n<dim;n++)
      p[i].f[n]=0.;
}


void save_result(particle *Kugel, int iteration, int ntot, int int_verfahren){
  
  char dateiname[50];
  if(int_verfahren == 1){
      sprintf(dateiname, "Verlet_Pos_%d.dat", iteration);
      
      ofstream ausgabedatei_1;  
      ausgabedatei_1.open(dateiname);
      for(unsigned int i=0; i<ntot; i++){
	  ausgabedatei_1 << Kugel[i].pos[0] << " " << Kugel[i].pos[1] << endl;
      }
      ausgabedatei_1.close();
  }
  
  
  if(int_verfahren == 2){
      sprintf(dateiname, "RK_Pos_%d.dat", iteration);
  
      ofstream ausgabedatei_2;  
      ausgabedatei_2.open(dateiname);
      for(unsigned int i=0; i<ntot; i++){
	  ausgabedatei_2 << Kugel[i].pos[0] << " " << Kugel[i].pos[1] << endl;
      }
      ausgabedatei_2.close();
  }
}  
  
void plot_xy(Gnuplot &gpl, int timesteps, int int_verfahren){
  
  char dateiname[50];
  gpl.set_xrange(0,length_x);
  gpl.set_yrange(0,height_y);
  gpl.set_pointsize(20*radius);
  
  for(int i=0; i<timesteps; i++){
      gpl.reset_plot();
      gpl.remove_tmpfiles();
      if(int_verfahren == 1){
	  sprintf(dateiname, "Verlet_Pos_%d.dat", i);
      }
      if(int_verfahren == 2){
	  sprintf(dateiname, "RK_Pos_%d.dat", i);
      }
      gpl.plotfile_xy(dateiname,1,2,"");
      getchar();
  } 
}