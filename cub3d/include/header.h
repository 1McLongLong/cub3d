#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "../libft/libft.h"
#include "../gnl/get_next_line.h"
#include "../MLX42/include/MLX42/MLX42.h"

# define S_W 1920
# define S_H 1080
# define TILE_SIZE 60
# define FOV 60 
# define ROTATION_SPEED 0.030 // rotation speed
# define PLAYER_SPEED 4 // player speed
# define PI 3.1415926535
# define NUM_RAYS S_W

typedef	struct s_temp
{
	int	NO;
	int	SO;
	int	WE;
	int	EA;
	int	F;
	int	C;
	int	i;
	int	j;
	int	N;
	int	S;
	int	E;
	int	W;
	int	find_map;
	int	find_new_line;
}	t_temp;

typedef	struct s_map
{
	char	*line;
	struct	s_map *next;
}	t_map;



typedef	struct s_cub3d
{
	char	**map;
	char	*NO;
	char	*SO;
	char	*WE;
	char	*EA;
	int		F;
	int		C;
	int p_x;
	int p_y;
	int map_cols;
	int map_rows;
}	t_cub3d;


typedef struct s_tex
{
	mlx_texture_t	*no;
	mlx_texture_t	*so;
	mlx_texture_t	*we;
	mlx_texture_t	*ea;
}	t_tex;

typedef struct s_img
{
	mlx_image_t	*no;
	mlx_image_t	*so;
	mlx_image_t	*we;
	mlx_image_t	*ea;
}	t_img;

typedef struct s_player
{
	int  plyr_x; // player x position in pixels
	int  plyr_y; // player y position in pixels
	double angle; // player angle
	float fov_rd; // field of view in radians
	int  rot; // rotation flag
	int  l_r; // left right flag
	int  u_d; // up down flag
} t_player;

typedef struct s_ray
{
	float ray_ngl; // ray angle
	float distance; // distance to the wall
	float v_inter_x;
	float v_inter_y;
	float h_inter_x;
	float h_inter_y;
	int ray;
	int  flag;  // flag for the wall (hit vertical/horizontal)
} t_ray;

typedef struct s_mlx //the mlx structure
{
	mlx_t *mlx_p;
	mlx_image_t *mlx_img;
	t_ray   *ray; 
	t_player  *player;
	t_cub3d	*cub3d;
	t_img *img;
	t_tex *text;
} t_mlx;



float norm_angle(float angle);
void	move_player(t_mlx *mlx, double move_x, double move_y);
void cast_rays(t_mlx *mlx);
void key_handler(mlx_key_data_t key, void *ml);
void ft_free(t_mlx *mlx);
void	render_wall3d(t_mlx	*mlx, int	ray);


/////////////////////////////////////////////////////////////////////////////			  PARSING     /////////////////////////////////////////////////////////////////////////////////

void	free_arr(char **values);
int		size_arr(char **arr);
void	ft_puterror(char *msg);
void	check_map_name(char *name);
void	start_parsing(char *name_file, t_cub3d *cub3d);
int		parsing_map_values(char *line, t_temp *temp, t_cub3d *cub3d);
int		pars_color(char	*line, t_temp *temp);
void	draw_map(t_cub3d *cub, t_map *map);
void	full_map(char *line, t_map **map, t_temp *temp);
void	check_if_valid_map(t_cub3d *cub);

t_map	*list_create(char	*line);
void	list_add(t_map **head, t_map *node);
int		list_size(t_map *head);
void	list_clean(t_map **head);

#endif
