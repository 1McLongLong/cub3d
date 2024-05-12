#include "../include/header.h"

void	rotate_player(t_mlx *mlx, int i)	// rotate the player
{
	if (i == 1)
	{
		mlx->player->angle += ROTATION_SPEED; // rotate right
		if (mlx->player->angle > 2 * PI)
			mlx->player->angle -= 2 * PI;
	}
	else
	{
		mlx->player->angle -= ROTATION_SPEED; // rotate left
		if (mlx->player->angle < 0)
			mlx->player->angle += 2 * M_PI;
	}
}

void	move_player(t_mlx *mlx, double move_x, double move_y)	// move the player
{
	int		map_grid_y;
	int		map_grid_x;
	int		new_x;
	int		new_y;

	new_x = roundf(mlx->player->plyr_x + move_x); // get the new x position
	new_y = roundf(mlx->player->plyr_y + move_y); // get the new y position
	map_grid_x = (new_x / TILE_SIZE); // get the x position in the map
	map_grid_y = (new_y / TILE_SIZE); // get the y position in the map
	if (mlx->data->map2d[map_grid_y][map_grid_x] != '1' && \
	(mlx->data->map2d[map_grid_y][mlx->player->plyr_x / TILE_SIZE] != '1' && \
	mlx->data->map2d[mlx->player->plyr_y / TILE_SIZE][map_grid_x] != '1')) // check the wall hit and the diagonal wall hit
	{
		mlx->player->plyr_x = new_x; // move the player
		mlx->player->plyr_y = new_y; // move the player
	}
}

void	hook(t_mlx *mlx, double move_x, double move_y)	// hook the player
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
	move_player(mlx, move_x, move_y); // move the player
}