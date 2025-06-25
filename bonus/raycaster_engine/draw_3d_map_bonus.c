/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham_algo_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 20:58:27 by yowazga           #+#    #+#             */
/*   Updated: 2023/08/15 16:02:44 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	init_arg_line(t_line *line, t_argline *arg)
{
	line->dx = abs(arg->x1 - arg->x0);
	line->dy = abs(arg->y1 - arg->y0);
	if (arg->x0 < arg->x1)
		line->sx = 1;
	else
		line->sx = -1;
	if (arg->y0 < arg->y1)
		line->sy = 1;
	else
		line->sy = -1;
	if (line->dx > line->dy)
		line->err = line->dx / 2;
	else
		line->err = -line->dy / 2;
}

void	draw_line(t_argline arg, mlx_image_t *image)
{
	t_line	line;

	init_arg_line(&line, &arg);
	while (1)
	{
		mlx_put_pixel(image, arg.x0, arg.y0, arg.color);
		if (arg.x0 == arg.x1 && arg.y0 == arg.y1)
			break ;
		line.e2 = line.err;
		if (line.e2 > -line.dx)
		{
			line.err -= line.dy;
			arg.x0 += line.sx;
		}
		if (line.e2 < line.dy)
		{
			line.err += line.dx;
			arg.y0 += line.sy;
		}
	}
}

int	get_texture_index(t_cast *cst)
{
	if (cst->washitvertical && cst->is_left)
		return (TEXTURE_EAST);
	else if (cst->washitvertical && cst->is_right)
		return (TEXTURE_WEST);
	else if (!cst->washitvertical && cst->is_up)
		return (TEXTURE_NORTH);
	else if (!cst->washitvertical && cst->is_down)
		return (TEXTURE_SOUTH);
	ft_errmsg("FATAL: texture index not found", 1);
	return (-1);
}

void	draw_bars(t_game *cb, t_argline arg, mlx_texture_t *t, int idx)
{
	int	y;

	y = arg.y0;
	while (arg.y0 <= arg.y1)
	{
		if (arg.y0 >= WIN_HEIGHT)
			break ;
		if (arg.y0 >= 0)
		{
			cb->y_step = (arg.y0 - y) * (t->height / arg.wal_height);
			if (cb->y_step < (int)t->height
				&& (idx == TEXTURE_SOUTH || idx == TEXTURE_EAST))
				mlx_put_pixel(cb->image, arg.x0, arg.y0,
					txt_pixel(t, cb->x_step, cb->y_step));
			else if (cb->y_step < (int)t->height)
				mlx_put_pixel(cb->image, arg.x0, arg.y0,
					txt_pixel(t, t->width - cb->x_step, cb->y_step));
		}
		arg.y0++;
	}
}

void	draw_3d_recast(t_game *cb, t_argline arg)
{
	mlx_texture_t	*tx;
	int				dx;

	dx = get_texture_index(&cb->cast);
	tx = cb->map.textures[dx];
	if (cb->cast.washitvertical)
		cb->x_step = (tx->width / TILE_SIZE)
			* (cb->cast.wal_y - (int)(cb->cast.wal_y / TILE_SIZE) * TILE_SIZE);
	else
		cb->x_step = (tx->width / TILE_SIZE)
			* (cb->cast.wal_x - (int)(cb->cast.wal_x / TILE_SIZE) * TILE_SIZE);
	draw_bars(cb, arg, tx, dx);
}
