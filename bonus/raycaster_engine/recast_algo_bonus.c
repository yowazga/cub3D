/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recast_algo_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 20:58:18 by yowazga           #+#    #+#             */
/*   Updated: 2023/08/15 14:44:08 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	calculate_distances(t_game *cub)
{
	if (cub->cast.fondhorwal)
		cub->cast.hordistance = distance_two_poins(cub->player.x, \
			cub->player.y, cub->cast.horwallhilt_x, cub->cast.horwallhilt_y);
	else
		cub->cast.hordistance = INT_MAX;
	if (cub->cast.fondverwal)
		cub->cast.verdistance = distance_two_poins(cub->player.x, \
			cub->player.y, cub->cast.verwallhilt_x, cub->cast.verwallhilt_y);
	else
		cub->cast.verdistance = INT_MAX;
	if (cub->cast.verdistance < cub->cast.hordistance)
	{
		cub->cast.wal_x = cub->cast.verwallhilt_x;
		cub->cast.wal_y = cub->cast.verwallhilt_y;
		cub->cast.distance = cub->cast.verdistance;
		cub->cast.washitvertical = 1;
	}
	else
	{
		cub->cast.wal_x = cub->cast.horwallhilt_x;
		cub->cast.wal_y = cub->cast.horwallhilt_y;
		cub->cast.distance = cub->cast.hordistance;
		cub->cast.washitvertical = 0;
	}
}

void	cast_ray(t_game *cub, float rayangle)
{
	cub->cast.rayangle = norm_angle(rayangle);
	cub->cast.wal_x = 0;
	cub->cast.wal_y = 0;
	cub->cast.distance = 0;
	cub->cast.washitvertical = 0;
	if (cub->cast.rayangle > 0 && cub->cast.rayangle < M_PI)
		cub->cast.is_down = 1;
	else
		cub->cast.is_down = 0;
	cub->cast.is_up = !cub->cast.is_down;
	if (cub->cast.rayangle < 0.5 * M_PI || cub->cast.rayangle > 1.5 * M_PI)
		cub->cast.is_right = 1;
	else
		cub->cast.is_right = 0;
	cub->cast.is_left = !cub->cast.is_right;
	handl_recast_horizontal(cub);
	handl_recast_vertical(cub);
	calculate_distances(cub);
}

void	init_image(t_game *cub)
{
	int	x;
	int	y;

	y = 0;
	while (y < (int)cub->image->height)
	{
		x = 0;
		while (x < (int)cub->image->width)
		{
			if (y <= (int)cub->image->height / 2)
				mlx_put_pixel(cub->image, x++, y, cub->map.ceiling_c);
			else if (y < (int)cub->image->height)
				mlx_put_pixel(cub->image, x++, y, cub->map.floor_c);
		}
		y++;
	}
}

void	draw_3d_map(t_game *cub)
{
	t_argline	arg;
	float		rayangle;
	int			i;

	i = -1;
	rayangle = cub->player.rorationangle - (cub->fov_angle / 2);
	arg.distance = (WIN_WIDTH / 2) / tan(cub->fov_angle / 2);
	while (++i < cub->num_rays)
	{
		cast_ray(cub, rayangle);
		arg.cor_dis = cub->cast.distance
			* cos(rayangle - cub->player.rorationangle);
		arg.wal_height = (TILE_SIZE / arg.cor_dis) * arg.distance;
		arg.x0 = i;
		arg.x1 = i;
		arg.y0 = (WIN_HEIGHT / 2) - (arg.wal_height / 2);
		arg.y1 = (WIN_HEIGHT / 2) + (arg.wal_height / 2);
		draw_3d_recast(cub, arg);
		rayangle += cub->fov_angle / cub->num_rays;
	}
}
