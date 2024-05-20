/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouabid <sbouabid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:04:01 by sbouabid          #+#    #+#             */
/*   Updated: 2024/05/18 17:58:18 by sbouabid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/header.h"

void	start_parsing(char *name_file, t_cub3d *cub3d)
{
	int		fd;
	char	*line;
	t_temp	temp;
	t_map	*map;

	map = NULL;
	ft_memset(&temp, 0, sizeof(temp));
	check_map_name(name_file);
	fd = open(name_file, O_RDONLY);
	if (fd == -1)
		ft_puterror("one file must be provided with <.cub> extension");
	line = get_next_line(fd);
	while (line)
	{
		if (parsing_map_values(line, &temp, cub3d) == 1)
			full_map(line, &map, &temp);
		free(line);
		line = get_next_line(fd);
	}
	if (temp.find_map == 0)
		ft_puterror("check_for_vars::vars missing in the file");
	draw_map(cub3d, map);
	check_if_valid_map(cub3d);
}
