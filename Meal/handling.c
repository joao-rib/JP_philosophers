/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2024/11/20 17:20:52 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/philo.h"

void	report_status(t_philo *phil, t_socas status)
{
	long	timestamp;

	if (get_mtx_bool(&(phil->tab->tab_mutex), &(phil->tab->ready_to_end)))
		return ;
	thread_mtx(&(phil->tab->print_mutex), LOCK);
	timestamp = get_time() - phil->tab->starting_time;
	if (status == FORK)
		printf("%ld %ld has taken a fork\n", timestamp, phil->index);
	else if (status == THINK)
		printf("%ld %ld is thinking\n", timestamp, phil->index);
	else if (status == SLEEP)
		printf("%ld %ld is sleeping\n", timestamp, phil->index);
	else if (status == EAT)
		printf("%ld %ld is eating\n", timestamp, phil->index);
	else if (status == DEAD)
		printf("%ld %ld died\n", timestamp, phil->index);
	thread_mtx(&(phil->tab->print_mutex), UNLOCK);
}

void	*handle_onephil(void *arg)
{
	t_philo	*phil;

	phil = (t_philo *)arg;
	while (!get_mtx_bool(&(phil->tab->tab_mutex), &(phil->tab->ready_to_start)))
		usleep(1);
	add_mtx_long(&(phil->tab->tab_mutex), &(phil->tab->running_threads), 1);
	set_mtx_long(&(phil->ph_mutex), &(phil->satt_time), get_time());
	report_status(phil, FORK);
	while (!get_mtx_bool(&(phil->tab->tab_mutex), &(phil->tab->ready_to_end)))
		usleep(2);
	return (NULL);
}

void	*handle_spaghetti(void *arg)
{
	t_philo	*phil;

	phil = (t_philo *)arg;
	while (!get_mtx_bool(&(phil->tab->tab_mutex), &(phil->tab->ready_to_start)))
		usleep(1);
	add_mtx_long(&(phil->tab->tab_mutex), &(phil->tab->running_threads), 1);
	set_mtx_long(&(phil->ph_mutex), &(phil->satt_time), get_time());
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
	long	i;

	tab = (t_table *)arg;
	while (!check_mtx_equalto(&(tab->tab_mutex),
			&(tab->running_threads), &(tab->num_philo)))
		usleep(1);
	while (!get_mtx_bool(&(tab->tab_mutex), &(tab->ready_to_end)))
	{
		i = 1;
		while (i <= tab->num_philo
			&& !get_mtx_bool(&(tab->tab_mutex), &(tab->ready_to_end)))
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
