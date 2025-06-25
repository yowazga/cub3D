/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 01:16:54 by zmoumen           #+#    #+#             */
/*   Updated: 2023/08/15 18:36:45 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	_set_texture(char **texture, char *path, int lcount, char *key)
{
	int	i;

	i = 0;
	if (*texture != NULL)
	{
		printf("Duplicate texture at line %d\n", lcount);
		ft_errmsg("Duplicate texture", 1);
	}
	while (path[i] && path[i] == ' ')
		i++;
	i += ft_strlen(key);
	while (path[i] && path[i] == ' ')
		i++;
	if (path[i] == '\0' || path[i] == '\n')
	{
		printf("Invalid texture path at line %d\n", lcount);
		ft_errmsg("Invalid texture path", 1);
	}
	*texture = ft_substr(path, i, ft_strlen(path + i) - 1);
}

void	_validate_texture(char	*line, t_map *map)
{
	int			j;
	char		**tmp;
	static char	*t_prfx[6] = {"NO", "SO", "WE", "EA", "F", "C"};

	tmp = ft_split(line, ' ');
	j = 0;
	while (j < 6)
	{
		if (ft_strncmp(tmp[0], t_prfx[j], ft_strlen(tmp[0])) == 0)
		{
			_set_texture(&map->_tx_paths[j],
				line, map->f_lcount, t_prfx[j]);
			ft_strlstfree(tmp);
			return ;
		}
		j++;
	}
	printf("Invalid texture key at line %d: %s\n", map->f_lcount, line);
	ft_errmsg("Invalid or incomplete list of textures", 1);
}

int	line_is_matrix(char *line, t_map *map)
{
	int	i;

	(void)map;
	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] == '1' || line[i] == '0')
		return (1);
	return (0);
}

void	check_all_textures_exist(t_map	*map)
{
	static char	*t_prfx[6] = {"NO", "SO", "WE", "EA", "F", "C"};
	int			i;

	i = 0;
	while (i < 6)
	{
		if (map->_tx_paths[i] == NULL)
		{
			printf("Missing texture: %s\n", t_prfx[i]);
			ft_errmsg("Missing texture", 1);
		}
		i++;
	}
}

/// @brief set the textures field in the map struct
void	get_textures(t_map *map, int fd)
{
	char	*line;

	line = skip_empty_lines(fd, &map->f_lcount);
	if (line == NULL)
		ft_errmsg("File is Empty", 1);
	while (line)
	{	
		if (line_is_matrix(line, map))
		{
			map->_tx_paths[TEXTURE_MATRIX_TMP] = line;
			break ;
		}
		_validate_texture(line, map);
		free(line);
		line = skip_empty_lines(fd, &map->f_lcount);
	}
	check_all_textures_exist(map);
}
