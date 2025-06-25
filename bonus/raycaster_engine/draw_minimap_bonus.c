/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 11:35:58 by yowazga           #+#    #+#             */
/*   Updated: 2023/08/15 16:00:52 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	draw_colom(int i, int j, t_game *cub, int status)
{
	int	a;
	int	b;
	int	save;

	a = i + (TILE_SIZE * cub->minimap_scale);
	while (i <= a)
	{
		b = j + (TILE_SIZE * cub->minimap_scale);
		save = j;
		while (save <= b)
		{
			if (status)
				mlx_put_pixel(cub->minimap, save, i, ft_pixel(47, 79, 79, 120));
			else if (!status)
				mlx_put_pixel(cub->minimap, save, i, 0xffffff78);
			save++;
		}
		i++;
	}
}

void	draw_map(t_game *cub)
{
	int	i;
	int	j;

	i = 0;
	while (i < cub->map.m_lcount)
	{
		j = 0;
		while (j < cub->map.m_width)
		{
			if (cub->map.matrix[i][j] == '1')
				draw_colom(cub->minimap_scale * (i * TILE_SIZE),
					cub->minimap_scale * (j * TILE_SIZE), cub, 1);
			else if (cub->map.matrix[i][j] == '0')
				draw_colom(cub->minimap_scale * (i * TILE_SIZE),
					cub->minimap_scale * (j * TILE_SIZE), cub, 0);
			j++;
		}
		i++;
	}
}

void	init_lin_player(t_game *cub, t_argline *arg)
{
	arg->x0 = cub->player.x * cub->minimap_scale;
	arg->y0 = cub->player.y * cub->minimap_scale;
	arg->x1 = (cub->player.x + cos(cub->player.rorationangle) * 25)
		* cub->minimap_scale;
	arg->y1 = (cub->player.y + sin(cub->player.rorationangle) * 25)
		* cub->minimap_scale;
	arg->color = ft_pixel(255, 38, 60, 120);
	draw_line(*arg, cub->minimap);
}

void	draw_player(t_game *cub)
{
	int		x;
	int		y;
	int		dx;
	int		dy;
	int		distance_squared;

	x = (cub->player.x - cub->player.radius) * cub->minimap_scale;
	while (x < (cub->player.x + cub->player.radius) * cub->minimap_scale)
	{
		y = (cub->player.y - cub->player.radius) * cub->minimap_scale;
		while (y < (cub->player.y + cub->player.radius) * cub->minimap_scale)
		{
			dx = x - cub->player.x * cub->minimap_scale;
			dy = y - cub->player.y * cub->minimap_scale;
			distance_squared = dx * dx + dy * dy;
			if (distance_squared < (cub->player.radius * cub->player.radius)
				* cub->minimap_scale)
				mlx_put_pixel(cub->minimap, x, y, ft_pixel(255, 38, 60, 120));
			y++;
		}
		x++;
	}
}
