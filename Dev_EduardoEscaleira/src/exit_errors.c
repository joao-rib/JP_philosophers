/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eescalei <eescalei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 16:22:12 by eescalei          #+#    #+#             */
/*   Updated: 2024/06/25 20:04:53 by eescalei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	write_status(t_philo *philo, t_philo_status status)
{
	long	elapsed;

	elapsed = gettime(MILLISECONDS) - philo->table->start_simulation;
	safe_mutex_handle(&philo->table->print_mtx, LOCK);
	if (THINKING == status && !get_bool(&philo->table->table_mtx,
			&philo->table->end_simulation))
		printf("%ld %d is thinking\n", elapsed, philo->philo_id);
	else if (EATING == status && !get_bool(&philo->table->table_mtx,
			&philo->table->end_simulation))
		printf("%ld %d is eating\n", elapsed, philo->philo_id);
	else if (SLEEPING == status && !get_bool(&philo->table->table_mtx,
			&philo->table->end_simulation))
		printf("%ld %d is sleeping\n", elapsed, philo->philo_id);
	else if (DIED == status && !get_bool(&philo->table->table_mtx,
			&philo->table->end_simulation))
		printf("%ld %d died\n", elapsed, philo->philo_id);
	else if ((TAKING_FIRST_FORK == status || TAKING_SECOND_FORK == status)
		&& !get_bool(&philo->table->table_mtx,
			&philo->table->end_simulation))
		printf("%ld %d has taken a fork\n", elapsed, philo->philo_id);
	safe_mutex_handle(&philo->table->print_mtx, UNLOCK);
}

void	clean(t_table *table)
{
	if (table->philo != NULL)
		free(&table->philo[0]);
	if (table->forks != NULL)
		free(&table->forks[0]);
}

void	exit_error(char *error)
{
	printf("%s", error);
	return ;
}
