#include  "../incs/philo.h"

// 0 means NOT FULL, -1 means FULL
static int supervisor_check_if_philo_full(t_philo *philo, int nb_philo_must_eat)
{
    int res;
	
	res = 0;
    pthread_mutex_lock(&philo->mutex_meals);
    if (philo->meals >= nb_philo_must_eat)
        res = -1;
    pthread_mutex_unlock(&philo->mutex_meals);
    return (res);
}

static int supervisor_check_philos_full(t_data *data)
{
    int i;

    if (data->nb_philo_must_eat < 0)
		return (0);

	i = 0;
	while (i < data->total_philos)
	{
		if (supervisor_check_if_philo_full(&data->philo[i], data->nb_philo_must_eat) == 0)
			return (0);
		i++;
	}
    pthread_mutex_lock(&data->mutex_is_full);
    data->is_full = 1; 
    pthread_mutex_unlock(&data->mutex_is_full);

    return(1); // Means he's full, so skip next while loop
}


static int	supervisor_check_if_philo_alive(t_philo *philo)
{
	long	time;

	pthread_mutex_lock(&philo->mutex_last_meal);
	get_time(&time);
	if (time - philo->last_meal >= philo->data_ref->time_to_die)
		return (pthread_mutex_unlock(&philo->mutex_last_meal), (-1));
	pthread_mutex_unlock(&philo->mutex_last_meal);
	return (0);
}


static int supervisor_check_philos_alive(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->total_philos)
	{
		if (supervisor_check_if_philo_alive(&data->philo[i]) == -1)
		{
			pthread_mutex_lock(&data->mutex_is_dead);
			data->is_dead = 1;
			pthread_mutex_unlock(&data->mutex_is_dead);
			print_msg(&data->philo[i], 4);
			return (-1);
		}
		i++;
	}
	return (0);
}


void	start_supervisor(t_data *data)
{
	int		i;

	usleep(125);
	while (supervisor_check_philos_alive(data) == 0 && supervisor_check_philos_full(data) == 0)
		usleep(800);
	i = 0;
	while (i < data->total_philos)
	{
		pthread_join(data->threads[i], NULL);
		i++;
	}
}