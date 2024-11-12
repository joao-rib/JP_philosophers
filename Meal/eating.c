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
	pthread_create(&(phil_temp->ph_thread), NULL, handle_onephil, phil_temp); //Considerar um handle_error;
	pthread_create(&(tab->tab_thread), NULL, handle_table, tab); //Considerar um handle_error
	tab->starting_time = get_time();
	set_mtx_bool(&tab->tab_mutex, &tab->ready_to_start, true);
	pthread_join(phil_temp->ph_thread, NULL); //Considerar um handle_error
	set_mtx_bool(&tab->tab_mutex, &tab->ready_to_end, true);
	pthread_join(tab->tab_thread, NULL); //Considerar um handle_error
}

void	start_eating(t_table *tab)
{
	t_philo	*phil_temp;
	long	i;

	i = 0;
	phil_temp = tab->phil_list;
	while (i != tab->num_philo)
	{
		pthread_create(&(phil_temp->ph_thread), NULL, handle_spaghetti, phil_temp); //Considerar um handle_error
		phil_temp = phil_temp->right;
		i++;
	}
	pthread_create(&(tab->tab_thread), NULL, handle_table, tab); //Considerar um handle_error
	tab->starting_time = get_time();
	set_mtx_bool(&tab->tab_mutex, &tab->ready_to_start, true);
	//phil_temp = tab->phil_list; //acho que já deu a volta...
	i = 0;
	while (i != tab->num_philo)
	{
		pthread_join(phil_temp->ph_thread, NULL); //Considerar um handle_error
		phil_temp = phil_temp->right;
		i++;
	}
	set_mtx_bool(&tab->tab_mutex, &tab->ready_to_end, true);
	pthread_join(tab->tab_thread, NULL); //Considerar um handle_error
}
