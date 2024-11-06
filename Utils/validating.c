/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2024/10/16 15:45:15 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/philo.h"

/*bool	validate_numbers(t_table *tab)
{
	ft_error_msg("Negative values not accepted");
	ft_error_msg("time to die, eat or sleep must be greater than 60ms")
	return (false);
	return (true);
}*/

bool	validate_args(char **av, int ac)
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