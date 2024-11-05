/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2024/11/05 13:02:46 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <fcntl.h>
# include <signal.h>
# include <time.h>
//# include <readline/readline.h>
//# include <readline/history.h>
//# include <sys/types.h>
//# include <sys/wait.h>
# include "../libft/libft.h"

typedef enum e_socas
{
	EAT,
	SLEEP,
	THINK,
	DEAD,
}	t_socas;

typedef struct s_fork
{
	int				index;
	bool			in_use;
	struct s_fork	*next;
}			t_fork;

typedef struct s_philo
{
	int				index;
	enum e_socas	state;
	struct s_fork	*l_hand;
	struct s_fork	*r_hand;
	struct s_philo	left;
	struct s_philo	right;
}			t_philo;

typedef struct s_table
{
	struct s_philo	*phil_list;
	struct s_fork	*fork_list;
	int				num_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				num_meals;
}			t_table;

//Utils - Initialising
int		testin(void);

#endif
