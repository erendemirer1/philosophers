#include "../philo.h"
int	dead_loop(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == 1)
		return (pthread_mutex_unlock(philo->dead_lock), 1);
	pthread_mutex_unlock(philo->dead_lock);
}

void	*philo_routine(void *pointer)
{
	t_philo	*philoo;

	philoo = (t_philo *)pointer;
	if (philoo->id % 2 == 0)
		ft_usleep(1);
	while (!dead_loop(philoo))
	{
		eat(philoo);
		sleeping(philoo);
		think(philoo);
	}
	return (pointer);
}
int	thread_create(t_program *program, pthread_mutex_t *forks)
{
	pthread_t	obs;
	int			i;
	if (pthread_create(&obs, NULL, &monitor, program->philos) != 0)
		destroy_all("Thread Creation fail.", program, forks);
	i = 0;
	while (i < program->philos->num_of_philos)
	{
		if (pthread_create(&program->philos[i].thread, NULL, &philo_routine, &program->philos[i]) != 0)
			destroy_all("Thread creation fail.", program, forks);
		i++;
	}
	i = 0;
	if (pthread_join(obs, NULL) != 0)
		destroy_all("Thread join fail.", program, forks);
	while (i < program->philos->num_of_philos)
	{
		if (pthread_join(&program->philos[i].thread, NULL) != 0)
			destroy_all("Thread join fail.", program, forks);
		i++;
	}
	return (0);
}