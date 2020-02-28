// 2020 GUILLEUS Hugues IATIC3 <hugues.guilleus@ens.uvsq.fr>

#ifndef TAB2D_H
#define TAB2D_H 1

#include <stdio.h>
#include <stdlib.h>

#include "tools.h"

float **tab2d_new(int width, int height);
void tab2d_load(float ***tab, int width, int height);
void tab2d_free(float **tab, int width);
void tab2d_printFile(float **tab, int width, int height, FILE *file);
void tab2d_print(float **tab, int width, int height);
bool tab2d_scan(float ***tab, int *w, int *h, FILE *file);
bool tab2d_scanInfo(int *w, int *h, FILE *file);

#endif
