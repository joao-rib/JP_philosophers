/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   innit_structs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eescalei <eescalei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:38:52 by eescalei          #+#    #+#             */
/*   Updated: 2024/06/26 14:38:59 by eescalei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

static void	assign_forks(t_philo *philo, t_fork *forks, int philo_position)
{
	int	philo_nbr;

	philo_nbr = philo->table->philo_nbr;
	if (philo_position % 2)
	{
		philo->first_fork = &forks[philo_position];
		philo->second_fork = &forks[(philo_position + 1) % philo_nbr];
	}
	else
	{
		philo->first_fork = &forks[(philo_position + 1) % philo_nbr];
		philo->second_fork = &forks[philo_position];
	}
}

void	innit_philo(t_table *table)
{
	int		i;
	t_philo	*philo;

	philo = table->philo;
	i = 0;
	while (table->philo_nbr > i)
	{
		philo->philo_id = i + 1;
		philo->full = false;
		philo->meals_counter = 0;
		philo->table = table;
		safe_mutex_handle(&philo->philo_mtx, INIT);
		assign_forks(philo, table->forks, i);
		philo++;
		i++;
	}
}

void	innit_struct(t_table *table)
{
	int	i;

	i = 0;
	table->start_simulation = 0;
	table->end_simulation = false;
	table->all_thread_ready = false;
	table->philo = (t_philo *)safe_malloc(sizeof(t_philo) * table->philo_nbr);
	safe_mutex_handle(&table->table_mtx, INIT);
	safe_mutex_handle(&table->print_mtx, INIT);
	table->threads_running = 0;
	table->forks = (t_fork *)safe_malloc(sizeof(t_fork) * table->philo_nbr);
	while (i < table->philo_nbr)
	{
		safe_mutex_handle(&table->forks[i].fork, INIT);
		table->forks->fork_id = i;
		i++;
	}
	innit_philo(table);
}
