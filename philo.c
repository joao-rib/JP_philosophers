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

static void	set_table(t_table *tab)
{
/*	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		ft_error_msg("Error while creating token");
	token->token = ft_strdup(symbol);
	if (!token->token)
		ft_error_msg("Error while saving token");
	token->type = type;
	token->next = NULL;
	token->to_merge = merge;
	if (!merge)
		ms->aux_merge = false;
	tklst_addback(&ms->tk_list, token);*/
	t_philo	*philosopher;
	t_fork	*fork;
	int		i;

	i = 0;
	while (i < tab->num_philo)
	{
		philosopher = ft_calloc(1, sizeof(t_philo));
		//Add error case
		philosopher->index = i;
		philosopher->l_hand = NULL;
		philosopher->r_hand = NULL;
		philosopher->state = THINK;
		//addback(tab->phil_list, philosopher);
		fork = ft_calloc(1, sizeof(t_fork));
		//Add error case
		fork->index = i;
		fork->in_use = false;
		//addback(tab->fork_list, fork);
		i++;
	}
}

static bool	arg_check(char **av, int ac)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j]))
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc == 5 || argc == 6)
	{
		if (!arg_check(argv, argc))
			ft_error_exit("Arguments must be numbers");
	}
	else
		ft_error_exit("Four or five arguments required");
	ft_bzero(&table, sizeof(t_table));
	table.num_philo = ft_atoi(argv[1]);
	table.time_die = ft_atoi(argv[2]);
	table.time_eat = ft_atoi(argv[3]);
	table.time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		table.num_meals = ft_atoi(argv[5]);
	set_table(&table);
	return (0);
}
