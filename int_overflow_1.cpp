#include <stdio.h>
#include <stdint.h>

int main()
{
	uint16_t masse_kg;
	uint16_t masse_gr;

	printf("Quelle masse d'uranium voulez vous produire en kg ?\n(ALERTE : ne pas dépasser 16000 g !)\n");
	scanf("%hu", &masse_kg);
	masse_gr = 1000*masse_kg;

	if (masse_gr > 16000)
	{
		fprintf(stderr, "ERREUR : %hu g : limite dépassée !\n", masse_gr);
		return -1;
	}

	printf("Production de %hu kg lancée !\n", masse_kg);
	if (masse_kg > 16)
		printf("Félicitations !\n");
}
