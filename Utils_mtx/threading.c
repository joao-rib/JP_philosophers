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

static void	handle_mtx_error(int mtx_return)
{
	if (mtx_return == 0)
		return ;
	else if (mtx_return == EINVAL)
		ft_error_msg("Invalid Mutex (EINVAL)");
	else if (mtx_return == EAGAIN)
		ft_error_msg("Mutex recursion limit (EAGAIN)");
	else if (mtx_return == ENOMEM)
		ft_error_msg("Mutex memory issue (ENOMEM)");
	else if (mtx_return == EDEADLK)
		ft_error_msg("Mutex deadlock (EDEADLK)");
	else if (mtx_return == EBUSY)
		ft_error_msg("Destroying mutex in use (EBUSY)");
	else if (mtx_return == EPERM)
		ft_error_msg("Mutex permission issues (EPERM)");
	else
		ft_error_msg("Unknown Mutex error");
}

void	thread_mtx(pthread_mutex_t *mutex, t_thraction action)
{
	if (action == LOCK)
		handle_mtx_error(pthread_mutex_lock(mutex));
	else if (action == UNLOCK)
		handle_mtx_error(pthread_mutex_unlock(mutex));
	else if (action == INITIATE)
		handle_mtx_error(pthread_mutex_init(mutex, NULL));
	else if (action == DESTROY)
		handle_mtx_error(pthread_mutex_destroy(mutex));
	else
		ft_error_msg("Unknown Mutex action");
}

static void	handle_thread_error(int thread_return)
{
	if (thread_return == 0)
		return ;
	else if (thread_return == EINVAL)
		ft_error_msg("Invalid thread (EINVAL)");
	else if (thread_return == EAGAIN)
		ft_error_msg("Thread recursion limit (EAGAIN)");
	else if (thread_return == ESRCH)
		ft_error_msg("Non-existent thread (ESRCH)");
	else if (thread_return == EDEADLK)
		ft_error_msg("Thread deadlock (EDEADLK)");
	else if (thread_return == EPERM)
		ft_error_msg("Thread permission issues (EPERM)");
	else
		ft_error_msg("Unknown thread error");
}

void	thread(pthread_t *thread, void *(*handle_action)(void *),
				void *arg, t_thraction action)
{
	if (action == CREATE)
		handle_thread_error(pthread_create(thread, NULL, handle_action, arg));
	else if (action == JOIN)
		handle_thread_error(pthread_join(*thread, NULL));
	else if (action == DETACH)
		handle_thread_error(pthread_detach(*thread));
	else
		ft_error_msg("Unknown Thread action");
}
