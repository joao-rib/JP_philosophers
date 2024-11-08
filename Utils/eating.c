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

static long int	get_time(void)
{
	struct timeval	tv;

	if(gettimeofday(&tv, NULL)) //Considerar um handle_error
		ft_error_exit("Failure with gettimeofday()");
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	start_eating(t_table *tab)
{
/*	int	i;

	i = -1;
	if (0 == table->philo_nbr)
		return ;
	else if (1 == table->philo_nbr)
		safe_thread_handle(&table->philo[0].thread_id,
			lone_philo, &table->philo[0], CREATE);
	else
		while (++i < table->philo_nbr)
			safe_thread_handle(&table->philo[i].thread_id,
				meal_simulation, &table->philo[i], CREATE);
	safe_thread_handle(&table->monitoring_thread, monitoring, table, CREATE);
	table->start_simulation = gettime(MILLISECONDS);
	set_bool(&table->table_mtx, &table->all_thread_ready, true);
	i = 0;
	while (i < table->philo_nbr)
	{
		safe_thread_handle(&table->philo[i].thread_id, NULL, NULL, JOIN);
		i++;
	}
	set_bool(&table->table_mtx, &table->end_simulation, true);
	safe_thread_handle(&table->monitoring_thread, NULL, NULL, JOIN);*/
	t_philo	*phil_temp;
	int		i;

	i = 0;
	phil_temp = tab->phil_list;
	while (i != tab->num_philo) //WIP Será necessário função específica para apenas um filósofo
	{
		pthread_create(phil_temp->ph_thread, NULL, handle_spaghetti, phil_temp); //=meal_simulation
		phil_temp = phil_temp->right;
		i++;
	}
	pthread_create(tab->tab_thread, NULL, handle_table, tab); //=monitoring
	tab->starting_time = get_time();
	//??? set_bool(&table->table_mtx, &table->all_thread_ready, true); //WIP all_thread_ready
	phil_temp = tab->phil_list;
	i = 0;
	while (i != tab->num_philo)
	{
		pthread_join(phil_temp->ph_thread, NULL);
		phil_temp = phil_temp->right;
		i++;
	}
	//??? set_bool(&table->table_mtx, &table->end_simulation, true); //WIP end_simulation
	pthread_join(tab->tab_thread, NULL);
}

/*void	set_bool(t_mtx *mutex, bool *dest, bool value)
{
	safe_mutex_handle(mutex, LOCK);
	*dest = value;
	safe_mutex_handle(mutex, UNLOCK);
}*/

//	pthread_mutex_lock(&(tab->tab_mutex));
//	pthread_mutex_unlock(&(tab->tab_mutex));

/*long	gettime(t_time_code time_code)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		exit_error("gettimeofday error");
	if (SECONDS == time_code)
		return (time.tv_sec + (time.tv_usec / 1e6));
	else if (MILLISECONDS == time_code)
		return (time.tv_sec * 1e3 + (time.tv_usec / 1e3));
	else if (MICROSECONDS == time_code)
		return (time.tv_sec * 1e6 + time.tv_usec);
	else
		exit_error("invalid time code");
	return (0);
}*/