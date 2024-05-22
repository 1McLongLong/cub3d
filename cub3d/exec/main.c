/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touahman <touahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:15:52 by touahman          #+#    #+#             */
/*   Updated: 2024/05/22 17:41:20 by touahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/header.h"

void f()
{
	system("leaks cub3D");
}

int	main(int ac, char **av)
{
	atexit(f);
	t_cub3d	cub3d;

	cub3d.ea = NULL;
	cub3d.no = NULL;
	cub3d.so = NULL;
	cub3d.we = NULL;
	cub3d.map = NULL;
	if (ac != 2)
	{
		ft_puterror("one file must be provided with <.cub> extension");
	}
	start_parsing(av[1], &cub3d);
	start_gaming(&cub3d);
	free_cub(&cub3d);
}
