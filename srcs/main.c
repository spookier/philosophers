# include  "../incs/philo.h"

int	parse_argv(char **argv, t_data *data)
{
	if ((ft_atoi(&data->total_philos, argv[1]) == -1) || data->total_philos <= 0)
		return (-1);
	if ((ascii2long(&data->time_to_die, argv[2]) == -1) || data->time_to_die < 0)
		return (-1);
	if ((ascii2long(&data->time_to_eat, argv[3]) == -1) || data->time_to_eat < 0)
		return (-1);
	if ((ascii2long(&data->time_to_sleep, argv[4]) == -1) || data->time_to_sleep < 0)
		return (-1);
	if (argv[5])
	{
		if ((ft_atoi(&data->nb_philo_must_eat, argv[5]) == -1) || data->nb_philo_must_eat < 0)
			return (-1);
	}
	else
		data->nb_philo_must_eat = -1;
	data->time_to_die *= 1000;
	data->time_to_eat *= 1000;
	data->time_to_sleep *= 1000;
	if (data->time_to_die < 0 || data->time_to_eat < 0 || data->time_to_sleep < 0)
		return (-1);
	data->is_dead = -1;
	data->is_full = -1;
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6 || (parse_argv(argv, &data) == -1))
		return (write(1, "Error Arg\n", 10), 1);
	if (data_init(&data) == -1)
		return (write(1, "Error Alloc\n", 12), 1);
	philo_init(&data);
	if (mutex_init(&data) == -1)
		return (write(1, "Error Mutex\n", 12), free_struct(&data), 1);
	if (start_threads(&data) == -1)
		return (write(1, "End of program. \n", 14), free_all(&data), 1);
	start_supervisor(&data);
	free_all(&data);
}