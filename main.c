// 2020 GUILLEUS Hugues IATIC3 <hugues.guilleus@ens.uvsq.fr>

#include "main.h"

int main(int argc, char const *argv[]) {
	matrix *m = matrix_scan();
	printf("\n");
	matrix_print(m);
	matrix_free(m);
	free(m);
	m = NULL;

	return 0;
}
