#include "inc/malloc.h"
// #include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int		main(void)
{
	char *str[4096];

	for (int i = 0; i < 4096; i++)
	{
		str[i] = (char *)malloc(sizeof(char) * 27);
		if (!str[i])
			return (1);
	}
	for (int i = 0; i < 4096; i++)
	{
		for (int j = 0; j < 26; j++)
			str[i][j] = 'a' + i % 26;
		str[i][26] = '\0';
	}
	// printf("%p\n", str);
	// for (int i = 0; i < 4096; i++)
	// 	printf("%p\n", str[i]);
	for (int i = 0; i < 4096; i++)
		printf("%s\n", str[i]);
	return (0);
}
