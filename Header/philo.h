/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2024/11/06 20:07:17 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <fcntl.h>
# include <signal.h>
# include <time.h>
# include <pthread.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/time.h>
# include "../libft/libft.h"

typedef struct s_table	t_table;

typedef enum e_socas
{
	FORK,
	EAT,
	SLEEP,
	THINK,
	DEAD,
}	t_socas;

typedef enum e_thraction
{
	INITIATE,
	DESTROY,
	LOCK,
	UNLOCK,
	CREATE,
	JOIN,
	DETACH,
}	t_thraction;

typedef struct s_fork
{
	long int		index;
	pthread_mutex_t	fork_mutex;
	struct s_fork	*left;
	struct s_fork	*right;
}			t_fork;

typedef struct s_philo
{
	long int		index;
	long int		meals;
	long int		satt_time;
	bool			satt;
	pthread_t		ph_thread;
	pthread_mutex_t	ph_mutex;
	struct s_fork	*l_hand;
	struct s_fork	*r_hand;
	struct s_philo	*left;
	struct s_philo	*right;
	struct s_table	*tab;
}			t_philo;

typedef struct s_table
{
	struct s_philo	*phil_list;
	struct s_fork	*fork_list;
	long int		num_philo;
	long int		time_die;
	long int		time_eat;
	long int		time_sleep;
	long int		num_meals;
	long int		starting_time;
	long int		running_threads;
	bool			ready_to_start;
	bool			ready_to_end;
	pthread_t		tab_thread;
	pthread_mutex_t	tab_mutex;
}			t_table;

//Utils - Listing
t_philo	*phil_last(t_philo *lst);
void	phil_addback(t_philo **p_lst, t_philo *new);
t_philo	*find_phil(t_philo *lst, long index);
t_fork	*fork_last(t_fork *lst);
void	fork_addback(t_fork **p_lst, t_fork *new);
//Utils - Validating
bool	validate_args(char **av, int ac);
void	validate_numbers(t_table *tab);
//Utils - Clearing
void	clear_table(t_table *tab);

//Utils (mtx) - Setting
void	set_mtx_bool(pthread_mutex_t *mutex, bool *dest, bool value);
void	set_mtx_long(pthread_mutex_t *mutex, long *dest, long value);
void	add_mtx_long(pthread_mutex_t *mutex, long *dest, long value);
void	subtr_mtx_long(pthread_mutex_t *mutex, long *dest, long value);
//Utils (mtx) - Getting
bool	get_mtx_bool(pthread_mutex_t *mutex, bool *dest);
long	get_mtx_long(pthread_mutex_t *mutex, long *dest);
long	get_time(void);
//Utils (mtx) - Checking
bool	check_mtx_equalto(pthread_mutex_t *mutex, long val1, long val2);
//Utils (mtx) - Threading
void	thread_mtx(pthread_mutex_t *mutex, t_thraction action);
void	thread(pthread_t *thread, void *(*handle_action)(void *),
				void *arg, t_thraction action);

//Meal - Eating
void	start_eating(t_table *tab);
void	eat_alone(t_table *tab);
//Meal - Handling
void	*handle_table(void *arg);
void	*handle_spaghetti(void *arg);
void	*handle_onephil(void *arg);
//Meal - Phil Actions
void	report_status(t_philo *phil, t_socas status);
void	phil_eat(t_philo *phil);
void	phil_sleep(t_philo *phil);
void	phil_think(t_philo *phil);
bool	phil_die(t_philo *phil);

#endif

/*Function              | Common Error Codes          | Description
----------------------|-----------------------------|-----------------------------------------------------------
pthread_mutex_init    | EINVAL, EAGAIN, ENOMEM      | Invalid attributes, resource limits, or memory shortage for
                      |                             | mutex initialization.
----------------------|-----------------------------|-----------------------------------------------------------
pthread_mutex_destroy | EBUSY, EINVAL               | Mutex is in use or not properly initialized.
----------------------|-----------------------------|-----------------------------------------------------------
pthread_mutex_lock    | EINVAL, EDEADLK, EAGAIN     | Invalid mutex, potential deadlock, or recursion limit
                      |                             | exceeded.
----------------------|-----------------------------|-----------------------------------------------------------
pthread_mutex_unlock  | EINVAL, EPERM               | Invalid mutex or unlocking by a non-owner thread.
----------------------|-----------------------------|-----------------------------------------------------------
pthread_join          | EINVAL, ESRCH, EDEADLK      | Invalid or detached thread, thread not found, or deadlock
                      |                             | if joining self.
----------------------|-----------------------------|-----------------------------------------------------------
pthread_detach        | EINVAL, ESRCH               | Invalid or nonexistent thread.
----------------------|-----------------------------|-----------------------------------------------------------
pthread_create        | EAGAIN, EINVAL, EPERM       | Resource limits, invalid attributes, or insufficient
                      |                             | permissions.
*/
