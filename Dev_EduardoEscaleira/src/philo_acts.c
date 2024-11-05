/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_acts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eescalei <eescalei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 01:42:56 by eescalei          #+#    #+#             */
/*   Updated: 2024/06/25 20:04:03 by eescalei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	pick_forks(t_philo *philo)
{
	safe_mutex_handle(&philo->first_fork->fork, LOCK);
	write_status(philo, TAKING_FIRST_FORK);
	safe_mutex_handle(&philo->second_fork->fork, LOCK);
	write_status(philo, TAKING_SECOND_FORK);
}

void	eat(t_philo *philo)
{
	safe_mutex_handle(&philo->first_fork->fork, LOCK);
	write_status(philo, TAKING_FIRST_FORK);
	safe_mutex_handle(&philo->second_fork->fork, LOCK);
	write_status(philo, TAKING_SECOND_FORK);
	set_long(&philo->philo_mtx, &philo->last_meal_time, gettime(MILLISECONDS));
	philo->meals_counter++;
	write_status(philo, EATING);
	precise_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->nbr_limit_meals > 0
		&& philo->meals_counter == philo->table->nbr_limit_meals)
		set_bool(&philo->philo_mtx, &philo->full, true);
	safe_mutex_handle(&philo->first_fork->fork, UNLOCK);
	safe_mutex_handle(&philo->second_fork->fork, UNLOCK);
}

void	think(t_philo *philo)
{
	write_status(philo, THINKING);
	precise_usleep(TIME_TO_THINK, philo->table);
}

void	sleep_philo(t_philo *philo)
{
	write_status(philo, SLEEPING);
	precise_usleep(philo->table->time_to_sleep, philo->table);
}
