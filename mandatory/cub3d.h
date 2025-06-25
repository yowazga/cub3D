/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 00:47:12 by zmoumen           #+#    #+#             */
/*   Updated: 2023/08/15 16:01:28 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <MLX42.h>
# include <libft.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <libft.h>
# include <errno.h>
# include <string.h>
# include <stdio.h>
# include <math.h>
# include <limits.h>

# define WIN_WIDTH 1700
# define WIN_HEIGHT 1200
# define WIN_TITLE "Cub3D"
# define BLOCK_SIZE 64

# define TILE_SIZE 64

# define WALL_STRIP_WIDTH 1

// # define cub->minimap_scale 0.1   

typedef struct s_cast
{
	float	rayangle;
	int		washitvertical;
	float	distance;
	float	wal_x;
	float	wal_y;
	float	horwallhilt_x;
	float	horwallhilt_y;
	float	verwallhilt_x;
	float	verwallhilt_y;
	float	hordistance;
	float	verdistance;
	float	dx;
	float	dy;
	float	x_intercept;
	float	y_intercept;
	int		is_down;
	int		is_up;
	int		is_right;
	int		is_left;
	int		fondhorwal;
	int		fondverwal;
}			t_cast;

typedef struct s_argline
{
	int			x0;
	int			y0;
	int			x1;
	int			y1;
	float		wal_height;
	float		distance;
	float		cor_dis;
	int32_t		color;
}				t_argline;

typedef struct s_player
{
	float	x;
	float	y;
	float	radius;
	float	turndirection;
	float	walkdirection;
	float	walkside;
	float	rorationangle;
	float	movespeed;
	float	rotationspeed;
	float	n_x;
	float	n_y;
}			t_player;

enum e_texture_index
{
	TEXTURE_NORTH,
	TEXTURE_SOUTH,
	TEXTURE_EAST,
	TEXTURE_WEST,
	TEXTURE_FLOOR,
	TEXTURE_CEILING,
	TEXTURE_MATRIX_TMP
};

typedef struct s_map
{
	int				f_lcount;
	int				m_lcount;
	int				m_width;
	char			*_tx_paths[7];
	mlx_texture_t	*textures[6];
	uint32_t		floor_c;
	uint32_t		ceiling_c;
	char			**matrix;
	t_player		player;
}				t_map;

typedef struct t_game
{
	float			fov_angle;
	float			num_rays;
	t_map			map;
	t_cast			cast;
	t_player		player;
	mlx_t			*mlx;
	mlx_image_t		*image;
	int				y_step;
	int				x_step;
	float			wall_project;

}			t_game;

int			open_cub_file(char *fpath);
void		get_textures(t_map *map, int fd);
void		get_matrix(int fd, t_map	*map);
char		*skip_empty_lines(int fd, int *lcount);
void		load_textures(t_map *map);
t_map		load_map(char	*fpath);
void		matrix_error(int y, int x, char *msg, t_map *map);
void		my_keyhook(mlx_key_data_t keydata, void *param);
void		check_press(mlx_key_data_t *keydata, t_game *cub);
void		ft_hook(void *param);
int			check_side(t_game *cub);
int			check_wall_in_move(t_game *cub);
void		draw_content(t_game *cub);
void		draw_3d_map(t_game *cub);
void		init_image(t_game *cub);
void		cast_ray(t_game *cub, float rayangle);
void		calculate_distances(t_game *cub);
void		handl_recast_vertical(t_game *cub);
void		init_ver_content(t_game *cub);
void		handl_recast_horizontal(t_game *cub);
void		init_hor_content(t_game *cub);
float		distance_two_poins(float x1, float y1, float x2, float y2);
float		norm_angle(float angle);
int			check_wall(t_map *map, float x, float y);
int32_t		ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
uint32_t	txt_pixel(mlx_texture_t *texture, int x, int y);
void		draw_3d_recast(t_game *cub, t_argline arg);
#endif