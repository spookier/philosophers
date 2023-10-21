#include  "../incs/philo.h"

int	data_init(t_data *data)
{
	data->threads = malloc(sizeof(pthread_t) * data->total_philos);
	if (!data->threads)
		return (-1);
	data->philo = malloc(sizeof(t_philo) * data->total_philos);
	if (!data->philo)
		return (free(data->threads), -1);
	data->fork = malloc(sizeof(pthread_mutex_t) * data->total_philos);
	if (!data->fork)
		return (free(data->philo), free(data->threads), -1);
	return (0);
}

void	philo_init(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->total_philos)
	{
		data->philo[i].id 			= i;
		data->philo[i].meals 		= 0;
		data->philo[i].left_fork 	= &data->fork[i];
		data->philo[i].right_fork 	= &data->fork[(i + 1) % data->total_philos];
		data->philo[i].data_ref 	= data;
		i++;
	}
}
