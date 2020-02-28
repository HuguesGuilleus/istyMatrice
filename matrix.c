// 2020 GUILLEUS Hugues IATIC3 <hugues.guilleus@ens.uvsq.fr>

#include "matrix.h"

/* MÉMOIRE */

// Alloue une nouvelle matrice qui sera renvoyé.
t_matrix *matrix_new(int w, int h) {
	t_matrix *m = NULL;
	if (w < 1 || h < 1) {
		TRACE("matrix_alloc() need strict positive width and height");
		return NULL;
	}

	m = (t_matrix *)malloc(sizeof(t_matrix));

	*m = (t_matrix){
		t : tab2d_new(w, h),
		w : w,
		h : h,
	};

	return m;
}

void matrix_free(t_matrix *m) {
	if (m == NULL) {
		return;
	}

	if (m->t != NULL) {
		tab2d_free(m->t, m->w);
	}

	free(m);
}

/* AFFICHAGE */

void matrix_print(t_matrix *m) {
	if (m == NULL || m->w <= 0 || m->h <= 0) {
		printf("(t_matrix) emty\n");
		return;
	}

	printf("(t_matrix) %dx%d\n", m->w, m->h);
	tab2d_print(m->t, m->w, m->h);
}

/* SAISIT */

t_matrix *matrix_scan(void) {
	t_matrix *m;

	m = (t_matrix *)malloc(sizeof(t_matrix));
	tab2d_scan(&m->t, &m->w, &m->h, stdin);

	return m;
}

/* OPÉRATION */

t_matrix *matrix_Mult(t_matrix *m1, t_matrix *m2) {
	t_matrix *res = NULL;
	int x, y, i;

	if (m1 == NULL || m2 == NULL) {
		return NULL;
	}

	if (!matrix_multCheck(m1, m2)) {
		printf("MAUVAIS DIMENSION\n");
		return NULL;
	}

	res = matrix_new(m2->w, m1->h);
	for (x = 0; x < m2->w; x++) {
		for (y = 0; y < m1->h; y++) {
			for (i = 0; i < m1->w; i++) {
				res->t[x][y] += m1->t[i][y] * m2->t[x][i];
			}
		}
	}

	return res;
}

// Renvoie vrai si deux matrice peuvent être multiplié.
bool matrix_multCheck(t_matrix *m1, t_matrix *m2) {
	if (m1 == NULL || m2 == NULL) {
		TRACE("matrix_multCheck() have NULL matrix ptr.");
		return;
	}

	return m1->w == m2->h;
}
