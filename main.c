#include <stdlib.h>
#include "inc/malloc.h"
#include "lib/ft_printf/inc/ft_printf.h"
#include <unistd.h>
#include <sys/mman.h>

int		tiny_test(void)
{
	char *arr[400];

	for (int i = 0; i < 400; i++)
	{
		arr[i] = (char *)malloc(sizeof(char) * 27);
		if (!arr[i])
			return (1);
	}
	for (int i = 0; i < 400; i++)
	{
		for (int j = 0; j < 26; j++)
			arr[i][j] = 'a' + i % 26;
		arr[i][26] = '\0';
	}
	for (int i = 0; i < 400; i++)
		ft_printf("%p <%s>\n", arr[i], arr[i]);
	show_alloc_mem();
	for (int i = 1; i < 400; i += 3)
		free(arr[i]);
	show_alloc_mem();
	for (int i = 0; i < 400; i++)
		free(arr[i]);
	show_alloc_mem();
	return (0);
}

int		large_test(void)
{
	char *arr[10];

	for (int i = 0; i < 10; i++)
	{
		arr[i] = (char *)malloc(sizeof(char) * (2048 + 1));
		if (!arr[i])
			return (1);
	}
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 2048; j++)
			arr[i][j] = 'a' + i % 26;
		arr[i][2048] = '\0';
	}
	show_alloc_mem();
	for (int i = 0; i < 10; i++)
		ft_printf("%p <%s>\n", arr[i], arr[i]);
	for (int i = 0; i < 10; i++)
		free(arr[i]);
	show_alloc_mem();
	return (0);
}

int		realloc_test(void)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * (4095 + 1));
	if (!str)
		return (1);
	for (int i = 0; i < 4095; i++)
		str[i] = 'a' + i % 26;
	str[4095] = '\0';
	show_alloc_mem();
	ft_printf("malloc: %s\n\n", str);
	str = realloc(str, 32);
	show_alloc_mem();
	ft_printf("realloc: %s\n\n", str);
	str = realloc(str, sizeof(char) * (16383 + 1));
	for (int i = 0; i < 16383; i++)
		str[i] = 'a' + i % 26;
	str[16383] = '\0';
	show_alloc_mem();
	ft_printf("realloc: %s\n\n", str);
	free(str);
	show_alloc_mem();
	return (0);
}

int		calloc_test(void)
{
	int		*arr;

	arr = (int *)calloc(sizeof(int), (16384));
	if (!arr)
		return (1);
	for (int i = 0; i < 16384; i++)
		ft_printf("%d / ", arr[i]);
	for (int i = 0; i < 16384; i++)
		arr[i] = i;
	show_alloc_mem();
	free(arr);
	return (0);
}

int		main(void)
{
	// tiny_test();
	// large_test();
	// realloc_test();
	calloc_test();
}
