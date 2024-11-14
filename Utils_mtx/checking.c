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

bool	check_mtx_equalto(pthread_mutex_t *mutex, long *val1, long *val2)
{
	bool	check;

	check = false;
	thread_mtx(mutex, LOCK);
	if (*val1 == *val2)
		check = true;
	thread_mtx(mutex, UNLOCK);
	return (check);
}
