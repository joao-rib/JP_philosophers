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
# include <fcntl.h>
# include <signal.h>
# include <time.h>
# include <pthread.h>
//# include <sys/types.h>
//# include <sys/wait.h>
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

typedef struct s_fork
{
	long int		index;
	bool			in_use;
	struct s_fork	*left;
	struct s_fork	*right;
}			t_fork;

typedef struct s_philo
{
	long int		index;
	bool			satt;
	pthread_t		ph_thread;
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
	bool			ready_to_start;
	bool			ready_to_end;
	pthread_t		tab_thread;
	pthread_mutex_t	tab_mutex;
}			t_table;

//Utils - Listing
t_philo	*phil_last(t_philo *lst);
void	phil_addback(t_philo **p_lst, t_philo *new);
t_fork	*fork_last(t_fork *lst);
void	fork_addback(t_fork **p_lst, t_fork *new);
//Utils - Setting
void	set_mtx_bool(pthread_mutex_t *mutex, bool *dest, bool value);
//Utils - Validating
bool	validate_args(char **av, int ac);
void	validate_numbers(t_table *tab);
//Utils - Clearing
void	clear_table(t_table *tab);

//Meal - Eating
void	start_eating(t_table *tab);
long	get_time(void);
//Meal - Handling
void	*handle_table(void *arg);
void	*handle_spaghetti(void *arg);
//Meal - Phil Actions
void	report_status(t_philo *phil, t_socas status);

#endif
