#ifndef master_H
#define master_H

#include <pebble.h>

double weight;
int sets;
// Metric vs Imperial
int unit_system;
char *unit_type;
extern double step_size[2];
extern double plate_weights[8][2];
extern int plate_numbers[8][2];
extern int barbell[2];

#endif