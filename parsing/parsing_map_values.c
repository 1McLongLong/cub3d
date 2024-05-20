/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_values.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouabid <sbouabid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:17:59 by sbouabid          #+#    #+#             */
/*   Updated: 2024/05/19 11:11:48 by sbouabid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/header.h"

void	draw_map(t_cub3d *cub, t_map *map)
{
	int	i;
	int	size;

	i = 0;
	size = list_size(map);
	cub->map = malloc((size + 1) * sizeof(char *));
	if (!cub->map)
		return ;
	while (i < size && map != NULL)
	{
		cub->map[i] = ft_strtrim(map->line, "\n");
		map = map->next;
		i++;
	}
	cub->map[i] = NULL;
}

int	check_if_empty(char	*line)
{
	int	i;

	i = 0;
	while (line[i] != '\0' && (line[i] == ' ' || line[i] == '\n'))
	{
		i++;
	}
	if (line[i] == '\0')
	{
		return (1);
	}
	return (0);
}

int	check_if_valid(char	*line, t_temp *temp)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != '0' && line[i] != ' ' && line[i] != 'N' && line[i] != 'S' && line[i] != 'E' && line[i] != 'W' && line[i] != '\n')
			return (1);
		if ((line[i] == '1' || line[i] == '0' || line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W') && temp->find_new_line == 1)
			return (1);
		i++;
	}
	if (check_if_empty(line))
		temp->find_new_line = 1;
	return (0);
}

void	full_map(char *line, t_map **map, t_temp *temp)
{
	if (temp->C != 1 || temp->EA != 1 || temp->F != 1 || temp->NO != 1 || temp ->SO != 1 || temp->WE != 1)
		ft_puterror("check_for_vars::vars missing in the file");
	if (check_if_valid(line, temp) == 1)
		ft_puterror("check_for_map::invalid map");
	if(check_if_empty(line) == 0)
		list_add(map, list_create(line));
}

int	parsing_map_values(char *line, t_temp *temp, t_cub3d *cub3d)
{
	char	**new;


	if (line[0] == '\n' && temp->find_map == 1)
		return (1);
	if (line[0] == '\n')
		return (0);
	if (temp->find_map == 1)
		return (1);
	new = ft_split(line, ' ');
	if (new == NULL)
		return 0;
	if (size_arr(new) != 2 && new[0][0] != '1')
	{
		free_arr(new);
		ft_puterror("check_for_map::invalid map");
	}
	if (ft_strcmp(new[0], "NO") == 0)
	{
		temp->NO += 1;
		cub3d->NO = ft_strtrim(new[1], "\n");
	}
	else if (ft_strcmp(new[0], "SO") == 0)
	{
		temp->SO += 1;
		cub3d->SO = ft_strtrim(new[1], "\n");
	}
	else if (ft_strcmp(new[0], "WE") == 0)
	{
		temp->WE += 1;
		cub3d->WE = ft_strtrim(new[1], "\n");
	}
	else if (ft_strcmp(new[0], "EA") == 0)
	{
		temp->EA += 1;
		cub3d->EA = ft_strtrim(new[1], "\n");
	}
	else if (ft_strcmp(new[0], "F") == 0)
	{
		temp->F += 1;
		cub3d->F = pars_color(new[1], temp);
	}
	else if (ft_strcmp(new[0], "C") == 0)
	{
		temp->C += 1;
		cub3d->C = pars_color(new[1], temp);
	}
	else if (new[0][0] == '1')
		temp->find_map = 1;
	free_arr(new);
	return (temp->find_map);
}
