#include "../include/header.h"

int	is_there_wall(float x, float y, t_mlx *mlx)
{
	int	map_x;
	int	map_y;

	if (x < 0 || y < 0)
		return (0);
	map_x = floor(x / TILE_SIZE);
	map_y = floor(y / TILE_SIZE);
	if ((map_y >= mlx->cub3d->map_rows || map_x >= mlx->cub3d->map_cols))
		return (0);
	if (mlx->cub3d->map[map_y]
		&& map_x <= (int)ft_strlen(mlx->cub3d->map[map_y]))
		if (mlx->cub3d->map[map_y][map_x] == '1')
			return (0);
	return (1);
}

int	ray_direct(float angle, float *inter, float *step, int horiz)
{
	if (horiz)
	{
		if (angle > 0 && angle < M_PI)
		{
			*inter += TILE_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	else
	{
		if (angle < 0.5 * M_PI || angle > 1.5 * M_PI)
		{
			*inter += TILE_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	return (1);
}

float	find_h_inter(t_mlx *mlx, float angle)
{
	float	xinter;
	float	yinter;
	float	xstep;
	float	ystep;
	int		pixel;

	angle = norm_angle(angle);
	ystep = TILE_SIZE;
	xstep = TILE_SIZE / tan(angle);
	yinter = floor(mlx->player->plyr_y / TILE_SIZE) * TILE_SIZE;
	pixel = ray_direct(angle, &yinter, &ystep, 1);
	xinter = mlx->player->plyr_x + (yinter - mlx->player->plyr_y) / tan(angle);
	if (((angle > M_PI / 2 && angle < 1.5 * M_PI) && xstep > 0)
		|| (!(angle > M_PI / 2 && angle < 1.5 * M_PI) && xstep < 0))
		xstep *= -1;
	while (is_there_wall(xinter, yinter - pixel, mlx))
	{
		xinter += xstep;
		yinter += ystep;
	}
	mlx->ray->h_inter_x = xinter;
	mlx->ray->h_inter_y = yinter;
	return (sqrt(pow(xinter - mlx->player->plyr_x, 2)
			+ pow(yinter - mlx->player->plyr_y, 2)));
}

float	find_v_inter(t_mlx *mlx, float angle)
{
	float	xinter;
	float	yinter;
	float	xstep;
	float	ystep;
	int		pixel;

	angle = norm_angle(angle);
	xstep = TILE_SIZE;
	ystep = TILE_SIZE * tan(angle);
	xinter = floor(mlx->player->plyr_x / TILE_SIZE) * TILE_SIZE;
	pixel = ray_direct(angle, &xinter, &xstep, 0);
	yinter = mlx->player->plyr_y + (xinter - mlx->player->plyr_x) * tan(angle);
	if (((angle > 0 && angle < M_PI) && ystep < 0)
		|| (!(angle > 0 && angle < M_PI) && ystep > 0))
		ystep *= -1;
	while (is_there_wall(xinter - pixel, yinter, mlx))
	{
		xinter += xstep;
		yinter += ystep;
	}
	mlx->ray->v_inter_x = xinter;
	mlx->ray->v_inter_y = yinter;
	return (sqrt(pow(xinter - mlx->player->plyr_x, 2)
			+ pow(yinter - mlx->player->plyr_y, 2)));
}

void	cast_rays(t_mlx *mlx)
{
	float	h_inter;
	float	v_inter;
	int		ray;

	ray = 0;
	mlx->ray->ray_ngl = mlx->player->angle - mlx->player->fov_rd / 2;
	while (ray < NUM_RAYS)
	{
		mlx->ray->flag = 0;
		h_inter = find_h_inter(mlx, mlx->ray->ray_ngl);
		v_inter = find_v_inter(mlx, mlx->ray->ray_ngl);
		if (v_inter <= h_inter)
		{
			mlx->ray->distance = v_inter;
		}
		else
		{
			mlx->ray->flag = 1;
			mlx->ray->distance = h_inter;
		}
		render_wall3d(mlx, ray);
		mlx->ray->ray_ngl += (mlx->player->fov_rd / NUM_RAYS);
		ray++;
	}
}

//////////////////////////////////////////////

// float find_h_inter(t_mlx *mlx, float angle)
// {
// 	angle = norm_angle(angle);
//
// 	int isRayFacingDown = angle > 0 && angle < M_PI;
// 	int isRayFacingUp = !isRayFacingDown;
// 	int isRayFacingRight = angle < 0.5 * M_PI || angle > 1.5 * M_PI;
// 	int isRayFacingLeft = !isRayFacingRight;
//
// 	float xintercept, yintercept;
// 	float xstep, ystep;
//
// 	ystep = TILE_SIZE;
// 	xstep = TILE_SIZE / tan(angle);
// 	yintercept = floor(mlx->player->plyr_y / TILE_SIZE) * TILE_SIZE;
// 	yintercept += isRayFacingDown ? TILE_SIZE : 0;
// 	ystep *= isRayFacingUp ? -1 : 1;
// 	xintercept = mlx->player->plyr_x + (yintercept - mlx->player->plyr_y) / tan(angle);
// 	xstep *= (isRayFacingLeft && xstep > 0) ? -1 : 1;
// 	xstep *= (isRayFacingRight && xstep < 0) ? -1 : 1;
// 	while (wall_hit(xintercept, yintercept + (isRayFacingUp ? -1 : 0), mlx))
// 	{
// 		xintercept += xstep;
// 		yintercept += ystep;
// 	}
// 	mlx->ray->h_inter_x = xintercept;
// 	mlx->ray->h_inter_y = yintercept;
// 	return (sqrt(pow(xintercept - mlx->player->plyr_x, 2) + pow(yintercept - mlx->player->plyr_y, 2)));
// }
//
// float find_v_inter(t_mlx *mlx, float angle)
// {
// 	angle = norm_angle(angle);
// 	int isRayFacingDown = angle > 0 && angle < M_PI;
// 	int isRayFacingUp = !isRayFacingDown;
// 	int isRayFacingRight = angle < 0.5 * M_PI || angle > 1.5 * M_PI;
// 	int isRayFacingLeft = !isRayFacingRight;
//
// 	float xintercept, yintercept;
// 	float xstep, ystep;
//
// 	xstep = TILE_SIZE;
// 	ystep = TILE_SIZE * tan(angle);
// 	xintercept = floor(mlx->player->plyr_x / TILE_SIZE) * TILE_SIZE;
// 	xintercept += isRayFacingRight ? TILE_SIZE : 0;
// 	xstep *= isRayFacingLeft ? -1 : 1;
// 	yintercept = mlx->player->plyr_y + (xintercept - mlx->player->plyr_x) * tan(angle);
// 	ystep *= (isRayFacingUp && ystep > 0) ? -1 : 1;
// 	ystep *= (isRayFacingDown && ystep < 0) ? -1 : 1;
//
// 	while (wall_hit(xintercept + (isRayFacingLeft ? -1 : 0), yintercept, mlx))
// 	{
// 		xintercept += xstep;
// 		yintercept += ystep;
// 	}
// 	mlx->ray->v_inter_x = xintercept;
// 	mlx->ray->v_inter_y = yintercept;
// 	return (sqrt(pow(xintercept - mlx->player->plyr_x, 2) + pow(yintercept - mlx->player->plyr_y, 2)));
// }
// void cast_rays(t_mlx *mlx)
// {
// 	float h_inter;
// 	float v_inter;
// 	int ray = 0;
//
// 	mlx->ray->ray_ngl = mlx->player->angle - (mlx->player->fov_rd / 2);
// 	while (ray < NUM_RAYS)
// 	{
// 		mlx->ray->flag = 0;
// 		h_inter = find_h_inter(mlx, norm_angle(mlx->ray->ray_ngl));
// 		v_inter = find_v_inter(mlx, norm_angle(mlx->ray->ray_ngl));
// 		if (v_inter <= h_inter)
// 		{
// 			mlx->ray->distance = v_inter;
// 		}
// 		else
// 		{	
// 			mlx->ray->flag = 1;
// 			mlx->ray->distance = h_inter;
// 		}
// 		// draw_ray(mlx, mlx->ray->ray_ngl, mlx->ray->distance);
// 		render_wall3d(mlx, ray);
// 		mlx->ray->ray_ngl += (mlx->player->fov_rd / NUM_RAYS);
// 		ray++;
// 	}
// }
