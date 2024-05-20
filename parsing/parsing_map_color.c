/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_color.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouabid <sbouabid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:39:27 by sbouabid          #+#    #+#             */
/*   Updated: 2024/05/16 18:03:48 by sbouabid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/header.h"

int	convert_and_check_range(char **color_values, int *color)
{
	int	r;
	int	g;
	int	b;

	r = ft_atoi(color_values[0]);
	g = ft_atoi(color_values[1]);
	b = ft_atoi(color_values[2]);
	// ft_split_free(color_values);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		ft_puterror("check_c_var::invalid color");
	*color = (r << 16) + (g << 8) + b;
	return (0);
}


int	pars_color(char	*line, t_temp *temp)
{
	char	**new;
	int		color;
	char	*temper;

	temp->i = 0;
	temp->j = 0;
	while (line[temp->i])
	{
		if (line[temp->i] == ',')
			temp->j += 1;
		temp->i += 1;
	}
	if (temp->j != 2)
		ft_puterror("check_c_var::invalid color");
	temper = ft_strtrim(line, "\n");
	new = ft_split(temper, ',');
	if (!new)
		return 0;
	convert_and_check_range(new, &color);
	free(temper);
	return (color);
}
