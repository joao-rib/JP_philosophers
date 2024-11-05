/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2024/10/16 15:44:34 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Header/philo.h"

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
			return (ft_error_exit("Arguments must be numbers"));
	}
	else
		return (ft_error_exit("Four or five arguments required"));

	table.num_philo = ft_atoi(argv[1]);
	table.time_die = ft_atoi(argv[2]);
	table.time_eat = ft_atoi(argv[3]);
	table.time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		table.num_meals = ft_atoi(argv[5]);
	return (0);
}
