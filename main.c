// 2020 GUILLEUS Hugues IATIC3 <hugues.guilleus@ens.uvsq.fr>

#include "main.h"

int main(int argc, char const *argv[]) {
	matrix m;

	matrix_alloc(20, 10, &m);
	matrix_print(&m);
	matrix_free(&m);

	return 0;
}
