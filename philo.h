#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eating;
	int				meals_eaten;
	size_t			last_meal;
	size_t			time_to_eat;
	size_t			time_to_die;
	size_t			time_to_sleep;
	size_t			start_time;
	int				num_of_philos;
	int				num_times_to_eat;
	int				*dead;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*eat_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*meal_lock;
}					t_philo;

typedef	struct s_program
{
	int			dead_flag;
	t_philo		*philos;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
}					t_program;

//init
void	init_program(t_program *program, t_philo *philos);
void	init_input(t_philo *philo, char **argv);
void	init_philos(t_philo *philos, t_program *program, pthread_mutex_t *forks,
		char **argv);
void	init_forks(pthread_mutex_t *forks, int philo_num);

//routine
void	think(t_philo *philo);
void	sleeping(t_philo *philo);
void	eat(t_philo *philo);

int		dead_loop(t_philo *philo);
void	print_message(char *str, t_philo *philo, int id);

//checks
int	check_arg_content(char *arg);
int	check_arguments(char ** argv);

//monitor
int		check_philo_dead(t_philo *philo, size_t time_to_die);
int		check_any_dead(t_philo *philos);
void	print_message(char *str, t_philo *philo, int id);
void	*monitor(void *pointer);
//utils
int		ft_strlen(char *str);
int		ft_atoi(char *str);
void	destroy_all(char *str, t_program *program, pthread_mutex_t *forks);
int		ft_usleep(size_t milliseconds);
size_t	get_current_time();
#endif