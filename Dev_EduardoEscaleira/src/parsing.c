/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eescalei <eescalei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:02:01 by eescalei          #+#    #+#             */
/*   Updated: 2024/06/25 19:44:21 by eescalei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	valid_input(const char *str)
{
	int	res;
	int	i;

	i = 0;
	res = 0;
	while ((*str >= 13 && *str <= 9) || *str == ' ' || *str == '\0')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
		{
			printf("negative values not acepted");
			return (-1);
		}
		str++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (str[i] - '0') + (res * 10);
		i++;
		if (i >= 10)
			return (-1);
	}
	return (res);
}

int	parsing_input(t_table *table, char **av)
{
	table->philo_nbr = valid_input(av[1]);
	table->time_to_die = valid_input(av[2]) * 1e3;
	table->time_to_eat = valid_input(av[3]) * 1e3;
	table->time_to_sleep = valid_input(av[4]) * 1e3;
	table->nbr_limit_meals = -1;
	if (NULL != av[5])
		table->nbr_limit_meals = valid_input(av[5]);
	if (table->time_to_die < 6e4 || table->time_to_eat < 6e4
		|| table->time_to_sleep < 6e4)
	{
		printf("time to die, eat or sleep must be greater than 60ms");
		return (-1);
	}
	return (0);
}
