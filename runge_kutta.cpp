#include <cmath>
#include <cstdlib> 
#include <iostream>
#include "runge_kutta.h"
#include "particle.h"


void runge_kutta_step(particle *Kugel, int ntot, double dt){
  

  double D = 0.5;
  
  double k_1 = 0;
  double j_1 = 0;
  double k_2 = 0;
  double j_2 = 0;
  double k_3 = 0;
  double j_3 = 0;
  double k_4 = 0;
  double j_4 = 0;
  
  for(int i=0; i<ntot; i++){
    for(int j=0; j<dim; j++){
	k_1 = Kugel[i].vel[j];
	j_1 = -D/Kugel[i].m * Kugel[i].vel[j] + Kugel[i].f[j]/Kugel[i].m;
	k_2 = Kugel[i].vel[j] + dt/2 * j_1;
	j_2 = -D/Kugel[i].m * (Kugel[i].vel[j] + dt/2 * j_1) + Kugel[i].f[j]/Kugel[i].m;
	k_3 = Kugel[i].vel[j] + dt/2 * j_2;
	j_3 = -D/Kugel[i].m * (Kugel[i].vel[j] + dt/2 * j_2) + Kugel[i].f[j]/Kugel[i].m;
	k_4 = Kugel[i].vel[j] + dt * j_3;
	j_4 = -D/Kugel[i].m * (Kugel[i].vel[j] + dt * j_3) + Kugel[i].f[j]/Kugel[i].m;
	
	Kugel[i].pos[j] += dt/6 * (k_1 + 2*k_2 + 2*k_3 + k_4);
	Kugel[i].vel[j] += dt/6 * (j_1 + 2*j_2 + 2*j_3 + j_4);
    } 
  } 
}  


void calc_force_runge_kutta(particle *Kugel, int ntot, double radius, double length_x, double height_y){
  
  double r_0 = 0;
  double r_1 = 0;
  double Abstand = 0;
  const double c = 12;
  double F_Kugeln = 0;
  
  for(int i=0;i<ntot;i++){
      Kugel[i].f[0] = 0;
      Kugel[i].f[1] = 0;
  }
  
  // Abstoßung zwischen den Kugeln
  
  for(int i=0;i<ntot-1;i++){
      for(int j=i+1; j<ntot;j++){
	  r_0 = Kugel[i].pos[0]-Kugel[j].pos[0];
	  r_1 = Kugel[i].pos[1]-Kugel[j].pos[1];
	  Abstand = sqrt(r_0*r_0 + r_1*r_1);
	  F_Kugeln = c*pow(2*radius/Abstand, 13);
	  
	 if(r_0*r_0+r_1*r_1 < radius*radius*4 ){
	    Kugel[i].f[0] += F_Kugeln*r_0/Abstand;
	    Kugel[i].f[1] += F_Kugeln*r_1/Abstand;
	    Kugel[j].f[0] -= F_Kugeln*r_0/Abstand;
	    Kugel[j].f[1] -= F_Kugeln*r_1/Abstand;
	    //cout << Kugel[i].f[0] <<" "<< Kugel[i].f[1] <<" "<< Kugel[j].f[0] <<" "<< Kugel[j].f[1] << endl;
	    //cout << Kugel[i].pos[0] <<" "<< Kugel[i].pos[1] <<" "<< Kugel[j].f[0] <<" "<< Kugel[j].f[1] << endl;
	 }
      }
  }
  
  // Abstoßung durch den Rand
  
  r_0 = 0;
  r_1 = 0;
  
  for(int i=0;i<ntot;i++){
      if(Kugel[i].pos[0] <=0 || Kugel[i].pos[1] <=0 ){
	  std::cout << "Kugel außerhalb der Grenzen - Beende Programm" << std::endl;
	  exit(EXIT_FAILURE);
      }
    
      if(Kugel[i].pos[0] < radius){
	  r_0 = Kugel[i].pos[0] - 0;
	  Kugel[i].f[0] += c*pow(2*radius/(r_0+radius), 13);
      }
      
      if(Kugel[i].pos[1] < radius){
	  r_1 = Kugel[i].pos[1] - 0;
	  Kugel[i].f[1] += c*pow(2*radius/(r_1+radius), 13);
      }
    
      if(Kugel[i].pos[0] > length_x - radius){
	  r_0 = length_x - Kugel[i].pos[0];
	  Kugel[i].f[0] -= c*pow(2*radius/(r_0+radius), 13);
      }
      
      if(Kugel[i].pos[1] > height_y - radius){
	  r_0 = height_y - Kugel[i].pos[1];
	  Kugel[i].f[1] -= c*pow(2*radius/(r_0+radius), 13);
      }
  }
}