#include  "../incs/philo.h"

int get_time(long *time) 
{
    struct timeval time_val;

    if (gettimeofday(&time_val, NULL) < 0) 
	{
        printf("Get time failed\n");
        return(-1);
    }
    *time = time_val.tv_sec * 1000000 + time_val.tv_usec;
    return(0);
}

int _usleep(long time)
{
	long	end;
	long	start;

	if (get_time(&start) == -1)
		return (-1);
	if (get_time(&end) == -1)
		return (-1);
	while (end - start < time)
	{
		usleep(500);
		if (get_time(&end) == -1)
			return (-1);
	}
	return (0);
}