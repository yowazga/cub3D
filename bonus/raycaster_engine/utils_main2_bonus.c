/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_main2_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 16:00:58 by yowazga           #+#    #+#             */
/*   Updated: 2023/08/15 16:01:12 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	ft_hook_mous(t_game *cub)
{
	mlx_get_mouse_pos(cub->mlx, &cub->x_mous, &cub->y_mous);
	if (fabs(cub->player.turndirection) == 1 || cub->x_mous < 0
		|| cub->x_mous > WIN_WIDTH
		|| cub->y_mous < 0 || cub->y_mous > WIN_HEIGHT)
		return ;
	cub->player.rorationangle = (cub->x_mous * (2 * M_PI)) / WIN_WIDTH;
	cub->player.rorationangle = norm_angle(cub->player.rorationangle);
	if (!cub->player.walkdirection && !cub->player.walkside)
		draw_content(cub);
}

void	check_rotasion(t_game *cub)
{
	if (fabs(cub->player.turndirection) == 1)
	{
		cub->player.rorationangle += cub->player.turndirection
			* cub->player.rotationspeed;
		cub->player.rorationangle = norm_angle(cub->player.rorationangle);
	}
}
