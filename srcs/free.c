#include  "../incs/philo.h"

void	free_struct(t_data *data)
{
	free(data->philo);
	free(data->threads);
	free(data->fork);
}


void free_all(t_data *data)
{
	destroy_all_mutex(data, data->total_philos, data->total_philos,
		data->total_philos);
	free_struct(data);
}