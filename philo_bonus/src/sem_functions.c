/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:07:17 by christophed       #+#    #+#             */
/*   Updated: 2025/02/06 14:35:11 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// Function to check or modify run_threads variable
int	check_run(t_rules *rules, int mode)
{
	int	run;

	sem_wait(rules->run_sem);
	if (mode == STOP)
		rules->run_threads = 0;
	run = rules->run_threads;
	sem_post(rules->run_sem);
	return (run);
}

// Function to check or modify last_meal variable
long long	check_last_meal(t_philo *philo, int mode)
{
	long long	last_meal;

	sem_wait(philo->last_meal_sem);
	if (mode == WRITE)
		philo->last_meal = get_actual_time();
	last_meal = philo->last_meal;
	sem_post(philo->last_meal_sem);
	return (last_meal);
}

// Function to check or modify n_meals variable
int	check_n_meals(t_philo *philo, int mode)
{
	int	n_meals;

	sem_wait(philo->n_meals_sem);
	if (mode == WRITE)
		philo->n_meals++;
	n_meals = philo->n_meals;
	sem_post(philo->n_meals_sem);
	return (n_meals);
}

// Function to write logs
void	write_log(t_philo *philo, int status)
{
	sem_wait(philo->rules->log_sem);
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
	sem_post(philo->rules->log_sem);
}
