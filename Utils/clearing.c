/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2024/10/16 15:45:15 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/philo.h"

static void	fork_clear(t_fork **lst, int size)
{
	t_fork	*buff;
	int		i;

	i = 0;
	if (lst)
	{
		while (i < size)
		{
			buff = (*lst)->right;
			free(*lst);
			*lst = buff;
			i++;
		}
	}
}

static void	phil_clear(t_philo **lst, int size)
{
	t_philo	*buff;
	int		i;

	i = 0;
	if (lst)
	{
		while (i < size)
		{
			buff = (*lst)->right;
			free(*lst);
			*lst = buff;
			i++;
		}
	}
}

void	clear_table(t_table *tab)
{
	if (tab->phil_list)
		phil_clear(&(tab->phil_list), tab->num_philo);
	if (tab->fork_list)
		fork_clear(&(tab->fork_list), tab->num_philo);
}
