#include "../include/header.h"


int	reverse_bytes(int c)
{
	unsigned int	b;

	b = 0;
	b |= (c & 0xFF) << 24;
	b |= (c & 0xFF00) << 8;
	b |= (c & 0xFF0000) >> 8;
	b |= (c & 0xFF000000) >> 24;
	return (b);
}

mlx_image_t  *get_image(t_mlx *mlx)
{
	mlx->ray->ray_ngl = norm_angle(mlx->ray->ray_ngl);
	if (mlx->ray->flag)
	{
		if (mlx->ray->ray_ngl > 0 && mlx->ray->ray_ngl < M_PI)
			return (mlx->img->so); // south
		else
		  return (mlx->img->no); // north
	}
	else
	{
		if (mlx->ray->ray_ngl < 0.5 * M_PI && mlx->ray->ray_ngl < 1.5 * M_PI)
			return (mlx->img->we);// west
		else
			return (mlx->img->ea);// east
	}
}


// void draw_floor_ceiling(t_mlx *mlx, int ray, int t_pixel, int b_pixel)
// {
// 	int  i;
//
// 	i = b_pixel;
// 	while (i < S_H)
// 		mlx_put_pixel(mlx->mlx_img, ray, i++, 0xc7a98b); // floor
// 	i = 0;
// 	while (i < t_pixel)
// 		mlx_put_pixel(mlx->mlx_img, ray, i++, 0x7eb7c2); // ceiling
// }
// 1920000
void draw_wall(t_mlx *mlx, int t_pixel, int b_pixel, double wall_height)
{
	mlx_image_t *image;
	uint32_t *arr;
	double texture_ox;
	
	image = get_image(mlx);
	mlx_resize_image(image, TILE_SIZE, TILE_SIZE);
	if (mlx->ray->flag)
		texture_ox = (int)fmodf((mlx->ray->v_inter_y * (image->width / TILE_SIZE)), image->width);
	else
		texture_ox = (int)fmodf((mlx->ray->h_inter_x * (image->width / TILE_SIZE)), image->width);
	// printf("v_inter_y: %f\n", mlx->ray->v_inter_y);
	// printf("h_inter_x: %f\n", mlx->ray->h_inter_x);
	arr = (uint32_t *)image->pixels;
	// int y = t_pixel;
	// int distance_top = y - (wall_height / 2) + (S_H / 2);
	// double factor = ((double)texture->height / wall_height);
	double texture_oy = (t_pixel - (S_H / 2) + (wall_height / 2));
	// if (texture_oy < 0)
 // 		texture_oy = 0;
	while (t_pixel < b_pixel)
	{
		// printf("oy: %d\n", texture_oy);
		// printf("arr: %u\n", (texture->width * (int)texture_oy) + (int)texture_ox);
		mlx_put_pixel(mlx->mlx_img, mlx->ray->ray, t_pixel, reverse_bytes (arr[(image->width * (int)texture_oy) + (int)texture_ox]));
		// texture_oy += factor;
		t_pixel++;
	}
}


void	render_wall3d(t_mlx	*mlx, int	ray)
{
	float plane_dis;
	float wall_height;
	float	t_pixel;
	float	b_pixel;

	mlx->ray->distance *= cos(norm_angle(mlx->ray->ray_ngl - mlx->player->angle));
	plane_dis = (S_W / 2) / tan(mlx->player->fov_rd / 2);
	wall_height = (TILE_SIZE / mlx->ray->distance) * plane_dis; // wallstripheight
	t_pixel = (S_H / 2) - (wall_height / 2);
	if (t_pixel < 0)
		t_pixel = 0;
	b_pixel = (S_H / 2) + (wall_height / 2);
	if (b_pixel > S_H)
		b_pixel = S_H;
	mlx->ray->ray = ray;
	draw_wall(mlx, t_pixel, b_pixel, wall_height);
	// draw_floor_ceiling(mlx, ray, t_pixel, b_pixel);
}

///////////////////////////////////////////////////

// void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
// {
// 	if (x < 0)
// 		return ;
// 	else if (x >= S_W)
// 		return ;
// 	if (y < 0)
// 		return ;
// 	else if (y >= S_H)
// 		return ;
// 	mlx_put_pixel(mlx->mlx_img, x, y, color);
// }
//
// double	get_x_o(mlx_texture_t	*texture, t_mlx *mlx)
// {
// 	double	x_o;
//
// 	if (mlx->ray->flag == 0)
// 		x_o = (int)fmodf((mlx->ray->h_inter_x * (texture->width / TILE_SIZE)), texture->width);
// 	else
// 		x_o = (int)fmodf((mlx->ray->v_inter_y * (texture->width / TILE_SIZE)), texture->width);
// 	return (x_o);
// }
//
// void	draw_wall(t_mlx *mlx, int t_pix, int b_pix, double wall_h)
// {
// 	double			x_o;
// 	double			y_o;
// 	mlx_texture_t	*texture;
// 	uint32_t		*arr;
// 	double			factor;
//
// 	texture = get_texture(mlx);
// 	arr = (uint32_t *)texture->pixels;
// 	factor = (double)texture->height / wall_h;
// 	x_o = get_x_o(texture, mlx);
// 	y_o = (t_pix - (S_H / 2) + (wall_h / 2)) * factor;
// 	if (y_o < 0)
// 		y_o = 0;
// 	while (t_pix < b_pix)
// 	{
// 		my_mlx_pixel_put(mlx, mlx->ray->ray, t_pix, reverse_bytes(arr[(int)y_o * texture->width + (int)x_o]));
// 		y_o += factor;
// 		t_pix++;
// 	}
// }
//
// void	render_wall3d(t_mlx *mlx, int ray)
// {
// 	double	wall_h;
// 	double	b_pix;
// 	double	t_pix;
//
// 	mlx->ray->distance *= cos(norm_angle(mlx->ray->ray_ngl - mlx->player->angle));
// 	wall_h = (TILE_SIZE / mlx->ray->distance) * ((S_W / 2) / \
// 	tan(mlx->player->fov_rd / 2));
// 	b_pix = (S_H / 2) + (wall_h / 2);
// 	t_pix = (S_H / 2) - (wall_h / 2);
// 	if (b_pix > S_H)
// 		b_pix = S_H;
// 	if (t_pix < 0)
// 		t_pix = 0;
// 	mlx->ray->ray = ray;
// 	draw_wall(mlx, t_pix, b_pix, wall_h);
// 	// draw_floor_ceiling(mlx, ray, t_pix, b_pix);
// }
