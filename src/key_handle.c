#include "../include/header.h"

void	move_a(t_mlx *gg)
{
	if (gg->data->map2d[gg->data->p_x][gg->data->p_y - 1] == '1')
		return ;
	gg->data->map2d[gg->data->p_x][gg->data->p_y - 1] = 'P';
	gg->data->map2d[gg->data->p_x][gg->data->p_y] = '0';
	gg->data->p_y = gg->data->p_y - 1;
}

void	move_s(t_mlx *gg)
{
	if (gg->data->map2d[gg->data->p_x + 1][gg->data->p_y] == '1')
		return ;
	gg->data->map2d[gg->data->p_x + 1][gg->data->p_y] = 'P';
	gg->data->map2d[gg->data->p_x][gg->data->p_y] = '0';
	gg->data->p_x = gg->data->p_x + 1;
}

void	move_w(t_mlx *gg)
{
	if (gg->data->map2d[gg->data->p_x - 1][gg->data->p_y] == '1')
		return ;
	gg->data->map2d[gg->data->p_x - 1][gg->data->p_y] = 'P';
	gg->data->map2d[gg->data->p_x][gg->data->p_y] = '0';
	gg->data->p_x = gg->data->p_x - 1;
}

void	move_d(t_mlx *gg)
{
	if (gg->data->map2d[gg->data->p_x][gg->data->p_y + 1] == '1')
		return ;
	gg->data->map2d[gg->data->p_x][gg->data->p_y + 1] = 'P';
	gg->data->map2d[gg->data->p_x][gg->data->p_y] = '0';
	gg->data->p_y = gg->data->p_y + 1;
}

int	handle_exit(t_mlx *data)
{
	(void)data;
	exit(0);
}

void ft_release(int key, t_mlx *mlx) // release the key
{
	if (key == 2)
		mlx->player->l_r = 0;
	else if (key == 0)
		mlx->player->l_r = 0;
	else if (key == 1)
		mlx->player->u_d = 0;
	else if (key == 13)
		mlx->player->u_d = 0;
	else if (key == 123)
		mlx->player->rot = 0;
	else if (key == 124)
		mlx->player->rot = 0;
}

int key_handler(int key, t_mlx *mlx)
{
	// if (keydata.key == MLX_KEY_ESCAPE && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)) // exit the game
	//  ft_exit(mlx);
	if (key == 0) // move left
	{
		mlx->player->l_r = -1;
		move_a(mlx);
	}
	else if (key == 2) // move right
	{
		mlx->player->l_r = 1;
		move_d(mlx);
	}
	else if (key == 1) // move down
	{
		mlx->player->u_d = -1;
		move_s(mlx);
	}
	else if (key == 13) // move up
	{
		mlx->player->u_d = 1;
		move_w(mlx);
	}
	else if (key == 123) // rotate left
	{	
		mlx->player->rot = -1;
	}
	else if (key == 124) // rotate right
	{
		mlx->player->rot = 1;
	}
	ft_release(key, mlx); // release the key
	return (0);
}
