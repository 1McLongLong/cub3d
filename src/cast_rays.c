#include "../include/header.h"

float norm_angle(float angle)
{
	if (angle >= (2 * M_PI))
    angle -= (2 * M_PI);
  if (angle < 0)
    angle += (2 * M_PI);
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
	if ((y_m >= mlx->data->map_rows || x_m >= mlx->data->map_cols))
		return (0);
	if (mlx->data->map2d[y_m] && x_m <= (int)strlen(mlx->data->map2d[y_m]))
		if (mlx->data->map2d[y_m][x_m] == '1')
			return (0);
	return (1);
}

float distanceBetweenPoints(float x1, float y1, float x2, float y2)
{
	return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

float find_h_inter(t_mlx *mlx, float rayAngle)
{
  rayAngle = norm_angle(rayAngle);

  int isRayFacingDown = rayAngle > 0 && rayAngle < M_PI;
  int isRayFacingUp = !isRayFacingDown;


  int isRayFacingRight = rayAngle < 0.5 * M_PI || rayAngle > 1.5 * M_PI;
  int isRayFacingLeft = !isRayFacingRight;

  float xintercept, yintercept;
  float xstep, ystep;

	xintercept = 0;
	yintercept = 0;
	xstep = 0;
	ystep = 0;
	// mlx->ray->h_inter_x = 0;
	// mlx->ray->h_inter_y = 0;

  yintercept = floor(mlx->player->plyr_y / TILE_SIZE) * TILE_SIZE;
  yintercept += isRayFacingDown ? TILE_SIZE : 0;

  xintercept = mlx->player->plyr_x + (yintercept - mlx->player->plyr_y) / tan(rayAngle);

  ystep = TILE_SIZE;
  ystep *= isRayFacingUp ? -1 : 1;

  xstep = TILE_SIZE / tan(rayAngle);
  xstep *= (isRayFacingLeft && xstep > 0) ? -1 : 1;
  xstep *= (isRayFacingRight && xstep < 0) ? -1 : 1;

  float nextHorzTouchX = xintercept;
  float nextHorzTouchY = yintercept;
  
  while (nextHorzTouchX > 0 && nextHorzTouchX < S_W && nextHorzTouchY > 0 && nextHorzTouchY < S_H)
  {
    float xToCheck = nextHorzTouchX;
    float yToCheck = nextHorzTouchY + (isRayFacingUp ? -1 : 0);

    if (!wall_hit(xToCheck, yToCheck, mlx))
    {
      mlx->ray->h_inter_x = nextHorzTouchX;
      mlx->ray->h_inter_y = nextHorzTouchY;
      break;
    } 
    else
    {
      nextHorzTouchX += xstep;
      nextHorzTouchY += ystep;
    }
  }
	return (sqrt(pow(mlx->ray->h_inter_x - mlx->player->plyr_x, 2) + pow(mlx->ray->h_inter_y - mlx->player->plyr_y, 2)));
}

float find_v_inter(t_mlx *mlx, float rayAngle)
{
  rayAngle = norm_angle(rayAngle);
  int isRayFacingDown = rayAngle > 0 && rayAngle < M_PI;
  int isRayFacingUp = !isRayFacingDown;

  int isRayFacingRight = rayAngle < 0.5 * M_PI || rayAngle > 1.5 * M_PI;
  int isRayFacingLeft = !isRayFacingRight;

  float xintercept, yintercept;
  float xstep, ystep;
	
	xintercept = 0;
	yintercept = 0;
	xstep = 0;
	ystep = 0;
  // mlx->ray->v_inter_x = 0;
  // mlx->ray->v_inter_x = 0;
  xintercept = floor(mlx->player->plyr_x / TILE_SIZE) * TILE_SIZE;
  xintercept += isRayFacingRight ? TILE_SIZE : 0;

  yintercept = mlx->player->plyr_y + (xintercept - mlx->player->plyr_x) * tan(rayAngle);

  xstep = TILE_SIZE;
  xstep *= isRayFacingLeft ? -1 : 1;

  ystep = TILE_SIZE * tan(rayAngle);
  ystep *= (isRayFacingUp && ystep > 0) ? -1 : 1;
  ystep *= (isRayFacingDown && ystep < 0) ? -1 : 1;

  float nextVertTouchX = xintercept;
  float nextVertTouchY = yintercept;
  while (nextVertTouchX > 0 && nextVertTouchX < S_W && nextVertTouchY > 0 && nextVertTouchY < S_H)
  {
    float xToCheck = nextVertTouchX + (isRayFacingLeft ? -1 : 0);
    float yToCheck = nextVertTouchY;

    if (!wall_hit(xToCheck, yToCheck, mlx))
    {
      mlx->ray->v_inter_x = nextVertTouchX;
      mlx->ray->v_inter_y = nextVertTouchY;
      break;
    } 
    else
    {
      nextVertTouchX += xstep;
      nextVertTouchY += ystep;
    }
  }
	return (sqrt(pow(mlx->ray->v_inter_x - mlx->player->plyr_x, 2) + pow(mlx->ray->v_inter_y - mlx->player->plyr_y, 2)));
}

// void render_rays(t_mlx *mlx, float x1, float y1, float x2, float y2)
// {
//   float dx = x2 - x1;
//   float dy = y2 - y1;
//   float step;
//   if (fabsf(dx) >= fabsf(dy))
//     step = fabsf(dx);
//   else
//     step = fabsf(dy);
//   float x_inc = dx / step;
//   float y_inc = dy / step;
//   float i = 1;
//    float current_x = x1;
//    float current_y = y1;
//   while (i <= step)
// 	{
// 		current_x += x_inc;
// 		current_y += y_inc;
//     mlx_put_pixel(mlx->mlx_img, current_x, current_y, 0xEEED312);
//     i++;
//   }
// }

void	draw_ray(t_mlx *mlx, float angle, float distance, int color)
{
	float	x;
	float	y;
	float		i;

	i = 0;
	y = mlx->player->plyr_y;
	x = mlx->player->plyr_x;
	while (i <= distance)
	{
		mlx_put_pixel(mlx->mlx_img, x, y, color);
		x += 1 * cos(angle);
		y += 1 * sin(angle);
		i++;
	}
}

void cast_rays(t_mlx *mlx)
{
  float h_inter;
  float v_inter;
	int ray = 0;
	
  mlx->ray->ray_ngl = norm_angle(mlx->player->angle) - (mlx->player->fov_rd / 2);
	while (ray < NUM_RAYS)
	{
    h_inter = find_h_inter(mlx, mlx->ray->ray_ngl);
    v_inter = find_v_inter(mlx, mlx->ray->ray_ngl);
		if (v_inter < h_inter)
		{
			mlx->ray->distance = v_inter;
      printf("v_inter: %f\n", v_inter);
			// render_rays(mlx, mlx->player->plyr_x, mlx->player->plyr_y, mlx->ray->v_inter_x, mlx->ray->v_inter_y);
		}
		else
		{
			mlx->ray->distance = h_inter;
      printf("h_inter: %f\n", h_inter);
			// render_rays(mlx, mlx->player->plyr_x, mlx->player->plyr_y, mlx->ray->v_inter_x, mlx->ray->v_inter_y);
		}
    draw_ray(mlx, mlx->ray->ray_ngl, mlx->ray->distance, 0xEEED312);
		mlx->ray->ray_ngl += (mlx->player->fov_rd / NUM_RAYS);
		ray++;
	}
}
