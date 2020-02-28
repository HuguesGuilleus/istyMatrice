// 2020 GUILLEUS Hugues IATIC3 <hugues.guilleus@ens.uvsq.fr>

#include "matrix.h"

/* MÉMOIRE */

// Alloue une nouvelle matrice qui sera renvoyée.
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

// Affiche la matrice dans un fichier. En cas d'erreur la fonction renvera TRUE.
bool matrix_printToFileName(t_matrix *m, char *fileName) {
	FILE *file = NULL;

	if (fileName == NULL) {
		TRACE("matrix_printToFileName() fileName is empty");
		return TRUE;
	}

	file = fopen(fileName, "w");
	if (file == NULL) {
		return TRUE;
	}
	matrix_print(m, file);
	fclose(file);

	return FALSE;
}

void matrix_print(t_matrix *m, FILE *file) {
	if (file == NULL) {
		TRACE("matrix_print() file is null.");
		return;
	}

	if (m == NULL || m->t == NULL || m->w <= 0 || m->h <= 0) {
		fprintf(file, "(t_matrix) empty\n");
		return;
	}

	fprintf(file, "(t_matrix) %dx%d\n", m->w, m->h);
	tab2d_printFile(m->t, m->w, m->h, file);
}

/* SAISIT */

t_matrix *matrix_scanFromFile(char *fileName) {
	FILE *file = NULL;
	t_matrix *m = NULL;

	if (fileName == NULL) {
		TRACE("matrix_scanFromFile() fileName is NULL");
		return NULL;
	}

	file = fopen(fileName, "r");
	if (file == NULL) {
		return NULL;
	}

	m = matrix_scan(file);

	fclose(file);

	return m;
}

t_matrix *matrix_scan(FILE *file) {
	t_matrix *m;

	if (file == NULL) {
		TRACE("matrix_scan() need a non empty file.");
		return NULL;
	}

	m = (t_matrix *)malloc(sizeof(t_matrix));
	*m = (t_matrix){};
	if (tab2d_scan(&m->t, &m->w, &m->h, file)) {
		free(m);
		return NULL;
	}

	return m;
}

/* OPÉRATION */

t_matrix *matrix_mult(t_matrix *m1, t_matrix *m2) {
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
