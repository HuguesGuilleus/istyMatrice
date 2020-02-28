// 2020 GUILLEUS Hugues IATIC3 <hugues.guilleus@ens.uvsq.fr>

#ifndef MATRIX
#define MATRIX

#include "tab2d.h"

// Une matrice.
typedef struct {
	float **t;
	int w;
	int h;
} t_matrix;

t_matrix *matrix_new(int w, int h);
void matrix_free(t_matrix *m);
bool matrix_printToFileName(t_matrix *m, char *fileName);
void matrix_print(t_matrix *m, FILE *file);
t_matrix *matrix_scan(FILE *file);
t_matrix *matrix_scanFromFile(char *fileName);
t_matrix *matrix_mult(t_matrix *m1, t_matrix *m2);
bool matrix_multCheck(t_matrix *m1, t_matrix *m2);

#endif
