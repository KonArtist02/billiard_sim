#ifndef _PARTICLE
#define _PARTICLE

const int dim=2;
struct particle{
    double pos[dim];
    double vel[dim];
    double f[dim];
    double fold[dim]; // für Verlet Verfahren
    double m;
};
#endif
