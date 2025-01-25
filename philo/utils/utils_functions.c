/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 07:55:31 by christophed       #+#    #+#             */
/*   Updated: 2025/01/25 11:11:36 by christophed      ###   ########.fr       */
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

// // Function to see if the number is a valid integer
// int	is_number(const char *nptr)
// {
// 	int	i;

// 	i = 0;
// 	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
// 		i++;
// 	if (nptr[i] == 43 || nptr[i] == 45)
// 		i++;
// 	if (nptr[i] < '0' || nptr[i] > '9')
// 		return (0);
// 	while (nptr[i] >= '0' && nptr[i] <= '9')
// 		i++;
// 	if (nptr[i] == '\0')
// 		return (1);
// 	return (0);
// }

