/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 17:29:00 by zmoumen           #+#    #+#             */
/*   Updated: 2023/08/15 18:17:47 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	draw_content(t_game *cub)
{
	t_argline	arg;

	init_image(cub);
	draw_3d_map(cub);
	draw_map(cub);
	init_lin_player(cub, &arg);
	draw_player(cub);
}

int	init_content(t_game *cub, char *path)
{
	cub->map = load_map(path);
	cub->minimap_scale = 0.6;
	if (cub->map.m_width > 25 || cub->map.m_lcount > 25)
		cub->minimap_scale = 0.1;
	cub->fov_angle = 60 * (M_PI / 180);
	cub->num_rays = WIN_WIDTH / WALL_STRIP_WIDTH;
	cub->player = cub->map.player;
	cub->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "CUB3D", true);
	mlx_set_mouse_pos(cub->mlx, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	if (!cub->mlx)
		exit(printf("Error: Fatal :%s\n", mlx_strerror(mlx_errno)));
	cub->image = mlx_new_image(cub->mlx, WIN_WIDTH, WIN_HEIGHT);
	cub->minimap = mlx_new_image(cub->mlx,
			cub->map.m_width * BLOCK_SIZE * cub->minimap_scale,
			cub->map.m_lcount * BLOCK_SIZE * cub->minimap_scale);
	if (!cub->image || ! cub->minimap
		|| mlx_image_to_window(cub->mlx, cub->image, 0, 0) == -1
		|| mlx_image_to_window(cub->mlx, cub->minimap, 0, 0) == -1)
		exit(printf("Error: Fatal :%s\n", mlx_strerror(mlx_errno)));
	return (0);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
		ft_errmsg("Please provide one map[.ber] file", 1);
	ft_bzero(&game, sizeof(t_game));
	if (init_content(&game, av[1]))
		return (1);
	draw_content(&game);
	mlx_loop_hook(game.mlx, ft_hook, &game);
	mlx_key_hook(game.mlx, &my_keyhook, &game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	return (0);
}
