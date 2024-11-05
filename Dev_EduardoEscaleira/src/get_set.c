/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eescalei <eescalei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:09:44 by eescalei          #+#    #+#             */
/*   Updated: 2024/06/25 13:15:46 by eescalei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	set_bool(t_mtx *mutex, bool *dest, bool value)
{
	safe_mutex_handle(mutex, LOCK);
	*dest = value;
	safe_mutex_handle(mutex, UNLOCK);
}

bool	get_bool(t_mtx *mutex, bool *src)
{
	bool	value;

	safe_mutex_handle(mutex, LOCK);
	value = *src;
	safe_mutex_handle(mutex, UNLOCK);
	return (value);
}

long	get_long(t_mtx *mutex, long int *src)
{
	long int	value;

	safe_mutex_handle(mutex, LOCK);
	value = *src;
	safe_mutex_handle(mutex, UNLOCK);
	return (value);
}

void	set_long(t_mtx *mutex, long int *dest, long int value)
{
	safe_mutex_handle(mutex, LOCK);
	*dest = value;
	safe_mutex_handle(mutex, UNLOCK);
}

bool	simulation_finished(t_table *table)
{
	return (get_bool(&table->table_mtx, &table->end_simulation));
}
