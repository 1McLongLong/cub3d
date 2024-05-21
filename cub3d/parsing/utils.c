/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouabid <sbouabid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:41:38 by sbouabid          #+#    #+#             */
/*   Updated: 2024/05/16 16:23:12 by sbouabid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/header.h"

void	free_arr(char **values)
{
	int	i;

	i = 0;
	while (values[i])
	{
		free(values[i]);
		i++;
	}
	free(values);
}

void	ft_puterror(char *msg)
{
	int	i;

	i = 0;
	write(1, "Error\n", 7);
	while (msg[i])
	{
		write(2, &msg[i], 1);
		i++;
	}
	write(1, "\n", 1);
	exit(1);
}

int	size_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		i++;
	}
	return (i);
}
