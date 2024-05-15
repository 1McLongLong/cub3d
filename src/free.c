#include "../include/header.h"


void ft_free(t_mlx *mlx)
{
 int i = 0;
 while (mlx->data->map2d[i])
  free(mlx->data->map2d[i++]);
 free(mlx->data->map2d);
 free(mlx->data);
 free(mlx->player);
 free(mlx->ray);
 mlx_delete_image(mlx->mlx_p, mlx->mlx_img);
 mlx_close_window(mlx->mlx_p); 
 mlx_terminate(mlx->mlx_p);
 exit(0);
}
