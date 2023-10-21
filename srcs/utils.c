# include  "../incs/philo.h"

int	ascii2long(long *result, char *str)
{
	int	i;
	int	sign;

	sign = 1;
	i = 0;
	while ((str[i] > 8 && str[i] < 14) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	*result = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (*result > *result * 10 + str[i] - 48)
			return (-1);
		*result = *result * 10 + str[i] - 48;
		i++;
	}
	*result *= sign;
	return (0);
}

int	ft_atoi(int *result, char *str)
{
	int	i;
	int	sign;

	sign = 1;
	i = 0;
	while ((str[i] > 8 && str[i] < 14) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	*result = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (*result > *result * 10 + str[i] - 48)
			return (-1);
		*result = *result * 10 + str[i] - 48;
		i++;
	}
	*result *= sign;
	return (0);
}

// 0 = eating
// 1 = sleeping
// 2 = thinking
// 3 = taking a fork
// 4 = dead

int print_msg(t_philo *philo, int msg_flag) 
{
    long time;
	long adjusted_time;

    pthread_mutex_lock(&philo->data_ref->mutex_print);

    if (msg_flag != 4 && philo_deathcheck(philo->data_ref) == -1) 
	{
        pthread_mutex_unlock(&philo->data_ref->mutex_print);
        return (-1);
    }

    get_time(&time);
    adjusted_time = (time - philo->data_ref->time_start) / 1000;

    if (msg_flag == 0) 
        printf("%ld %d is eating\n", adjusted_time, philo->id + 1);
	else if (msg_flag == 1) 
        printf("%ld %d is sleeping\n", adjusted_time, philo->id + 1);
	else if (msg_flag == 2)
        printf("%ld %d is thinking\n", adjusted_time, philo->id + 1);
	else if (msg_flag == 3)
        printf("%ld %d has taken a fork\n", adjusted_time, philo->id + 1);
	else if (msg_flag == 4)
        printf("%ld %d died\n", adjusted_time, philo->id + 1);
	else 
        printf("Invalid msg_flag\n");
    pthread_mutex_unlock(&philo->data_ref->mutex_print);
    return (0);
}
