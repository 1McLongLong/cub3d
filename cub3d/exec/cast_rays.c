#include "../include/header.h"

// float	norm_angle(float angle)
// {
// 	if (angle < 0)
// 		angle += (2 * M_PI);
// 	if (angle > (2 * M_PI))
// 		angle -= (2 * M_PI);
// 	return (angle);
// }
//
// int	unit_circle(float angle, char c)
// {
// 	if (c == 'x')
// 	{
// 		if (angle > 0 && angle < M_PI)
// 			return (1);
// 	}
// 	else if (c == 'y')
// 	{
// 		if (angle > (M_PI / 2) && angle < (3 * M_PI) / 2)
// 			return (1);
// 	}
// 	return (0);
// }
//
// int	inter_check(float angle, float *inter, float *step, int is_horizon)
// {
// 	if (is_horizon)
// 	{
// 		if (angle > 0 && angle < M_PI)
// 		{
// 			*inter += TILE_SIZE;
// 			return (-1);
// 		}
// 		*step *= -1;
// 	}
// 	else
// 	{
// 		if (!(angle > M_PI / 2 && angle < 3 * M_PI / 2))
// 		{
// 			*inter += TILE_SIZE;
// 			return (-1);
// 		}
// 		*step *= -1;
// 	}
// 	return (1);
// }
//
// int	wall_hit(float x, float y, t_mlx *mlx)
// {
// 	int		x_m;
// 	int		y_m;
//
// 	if (x < 0 || y < 0)
// 		return (0);
// 	x_m = floor (x / TILE_SIZE);
// 	y_m = floor (y / TILE_SIZE);
// 	if ((y_m >= mlx->cub3d->map_rows || x_m >= mlx->cub3d->map_cols))
// 		return (0);
// 	if (mlx->cub3d->map[y_m] && x_m <= (int)ft_strlen(mlx->cub3d->map[y_m]))
// 		if (mlx->cub3d->map[y_m][x_m] == '1')
// 			return (0);
// 	return (1);
// }
//
// float	get_h_inter(t_mlx *mlx, float angl)
// {
// 	float	h_x;
// 	float	h_y;
// 	float	x_step;
// 	float	y_step;
// 	int		pixel;
//
// 	y_step = TILE_SIZE;
// 	x_step = TILE_SIZE / tan(angl);
// 	h_y = floor(mlx->player->plyr_y / TILE_SIZE) * TILE_SIZE;
// 	pixel = inter_check(angl, &h_y, &y_step, 1);
// 	h_x = mlx->player->plyr_x + (h_y - mlx->player->plyr_y) / tan(angl);
// 	if ((unit_circle(angl, 'y') && x_step > 0) || (!unit_circle(angl, 'y') && x_step < 0))
// 		x_step *= -1;
// 	while (wall_hit(h_x, h_y - pixel, mlx))
// 	{
// 		h_x += x_step;
// 		h_y += y_step;
// 	}
// 	mlx->ray->h_inter_x = h_x;
// 	mlx->ray->h_inter_y = h_y;
// 	return (sqrt(pow(h_x - mlx->player->plyr_x, 2) +  pow(h_y - mlx->player->plyr_y, 2)));
// }
//
// float	get_v_inter(t_mlx *mlx, float angl)
// {
// 	float	v_x;
// 	float	v_y;
// 	float	x_step;
// 	float	y_step;
// 	int		pixel;
//
// 	x_step = TILE_SIZE;
// 	y_step = TILE_SIZE * tan(angl);
// 	v_x = floor(mlx->player->plyr_x / TILE_SIZE) * TILE_SIZE;
// 	pixel = inter_check(angl, &v_x, &x_step, 0);
// 	v_y = mlx->player->plyr_y + (v_x - mlx->player->plyr_x) * tan(angl);
// 	if ((unit_circle(angl, 'x') && y_step < 0) ||	(!unit_circle(angl, 'x') && y_step > 0))
// 		y_step *= -1;
// 	while (wall_hit(v_x - pixel, v_y, mlx))
// 	{
// 		v_x += x_step;
// 		v_y += y_step;
// 	}
// 	mlx->ray->v_inter_x = v_x;
// 	mlx->ray->v_inter_y = v_y;
// 	return (sqrt(pow(v_x - mlx->player->plyr_x, 2) +  pow(v_y - mlx->player->plyr_y, 2)));
// }
//
// void	cast_rays(t_mlx *mlx)
// {
// 	double	h_inter;
// 	double	v_inter;
// 	int		ray;
//
// 	ray = 0;
// 	mlx->ray->ray_ngl = mlx->player->angle - (mlx->player->fov_rd / 2);
// 	while (ray < S_W)
// 	{
// 		mlx->ray->flag = 0;
// 		h_inter = get_h_inter(mlx, norm_angle(mlx->ray->ray_ngl));
// 		v_inter = get_v_inter(mlx, norm_angle(mlx->ray->ray_ngl));
// 		if (v_inter <= h_inter)
// 			mlx->ray->distance = v_inter;
// 		else
// 		{
// 			mlx->ray->distance = h_inter;
// 			mlx->ray->flag = 1;
// 		}
// 		render_wall3d(mlx, ray);
// 		ray++;
// 		mlx->ray->ray_ngl += (mlx->player->fov_rd / S_W);
// 	}
// }


