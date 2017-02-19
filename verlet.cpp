#include <cmath>
#include <iostream>
#include <cstdlib>
#include "particle.h"
#include "verlet.h"

//VERLET::

void update_positions(particle *const p,const int nmax, const double dt){
  double a;
  for(int i=0;i<nmax;i++){
    a= 0.5*dt/p[i].m;
    for(int n = 0; n<dim; n++){
      p[i].pos[n] += dt * (p[i].vel[n]+ a*p[i].f[n]);
      p[i].fold[n] = p[i].f[n];
    }
  }
}

void update_velocities(particle *const p, const int nmax, const double dt){
  double a;
  for(int i=0;i<nmax;i++){
    a= 0.5*dt/p[i].m;
    for(int n=0;n<dim;n++)
      p[i].vel[n] += a * (p[i].f[n]+p[i].fold[n]);
  }
}

void calc_force_verlet(particle *Kugel, int ntot, double radius, double length_x, double height_y){
    
  double r_0 = 0;
  double r_1 = 0;
  double Abstand = 0;
  const double c = 12;
  double F_Kugeln = 0;
  
  double D = 0.5;
  
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
  
  // Reibungskraft
  for(int i=0; i<ntot; i++){
    Kugel[i].f[0] -= D*Kugel[i].vel[0];
  }
  
  for(int i=0; i<ntot; i++){
    Kugel[i].f[1] -= D*Kugel[i].vel[1];
  }

}