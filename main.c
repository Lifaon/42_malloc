#include "inc/malloc.h"
// #include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>

int		tiny_test(void)
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
	for (int i = 0; i < 4096; i++)
		printf("%p <%s>\n", str[i], str[i]);
	return (0);
}

int		large_test(void)
{
	char *str[10];

	for (int i = 0; i < 10; i++)
	{
		str[i] = (char *)malloc(sizeof(char) * 511 + 1);
		if (!str[i])
			return (1);
	}
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 511; j++)
			str[i][j] = 'a' + i % 511;
		str[i][511] = '\0';
	}
	for (int i = 0; i < 10; i++)
		printf("%p <%s>\n", str[i], str[i]);
	return (0);
	return (0);
}

int		main(void)
{
	tiny_test();
	// large_test();

	// char	*str;
	// int		page_size;

	// page_size = getpagesize();
	// str = mmap(NULL, page_size, PROT_READ | PROT_WRITE,
	// 	MAP_ANON | MAP_PRIVATE, -1, 0);
	// for (int i = 0; i < page_size; i++)
	// 	str[i] = 'a' + i % 26;
	// str[page_size - 1] = 0;
	// printf("1) %s\n\n", str);
	// str = mmap(str, page_size, PROT_READ | PROT_WRITE,
	// 	MAP_ANON | MAP_PRIVATE, -1, page_size);
	// // for (int i = 0; i < page_size * 2; i++)
	// // 	str[i] = 'a' + i % 26;
	// // str[page_size * 2 - 1] = 0;
	// printf("2) %s\n", str);
	// munmap(str, page_size * 2);
}

// __attribute__((destructor))	void end(void)
// {
// 	while (1);
// }