//////////////////////////////////////////////////////////////////////////////////////////////////////////////



float norm_angle(float angle)
{
	if (angle < 0)
		angle += (2 * M_PI);
	if (angle > (2 * M_PI))
		angle -= (2 * M_PI);
	return (angle);
}

int wall_hit(float x, float y, t_mlx *mlx)
{
	int  x_m;
	int  y_m;

	if (x < 0 || y < 0)
		return (0);
	x_m = floor(x / TILE_SIZE);
	y_m = floor(y / TILE_SIZE);
	if ((y_m >= mlx->cub3d->map_rows || x_m >= mlx->cub3d->map_cols))
		return (0);
	if (mlx->cub3d->map[y_m] && x_m <= (int)strlen(mlx->cub3d->map[y_m]))
		if (mlx->cub3d->map[y_m][x_m] == '1')
			return (0);
	return (1);
}

int check_inter(float angle, float *inter, float *step, int horiz)
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

float find_h_inter(t_mlx *mlx, float angle)
{
	float	xinter;
	float	yinter;
	float xstep;
	float	ystep;
	int	pixel;
	
	ystep = TILE_SIZE;
	xstep = TILE_SIZE / tan(angle);
	yinter = floor(mlx->player->plyr_y / TILE_SIZE) * TILE_SIZE;
	pixel = check_inter(angle, &yinter, &ystep, 1);
	xinter = mlx->player->plyr_x + (yinter - mlx->player->plyr_y) / tan(angle);
	if (((angle > M_PI / 2 && angle < 1.5 * M_PI) && xstep > 0) || (!(angle > M_PI / 2 && angle < 1.5 * M_PI) && xstep < 0))
		xstep *= -1;
	while (wall_hit(xinter, yinter - pixel, mlx))
	{
		xinter += xstep;
		yinter += ystep;
	}
	mlx->ray->h_inter_x = xinter;
	mlx->ray->h_inter_y = yinter;
	return (sqrt(pow(xinter - mlx->player->plyr_x, 2) + pow(yinter - mlx->player->plyr_y, 2)));
}

float find_v_inter(t_mlx *mlx, float angle)
{	
	float	xinter;
	float	yinter;
	float xstep;
	float	ystep;
	int	pixel;

	xstep = TILE_SIZE;
	ystep = TILE_SIZE * tan(angle);
	xinter = floor(mlx->player->plyr_x / TILE_SIZE) * TILE_SIZE;
	pixel = check_inter(angle, &xinter, &xstep, 0);
	yinter = mlx->player->plyr_y + (xinter - mlx->player->plyr_x) * tan(angle);
	if (((angle > 0 && angle < M_PI) && ystep < 0) || (!(angle > 0 && angle < M_PI) && ystep > 0))
		ystep *= -1;
	while (wall_hit(xinter - pixel, yinter, mlx))
	{
		xinter += xstep;
		yinter += ystep;
	}
	mlx->ray->v_inter_x = xinter;
	mlx->ray->v_inter_y = yinter;
	return (sqrt(pow(xinter - mlx->player->plyr_x, 2) + pow(yinter - mlx->player->plyr_y, 2)));
}

void cast_rays(t_mlx *mlx)
{
  float h_inter;
  float v_inter;
	int ray = 0;
	
  mlx->ray->ray_ngl = norm_angle(mlx->player->angle) - (mlx->player->fov_rd / 2);
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
    // draw_ray(mlx, mlx->ray->ray_ngl, mlx->ray->distance, 0xEEED312);
		render_wall3d(mlx, ray);
		mlx->ray->ray_ngl += (mlx->player->fov_rd / NUM_RAYS);
		ray++;
	}
}

//////////////////////////////////////////////

// float norm_angle(float angle)
// {
// 	if (angle < 0)
// 		angle += (2 * M_PI);
// 	if (angle > (2 * M_PI))
// 		angle -= (2 * M_PI);
// 	return (angle);
// }
//
// int wall_hit(float x, float y, t_mlx *mlx)
// {
// 	int  x_m;
// 	int  y_m;
//
// 	if (x < 0 || y < 0)
// 		return (0);
// 	x_m = floor(x / TILE_SIZE);
// 	y_m = floor(y / TILE_SIZE);
// 	if ((y_m >= mlx->cub3d->map_rows || x_m >= mlx->cub3d->map_cols))
// 		return (0);
// 	if (mlx->cub3d->map[y_m] && x_m <= (int)strlen(mlx->cub3d->map[y_m]))
// 		if (mlx->cub3d->map[y_m][x_m] == '1')
// 			return (0);
// 	return (1);
// }
//
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
//
// void	draw_ray(t_mlx *mlx, float angle, float distance)
// {
// 	float	x;
// 	float	y;
// 	float		i;
//
// 	i = 0;
// 	y = mlx->player->plyr_y;
// 	x = mlx->player->plyr_x;
// 	while (i <= distance)
// 	{
// 		mlx_put_pixel(mlx->mlx_img, x, y, 0xEEED312);
// 		x += 1 * cos(angle);
// 		y += 1 * sin(angle);
// 		i++;
// 	}
// }
//
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
