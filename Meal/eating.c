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

void	eat_alone(t_table *tab)
{
	t_philo	*phil_temp;

	phil_temp = tab->phil_list;
	thread(&(phil_temp->ph_thread), handle_onephil, phil_temp, CREATE);
	thread(&(tab->tab_thread), handle_table, tab, CREATE);
	tab->starting_time = get_time();
	set_mtx_bool(&tab->tab_mutex, &tab->ready_to_start, true);
	thread(&(phil_temp->ph_thread), NULL, NULL, JOIN);
	set_mtx_bool(&tab->tab_mutex, &tab->ready_to_end, true);
	thread(&(tab->tab_thread), NULL, NULL, JOIN);
}

void	start_eating(t_table *tab)
{
	t_philo	*phil_temp;
	long	i;

	i = 0;
	phil_temp = tab->phil_list;
	tab->starting_time = get_time();
	while (i != tab->num_philo)
	{
		phil_temp->satt_time = tab->starting_time;
		thread(&(phil_temp->ph_thread), handle_spaghetti, phil_temp, CREATE);
		phil_temp = phil_temp->right;
		i++;
	}
	thread(&(tab->tab_thread), handle_table, tab, CREATE);
	set_mtx_bool(&tab->tab_mutex, &tab->ready_to_start, true);
	//phil_temp = tab->phil_list; //acho que já deu a volta...
	i = 0;
	while (i != tab->num_philo)
	{
		thread(&(phil_temp->ph_thread), NULL, NULL, JOIN);
		phil_temp = phil_temp->right;
		i++;
	}
	set_mtx_bool(&tab->tab_mutex, &tab->ready_to_end, true);
	thread(&(tab->tab_thread), NULL, NULL, JOIN);
}
