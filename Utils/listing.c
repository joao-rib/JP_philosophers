/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2024/11/20 16:52:31 by joao-rib         ###   ########.fr       */
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

t_philo	*find_phil(t_philo *lst, long index)
{
	t_philo	*buff;

	if (!lst)
		return (NULL);
	buff = lst;
	if (buff->index == index)
		return (buff);
	else
		buff = buff->right;
	while (buff->right != NULL && (buff->index > buff->left->index))
	{
		if (buff->index == index)
			break ;
		buff = buff->right;
	}
	return (buff);
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
