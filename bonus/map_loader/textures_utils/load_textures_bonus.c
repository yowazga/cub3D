/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 20:06:43 by zmoumen           #+#    #+#             */
/*   Updated: 2023/08/15 18:22:21 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	verify_colorline(char *line)
{
	while (*line)
	{
		if (!ft_isdigit(*line) && *line != ',')
		{
			printf("invalid character in color line: `%c'\n", *line);
			ft_errmsg("Invalid color line", 1);
		}
		line++;
	}
}

uint32_t	parse_color(char	*tline)
{
	char		**split;
	int			rgb[3];
	int			i;

	verify_colorline(tline);
	split = ft_split(tline, ',');
	i = 0;
	while (split[i])
	{
		if (i > 2)
			ft_errmsg("Invalid color line", 1);
		rgb[i] = ft_atoi(split[i]);
		if (rgb[i] < 0 || rgb[i] > 255 || ft_strlen(split[i]) > 3)
			ft_errmsg("Invalid color line", 1);
		i++;
	}
	if (i < 3)
		ft_errmsg("Invalid color line", 1);
	ft_strlstfree(split);
	return (ft_pixel(rgb[0], rgb[1], rgb[2], 255));
}

mlx_texture_t	*load_image(char	*tpath)
{	
	mlx_texture_t	*image;

	image = mlx_load_png(tpath);
	if (!image)
	{
		printf("Couldn't load %s: %s\n", tpath, mlx_strerror(mlx_errno));
		printf("make sure path is a valid [.png] relative to executable\n");
		ft_errmsg("Invalid texture path", 1);
	}
	if (image->width != image->height)
	{
		printf("texture %s has invalid size.\n", tpath);
		printf("Make sure the texture is a square.\n");
		ft_errmsg("Invalid texture size", 1);
	}
	return (image);
}

void	load_textures(t_map *map)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (!map->_tx_paths[i])
			ft_errmsg("Missing texture path", 1);
		map->textures[i] = load_image(map->_tx_paths[i]);
		i++;
	}
	if (!map->_tx_paths[TEXTURE_FLOOR])
		ft_errmsg("Missing floor color", 1);
	map->floor_c = parse_color(map->_tx_paths[TEXTURE_FLOOR]);
	if (!map->_tx_paths[TEXTURE_CEILING])
		ft_errmsg("Missing ceiling color", 1);
	map->ceiling_c = parse_color(map->_tx_paths[TEXTURE_CEILING]);
}
