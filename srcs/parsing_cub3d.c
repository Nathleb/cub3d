/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cub3d.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-biha <nle-biha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 21:01:47 by nle-biha          #+#    #+#             */
/*   Updated: 2021/05/12 16:04:43 by nle-biha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	allinfo_set(int *is_set)
{
	int i;

	i = 0;
	while(i < 8)
	{
		if (is_set[i] == 0)
			return (0);
		i++;
	}
	return (1);
}

void	free_nulltermchartab(char **tab)
{
	int i;

	i = 0;
	if (tab == NULL)
		return ;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

char	*trim_char(char *string, char c)
{
	while (*string == c)
		string++;
	return (string);
}

int		valid_mapfile(t_path mapfile)
{
	size_t len;

	len = ft_strlen(mapfile);
	if (len >= 4 && mapfile[len - 1] == 'b' && mapfile[len - 2] == 'u'
			&& mapfile[len - 3] == 'c' && mapfile[len - 4] == '.')
		return (1);
	return (0);
}

int		getline_id(char *line_descriptor)
{
int		i;
	int		len;
	char 	*id[9] = {"R","NO","SO","WE","EA","S","F","C", NULL};

	len = ft_strlen(line_descriptor);
	i = 0;
	while (id[i])
	{
		if (ft_strncmp(id[i], line_descriptor, len + 1) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int		error_get(char *errmessage)
{
	write(2, "Error\n", 6);
	write(2, errmessage, ft_strlen(errmessage));
	return (-1);
}

int		get_color(char *rgb, t_mapinfo *mapinfo, int line_id)
{
	char **colors;
	int i;
	int rgbvalue[3];
	int iserr;

	i = 0;
	iserr = 0;
/**/colors = ft_split(rgb, ',');
	while (colors && colors[i])
		i++;
	if (i != 3)
		iserr = 1;
	i = -1;
	while(++i < 3 && iserr != 1)
	{
		rgbvalue[i] = ft_atoi(colors[i]);
		if (!ft_strisdigit(colors[i]) || rgbvalue[i] > 255 || rgbvalue[i] < 0)
			iserr = 1;
	}
	free_nulltermchartab(colors);
	if (iserr)
		return(error_get("Wrong color argument\n"));
	if (line_id == 6)
		mapinfo->F = rgbvalue;
	if (line_id == 7)
		mapinfo->C = rgbvalue;
	return (1);
}

int		get_resolution(char **xy, t_mapinfo *mapinfo)
{	
	int i;
	int sizes[2];
	int iserr;

	i = 0;
	iserr = 0;
	while (xy[i])
		i++;
	if (i != 3)
		iserr = 1;
	i = -1;
	while(++i < 2 && iserr != 1)
	{
		sizes[i] = ft_atoi(xy[i + 1]);
		if (!ft_strisdigit(xy[i + 1]) || sizes[i] < 0)
			iserr = 1;
	}
	if (iserr)
		return(error_get("Wrong resolution argument\n"));
	mapinfo->R = sizes;
	return (1);
}

int		get_pathname(char *pathname, t_mapinfo *mapinfo, int line_id)
{
	int iserr;
//faire une validation du path, voir apres.
// bien regarder les free.
	iserr = 0;
	if (line_id == 1)
		mapinfo->NO = pathname;
	if (line_id == 2)
		mapinfo->SO = pathname;
	if (line_id == 3)
		mapinfo->WE = pathname;
	if (line_id == 4)
		mapinfo->EA = pathname;
	if (line_id == 5)
		mapinfo->S = pathname;
	return (1);
}

