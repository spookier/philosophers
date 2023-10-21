#include  "../incs/philo.h"

int init_single_mutex(pthread_mutex_t *mutex) 
{
	if (pthread_mutex_init(mutex, NULL) < 0) 
		return (-1);
	return 0;
}

void destroy_common_mutexes(t_data *data) 
{
    pthread_mutex_destroy(&data->mutex_print);
    pthread_mutex_destroy(&data->mutex_is_dead);
    pthread_mutex_destroy(&data->mutex_is_full);
}

void destroy_all_mutex(t_data *data, int i, int j, int k)
{
    int x = 0;
    while (x < i)
    {
        pthread_mutex_destroy(&data->fork[x]);
        x++;
    }
    x = 0;
    while (x < j)
    {
        pthread_mutex_destroy(&data->philo[x].mutex_meals);
        x++;
    }
    x = 0;
    while (x < k)
    {
        pthread_mutex_destroy(&data->philo[x].mutex_last_meal);
        x++;
    }
    pthread_mutex_destroy(&data->mutex_print);
    pthread_mutex_destroy(&data->mutex_is_dead);
}


int mutex_init(t_data *data) 
{
    int i = 0;

    if (init_single_mutex(&data->mutex_print) < 0)
        return (-1);
    if (init_single_mutex(&data->mutex_is_dead) < 0) 
	{
        destroy_common_mutexes(data);
        return (-1);
    }
    if (init_single_mutex(&data->mutex_is_full) < 0) 
	{
        destroy_common_mutexes(data);
        return (-1);
    }
    while (i < data->total_philos)
	{
        if (init_single_mutex(&data->fork[i]) < 0)
		{
            destroy_all_mutex(data, i, i, i);
            return (-1);
        }
        if (init_single_mutex(&data->philo[i].mutex_meals) < 0)
		{
            destroy_all_mutex(data, i + 1, i, i);
            return (-1);
        }
        if (init_single_mutex(&data->philo[i].mutex_last_meal) < 0)
		{
            destroy_all_mutex(data, i + 1, i + 1, i);
            return (-1);
        }
        i++;
    }
    return(0);
}
