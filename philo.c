/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2024/11/20 15:53:18 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Header/philo.h"

static void	assign_forks(t_table *tab)
{
	t_philo	*phil_buff;
	t_fork	*fork_buff;
	long	i;

	i = 1;
	phil_buff = tab->phil_list;
	fork_buff = tab->fork_list;
	while (i <= tab->num_philo)
	{
		phil_buff->l_hand = fork_buff;
		if (tab->num_philo == 1)
			break ;
		phil_buff->r_hand = fork_buff->right;
		phil_buff = phil_buff->right;
		fork_buff = fork_buff->right;
		i++;
	}
}

static void	create_fork(t_table *tab, long i)
{
	t_fork	*fork;

	fork = ft_calloc(1, sizeof(t_fork));
	if (!fork)
	{
		ft_error_msg("Memory allocation (fork)");
		clear_table(tab);
	}
	fork->index = i;
	fork->left = NULL;
	fork->right = NULL;
	if (i > 0 && i + 1 == tab->num_philo)
	{
		fork->right = tab->fork_list;
		tab->fork_list->left = fork;
	}
	thread_mtx(&(fork->fork_mutex), INITIATE);
	fork_addback(&tab->fork_list, fork);
}

static void	create_philo(t_table *tab, long i)
{
	t_philo	*philosopher;

	philosopher = ft_calloc(1, sizeof(t_philo));
	if (!philosopher)
	{
		ft_error_msg("Memory allocation (philosopher)");
		clear_table(tab);
	}
	philosopher->index = i;
	philosopher->meals = 0;
	philosopher->satt = false;
	philosopher->tab = tab;
	if (i > 1 && i == tab->num_philo)
	{
		philosopher->right = tab->phil_list;
		tab->phil_list->left = philosopher;
	}
	thread_mtx(&(philosopher->ph_mutex), INITIATE);
	phil_addback(&tab->phil_list, philosopher);
}

static void	set_table(t_table *tab)
{
	long	i;

	i = 0;
	while (i < tab->num_philo)
	{
		create_philo(tab, i + 1);
		create_fork(tab, i);
		i++;
	}
	assign_forks(tab);
	tab->running_threads = 0;
	tab->ready_to_start = false;
	tab->ready_to_end = false;
	thread_mtx(&(tab->tab_mutex), INITIATE);
	thread_mtx(&(tab->print_mutex), INITIATE);
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc != 5 && argc != 6)
		return (ft_error_msg("Four or five arguments required"));
	else if (!validate_args(argv, argc))
		return (ft_error_msg("Arguments must be numbers"));
	ft_bzero(&table, sizeof(t_table));
	table.num_philo = ft_atol(argv[1]);
	table.time_die = ft_atol(argv[2]);
	table.time_eat = ft_atol(argv[3]);
	table.time_sleep = ft_atol(argv[4]);
	table.num_meals = -1;
	if (argc == 6)
		table.num_meals = ft_atol(argv[5]);
	if (argc == 6 && table.num_meals < 0)
		return (ft_error_msg("Negative values not accepted"));
	if (!validate_numbers(&table))
		return (1);
	set_table(&table);
	if (table.num_philo == 1)
		eat_alone(&table);
	else
		start_eating(&table);
	clear_table(&table);
	return (0);
}