int			build_map(char *line, t_mapinfo *mapinfo)
{
	int i;
	int cur_nbrlines;
	char **newmap;	
	i = 0;
	cur_nbrlines = 0;
	while (mapinfo->map && mapinfo->map[cur_nbrlines])
		cur_nbrlines++;
	while(line[i])
	{
		if (ft_strchr(MAPCHAR, line[i]) == NULL)
			return (error_get("BAD CHARACTER IN MAP"));
		if (ft_strchr("NSEW", line[i]))
		{
			if (mapinfo->starting_line != -1)
				return (error_get("Multiple starting position"));
			mapinfo->starting_col = i;
			mapinfo->starting_line = cur_nbrlines;
			mapinfo->starting_orientation = line[i];
		}
				i++;
	}
/**/newmap = malloc((cur_nbrlines + 2) * sizeof(char*));
	i = -1;
	while (++i < cur_nbrlines)
		newmap[i] = mapinfo->map[i];
	newmap[i] = line;
	newmap[i + 1] = NULL;
   	free(mapinfo->map);
	mapinfo->map = newmap;
	return (1);	
}

int 		get_tocall(char **split_space_line, t_mapinfo *mapinfo, int id)
{
	if (mapinfo->is_set[id] == 0)
	{
		mapinfo->is_set[id] = 1;
		if (id == 0)
			return(get_resolution(split_space_line, mapinfo));
		else if (id > 5)
			return(get_color(split_space_line[1], mapinfo, id));
		else
			return(get_pathname(split_space_line[1], mapinfo, id));
	}
	else
		return(error_get("Descriptor appears multiple times"));
}

t_mapinfo	getinfo(int fd, t_mapinfo *mapinfo)
{
	char *readline;
	char **split_space_line;
	int id;
	int isnoterr;

	isnoterr = 1;
	while(get_next_line(fd, &readline) && isnoterr == 1) {
		if (allinfo_set(mapinfo->is_set))
			isnoterr = build_map(readline, mapinfo);	
		else
		{
/**/		split_space_line = ft_split(readline, ' ');
			if (split_space_line[0] && 
					(id = getline_id(split_space_line[0])) != -1 && split_space_line[1])
				isnoterr = get_tocall(split_space_line, mapinfo, id);
			else
				isnoterr = error_get("Wrong descriptor or no value after descriptor");
			free_nulltermchartab(split_space_line);
			free(readline);
		}
	}
	if (isnoterr == 0)
		free(readline);
	else
		build_map(readline, mapinfo);
	return (*mapinfo);
}

int	flood_fill(char **visited, int line, int col)
{
	int ret;
	ret = 1;
	visited[line][col] = 'V';
	if (visited[line + 1][col] && visited[line - 1][col] && visited[line][col + 1] && visited[line][col - 1] && visited[line + 1][col] != ' ' && visited[line - 1][col] != ' ' && visited[line][col + 1] != ' ' && visited[line][col - 1] != ' ')
	{
		if (visited[line + 1][col] == '0' || visited[line + 1][col] == '2')
				ret = flood_fill(visited, line + 1, col);
		if ((visited[line - 1][col] == '0' || visited[line - 1][col] == 2) && ret == 1)
				ret = flood_fill(visited, line - 1, col);
		if ((visited[line][col + 1] == '0' || visited[line][col + 1] == '2') && ret == 1)
				ret = flood_fill(visited, line, col + 1);
		if ((visited[line][col - 1] == '0' || visited[line][col - 1] == '2') && ret == 1)
				ret = flood_fill(visited, line, col - 1);
	}
	else
		return (0);
	return(ret);
	
}

int is_validmap(t_mapinfo *mapinfo)
{	
	int i;
	char **newmap;	
	
	i = 0;
	while (mapinfo->map && mapinfo->map[i])
		i++;
/**/newmap = malloc(sizeof(char *) * (i + 1));
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

int main(int argc, char **argv)
{
	int fd;
	int i;

	t_mapinfo mapinfo;
	mapinfo.map = NULL;
	i = 0;
	while(i < 8)
		mapinfo.is_set[i++] = 0;
	mapinfo.starting_line = -1;
	if (argc != 1 && argc != 2)
		return (error_get("Wrong number of arguments"));
	if (!valid_mapfile(argv[1]))
		return (error_get("Not valid extension"));
	fd = open(argv[1], O_RDONLY);
	mapinfo = getinfo(fd, &mapinfo);
	i = 0;
	while (mapinfo.map[i])
	{
		printf("%d : %s\n",i, mapinfo.map[i]);
		i++;
	}
	if (!is_validmap(&mapinfo))
		error_get("Invalid map");
}
