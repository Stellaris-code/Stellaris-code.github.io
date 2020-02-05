#include <stdio.h>
#include <stdint.h>

int main()
{
	int16_t solde = -1000;

	int16_t valeur;
	printf("Solde : %hd\n", solde);
	while (scanf("%hd", &valeur)) // tant qu'on lit un entier
	{
		if (valeur < 0)
			printf("Débit interdit !\n");
		else
		{
			solde -= valeur;
			printf("Solde : %hd\n", solde);
		}
	}
}
