/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 20:57:39 by yowazga           #+#    #+#             */
/*   Updated: 2023/08/15 14:44:08 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

int	check_wall(t_map *map, float x, float y)
{
	int	x_map;
	int	y_map;

	x_map = (int)x / TILE_SIZE;
	y_map = (int)y / TILE_SIZE;
	if (x_map < 0 || x_map >= map->m_width
		|| y_map < 0 || y_map >= map->m_lcount)
		return (1);
	if (map->matrix[y_map][x_map] == '1')
		return (0);
	return (1);
}

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

float	norm_angle(float angle)
{
	if (angle < 0)
		angle = (2 * M_PI) + angle;
	if (angle > 2 * M_PI)
		angle = angle - (2 * M_PI);
	return (angle);
}

float	distance_two_poins(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void	handl_err_pixl(t_game *cub)
{
	if (cub->cast.is_up && cub->cast.is_left)
	{
		cub->cast.wal_x += 1;
		cub->cast.wal_y += 1;
	}
	else if (cub->cast.is_up && cub->cast.is_right)
	{
		cub->cast.wal_x -= 1;
		cub->cast.wal_y += 1;
	}
	if (cub->cast.is_down && cub->cast.is_left)
	{
		cub->cast.wal_x += 1;
		cub->cast.wal_y -= 1;
	}
	else if (cub->cast.is_down && cub->cast.is_right)
	{
		cub->cast.wal_x -= 1;
		cub->cast.wal_y -= 1;
	}
}
