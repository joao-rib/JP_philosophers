/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phil_actions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2024/11/20 17:28:18 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/philo.h"

static void	grab_forks(t_philo *phil)
{
	if (!(phil->index % 3))
		usleep(1000);
	if (phil->l_hand->index < phil->r_hand->index)
	{
		thread_mtx(&(phil->l_hand->fork_mutex), LOCK);
		report_status(phil, FORK);
		thread_mtx(&(phil->r_hand->fork_mutex), LOCK);
		report_status(phil, FORK);
	}
	else
	{
		thread_mtx(&(phil->r_hand->fork_mutex), LOCK);
		report_status(phil, FORK);
		thread_mtx(&(phil->l_hand->fork_mutex), LOCK);
		report_status(phil, FORK);
	}
}

void	phil_eat(t_philo *phil)
{
	long	meal_start;

	grab_forks(phil);
	set_mtx_long(&(phil->ph_mutex), &(phil->satt_time), get_time());
	meal_start = get_mtx_long(&(phil->ph_mutex), &(phil->satt_time));
	phil->meals++;
	report_status(phil, EAT);
	while (get_time() - meal_start < phil->tab->time_eat)
	{
		if (get_mtx_bool(&(phil->tab->tab_mutex), &(phil->tab->ready_to_end)))
			break ;
	}
	if (phil->tab->num_meals >= 0 && phil->meals == phil->tab->num_meals)
		set_mtx_bool(&(phil->ph_mutex), &(phil->satt), true);
	thread_mtx(&(phil->l_hand->fork_mutex), UNLOCK);
	thread_mtx(&(phil->r_hand->fork_mutex), UNLOCK);
}

void	phil_sleep(t_philo *phil)
{
	long	sleepy_time;
	long	lastmeal_time;

	if (get_mtx_bool(&(phil->tab->tab_mutex), &(phil->tab->ready_to_end)))
		return ;
	report_status(phil, SLEEP);
	sleepy_time = get_time();
	lastmeal_time = get_mtx_long(&(phil->ph_mutex), &(phil->satt_time));
	while (get_time() - sleepy_time < phil->tab->time_sleep)
	{
		if (get_mtx_bool(&(phil->tab->tab_mutex), &(phil->tab->ready_to_end)))
			break ;
	}
}

void	phil_think(t_philo *phil)
{
	if (get_mtx_bool(&(phil->tab->tab_mutex), &(phil->tab->ready_to_end)))
		return ;
	report_status(phil, THINK);
	usleep(1000);
}

bool	phil_die(t_philo *phil)
{
	long	hungry_time;
	long	lastmeal_time;

	if (get_mtx_bool(&(phil->ph_mutex), &(phil->satt)))
		return (false);
	lastmeal_time = get_mtx_long(&(phil->ph_mutex), &(phil->satt_time));
	hungry_time = get_time();
	subtr_mtx_long(&(phil->ph_mutex), &hungry_time, lastmeal_time);
	if (hungry_time > phil->tab->time_die)
		return (true);
	return (false);
}
