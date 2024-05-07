#include "../include/header.h"


int	render(t_mlx *mlx)
{
	int	i;
	int	j;

	if (mlx->mlx_p == NULL)
		return (1);
	i = 0;
	while (i < mlx->data->map_rows)
	{
		j = 0;
		while (j < mlx->data->map_cols)
		{
			int tile_y = i * TILE_SIZE;
			while (tile_y < (i + 1) * TILE_SIZE)
			{
				int tile_x = j * TILE_SIZE;
				while (tile_x < (j + 1) * TILE_SIZE)
				{
					if (mlx->data->map2d[i][j] == '1')
						mlx_pixel_put(mlx->mlx_p, mlx->mlx_win, tile_x, tile_y, 0x0C0C0C);
					else if (mlx->data->map2d[i][j] == '0')
						mlx_pixel_put(mlx->mlx_p, mlx->mlx_win, tile_x, tile_y, 0xEEEEEE);
					else if (mlx->data->map2d[i][j] == 'P')
					{
						mlx_pixel_put(mlx->mlx_p, mlx->mlx_win, tile_x, tile_y, 0x0000FF);
						draw_line(mlx);
					}
					tile_x++;
				}
				tile_y++;
			}
			j++;
		}
		i++;
	}
	return (0);
}

void init_player(t_mlx mlx)
{
	mlx.player->plyr_x =	mlx.data->p_x * TILE_SIZE + TILE_SIZE / 2;
	mlx.player->plyr_y = mlx.data->p_y * TILE_SIZE + TILE_SIZE / 2;
	mlx.player->angle = PI / 2;
	mlx.player->fov_rd = (PI * FOV) / 180;
}

void start_game(t_data *data)
{
	t_mlx mlx;

	mlx.data = data;
	mlx.player = calloc(1, sizeof(t_player));
	mlx.ray = calloc(1, sizeof(t_ray));
	init_player(mlx);
	mlx.mlx_p = mlx_init();
	mlx.mlx_win = mlx_new_window(mlx.mlx_p, data->map_cols * TILE_SIZE, data->map_rows * TILE_SIZE, "CUB3D");
	mlx_loop_hook(mlx.mlx_p, render, &mlx);
	mlx_hook(mlx.mlx_win, 17, 0, handle_exit, &mlx);
	mlx_hook(mlx.mlx_win, 2, 0, key_handler, &mlx);
	mlx_loop(mlx.mlx_p);
}


t_data *init_data()
{
	t_data *data;
	data = calloc(1, sizeof(t_data));
	data->map2d = calloc(11, sizeof(char *));
	data->map2d[0] = strdup("1111111111111111111111111");
	data->map2d[1] = strdup("1000000000000000000100001");
	data->map2d[2] = strdup("1001000000000P00000000001");
	data->map2d[3] = strdup("1001000000000000001000001");
	data->map2d[4] = strdup("1001000000000000001000001");
	data->map2d[5] = strdup("1001000000100000001000001");
	data->map2d[6] = strdup("1001000000000000001000001");
	data->map2d[7] = strdup("1001000000001000001000001");
	data->map2d[8] = strdup("1000000100000000000000101");
	data->map2d[9] = strdup("1111111111111111111111111");
	data->map2d[10] = NULL;
	data->p_x = 3;
	data->p_y = 14;
	data->map_rows = 10;
	data->map_cols = 25;
	return (data);
}

int main()
{
	t_data *data;

	data = init_data();
	start_game(data);
}
