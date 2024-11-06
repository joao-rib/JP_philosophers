/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2024/11/05 13:05:13 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Header/philo.h"

static void	create_fork(t_table *tab, int i)
{
	t_fork	*fork;

	fork = ft_calloc(1, sizeof(t_fork));
	if (!fork)
		ft_error_exit("Memory allocation (fork)");
	fork->index = i;
	fork->in_use = false;
	fork->left = NULL;
	fork->right = NULL;
	if (i + 1 == tab->num_philo)
	{
		fork->right = tab->fork_list;
		tab->fork_list->left = fork;
	}
	fork_addback(tab, fork);
}

static void	create_philo(t_table *tab, int i)
{
	t_philo	*philosopher;

	philosopher = ft_calloc(1, sizeof(t_philo));
	if (!philosopher)
		ft_error_exit("Memory allocation (philosopher)");
	philosopher->index = i;
	philosopher->l_hand = NULL;
	philosopher->r_hand = NULL;
	philosopher->state = THINK;
	if (i + 1 == tab->num_philo)
	{
		philosopher->right = tab->phil_list;
		tab->phil_list->left = philosopher;
	}
	phil_addback(&tab->phil_list, philosopher);
}

static void	set_table(t_table *tab)
{
	int	i;

	i = 0;
	while (i < tab->num_philo)
	{
		create_philo(tab, i);
		create_fork(tab, i);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc != 5 && argc != 6)
		ft_error_exit("Four or five arguments required");
	else if (!validate_args(argv, argc))
		ft_error_exit("Arguments must be numbers");
	ft_bzero(&table, sizeof(t_table));
	table.num_philo = ft_atoi(argv[1]);
	table.time_die = ft_atoi(argv[2]);
	table.time_eat = ft_atoi(argv[3]);
	table.time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		table.num_meals = ft_atoi(argv[5]);
	//if (!validate_numbers(&table))
	//	return (0);
	set_table(&table);
	//start_eating(&table);
	clear_table(&table);
	return (0);
}
