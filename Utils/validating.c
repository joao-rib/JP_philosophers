/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validating.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2024/11/20 17:42:19 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/philo.h"

bool	validate_numbers(t_table *tab)
{
	if (tab->time_die < 0 || tab->time_eat < 0 || tab->time_sleep < 0
		|| tab->num_philo < 0)
		ft_error_msg("Negative values not accepted");
	else if (tab->time_die < 60)
		ft_error_msg("Time to die must be greater than 60 miliseconds");
	else if (tab->time_eat < 60)
		ft_error_msg("Time to eat must be greater than 60 miliseconds");
	else if (tab->time_sleep < 60)
		ft_error_msg("Time to sleep must be greater than 60 miliseconds");
	else if (tab->num_philo == 0 || tab->num_meals == 0)
		return (false);
	else
		return (true);
	return (false);
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
			j++;
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
