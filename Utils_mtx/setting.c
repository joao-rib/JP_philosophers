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

void	subtr_mtx_long(pthread_mutex_t *mutex, long *dest, long value)
{
	thread_mtx(mutex, LOCK);
	*dest -= value;
	thread_mtx(mutex, UNLOCK);
}

void	add_mtx_long(pthread_mutex_t *mutex, long *dest, long value)
{
	thread_mtx(mutex, LOCK);
	*dest += value;
	thread_mtx(mutex, UNLOCK);
}

void	set_mtx_long(pthread_mutex_t *mutex, long *dest, long value)
{
	thread_mtx(mutex, LOCK);
	*dest = value;
	printf ("\nSet_mtx_long, Value=%ld\n\n", value); //ELIMINATE
	thread_mtx(mutex, UNLOCK);
}

void	set_mtx_bool(pthread_mutex_t *mutex, bool *dest, bool value)
{
	thread_mtx(mutex, LOCK);
	*dest = value;
	thread_mtx(mutex, UNLOCK);
}
