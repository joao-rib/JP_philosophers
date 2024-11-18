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

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*buff;

	buff = malloc(nmemb * size);
	if (buff != NULL)
		memset(buff, 0, nmemb * size);
	return (buff);
}

int	ft_error_msg(char *str)
{
	printf("\033[1m""\033[31m""""Error: ""\033[0m""%s\n", str);
	return (1);
}

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*str;

	i = 0;
	str = (char *)s;
	while (i < n)
	{
		str[i] = '\0';
		i++;
	}
}
