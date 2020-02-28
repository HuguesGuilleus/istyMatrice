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
void matrix_print(t_matrix *m);
t_matrix *matrix_scan(void);
t_matrix *matrix_Mult(t_matrix *m1, t_matrix *m2);
bool matrix_multCheck(t_matrix *m1, t_matrix *m2);

#endif
