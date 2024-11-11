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

long	get_mtx_long(pthread_mutex_t *mutex, long *dest)
{
	bool	value;

	pthread_mutex_lock(mutex); //Considerar um handle_error
	value = *dest;
	pthread_mutex_unlock(mutex); //Considerar um handle_error
	return (value);
}

bool	get_mtx_bool(pthread_mutex_t *mutex, bool *dest)
{
	bool	value;

	pthread_mutex_lock(mutex); //Considerar um handle_error
	value = *dest;
	pthread_mutex_unlock(mutex); //Considerar um handle_error
	return (value);
}

long	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		ft_error_exit("Failure with gettimeofday()");
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
