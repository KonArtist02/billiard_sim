#ifndef _VERLET
#define _VERLET
#include "particle.h"

extern void update_positions(particle *const p,const int nmax, const double dt);
extern void update_velocities(particle *const p, const int nmax, const double dt);
extern void calc_force_verlet(particle *Kugel, int ntot, double radius, double length_x, double height_y);

#endif
