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

static bool	arg_check(char **av)
{
	int		i;

	i = 0;
	while (i < 4)
	{
		if (!ft_isdigit(av[i][0]))
			return (false);
		i++;
	}
	return (true);
}

int	main(int argc, char **argv)
{
	int	num_philo;
	int	time_die;
	int	time_eat;
	int	time_sleep;
	int	num_meals;

	if (argc != 5 && argc != 6)
		return (ft_error_msg("Four arguments required"));
	if (!arg_check(argv + 1))
		return (ft_error_msg("Arguments must be numbers"));
	num_philo = ft_atoi(argv[1]);
	time_die = ft_atoi(argv[2]);
	time_eat = ft_atoi(argv[3]);
	time_sleep = ft_atoi(argv[4]);
	if (argv[5])
		num_meals = ft_atoi(argv[5]);
	return (0);
}
