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

/*void	start_eating(t_table *tab)
{
	t_philo	*phil_temp;
	int		i;

	i = 0;
	phil_temp = tab->phil_list;
	while (i != tab->num_philo)
	{
		//pthread_create(tab->phil_list->ph_thread, NULL, handle_spaghetti, phil_temp);
		phil_temp = phil_temp->right;
		i++;
	}
	//pthread_create(tab->tab_thread, NULL, handle_table, tab);
	return ;
}*/

void	*handle_spaghetti(t_philo *phil)
{

}

void	*handle_table(t_table *tab)
{

}