/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_matrix.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 17:21:45 by zmoumen           #+#    #+#             */
/*   Updated: 2023/08/15 18:28:56 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

#define MATRIX_CHARS "01NSEW "

void	validate_matrix_line(char	*mline, int lcount)
{
	int	found_charset;

	found_charset = 0;
	while (*mline && *mline != '\n')
	{
		if (!ft_strchr(MATRIX_CHARS, *mline))
		{
			printf("Found: %c at line: %d!\n", *mline, lcount);
			ft_errmsg("Invalid character in matrix", 1);
		}
		if (*mline != ' ')
			found_charset = 1;
		mline++;
	}
	if (!found_charset)
	{
		printf("Empty line at line: %d!\n", lcount);
		ft_errmsg("Map Matrix Should be Continuous", 1);
	}
}

void	set_player(t_map *map, int x, int y, char **pos)
{
	if (map->player.x != 0)
		ft_errmsg("Duplicate player position", 1);
	map->player.x = x * BLOCK_SIZE + (BLOCK_SIZE / 2);
	map->player.y = y * BLOCK_SIZE + (BLOCK_SIZE / 2);
	if (pos[y][x] == 'E')
		map->player.rorationangle = 2 * M_PI;
	else if (pos[y][x] == 'N')
		map->player.rorationangle = (3 * M_PI) / 2;
	else if (pos[y][x] == 'W')
		map->player.rorationangle = M_PI;
	else if (pos[y][x] == 'S')
		map->player.rorationangle = M_PI / 2;
	pos[y][x] = '0';
	map->player.radius = 5;
	map->player.turndirection = 0;
	map->player.walkdirection = 0;
	map->player.walkside = 0;
	map->player.movespeed = 2;
	map->player.rotationspeed = 2 * (M_PI / 180);
}

void	validate_matrix_maze(t_map *map)
{
	int	y;
	int	x;

	y = 0;
	while (map->matrix[y])
	{
		x = 0;
		while (map->matrix[y][x])
		{
			if (map->matrix[y][x] == ' ')
				(void)x;
			else if ((y * x == 0 || !map->matrix[y + 1]
					|| !map->matrix[y][x + 1]) && map->matrix[y][x] != '1')
				matrix_error(y, x, "Map should be surrounded by walls", map);
			else if (ft_strchr("NSEW0", map->matrix[y][x]) &&
			(map->matrix[y - 1][x] == ' ' || map->matrix[y + 1][x] == ' '
			|| map->matrix[y][x - 1] == ' ' || map->matrix[y][x + 1] == ' '))
				matrix_error(y, x, "Map should be surrounded by walls", map);
			if (ft_strchr("NSEW", map->matrix[y][x]))
				set_player(map, x, y, map->matrix);
			x++;
		}
		y++;
	}
}

void	unionize_matrix_width(t_map *map)
{
	char		**traverser;
	int			tlen;

	traverser = map->matrix;
	map->m_width = 0;
	while (*traverser)
	{
		if (map->m_width < (int)ft_strlen(*traverser))
			map->m_width = ft_strlen(*traverser);
		traverser++;
	}
	traverser = map->matrix;
	while (*traverser)
	{
		tlen = map->m_width - ft_strlen(*traverser);
		if (tlen > 0)
			*traverser = ft_strjoin_free(
					*traverser,
					ft_memset(ft_calloc(tlen + 1, sizeof(char)), ' ', tlen),
					1, 1);
		traverser++;
	}
}

void	get_matrix(int fd, t_map *map)
{
	char	*line;
	char	*tmp;

	line = map->_tx_paths[TEXTURE_MATRIX_TMP];
	tmp = ft_strdup("");
	if (line == NULL)
		ft_errmsg("No map found", 1);
	map->_tx_paths[TEXTURE_MATRIX_TMP] = NULL;
	while (line)
	{
		validate_matrix_line(line, map->f_lcount);
		map->m_lcount++;
		tmp = ft_strjoin_free(tmp, line, 1, 1);
		line = get_next_line(fd);
		if (line)
			map->f_lcount++;
	}
	map->matrix = ft_split(tmp, '\n');
	free(tmp);
	unionize_matrix_width(map);
	validate_matrix_maze(map);
	if (map->player.x == 0)
		ft_errmsg("No player found", 1);
}
