/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validating.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2024/11/15 10:30:40 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/philo.h"

void	validate_numbers(t_table *tab)
{
	if (tab->time_die < 60)
		ft_error_exit("Time to die must be greater than 60 miliseconds");
	if (tab->time_eat < 60)
		ft_error_exit("Time to eat must be greater than 60 miliseconds");
	if (tab->time_sleep < 60)
		ft_error_exit("Time to sleep must be greater than 60 miliseconds");
	if (tab->num_philo == 0)
		exit(0);
}

bool	validate_args(char **av, int ac)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		while (ft_isdelim(av[i][j]))
			j++;
		if (av[i][j] == '-')
			ft_error_exit("Negative values not accepted");
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
