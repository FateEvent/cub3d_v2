/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 16:48:22 by albaur            #+#    #+#             */
/*   Updated: 2022/10/21 10:50:30 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

static int	check_texture(t_map *m, char *map, int *count, t_ctexture c)
{
	if (c.str[1] == '\0')
	{
		if (map[0] == c.str[0] && map[1] == ' ')
		{
			if (get_color(map, m, c.index) == -1)
				return (1);
			++*count;
			return (0);
		}
	}
	else
	{
		if (map[0] == c.str[0] && map[1] == c.str[1] && map[2] == ' ')
		{
			if (get_texture(map, m, c.index) == -1)
				return (1);
			++*count;
			return (0);
		}
	}
	return (1);
}

static int	check_map_settings(t_map *m, char **map)
{
	size_t			i;
	int				count;

	i = -1;
	count = 0;
	while (map[++i])
	{
		if (ft_strlen(map[i]) < 3)
			return (-1);
		if (!check_texture(m, map[i], &count, (t_ctexture){"NO", 0})
			|| !check_texture(m, map[i], &count, (t_ctexture){"SO", 1})
			|| !check_texture(m, map[i], &count, (t_ctexture){"WE", 2})
			|| !check_texture(m, map[i], &count, (t_ctexture){"EA", 3})
			|| !check_texture(m, map[i], &count, (t_ctexture){"C\0", 0})
			|| !check_texture(m, map[i], &count, (t_ctexture){"F\0", 1}))
			continue ;
		else
		{
			if (count == 6)
				return (0);
			return (-1);
		}
	}
	return (0);
}

static void	check_map_integrity_vol2(t_map *m, char **map)
{
	if (check_map_components(m->map) == -1)
	{
		freearr(map);
		throw_err_ex("Error : Invalid map file.");
	}
	freearr(map);
}

t_map	*check_map_integrity(char *path)
{
	t_map	*mapstruct;
	char	**map;

	mapstruct = malloc(sizeof(t_map));
	if (!mapstruct)
		throw_err_ex("Error : Cannot malloc map structure.");
	map = ft_map_reader(path);
	if (check_map_settings(mapstruct, map) == -1)
	{
		freearr(map);
		throw_err_ex("Error : Invalid map file.");
	}
	mapstruct->map = get_map_description(map);
	if (mapstruct->map == NULL)
	{
		freearr(map);
		throw_err_ex("Error : Invalid map file.");
	}
	check_map_integrity_vol2(mapstruct, map);
	get_spawn_position(mapstruct);
	return (mapstruct);
}

void	check_map_extension(char *argv[])
{
	int	fd;

	if (!ft_strstr(argv[1], ".cub\0"))
		throw_err_ex("Error: Invalid file extension.");
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		close(fd);
		throw_err_ex("Error: Cannot open file.");
	}
	close(fd);
}
