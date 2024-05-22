#include "../include/header.h"


void delete_textures(t_mlx *mlx)
{
	mlx_delete_texture(mlx->text->no);
	mlx_delete_texture(mlx->text->so);
	mlx_delete_texture(mlx->text->ea);
	mlx_delete_texture(mlx->text->we);
}

void	ft_free(t_mlx *mlx)
{
	delete_textures(mlx);
	free(mlx->player);
	free(mlx->ray);
	free(mlx->text);
	mlx_delete_image(mlx->mlx_p, mlx->mlx_img);
	mlx_close_window(mlx->mlx_p);
	mlx_terminate(mlx->mlx_p);
	exit(0);
}
