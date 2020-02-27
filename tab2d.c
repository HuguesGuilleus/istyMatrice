// 2020 GUILLEUS Hugues IATIC3 <hugues.guilleus@ens.uvsq.fr>

#include "tab2d.h"

/* GESTION DE LA MÉMOIRE */

// Alloue un tableau 2d, les valeurs sont initilalisées à 0.
float **tab2d_new(int width, int height) {
	float **tab = NULL;
	int x, y;

	if (width < 1 || height < 1) {
		TRACE("tab2d_new() width or heigth have not strict positive values.");
		return NULL;
	}

	tab = (float **)malloc(width * sizeof(float *));
	for (x = 0; x < width; x++) {
		tab[x] = (float *)malloc(height * sizeof(float *));
		for (y = 0; y < height; y++) {
			tab[x][y] = 0.0;
		}
	}
	return tab;
}

// Alloue un tableau 2d, les valeurs sont initilalisées à 0.
void tab2d_load(float ***tab, int width, int height) {
	if (tab == NULL) {
		TRACE("tab2d_load() must have a non NULL pointer.");
		return;
	}
	*tab = tab2d_new(width, height);
}

// Désaloue un tableau.
void tab2d_free(float **tab, int width) {
	int x;

	if (width < 1) {
		TRACE("tab2d_free() width is not strict positif.");
		return;
	}

	if (tab == NULL) {
		return;
	}

	for (x = 0; x < width; x++) {
		free(tab[x]);
	}
	free(tab);
}

/* AFFICHAGE ET SAISIT */

// Affiche le tableau dans la console.
void tab2d_print(float **tab, int width, int height) {
	int x, y;

	if (width < 0 || height < 0) {
		printf("(float[]) ???\n");
		return;
	}

	if (tab == NULL || width == 0 || height == 0) {
		printf("(float[]) null\n");
		return;
	}

	for (y = 0; y < height; y++) {
		for (x = 0; x < width; x++) {
			printf("%15.5f ", tab[x][y]);
		}
		printf("\n");
	}
}

// Saisit la taille et les coeficients d'un tableau. Renvoie TRUE en cas
// d'erreur.
//
// Si le tableau est vide, il sera désaloué mais alors w doit correspondre à
// la précédente valeur.
//
// Si file est le flux d'entré standard, alors des instructions seront données
// à l'utlisateur.
bool tab2d_scan(float ***tab, int *w, int *h, FILE *file) {
	int x, y;

	if (tab == NULL || w == NULL || h == NULL || file == NULL) {
		TRACE("tab2d_scan() tab, file, w or h are NULL.");
		return TRUE;
	}

	if (tab2d_scanInfo(w, h, file)) {
		return TRUE;
	}

	if (*tab != NULL) {
		tab2d_free(*tab, *w);
		*tab = NULL;
	}
	*tab = tab2d_new(*w, *h);

	for (y = 0; y < *h; y++) {
		for (x = 0; x < *w; x++) {
			if (file == stdin) {
				printf("tab[%d][%d]: ", x + 1, y + 1);
				while (scanf(" %f", &((*tab)[x][y])) != 1) {
					clearStdin();
					printf("Mauvaise rentrée\n");
					printf("tab[%d][%d]: ", x + 1, y + 1);
				}
			} else if (fscanf(file, " %f", &((*tab)[x][y])) != 1) {
				return TRUE;
			}
		}
	}

	return FALSE;
}

// Récupère la largeur et la hauteur depuis un stream (ex: stdin)
// Si la saisit s'est bien passé, les valeur de w et h seront strictement
// positives; en cas d'erreur, les valeurs seront nulle.
//
// Si file est stdin, des instruction pour l'utilisateur seront données et
// en cas d'erreur une nouvelle valeur est demandé à l'utilisateur.
//
// Si file un fichier quelconque, alors aucune instruction ne sera affichée. Si
// une erreur survient lors de la saisit, la fonction se termine.
//
// Si les valeurs saisis sont négatives ou nulles une nouvelle saisi des deux
// valeurs est effectuée.
bool tab2d_scanInfo(int *w, int *h, FILE *file) {
	if (file == NULL) {
		TRACE("tab2d_scanInfo() need a non NULL file");
		*w = *h = 0;
		return TRUE;
	}

	do {
		if (file == stdin) {
			printf("width (>0): ");
			while (scanf(" %d", w) != 1) {
				clearStdin();
				printf("Wrong value\n");
				printf("width (>0): ");
			}
			printf("height (>0): ");
			while (scanf(" %d", h) != 1) {
				clearStdin();
				printf("Wrong value\n");
				printf("height (>0): ");
			}
		} else {
			if (fscanf(file, " %d", w) != 1) {
				*w = *h = 0;
				return TRUE;
			}
			if (fscanf(file, " %d", h) != 1) {
				*w = *h = 0;
				return TRUE;
			}
		}
	} while (*w < 1 || *h < 1);

	if (file == stdin) {
		printf("\n");
	}

	return FALSE;
}
