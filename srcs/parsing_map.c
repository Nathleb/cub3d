/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-biha <nle-biha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 16:12:46 by nle-biha          #+#    #+#             */
/*   Updated: 2021/05/13 15:47:31 by nle-biha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		is_validline(char *line, t_mapinfo *mapinfo, int cur_nbrlines)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (ft_strchr(MAPCHAR, line[i]) == NULL)
			return (error_get("Bad character in map\n"));
		if (ft_strchr("NSEW", line[i]))
		{
			if (mapinfo->starting_line != -1)
				return (error_get("Multiple starting position\n"));
			mapinfo->starting_col = i;
			mapinfo->starting_line = cur_nbrlines;
			mapinfo->starting_orientation = line[i];
		}
		i++;
	}
	return (1);
}

int		build_map(char *line, t_mapinfo *mapinfo)
{
	int		i;
	int		cur_nbrlines;
	char	**newmap;

	i = 0;
	cur_nbrlines = 0;
	while (mapinfo->map && mapinfo->map[cur_nbrlines])
		cur_nbrlines++;
	if (is_validline(line, mapinfo, cur_nbrlines) == 0)
		return (0);
	newmap = malloc((cur_nbrlines + 2) * sizeof(char*));
	i = -1;
	while (++i < cur_nbrlines)
		newmap[i] = mapinfo->map[i];
	newmap[i] = line;
	newmap[i + 1] = NULL;
	free(mapinfo->map);
	mapinfo->map = newmap;
	return (1);
}

int		flood_fill(char **map, int line, int col)
{
	int ret;

	ret = 1;
	map[line][col] = 'V';
	if (map[line + 1][col] && map[line - 1][col] && map[line][col + 1] &&
	map[line][col - 1] && map[line + 1][col] != ' ' &&
	map[line - 1][col] != ' ' &&
	map[line][col + 1] != ' ' && map[line][col - 1] != ' ')
	{
		if (map[line + 1][col] == '0' || map[line + 1][col] == '2')
			ret = flood_fill(map, line + 1, col);
		if ((map[line - 1][col] == '0' || map[line - 1][col] == 2)
				&& ret == 1)
			ret = flood_fill(map, line - 1, col);
		if ((map[line][col + 1] == '0' || map[line][col + 1] == '2')
				&& ret == 1)
			ret = flood_fill(map, line, col + 1);
		if ((map[line][col - 1] == '0' || map[line][col - 1] == '2')
				&& ret == 1)
			ret = flood_fill(map, line, col - 1);
	}
	else
		return (0);
	return (ret);
}

int		is_validmap(t_mapinfo *mapinfo)
{
	int		i;
	char	**newmap;

	i = 0;
	while (mapinfo->map && mapinfo->map[i])
		i++;
	newmap = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (mapinfo->map && mapinfo->map[i])
	{
		newmap[i] = ft_strdup(mapinfo->map[i]);
		i++;
	}
	newmap[i] = NULL;
	i = 0;
	if (mapinfo->starting_line != -1)
		i = flood_fill(newmap, mapinfo->starting_line, mapinfo->starting_col);
	free_nulltermchartab(newmap);
	return (i);
}
