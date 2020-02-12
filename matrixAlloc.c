// 2020 GUILLEUS Hugues IATIC3 <hugues.guilleus@ens.uvsq.fr>

#include "matrixAlloc.h"

/* MÉMOIRE DES MATRICES */

// Créé une nouvelle matrix et règle les valeurs à zéro.
matrix *matrix_new(int w, int h) {
	int i, j;
	matrix *m = NULL;

	if (w == 0 || h == 0) {
		return NULL;
	}

	m = (matrix *)malloc(sizeof(matrix));
	*m = (matrix){
		w : w,
		h : h,
		tab : (float **)malloc(sizeof(float *) * w),
	};
	for (i = 0; i < w; i++) {
		m->tab[i] = (float *)malloc(sizeof(float) * h);
		for (j = 0; j < h; j++) {
			m->tab[i][j] = 0.0;
		}
	}
	return m;
}

void matrix_alloc(int w, int h, matrix *m) {
	matrix *mm = matrix_new(w, h);
	*m = *mm;
	free(mm);
}

// Désaloue le contenue de la matrice mais pas la structure matrice.
void matrix_free(matrix *m) {
	int w;
	if (m == NULL) {
		return;
	}
	for (w = 0; w < m->w; w++) {
		free(m->tab[w]);
	}
	free(m->tab);
	*m = (matrix){};
}

/* PRINT ET EXPORT */

// Affiche dans la console la matrice.
void matrix_print(matrix *m) { matrix_fprint(stdin, m); }

void matrix_fprint(FILE *file, matrix *m) {
	int w, h;
	if (m == NULL || m->tab == NULL) {
		printf("matrice vide\n");
		return;
	}
	for (h = 0; h < m->h; h++) {
		for (w = 0; w < m->w; w++) {
			printf("%3.3f ", m->tab[w][h]);
		}
		printf("\n");
	}
}

/* SAISIT */

// Saisit une matrice depuis le fichier in. Si le fichier est NULL, alors la
// fonction renvoie un tableau vide.
matrix *matrix_fscan(FILE *in) {
	matrix *m = NULL;
	int w, h;
	int maxW, maxH;
	char _;

	if (in == NULL)
		return NULL;

	if (fscanf(in, "%d%c%d", &maxW, &_, &maxH) != 3)
		return NULL;
	m = matrix_new(maxW, maxH);

	for (h = 0; h < maxH; h++) {
		for (w = 0; w < maxW; w++) {
			if (fscanf(in, " %f", &(m->tab[w][h])) != 1) {
				return m;
			}
		}
	}
	return m;
}

// Saisit une matrice depuis l'entré standard.
matrix *matrix_scan(void) {
	matrix *m = NULL;
	while ((m = matrix_fscan(stdin)) == NULL) {
		printf("Saisit invalide\n");
	}
	return m;
}
