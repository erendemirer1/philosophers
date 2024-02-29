#include "../philo.h"

int	check_arg_content(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] != '\0')
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (1);
		i++;
	}
	return (0);
}
int	check_arguments(char ** argv)
{
	if (ft_atoi(argv[1]) <= 0 || check_arg_content(argv[1]) == 1)
	return (write(2, "Invalid philosophers number\n", 29), 1);
	if (ft_atoi(argv[2]) <= 0 || check_arg_content(argv[2]) == 1)
		return (write(2, "Invalid time to die\n", 21), 1);
	if (ft_atoi(argv[3]) <= 0 || check_arg_content(argv[3]) == 1)
		return (write(2, "Invalid time to eat\n", 21), 1);
	if (ft_atoi(argv[4]) <= 0 || check_arg_content(argv[4]) == 1)
		return (write(2, "Invalid time to sleep\n", 23), 1);
	if (argv[5] && (ft_atoi(argv[5]) < 0 || check_arg_content(argv[5]) == 1))
		return (write(2, "Invalid number of times each philosopher must eat\n",
				51), 1);
	return (0);
}
int	main(int argc, char **argv)
{
	t_program		program;
	t_philo			*philos;
	pthread_mutex_t	*forks;

	if (argc != 5 && argc != 6)
		return (write (2, "Miss or Extra arguments!", 25), 1);
	philos = (t_philo *)malloc(sizeof(t_philo) * ft_atoi(argv[1]));
	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * ft_atoi(argv[1]));
	init_program(&program, philos);
	init_forks(forks, ft_atoi(argv[1]));
	init_philos(philos, &program, forks, argv);
	thread_create(&program, forks);
	destroy_all(NULL, &program,forks);
	return (0);
}