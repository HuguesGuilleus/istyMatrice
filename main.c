// 2020 GUILLEUS Hugues IATIC3 <hugues.guilleus@ens.uvsq.fr>

#include "main.h"

int main(int argc, char const *argv[]) {
	t_matrix *m1 = NULL, *m2 = NULL;

	TRACE("matrice 1 :::");
	m1 = matrix_scan();
	TRACE("matrice 2 :::");
	m2 = matrix_scan();

	TRACE("Affichage ...");

	matrix_print(matrix_Mult(m1, m2));

	TRACE("Fin affichage");

	return 0;
}
