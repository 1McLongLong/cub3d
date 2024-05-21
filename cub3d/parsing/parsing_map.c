/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouabid <sbouabid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 17:58:42 by sbouabid          #+#    #+#             */
/*   Updated: 2024/05/19 11:27:26 by sbouabid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/header.h"

void	check_first_and_last(t_cub3d *cub)
{
	int	i;
	int	j;

	i = 0;
	while (cub->map[0][i])
	{
		if (cub->map[0][i] != ' ' && cub->map[0][i] != '1')
			ft_puterror("check_for_map::invalid map");
		i++;
	}
	j = size_arr(cub->map);
	i = 0;
	while (cub->map[j - 1][i])
	{
		if (cub->map[j - 1][i] != ' ' && cub->map[j - 1][i] != '1')
			ft_puterror("check_for_map::invalid map");
		i++;
	}
}

void	check_player(char **map)
{
	t_temp	temp;

	ft_memset(&temp, 0, sizeof(t_temp));
	while (map[temp.i])
	{
		temp.j = 0;
		while (map[temp.i][temp.j])
		{
			if (map[temp.i][temp.j] == 'N')
				temp.N += 1;
			else if (map[temp.i][temp.j] == 'S')
				temp.S += 1;
			else if (map[temp.i][temp.j] == 'E')
				temp.E += 1;
			else if (map[temp.i][temp.j] == 'W')
				temp.W += 1;
			temp.j++;
		}
		temp.i++;
	}
	if (temp.N > 1 || temp.S > 1 || temp.E > 1 || temp.W > 1)
		ft_puterror("check_for_map::invalid map");
	if (temp.N == 1 && (temp.S == 1 || temp.E == 1 || temp.W == 1))
		ft_puterror("check_for_map::invalid map");
	if (temp.S == 1 && (temp.E == 1 || temp.E == 1 || temp.N == 1))
		ft_puterror("check_for_map::invalid map");
	if (temp.E == 1 && (temp.S == 1 || temp.N == 1 || temp.W == 1))
		ft_puterror("check_for_map::invalid map");
	if (temp.W == 1 && (temp.S == 1 || temp.N == 1 || temp.E == 1))
		ft_puterror("check_for_map::invalid map");
	if (temp.W == 0 && temp.S == 0 && temp.N == 0 && temp.E == 0)
		ft_puterror("check_for_map::invalid map need a player");
}

void	check_if_valid_map(t_cub3d *cub)
{
	int	i;
	int	j;
	int	valid;

	if (size_arr(cub->map) < 3)
		ft_puterror("check_for_map::invalid map");
	check_player(cub->map);
	check_first_and_last(cub);
	i = 1;
	while (cub->map[i + 1] != NULL)
	{
		j = 0;
		valid = 1;
		while (cub->map[i][j])
		{
			if (cub->map[i][j] == ' ' || cub->map[i][j] == '1')
				j++;
			else
			{
				if (j > 0 && (cub->map[i][j - 1] == ' ' || cub->map[i][j + 1] == '\0'))
					valid = 0;
				if (j == 0 && cub->map[i][j + 1] == '\0')
					valid = 0;
				if (cub->map[i + 1][j] == ' ' || cub->map[i - 1][j] == ' ' || cub->map[i + 1][j] == '\0' || cub->map[i - 1][j] == '\0'  )
					valid = 0;
				if (!valid)
					ft_puterror("check_for_map::invalid map");
				j++;
			}
		}
		i++;
	}
}
