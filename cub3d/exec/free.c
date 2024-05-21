#include "../include/header.h"


void delete_textures(t_mlx *mlx)
{
	if (mlx->text->no)
		free(mlx->text->no);
	if (mlx->text->so)
		free(mlx->text->so);
	if (mlx->text->we)
		free(mlx->text->we);
	if (mlx->text->ea)
		free(mlx->text->ea);
}

void ft_free(t_mlx *mlx)
{
	// int i = 0;
	// while (mlx->data->map2d[i])
	//  free(mlx->data->map2d[i++]);
	// free(mlx->data->map2d);
	// free(mlx->data);
	delete_textures(mlx);
	free(mlx->player);
	free(mlx->ray);
	mlx_delete_image(mlx->mlx_p, mlx->mlx_img);
	mlx_close_window(mlx->mlx_p); 
	mlx_terminate(mlx->mlx_p);
	exit(0);
}
