#include "../include/header.h"


void draw_line(t_mlx *mlx, int x1, int y1, int x2, int y2)
{
  int dx = x2 - x1;
  int dy = y2 - y1;
  int step;
  if (abs(dx) > abs(dy))
    step = abs(dx);
  else
    step = abs(dy);
  float x_inc = (float)dx / step;
  float y_inc = (float)dy / step;
  int i = 0;
  while (i <= step)
	{
    int current_x = x1 + (int)(i * x_inc);
    int current_y = y1 + (int)(i * y_inc);
    mlx_put_pixel(mlx->mlx_img, current_x, current_y, 0xEEED312);
    i++;
  }
}

void	render_wall(t_mlx *mlx)
{
	int	i;
	int	j;

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
						mlx_put_pixel(mlx->mlx_img, tile_x, tile_y, 0x0C0C0C);
					else if (mlx->data->map2d[i][j] != 'P')
						mlx_put_pixel(mlx->mlx_img, tile_x, tile_y, 0xEEEEEEEE);
					tile_x++;
				}
				tile_y++;
			}
			j++;
		}
		i++;
	}
}

void render_player(t_mlx *mlx)
{
	int player_x = mlx->player->plyr_x;
	int player_y = mlx->player->plyr_y;

	int player_size = TILE_SIZE * 0.3;

	// Calculate top-left corner coordinates for drawing the player
	int top_left_x = player_x - player_size / 2;
	int top_left_y = player_y - player_size / 2;

	for (int y = 0; y < player_size; y++) 
	{
		for (int x = 0; x < player_size; x++)
		{
			if (top_left_x + x >= 0 && top_left_y + y >= 0 &&
				top_left_x + x < S_W && top_left_y + y < S_H)
			{
				mlx_put_pixel(mlx->mlx_img, top_left_x + x, top_left_y + y, 0xFF0000FF);
			}
		}
	}
	draw_line(mlx, player_x, player_y, player_x + cos(mlx->player->angle) * 30, player_y + sin(mlx->player->angle) * 30);
}


void castray(float ray_angle, int stripid)
{}

void cast_rays(t_mlx *mlx)
{
	mlx->ray->ray_ngl = mlx->player->angle - (mlx->player->fov_rd / 2); // fov_rd could be FOV i'm not sure
	int stripid = 0;
	while (stripid < NUM_RAYS)
	{
		castray(mlx->ray->ray_ngl, stripid);
		mlx->ray->ray_ngl += mlx->player->fov_rd / NUM_RAYS;
		stripid++;
	}
}


void init_player(t_mlx mlx)
{
	mlx.player->plyr_x =	mlx.data->p_x * TILE_SIZE;
	mlx.player->plyr_y = mlx.data->p_y * TILE_SIZE;
	mlx.player->angle = PI / 2;
	mlx.player->fov_rd = (PI * FOV) / 180;
}

void game_loop(void *ml)
{
	t_mlx *mlx;

	mlx = ml;
	mlx_delete_image(mlx->mlx_p, mlx->mlx_img);
	mlx->mlx_img = mlx_new_image(mlx->mlx_p, S_W, S_H);
	render_wall(mlx);
	render_player(mlx);
	hook(mlx, 0, 0);
	// cast_rays(mlx);
	mlx_image_to_window(mlx->mlx_p, mlx->mlx_img, 0, 0);
}

void start_game(t_data *data)
{
	t_mlx mlx;

	mlx.data = data;
	mlx.player = calloc(1, sizeof(t_player));
	mlx.ray = calloc(1, sizeof(t_ray));
	init_player(mlx);
	mlx.mlx_p = mlx_init(S_W, S_H, "Cub3D", 0);
	mlx.mlx_img = mlx_new_image(mlx.mlx_p, S_W, S_H);
	mlx_loop_hook(mlx.mlx_p, game_loop, &mlx);
	mlx_key_hook(mlx.mlx_p, &key_handler, &mlx);
	mlx_loop(mlx.mlx_p);
}


t_data *init_data()
{
	t_data *data;
	data = calloc(1, sizeof(t_data));
	data->map2d = calloc(14, sizeof(char *));
	data->map2d[0] = strdup("11111111111111111111");
	data->map2d[1] = strdup("10000000000000100001");
	data->map2d[2] = strdup("10010000000000000001");
	data->map2d[3] = strdup("10010000000001000001");
	data->map2d[4] = strdup("10000000000000100001");
	data->map2d[5] = strdup("10010000000001000001");
	data->map2d[6] = strdup("10010000100000100001");
	data->map2d[7] = strdup("10010000000001000001");
	data->map2d[8] = strdup("10000000111111000001");
	data->map2d[9] = strdup("10010000001000100001");
	data->map2d[10] = strdup("10000100000000000101");
	data->map2d[11] = strdup("10010000100000100001");
	data->map2d[12] = strdup("11111111111111111111");
	data->map2d[13] = NULL;
	data->p_x = 12;
	data->p_y = 3;
	data->map_rows = 13;
	data->map_cols = 20;
	return (data);
}

int main()
{
	t_data *data;

	data = init_data();
	start_game(data);
}
