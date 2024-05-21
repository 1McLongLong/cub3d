#include "../include/header.h"

void	rotate_player(t_mlx *mlx, int i)
{
	if (i == 1)
	{
		mlx->player->angle += ROTATION_SPEED;
		if (mlx->player->angle > 2 * M_PI)
			mlx->player->angle -= 2 * M_PI;
	}
	else
	{
		mlx->player->angle -= ROTATION_SPEED;
		if (mlx->player->angle < 0)
			mlx->player->angle += 2 * M_PI;
	}
}

void	change_playerxy(t_mlx *mlx, double move_x, double move_y)
{
	int		map_grid_y;
	int		map_grid_x;
	int		new_x;
	int		new_y;

	new_x = roundf(mlx->player->plyr_x + move_x);
	new_y = roundf(mlx->player->plyr_y + move_y);
	map_grid_x = floor(new_x / TILE_SIZE);
	map_grid_y = floor(new_y / TILE_SIZE);
	// if (mlx->cub3d->map[map_grid_y][map_grid_x] != '1'
	// && (mlx->cub3d->map[map_grid_y][mlx->player->plyr_x / TILE_SIZE] != '1' && 
	// mlx->cub3d->map[mlx->player->plyr_y / TILE_SIZE][map_grid_x] != '1'))
	
	// printf("%p\n", &mlx->cub3d->map[map_grid_x][map_grid_y]);
	// if (map_grid_x > 0 && map_grid_x < S_W && map_grid_y > 0 && map_grid_y < S_H && mlx->cub3d->map[map_grid_x][map_grid_y] != '1')
	// {
	// printf("%d %d\n", map_grid_x, map_grid_y);
	if ((map_grid_y > 0 && map_grid_y < (mlx->cub3d->map_rows)) && (map_grid_x > 0 && map_grid_x < (int)ft_strlen(mlx->cub3d->map[map_grid_y])) && mlx->cub3d->map[map_grid_y][map_grid_x] != '1' \
		&& mlx->cub3d->map[mlx->player->plyr_y / TILE_SIZE ][map_grid_x] != '1' && mlx->cub3d->map[map_grid_y][mlx->player->plyr_x / TILE_SIZE] != '1')
	// if (map_grid_x > 0 && map_grid_x < (mlx->cub3d->map_rows)  &&map_grid_y > 0 && map_grid_y < (int)ft_strlen(mlx->cub3d->map[map_grid_x]) &&  mlx->cub3d->map[map_grid_x][map_grid_y] != '1'\
	// 	&& mlx->cub3d->map[mlx->player->plyr_x / TILE_SIZE][map_grid_y] != '1' && mlx->cub3d->map[map_grid_x][mlx->player->plyr_y / TILE_SIZE] != '1')
	{
		mlx->player->plyr_y = new_y;
		mlx->player->plyr_x = new_x;
	}
	// }
}

void	move_player(t_mlx *mlx, double move_x, double move_y)
{
	if (mlx->player->rot == 1) //rotate right
		rotate_player(mlx, 1);
	if (mlx->player->rot == -1) //rotate left
		rotate_player(mlx, 0);
	if (mlx->player->l_r == 1) //move right
	{
		move_x = -sin(mlx->player->angle) * PLAYER_SPEED;
		move_y = cos(mlx->player->angle) * PLAYER_SPEED;
	}
	if (mlx->player->l_r == -1) //move left
	{
		move_x = sin(mlx->player->angle) * PLAYER_SPEED;
		move_y = -cos(mlx->player->angle) * PLAYER_SPEED;
	}
	if (mlx->player->u_d == 1) //move up
	{
		move_x = cos(mlx->player->angle) * PLAYER_SPEED;
		move_y = sin(mlx->player->angle) * PLAYER_SPEED;
	}
	if (mlx->player->u_d == -1) //move down
	{
		move_x = -cos(mlx->player->angle) * PLAYER_SPEED;
		move_y = -sin(mlx->player->angle) * PLAYER_SPEED;
	}
	change_playerxy(mlx, move_x, move_y);
}
