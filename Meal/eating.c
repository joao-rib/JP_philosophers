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

long	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		ft_error_exit("Failure with gettimeofday()");
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	start_eating(t_table *tab)
{
	t_philo	*phil_temp;
	int		i;

	i = 0;
	phil_temp = tab->phil_list;
	while (i != tab->num_philo) //WIP Será necessário função específica para apenas um filósofo
	{
		pthread_create(phil_temp->ph_thread, NULL, handle_spaghetti, phil_temp);
		phil_temp = phil_temp->right;
		i++;
	}
	pthread_create(tab->tab_thread, NULL, handle_table, tab);
	tab->starting_time = get_time();
	set_mtx_bool(&tab->tab_mutex, &tab->ready_to_start, true); //=all_thread_ready
	phil_temp = tab->phil_list;
	i = 0;
	while (i != tab->num_philo)
	{
		pthread_join(phil_temp->ph_thread, NULL);
		phil_temp = phil_temp->right;
		i++;
	}
	set_mtx_bool(&tab->tab_mutex, &tab->ready_to_end, true); //=end_simulation
	pthread_join(tab->tab_thread, NULL);
}