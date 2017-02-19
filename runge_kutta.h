#ifndef _RUNGE_KUTTA
#define _RUNGE_KUTTA
#include "particle.h"

extern void runge_kutta_step(particle *Kugel, int ntot, double dt);
extern void calc_force_runge_kutta(particle *Kugel,int ntot, double radius, double length_x, double height_y);

#endif
