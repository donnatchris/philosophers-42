/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 07:55:31 by christophed       #+#    #+#             */
/*   Updated: 2025/01/27 14:09:54 by chdonnat         ###   ########.fr       */
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

void	print_rules(t_rules rules)
{
	printf("\n*************************  Rules  *************************\n");
	printf("Number of philosophers:\t\t\t\t%d\n", rules.nb_philo);
	printf("Time to die:\t\t\t\t\t%d\n", rules.time_to_die);
	printf("Time to eat:\t\t\t\t\t%d\n", rules.time_to_eat);
	printf("Time to sleep:\t\t\t\t\t%d\n", rules.time_to_sleep);
	if (rules.nb_must_eat == -1)
		printf("Number of times each philosopher must eat:\tuntil death\n");
	else
	printf("Number of times each philosopher must eat:\t%d\n", rules.nb_must_eat);
	printf("***********************************************************\n\n");

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

