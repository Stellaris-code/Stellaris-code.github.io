#include <stdio.h>
#include <stdint.h>

#define USER_COUNT 4

// format : paires de (username, password)
const char* user_info[USER_COUNT*2] =
{ "admin", "oV3rFl0wSk1llz",
  "user1", "notaflag",
  "user2", "helloworld",
  "user3", "133742"
};

int main()
{
	uint16_t index;
	printf("Entrez l'index d'utilisateur à récupérer :\n");
	scanf("%hd", &index);

	if (index == 0)
	{
		fprintf(stderr, "Accès aux infos d'admin interdit !\n");
		return -1;
	}

	uint16_t user_index = index*2;
	uint16_t pswd_index = index*2+1;

	if (pswd_index >= USER_COUNT*2)
	{
		fprintf(stderr, "Index invalide !\n");
		return -2;
	}

	printf("User : '%s'\nFlag: '%s'\n", user_info[user_index], user_info[pswd_index]);
}
