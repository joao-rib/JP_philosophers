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

t_fork	*fork_last(t_fork *lst)
{
	t_fork	*ult;

	if (!lst)
		return (NULL);
	ult = lst;
	while (ult->right != NULL && (ult->index < ult->right->index))
		ult = ult->right;
	return (ult);
}

void	fork_addback(t_fork **lst, t_fork *new)
{
	t_fork	*ultimo;

	if (lst && new)
	{
		if (*lst)
		{
			ultimo = fork_last(*lst);
			ultimo->right = new;
			new->left = ultimo;
		}
		else
			*lst = new;
	}
}

t_philo	*phil_last(t_philo *lst)
{
	t_philo	*ult;

	if (!lst)
		return (NULL);
	ult = lst;
	while (ult->right != NULL && (ult->index < ult->right->index))
		ult = ult->right;
	return (ult);
}

void	phil_addback(t_philo **lst, t_philo *new)
{
	t_philo	*ultimo;

	if (lst && new)
	{
		if (*lst)
		{
			ultimo = phil_last(*lst);
			ultimo->right = new;
			new->left = ultimo;
		}
		else
			*lst = new;
	}
}
