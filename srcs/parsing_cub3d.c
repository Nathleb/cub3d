/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cub3d.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-biha <nle-biha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 21:01:47 by nle-biha          #+#    #+#             */
/*   Updated: 2021/04/26 16:20:53 by nle-biha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	char	**identifiers;
	int		i;
	int		len;

	len = ft_strlen(line_descriptor);
	identifiers = ft_split(ID, ' ');
	i = 0;
	while (identifiers[i])
	{
		if (ft_strncmp(identifiers[i], line_descriptor, len) == 0)
		{
			free_nulltermchartab(identifiers);
			return (i);
		}
		i++;
	}
	free_nulltermchartab(identifiers);
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
	colors = ft_split(rgb, ',');
	while (colors[i])
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


t_mapinfo	getinfo(int fd)
{
	char *readline;
	char **split_space_line;
	int id;
	t_mapinfo mapinfo;

	while(get_next_line(fd, &readline))
	{
		split_space_line = ft_split(readline, ' ');
		if (split_space_line[0] && 
				(id = getline_id(split_space_line[0])) != -1)
		{
			if (id == 0 && split_space_line[1])
				get_resolution(split_space_line, &mapinfo);
			else if (id > 5 && split_space_line[1])
				get_color(split_space_line[1], &mapinfo, id);
			else if (split_space_line[1])
				get_pathname(split_space_line[1], &mapinfo, id);
			else
				error_get("No value after identifier\n");
		}	
		free(readline);
		free_nulltermchartab(split_space_line);
	}
	free(readline);
	return (mapinfo);
}

int main(int argc, char **argv)
{
	int fd;
	t_mapinfo mapinfo;

	(void) argc;
	if (!valid_mapfile(argv[1]))
	{
		printf("not valid");
		return (0);
	}
	fd = open(argv[1], O_RDONLY);
	mapinfo = getinfo(fd);
}
