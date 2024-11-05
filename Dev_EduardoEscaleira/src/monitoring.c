/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eescalei <eescalei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 14:55:01 by eescalei          #+#    #+#             */
/*   Updated: 2024/06/25 20:28:54 by eescalei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

bool	philo_died(t_philo *philo)
{
	long	elapsed;
	long	time_to_die;

	if (get_bool(&philo->philo_mtx, &philo->full))
		return (false);
	elapsed = gettime(MILLISECONDS) - get_long(&philo->philo_mtx,
			&philo->last_meal_time);
	time_to_die = philo->table->time_to_die / 1e3;
	if (elapsed > time_to_die)
		return (true);
	return (false);
}

void	increase_long(t_mtx *mutex, long *value)
{
	safe_mutex_handle(mutex, LOCK);
	(*value)++;
	safe_mutex_handle(mutex, UNLOCK);
}

bool	all_threads_running(t_mtx *mutex, long *threads, long filo_nbr)
{
	bool	ret;

	ret = false;
	safe_mutex_handle(mutex, LOCK);
	if (*threads == filo_nbr)
		ret = true;
	safe_mutex_handle(mutex, UNLOCK);
	return (ret);
}

void	*monitoring(void *data)
{
	t_table	*table;
	int		i;

	table = (t_table *)data;
	while (!all_threads_running(&table->table_mtx, &table->threads_running,
			table->philo_nbr))
		;
	while (!simulation_finished(table))
	{
		i = -1;
		while (++i < table->philo_nbr && !simulation_finished(table))
		{
			if (philo_died(table->philo + i))
			{
				write_status(table->philo + i, DIED);
				set_bool(&table->table_mtx, &table->end_simulation, true);
			}
		}
	}
	return (NULL);
}
