#include <stdio.h>
#include <pthread.h>
#include "lib/ft_printf/inc/ft_printf.h"

static pthread_mutex_t	mtx;

void	*f(void *atr)
{
	static int i = 0;

	pthread_mutex_lock(&mtx);
	ft_printf("thread #%d\n", i++);
	pthread_mutex_unlock(&mtx);
	pthread_exit(NULL);
}

int		main(void)
{
	pthread_t	t[8];

	// if (pthread_mutex_init(&mtx, NULL))
	// 	return (1);
	for (int i = 0; i < 8; i++)
		pthread_create(&t[i], NULL, f, &i);
	for (int i = 0; i < 8; i++)
		pthread_join(t[i], NULL);
	pthread_mutex_destroy(&mtx);
	return (0);
}
