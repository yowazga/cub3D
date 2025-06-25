/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 20:58:11 by yowazga           #+#    #+#             */
/*   Updated: 2023/08/15 15:11:38 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_wall_in_move(t_game *cub)
{
	if ((!check_wall(&cub->map, cub->player.n_x, cub->player.y)
			&& !check_wall(&cub->map, cub->player.x, cub->player.n_y)) \
			|| !check_wall(&cub->map, cub->player.n_x, cub->player.n_y))
		return (1);
	return (0);
}

int	check_side(t_game *cub)
{
	int	mv;

	mv = cub->player.movespeed;
	if (fabs(cub->player.walkside) == 1)
	{
		if (cub->player.walkside == 1)
		{
			cub->player.n_x = cub->player.x
				- cos(cub->player.rorationangle - M_PI / 2) * mv;
			cub->player.n_y = cub->player.y
				- sin(cub->player.rorationangle - M_PI / 2) * mv;
		}
		if (cub->player.walkside == -1)
		{
			cub->player.n_x = cub->player.x
				+ cos(cub->player.rorationangle - M_PI / 2) * mv;
			cub->player.n_y = cub->player.y
				+ sin(cub->player.rorationangle - M_PI / 2) * mv;
		}
		if (check_wall_in_move(cub))
			return (0);
		cub->player.x = cub->player.n_x;
		cub->player.y = cub->player.n_y;
	}
	return (1);
}

void	ft_hook(void *param)
{
	t_game	*cub;
	float	mv;

	cub = (t_game *)param;
	mv = cub->player.walkdirection * cub->player.movespeed;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(cub->mlx);
	if (fabs(cub->player.turndirection) == 1)
	{
		cub->player.rorationangle += cub->player.turndirection
			* cub->player.rotationspeed;
		cub->player.rorationangle = norm_angle(cub->player.rorationangle);
	}
	if (fabs(cub->player.walkdirection) == 1)
	{
		cub->player.n_x = cub->player.x + cos(cub->player.rorationangle) * mv;
		cub->player.n_y = cub->player.y + sin(cub->player.rorationangle) * mv;
		if (check_wall_in_move(cub))
			return ;
		cub->player.x = cub->player.n_x;
		cub->player.y = cub->player.n_y;
	}
	if (check_side(cub) && (fabs(cub->player.turndirection)
			|| fabs(cub->player.walkdirection) || fabs(cub->player.walkside)))
		draw_content(cub);
}

void	check_press(mlx_key_data_t *keydata, t_game *cub)
{
	if (keydata->key == MLX_KEY_W && keydata->action == MLX_PRESS)
		cub->player.walkdirection = 1;
	else if (keydata->key == MLX_KEY_S && keydata->action == MLX_PRESS)
		cub->player.walkdirection = -1;
	else if (keydata->key == MLX_KEY_LEFT && keydata->action == MLX_PRESS)
		cub->player.turndirection = -1;
	else if (keydata->key == MLX_KEY_RIGHT && keydata->action == MLX_PRESS)
		cub->player.turndirection = 1;
	else if (keydata->key == MLX_KEY_A && keydata->action == MLX_PRESS)
		cub->player.walkside = -1;
	else if (keydata->key == MLX_KEY_D && keydata->action == MLX_PRESS)
		cub->player.walkside = 1;
}

void	my_keyhook(mlx_key_data_t keydata, void *param)
{
	t_game	*cub;

	cub = (t_game *)param;
	check_press(&keydata, cub);
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_RELEASE)
		cub->player.walkdirection = 0;
	else if (keydata.key == MLX_KEY_S && keydata.action == MLX_RELEASE)
		cub->player.walkdirection = 0;
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_RELEASE)
		cub->player.turndirection = 0;
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_RELEASE)
		cub->player.turndirection = 0;
	else if (keydata.key == MLX_KEY_A && keydata.action == MLX_RELEASE)
		cub->player.walkside = 0;
	else if (keydata.key == MLX_KEY_D && keydata.action == MLX_RELEASE)
		cub->player.walkside = 0;
}
