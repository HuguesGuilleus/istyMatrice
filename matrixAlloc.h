// 2020 GUILLEUS Hugues IATIC3 <hugues.guilleus@ens.uvsq.fr>

#ifndef MATRIC_ALLOC_H
#define MATRIC_ALLOC_H 1

#include <stdio.h>
#include <stdlib.h>

// Une matrice
typedef struct {
	float **tab;
	int w;
	int h;
} matrix;

matrix *matrix_new(int w, int h);
void matrix_alloc(int w, int h, matrix *m);
void matrix_free(matrix *m);
void matrix_fprint(FILE* file, matrix*m);
void matrix_print(matrix *m);

#endif
