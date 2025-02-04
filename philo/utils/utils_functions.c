/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 07:55:31 by christophed       #+#    #+#             */
/*   Updated: 2025/02/04 14:34:57 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// Function to convert a string to a long integer
long	ft_atoi_long(const char *nptr)
{
	int		i;
	int		sign;
	long	result;

	result = 0;
	sign = 1;
	i = 0;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == 43 || nptr[i] == 45)
	{
		if (nptr[i] == 45)
			sign = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + (nptr[i] - '0');
		i++;
	}
	return (result * sign);
}

// Function to convert a timeval structure to milliseconds
long long	timeval_to_ms(t_timeval time)
{
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

// Function to get the actual time in milliseconds
long long	get_actual_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (timeval_to_ms(time));
}

// Function to get the elapsed time since the last meal
long long	get_elapsed_time(long long event)
{
	long long	elapsed;
	long long	actual;

	actual = get_actual_time();
	elapsed = actual - event;
	return (elapsed);
}
