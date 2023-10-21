#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>


typedef struct s_philo
{
	int				id;
	struct s_data	*data_ref;
	int				meals;
	pthread_mutex_t	mutex_meals;
	long			last_meal;
	pthread_mutex_t	mutex_last_meal;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}	t_philo;

typedef struct s_data
{
	int				total_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			time_start;
	int				nb_philo_must_eat;
	int				is_full;
	pthread_mutex_t	mutex_is_full;
	int				is_dead;
	pthread_mutex_t	mutex_is_dead;
	pthread_t		*threads;
	t_philo			*philo;
	pthread_mutex_t	*fork;
	pthread_mutex_t	mutex_print;

}	t_data;


// ALLOC & INIT
int			data_init(t_data *data);
void		philo_init(t_data *data);


// MUTEX
int 		mutex_init(t_data *data);
void 		destroy_all_mutex(t_data *data, int i, int j, int k);


// UTILS FOR PARSING
int			ascii2long(long *result, char *str);
int			ft_atoi(int *result, char *str);


// TIME
int			get_time(long *time);
int 		_usleep(long time);


// THREADS
int			start_threads(t_data *data);

// SUPERVISOR
void	start_supervisor(t_data *data);

// PHILO LOOP
void		*philo_loop(t_philo *philo);
int 		print_msg(t_philo *philo, int msg_flag);
int			philo_deathcheck(t_data *data);


// FREE
void		free_struct(t_data *data);
void		free_all(t_data *data);


#endif