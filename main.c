// 2020 GUILLEUS Hugues IATIC3 <hugues.guilleus@ens.uvsq.fr>

#include "main.h"
#include "flag.h"

#define VERSION "dev0.1"

int main(int argc, char const *argv[]) {
	bool verbose = FALSE;
	const char *output = "out.txt";
	t_matrix *m1 = NULL;
	t_matrix *m2 = NULL;
	t_matrix *res = NULL;
	char *m1File = "mat1.txt";
	char *m2File = "mat2.txt";

	flag_bool(&verbose, "v", "Verbose mode");
	flag_str(&output, "o", "Fichier de sortie");
	flag_parse(argc, argv, VERSION);

	TRACE("Matrice 1 ...");
	m1 = matrix_scanFromFile(m1File);
	if (m1 == NULL) {
		fprintf(stderr, "Erreur dans la lecture de la matrice 1\n");
		return 1;
	}
	if (verbose) {
		matrix_print(m1, stdout);
	}

	TRACE("Matrice 2 ...");
	m2 = matrix_scanFromFile(m2File);
	if (m2 == NULL) {
		fprintf(stderr, "Erreur dans la lecture de la matrice 2\n");
		return 1;
	}
	if (verbose) {
		matrix_print(m2, stdout);
	}

	TRACE("Multiplication ...");
	if (!matrix_multCheck(m1, m2)) {
		fprintf(stderr, "Les matrices ne peuvent pas être multiplié ensemble\n");
		return 2;
	}
	res = matrix_mult(m1, m2);
	matrix_free(m1);
	matrix_free(m2);
	if (verbose) {
		matrix_print(res, stdout);
	}

	TRACE("Fichier de sortie");
	if (matrix_printToFileName(res, output)) {
		fprintf(stderr, "Erreur lors de l'écriture du fichier de sortie\n");
		return 1;
	}
	matrix_free(res);

	return 0;

	// TRACE("matrice 1 :::");
	// m1 = matrix_scan();
	// TRACE("matrice 2 :::");
	// m2 = matrix_scan();
	//
	// TRACE("Affichage ...");
	//
	// matrix_print(matrix_Mult(m1, m2));
	//
	// TRACE("Fin affichage");
	//
	// return 0;
}
