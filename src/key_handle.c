#include "../include/header.h"

void ft_release(mlx_key_data_t keydata, t_mlx *mlx) // release the key
{
	if (keydata.key == MLX_KEY_D && (keydata.action == MLX_RELEASE))
		mlx->player->l_r = 0;
	else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_RELEASE))
		mlx->player->l_r = 0;
	else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_RELEASE))
		mlx->player->u_d = 0;
	else if (keydata.key == MLX_KEY_W && (keydata.action == MLX_RELEASE))
		mlx->player->u_d = 0;
	else if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_RELEASE))
		mlx->player->rot = 0;
	else if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_RELEASE))
		mlx->player->rot = 0;
}

void key_handler(mlx_key_data_t keydata, void *ml)
{
	t_mlx *mlx;
	mlx = ml;
	// if (keydata.key == MLX_KEY_ESCAPE && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)) // exit the game
	// 	ft_exit(mlx);
	if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS))
	{
		// mlx->player->l_r = -1;
	}
	else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS))
	{
		// mlx->player->l_r = 1;
	}
	else if (keydata.key == MLX_KEY_W && (keydata.action == MLX_PRESS))
	{
		mlx->player->u_d = -1;
	}
	else if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
	{
		mlx->player->u_d = 1;
	}
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
	{	
		mlx->player->rot = -1;
	}
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
	{
		mlx->player->rot = 1;
	}
	ft_release(keydata, mlx);
}
