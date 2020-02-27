// 2020 GUILLEUS Hugues IATIC3 <hugues.guilleus@ens.uvsq.fr>

#include "tools.h"

// Vide Stdin jusqu'a une nouvelle ligne ou la fin du fichier.
void clearStdin(void) {
	char c;
	while ((c = getchar()) != '\n' && c != EOF)
		;
}
