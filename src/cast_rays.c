#include "../include/header.h"

float norm_angle(float angle)
{
  if (angle < 0)
    angle += (2 * PI);
  if (angle > (2 * PI))
    angle -= (2 * PI);
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

float find_h_inter(t_mlx *mlx, float rayAngle)
{
  rayAngle = norm_angle(rayAngle);

  int isRayFacingDown = rayAngle > 0 && rayAngle < PI;
  int isRayFacingUp = !isRayFacingDown;

  int isRayFacingRight = rayAngle < 0.5 * PI || rayAngle > 1.5 * PI;
  int isRayFacingLeft = !isRayFacingRight;

  float xintercept, yintercept;
  float xstep, ystep;

  // Find the y-coordinate of the closest horizontal grid intersection
  yintercept = floor(mlx->player->plyr_y / TILE_SIZE) * TILE_SIZE;
  yintercept += isRayFacingDown ? TILE_SIZE : 0;

  // Find the x-coordinate of the closest horizontal grid intersection
  xintercept = mlx->player->plyr_x + (yintercept - mlx->player->plyr_y) / tan(rayAngle);

  // Calculate the increment xstep and ystep
  ystep = TILE_SIZE;
  ystep *= isRayFacingUp ? -1 : 1;

  xstep = TILE_SIZE / tan(rayAngle);
  xstep *= (isRayFacingLeft && xstep > 0) ? -1 : 1;
  xstep *= (isRayFacingRight && xstep < 0) ? -1 : 1;

  float nextHorzTouchX = xintercept;
  float nextHorzTouchY = yintercept;

  // Increment xstep and ystep until we find a wall
  while (nextHorzTouchX >= 0 && nextHorzTouchX <= S_W && nextHorzTouchY >= 0 && nextHorzTouchY <= S_H)
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
  int isRayFacingDown = rayAngle > 0 && rayAngle < PI;
  int isRayFacingUp = !isRayFacingDown;

  int isRayFacingRight = rayAngle < 0.5 * PI || rayAngle > 1.5 * PI;
  int isRayFacingLeft = !isRayFacingRight;

  float xintercept, yintercept;
  float xstep, ystep;

  xintercept = floor(mlx->player->plyr_x / TILE_SIZE) * TILE_SIZE;
  xintercept += isRayFacingRight ? TILE_SIZE : 0;

  yintercept = mlx->player->plyr_y + (xintercept - mlx->player->plyr_x) * tan(rayAngle);

  // Calculate the increment xstep and ystep
  xstep = TILE_SIZE;
  xstep *= isRayFacingLeft ? -1 : 1;

  ystep = TILE_SIZE * tan(rayAngle);
  ystep *= (isRayFacingUp && ystep > 0) ? -1 : 1;
  ystep *= (isRayFacingDown && ystep < 0) ? -1 : 1;

  float nextVertTouchX = xintercept;
  float nextVertTouchY = yintercept;
  // Increment xstep and ystep until we find a wall
  while (nextVertTouchX >= 0 && nextVertTouchX <= S_W && nextVertTouchY >= 0 && nextVertTouchY <= S_H)
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

void render_rays(t_mlx *mlx, float x1, float y1, float x2, float y2)
{
  float dx = x2 - x1;
  float dy = y2 - y1;
  float step;
  if (fabsf(dx) >= fabsf(dy))
    step = fabsf(dx);
  else
    step = fabsf(dy);
  float x_inc = dx / step;
  float y_inc = dy / step;
  float i = 0;
  while (i <= step)
	{
    float current_x = x1 + (i * x_inc);
    float current_y = y1 + (i * y_inc);
    mlx_put_pixel(mlx->mlx_img, current_x, current_y, 0xEEED312);
    i++;
  }
}

void cast_rays(t_mlx *mlx)
{
  float h_inter;
  float v_inter;
	int ray = 0;
	
  mlx->ray->ray_ngl = mlx->player->angle - (mlx->player->fov_rd / 2);
	while (ray < NUM_RAYS)
	{
    mlx->ray->flag = 0;
    h_inter = find_h_inter(mlx, mlx->ray->ray_ngl);
    v_inter = find_v_inter(mlx, mlx->ray->ray_ngl);
		if (v_inter <= h_inter)
		{
			mlx->ray->distance = v_inter;
			render_rays(mlx, mlx->player->plyr_x, mlx->player->plyr_y, mlx->ray->v_inter_x, mlx->ray->v_inter_y);
		}
		else
		{
			mlx->ray->distance = h_inter;
			render_rays(mlx, mlx->player->plyr_x, mlx->player->plyr_y, mlx->ray->h_inter_x, mlx->ray->h_inter_y);
		}
		mlx->ray->ray_ngl += norm_angle(mlx->player->fov_rd / NUM_RAYS);
		ray++;
	}
}
