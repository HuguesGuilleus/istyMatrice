// 2020 GUILLEUS Hugues IATIC3 <hugues.guilleus@ens.uvsq.fr>

#include "main.h"

int main(int argc, char const *argv[]) {
	float **tab = NULL;
	int w, h;

	bool e = tab2d_scan(&tab, &w, &h, stdin);

	printf("\nRetourn de tab2d_scan(): %d\n", e);

	tab2d_print(tab, w, h);

	return 0;
}
