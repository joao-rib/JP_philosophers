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

void	*handle_spaghetti(void *arg)
{
	t_philo	*phil;

	phil = (t_philo *)arg;
	while (get_mtx_bool(&(phil->tab->tab_mutex), &(phil->tab->ready_to_start)))
		phil = (t_philo *)arg;
	add_mtx_long(&(phil->tab->tab_mutex), &(phil->tab->running_threads), 1);
	set_mtx_long(&(phil->tab->tab_mutex), &(phil->satt_time), get_time());
	while (!get_mtx_bool(&(phil->tab->tab_mutex), &(phil->tab->ready_to_end)))
	{
		if (phil->satt)
			break ;
		phil_eat(phil);
		phil_sleep(phil);
		phil_think(phil);
	}
	return (NULL);
}

void	*handle_table(void *arg)
{
	t_table	*tab;
	long		i;

	tab = (t_table *)arg;
	while (!check_mtx_equalto(&(tab->tab_mutex), tab->running_threads, tab->num_philo))
		i = 0;
	while (!get_mtx_bool(&(tab->tab_mutex), &(tab->ready_to_end)))
	{
		i = 1;
		while (i <= tab->num_philo &&
				!get_mtx_bool(&(tab->tab_mutex), &(tab->ready_to_end)))
		{
			if (phil_die(find_phil(tab->phil_list, i)))
			{
				report_status(find_phil(tab->phil_list, i), DEAD);
				set_mtx_bool(&tab->tab_mutex, &tab->ready_to_end, true);
			}
		i++;
		}
	}
	return (NULL);
}

/*bool	philo_died(t_philo *philo)
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
}*/