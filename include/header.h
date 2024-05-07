#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <mlx.h>

# define S_W 1900 
# define S_H 1000 
# define TILE_SIZE 30
# define FOV 60 
# define ROTATION_SPEED 0.069 // rotation speed
# define PLAYER_SPEED 4 // player speed
# define PI 3.1415926535

typedef struct s_player //the player structure
{
 int  plyr_x; // player x position in pixels
 int  plyr_y; // player y position in pixels
 double angle; // player angle
 float fov_rd; // field of view in radians
 int  rot; // rotation flag
 int  l_r; // left right flag
 int  u_d; // up down flag
} t_player;

typedef struct s_ray //the ray structure
{
 double ray_ngl; // ray angle
 double distance; // distance to the wall
 int  flag;  // flag for the wall
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
 void *mlx_p; // the mlx pointer
 void *mlx_win;
 t_ray   *ray; 
 t_data   *data; 
 t_player  *player; 
} t_mlx;




int key_handler(int key, t_mlx *mlx);
int	handle_exit(t_mlx *data);


#endif
