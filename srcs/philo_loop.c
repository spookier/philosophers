#include  "../incs/philo.h"

void single_philo_case(t_philo *philo) 
{
    pthread_mutex_lock(philo->left_fork);
    print_msg(philo, 3);
    while (philo_deathcheck(philo->data_ref) == 0)
		_usleep(125);
    pthread_mutex_unlock(philo->left_fork);
}

static int	philo_lock_forks(t_philo *philo)
{

	if (philo->id % 2 == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		if (print_msg(philo, 3) == -1)
			return (pthread_mutex_unlock(philo->left_fork), (-1));

		pthread_mutex_lock(philo->right_fork);
		if (print_msg(philo, 3) == -1)
			return (pthread_mutex_unlock(philo->left_fork), pthread_mutex_unlock(philo->right_fork), (-1));
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		if (print_msg(philo, 3) == -1)
			return (pthread_mutex_unlock(philo->right_fork), (-1));
		pthread_mutex_lock(philo->left_fork);
		if (print_msg(philo, 3) == -1)
			return (pthread_mutex_unlock(philo->left_fork), pthread_mutex_unlock(philo->right_fork), (-1));
	}

	return (0);
}

int	philo_deathcheck(t_data *data)
{
	pthread_mutex_lock(&data->mutex_is_dead);
	if (data->is_dead >= 0)
		return (pthread_mutex_unlock(&data->mutex_is_dead), (-1));
	pthread_mutex_unlock(&data->mutex_is_dead);
	pthread_mutex_lock(&data->mutex_is_full);
	if (data->is_full >= 0)
		return (pthread_mutex_unlock(&data->mutex_is_full), (-1));
	pthread_mutex_unlock(&data->mutex_is_full);
	return (0);
}

static int philo_eat(t_philo *philo)
{

	if (philo_lock_forks(philo) == -1)
		return (-1);

	if (print_msg(philo, 0) == -1)
		return (pthread_mutex_unlock(philo->right_fork), pthread_mutex_unlock(philo->left_fork), (-1));
	pthread_mutex_lock(&philo->mutex_last_meal);
	get_time(&philo->last_meal);
	pthread_mutex_unlock(&philo->mutex_last_meal);
	_usleep(philo->data_ref->time_to_eat);
	pthread_mutex_lock(&philo->mutex_last_meal);
	philo->meals++;
	pthread_mutex_unlock(&philo->mutex_last_meal);

	if (philo->id % 2 == 1)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
	return (0);

}

static int	philo_sleep(t_philo *philo)
{
	if (print_msg(philo, 1) == -1)
		return (-1);
	_usleep(philo->data_ref->time_to_sleep);
	return (0);
}

void	*philo_loop(t_philo *philo)
{
	int default_sleep;

	if (philo->data_ref->total_philos == 1)
	{
		single_philo_case(philo);
		return (NULL);
	}
	while (philo_deathcheck(philo->data_ref) == 0)
	{
		if (philo->id % 2 == 0)
			_usleep(500);

		if (philo_eat(philo) == -1)
			break ;

		if (philo_sleep(philo) == -1)
			break ;
		
		if(philo->data_ref->time_to_eat > philo->data_ref->time_to_sleep)
			default_sleep = philo->data_ref->time_to_eat - philo->data_ref->time_to_sleep;
		else
			default_sleep = 0;
		default_sleep += 125;
		_usleep(default_sleep);
		if (print_msg(philo, 2) == -1)
			break ;
	}
	return (NULL);
}
