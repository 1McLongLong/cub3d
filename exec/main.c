#include "../include/header.h"

void	count_rows_cols(t_mlx *mlx)
{
	int	i;
	int	j;

	i = 0;
	mlx->cub3d->map_cols = 0;
	while (mlx->cub3d->map[i])
	{
		j = 0;
		while (mlx->cub3d->map[i][j])
			j++;
		if (j > mlx->cub3d->map_cols)
			mlx->cub3d->map_cols = j;
		i++;
	}
	mlx->cub3d->map_rows = i;
}

void get_angle(t_mlx *mlx)
{
	char c;

	c = mlx->cub3d->map[mlx->cub3d->p_x][mlx->cub3d->p_y];
	if (c == 'E')
		mlx->player->angle = 0;
	else if (c == 'S')
		mlx->player->angle = M_PI / 2;
	else if (c == 'W')
		mlx->player->angle = M_PI;
	else if (c == 'N')
		mlx->player->angle = M_PI * 1.5;
}

void find_player(t_mlx *mlx)
{
	int i;
	int j;

	i = 0;
	while (mlx->cub3d->map[i])
	{
		j = 0;
		while (mlx->cub3d->map[i][j])
		{
			if (mlx->cub3d->map[i][j] == 'N' || mlx->cub3d->map[i][j] == 'S'
				|| mlx->cub3d->map[i][j] == 'W' || mlx->cub3d->map[i][j] == 'E')
			{
				mlx->cub3d->p_x = i;
				mlx->cub3d->p_y = j;
			}
			j++;
		}
		i++;
	}
	count_rows_cols(mlx);
}


int load_images(t_mlx *mlx)
{
	mlx->img->no = mlx_texture_to_image(mlx->mlx_p, mlx->text->no);
	if (!mlx->img->no)
		return (printf("Wrong image\n"), 1);
	mlx->img->so = mlx_texture_to_image(mlx->mlx_p, mlx->text->so);
	if (!mlx->img->so)
		return (printf("Wrong image\n"), 1);
	mlx->img->we = mlx_texture_to_image(mlx->mlx_p, mlx->text->we);
	if (!mlx->img->we)
		return (printf("Wrong image\n"), 1);
	mlx->img->ea = mlx_texture_to_image(mlx->mlx_p, mlx->text->ea);
	if (!mlx->img->ea)
		return (printf("Wrong image\n"), 1);
	return (0);
}

int load_textures(t_mlx *mlx)
{
	mlx->text->no = mlx_load_png(mlx->cub3d->NO);
	if (!mlx->text->no)
		return (printf("Wrong Texture\n"), 1);
	mlx->text->so = mlx_load_png(mlx->cub3d->SO);
	if (!mlx->text->so)
		return (printf("Wrong Texture\n"), 1);
	mlx->text->we = mlx_load_png(mlx->cub3d->WE);
	if (!mlx->text->we)
		return (printf("Wrong Texture\n"), 1);
	mlx->text->ea = mlx_load_png(mlx->cub3d->EA);
	if (!mlx->text->ea)
		return (printf("Wrong Texture\n"), 1);
	return (0);
}

int init_player(t_mlx mlx)
{
	find_player(&mlx);
	mlx.player->plyr_x =	mlx.cub3d->p_x * TILE_SIZE + TILE_SIZE / 2;
	mlx.player->plyr_y = mlx.cub3d->p_y * TILE_SIZE + TILE_SIZE / 2;
	get_angle(&mlx);
	mlx.player->fov_rd = (PI * FOV) / 180;
	if (load_textures(&mlx))
		return (1);
	if (load_images(&mlx))
		return (1);
	return (0);
}

void game_loop(void *ml)
{
	t_mlx *mlx;

	mlx = ml;
	mlx_delete_image(mlx->mlx_p, mlx->mlx_img);
	mlx->mlx_img = mlx_new_image(mlx->mlx_p, S_W, S_H);
	move_player(mlx, 0, 0);
	cast_rays(mlx);
	mlx_image_to_window(mlx->mlx_p, mlx->mlx_img, 0, 0);
}

void start_game(t_cub3d *cub3d)
{
	t_mlx mlx;

	mlx.cub3d = cub3d;
	mlx.player = calloc(1, sizeof(t_player));
	mlx.ray = calloc(1, sizeof(t_ray));
	mlx.text = calloc(1, sizeof(t_tex));
	mlx.img = calloc(1, sizeof(t_img));
	if (!mlx.img || !mlx.text || !mlx.ray || !mlx.player)
		exit(0);
	mlx.mlx_p = mlx_init(S_W, S_H, "Cub3D", 0);
	if (init_player(mlx))
		ft_free(&mlx);
	mlx.mlx_img = mlx_new_image(mlx.mlx_p, S_W, S_H);
	mlx_loop_hook(mlx.mlx_p, game_loop, &mlx);
	mlx_key_hook(mlx.mlx_p, &key_handler, &mlx);
	mlx_loop(mlx.mlx_p);
	ft_free(&mlx);
}

int main(int ac, char **av)
{
	t_cub3d	cub3d;

	if (ac != 2)
	{
		ft_puterror("one file must be provided with <.cub> extension");
	}
	start_parsing(av[1], &cub3d);

	start_game(&cub3d);
}
