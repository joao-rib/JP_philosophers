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

/*void	precise_usleep(long usec, t_table *table)
{
	long	start;
	long	elapsed;
	long	rem;

	start = gettime(MICROSECONDS);
	while (gettime(MICROSECONDS) - start < usec)
	{
		if (simulation_finished(table))
			break ;
		elapsed = gettime(MICROSECONDS) - start;
		rem = usec - elapsed;
		if (rem > 1e3)
			usleep(rem / 2);
		else
			while (gettime(MICROSECONDS) - start < usec)
				;
	}
}*/

void	report_status(t_philo *phil, t_socas status)
{
	long	timestamp;

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

void	phil_eat(t_philo *phil)
{
	thread_mtx(&(phil->l_hand->fork_mutex), LOCK);
	report_status(phil, FORK);
	thread_mtx(&(phil->r_hand->fork_mutex), LOCK);
	report_status(phil, FORK);
	set_mtx_long(&(phil->ph_mutex), &(phil->satt_time), get_time());
	phil->meals++;
	report_status(phil, EAT);
	usleep(phil->tab->time_eat * 1000);
	if (phil->tab->num_meals >= 0 && phil->meals == phil->tab->num_meals)
		set_mtx_bool(&(phil->ph_mutex), &(phil->satt), true);
	thread_mtx(&(phil->l_hand->fork_mutex), UNLOCK);
	thread_mtx(&(phil->r_hand->fork_mutex), UNLOCK);
}

void	phil_sleep(t_philo *phil)
{
	report_status(phil, SLEEP);
	usleep(phil->tab->time_sleep * 1000);
}

void	phil_think(t_philo *phil)
{
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
