/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eescalei <eescalei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 14:09:30 by eescalei          #+#    #+#             */
/*   Updated: 2024/06/25 19:48:23 by eescalei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

/* 1 mili = 1000 micro */

int	main(int ac, char **av)
{
	t_table	table;

	if (5 == ac || 6 == ac)
	{
		parsing_input(&table, av);
		innit_struct(&table);
		meal_start(&table);
		clean(&table);
	}
	else
		printf("Wrong input\n");
	return (0);
}
