/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2024/11/06 20:08:09 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/philo.h"

/*void	*meal_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_thread_ready(philo->table);
	increase_long(&philo->table->table_mtx, &philo->table->threads_running);
	set_long(&philo->philo_mtx, &philo->last_meal_time, gettime(MILLISECONDS));
	while (!simulation_finished(philo->table))
	{
		if (philo->full)
			break ;
		eat(philo);
		sleep_philo(philo);
		think(philo);
	}
	return (NULL);
}*/

void	*handle_spaghetti(void *arg)
{
	t_philo	*phil;

	phil = (t_philo *)arg;
	//wait_all_thread_ready(philo->table);
	//increase_long(&philo->table->table_mtx, &philo->table->threads_running);
	//set_long(&philo->philo_mtx, &philo->last_meal_time, gettime(MILLISECONDS));
	while (!simulation_finished(philo->table)) //WIP escrever função própria
	{
		if (phil->satt) // num_meals?
			break ;
		phil_eat(phil); //report_status(phil, FORK)x2 + report_status(phil, EAT);
		phil_sleep(phil); //report_status(phil, SLEEP);
		phil_think(phil); //report_status(phil, THINK);
	}
	return (NULL);
}

/*void	*monitoring(void *data)
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
*/

void	*handle_table(void *arg)
{
	t_table	*tab;
	int		i;

	tab = (t_philo *)arg;
	//while (!all_threads_running(&table->table_mtx, &table->threads_running,
	//		table->philo_nbr)) //WIP escrever função própria
		i = 0;
	while (!simulation_finished(table)) //WIP escrever função própria
	{
		i = 0;
		while (i < tab->num_philo && !simulation_finished(table)) //WIP escrever função própria
		{
			if (philo_died(table->philo + i)) //WIP escrever função própria
			{
				report_status(find_phil(tab->phil_list, i), DEAD); //WIP escrever find_phil
				set_mtx_bool(&tab->tab_mutex, &tab->ready_to_end, true);
			}
		i++;
		}
	}
	return (NULL);
}