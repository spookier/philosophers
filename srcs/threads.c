#include  "../incs/philo.h"

void init_last_meal_times(t_data *data, int limit)
{
    int i = 0;
    while (i < limit) 
	{
        get_time(&(data->philo[i].last_meal));
        i++;
    }
}

void join_threads(t_data *data, int limit) 
{
    int i;
    
    i = limit - 1;
    while (i >= 0) 
	{
        pthread_join(data->threads[i], NULL);
        i--;
    }
}

int start_threads(t_data *data) 
{
    int i = 0;
    get_time(&data->time_start);
    init_last_meal_times(data, data->total_philos);

    while (i < data->total_philos) 
	{
        if (pthread_create(&data->threads[i], NULL, (void *)philo_loop, &data->philo[i]) == -1) 
		{
            join_threads(data, i);
            return (-1);
        }
        i++;
    }
    return (0);
}
