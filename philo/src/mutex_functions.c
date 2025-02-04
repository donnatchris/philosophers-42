/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:07:17 by christophed       #+#    #+#             */
/*   Updated: 2025/02/04 19:27:05 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// Function to check or modify run_threads variable
int	check_run(t_rules *rules, int mode)
{
	int	run;

	pthread_mutex_lock(&rules->run_mutex);
	if (mode == STOP)
		rules->run_threads = 0;
	run = rules->run_threads;
	pthread_mutex_unlock(&rules->run_mutex);
	return (run);
}

// Function to check or modify last_meal variable
long long	check_last_meal(t_philo *philo, int mode)
{
	long long	last_meal;

	pthread_mutex_lock(&philo->last_meal_mutex);
	if (mode == WRITE)
		philo->last_meal = get_actual_time();
	last_meal = philo->last_meal;
	pthread_mutex_unlock(&philo->last_meal_mutex);
	return (last_meal);
}

// Function to check or modify n_meals variable
int	check_n_meals(t_philo *philo, int mode)
{
	int	n_meals;

	pthread_mutex_lock(&philo->n_meals_mutex);
	if (mode == WRITE)
		philo->n_meals++;
	n_meals = philo->n_meals;
	pthread_mutex_unlock(&philo->n_meals_mutex);
	return (n_meals);
}

// Function to write logs
void	write_log(t_philo *philo, int status)
{
	pthread_mutex_lock(&philo->rules->log_mutex);
	if (check_run(philo->rules, READ))
	{
		if (status == WON)
		{
			check_run(philo->rules, STOP);
			printf("%lld All philosophers have eaten enough\n", \
			get_actual_time());
		}
		else if (status == DEAD)
		{
			check_run(philo->rules, STOP);
			printf("%lld %d died\n", get_actual_time(), philo->id);
		}
		else if (status == FORK)
			printf("%lld %d has taken a fork\n", get_actual_time(), philo->id);
		else if (status == EAT)
			printf("%lld %d is eating\n", get_actual_time(), philo->id);
		else if (status == SLEEP)
			printf("%lld %d is sleeping\n", get_actual_time(), philo->id);
		else if (status == THINK)
			printf("%lld %d is thinking\n", get_actual_time(), philo->id);
	}
	pthread_mutex_unlock(&philo->rules->log_mutex);
}
