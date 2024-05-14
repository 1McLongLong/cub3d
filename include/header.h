#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "../MLX42/include/MLX42/MLX42.h"

# define S_W 1280
# define S_H 832
# define TILE_SIZE 64
# define FOV 60 
# define ROTATION_SPEED 0.069 // rotation speed
# define PLAYER_SPEED 4 // player speed
# define PI 3.1415926535
# define PLAYER_RADIUS 5
# define NUM_RAYS S_W

typedef struct s_player //the player structure
{
	int  plyr_x; // player x position in pixels
	int  plyr_y; // player y position in pixels
	double angle; // player angle
	float fov_rd; // field of view in radians
	float width;
	float height;
	int  rot; // rotation flag
	int  l_r; // left right flag
	int  u_d; // up down flag
} t_player;

typedef struct s_ray //the ray structure
{
	float ray_ngl; // ray angle
	double distance; // distance to the wall
	float v_inter_x;
	float v_inter_y;
	float h_inter_x;
	float h_inter_y;
	int  flag;  // flag for the wall (hit vertical/horizontal)
} t_ray;

typedef struct s_data //the data structure
{
	char **map2d; // the map
	int  p_x;  // player x position in the map
	int  p_y;  // player y position in the map
	int  map_cols;  // map width
	int  map_rows;  // map height
} t_data;

typedef struct s_mlx //the mlx structure
{
	mlx_t *mlx_p;
	mlx_image_t *mlx_img;
	t_ray   *ray; 
	t_data   *data; 
	t_player  *player; 
} t_mlx;



void	hook(t_mlx *mlx, double move_x, double move_y);
void cast_rays(t_mlx *mlx);

void key_handler(mlx_key_data_t key, void *ml);


#endif
