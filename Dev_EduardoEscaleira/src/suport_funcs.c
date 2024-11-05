/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suport_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eescalei <eescalei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:27:31 by eescalei          #+#    #+#             */
/*   Updated: 2024/06/25 13:14:34 by eescalei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	*safe_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		exit_error("malloc error");
	return (ptr);
}

void	handle_mutex_error(int status, t_opcode opcode)
{
	if (0 == status)
		return ;
	if (EINVAL == status && (LOCK == opcode || UNLOCK == opcode))
		exit_error("The value specified by mutex is invalid");
	else if (EINVAL == status && INIT == opcode)
		exit_error("The value specified by attr is invalid");
	else if (EDEADLK == status)
		exit_error("A deadlock condition would occur if the \
				thread blocked waiting for mutex");
	else if (EPERM == status)
		exit_error("The current thread does not hold on mutex");
	else if (ENOMEM == status)
		exit_error("The process cannot allocate enough memory to \
				create another mutex");
	else if (EBUSY == status)
		exit_error("The mutex is locked");
}

void	safe_mutex_handle(t_mtx *mutex, t_opcode opcode)
{
	if (LOCK == opcode)
		handle_mutex_error(pthread_mutex_lock(mutex), opcode);
	else if (UNLOCK == opcode)
		handle_mutex_error(pthread_mutex_unlock(mutex), opcode);
	else if (INIT == opcode)
		handle_mutex_error(pthread_mutex_init(mutex, NULL), opcode);
	else if (DESTROY == opcode)
		handle_mutex_error(pthread_mutex_destroy(mutex), opcode);
	else
		exit_error("invalid mutex opcode");
}

void	handle_thread_error(int status, t_opcode opcode)
{
	if (0 == status)
		return ;
	if (EAGAIN == status)
		exit_error("No resources to create another thread");
	else if (EPERM == status)
		exit_error("The caller does not have appropriate permission");
	else if (EINVAL == status && CREATE == opcode)
		exit_error("The value specified by attr is invalid");
	else if (EINVAL == status && (JOIN == opcode || DETACH == opcode))
		exit_error("The value specified by thread is not a joinable thread");
	else if (ESRCH == status)
		exit_error("No thread could be found corresponding to that \
				specified by the given thread ID");
	else if (EDEADLK == status)
		exit_error("A deadlock was detected or the value of thread \
				specifies the calling thread");
}

void	safe_thread_handle(pthread_t *thread,
		void *(*start_routine)(void *), void *arg, t_opcode opcode)
{
	if (CREATE == opcode)
		handle_mutex_error(pthread_create(thread, NULL,
				start_routine, arg), opcode);
	else if (JOIN == opcode)
		handle_mutex_error(pthread_join(*thread, NULL), opcode);
	else if (DETACH == opcode)
		handle_mutex_error(pthread_detach(*thread), opcode);
	else
		exit_error("Wrong opcode for thread_handle");
}
