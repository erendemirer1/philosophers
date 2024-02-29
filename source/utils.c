#include "philo.h"
#include <sys/time.h>

int	ft_strlen(char *str)
{
	int	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_atoi(char *str)
{
	unsigned long long	num;
	int					sign;
	int					i;

	num = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return (sign * num);
}

void	destroy_all(char *str, t_program *program, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	if (str)
	{
		write(2, str, ft_strlen(str));
		write(2, "\n", 1);
	}
	pthread_mutex_destroy(&program->dead_lock);
	pthread_mutex_destroy(&program->meal_lock);
	pthread_mutex_lock(&program->write_lock);
	while (i < program->philos->num_of_philos)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
}
size_t	get_current_time()
{
	struct timeval time;
	
	if (gettimeofday(&time, NULL) == -1)
		write (2, "gettimeofday() error!\n", 23);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}