/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cub3d.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-biha <nle-biha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 21:01:47 by nle-biha          #+#    #+#             */
/*   Updated: 2021/04/02 03:04:25 by nle-biha         ###   ########.fr       */
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

int		get_color(char *rgb, t_mapinfo *mapinfo, int line_id)
{
	char **colors;
	int i;
	int j;
	int rgbvalue;

	i = 0;
	colors = ft_split(rgb, ',');
	while (colors[i])
		i++;
	if (i != 3)
		return (exitfunc);
	i = 0;
	while(i < 3)
	{
		j = 0;
		while (colors[i][j])
			if (ft_isdigit(colors[i][j++] == 0)
					return (exitfunc);
		rgbvalue = ft_atoi(colors[i])	
		if (rgbvalue > 255 || rgbvalue < 0)
			return (exifunc)
		if (line_id == 6)
			mapinfo.F[i] == rgbvalue; //rework les structures


	}
	return (1);
}

int		get_resolution(char *xy, t_mapinfo *mapinfo, int line_id)
{	
	printf("getresolution");
	return (1);
}

int		get_pathname(char *pathname, t_mapinfo *mapinfo, int line_id)
{
	printf("pathname");
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
			if (id == 0)
				get_resolution(split_space_line[1], &mapinfo, id);
			else if (id > 5)
				get_color(split_space_line[1], &mapinfo, id);
			else
				get_pathname(split_space_line[1], &mapinfo, id);
		}	
		free(readline);
		free_nulltermchartab(split_space_line);
	}
	free(readline);
	return (mapinfo);
}
/*
int valid_texturefile(t_path texture)
{

}

int valid_infos(s_mapinfo mapinfos)
{

}*/

int main(int argc, char **argv)
{
	int fd;
	t_mapinfo mapinfo;

	if (!valid_mapfile(argv[1]))
		printf("not valid");
		//exit;
	fd = open(argv[1], O_RDONLY);
	mapinfo = getinfo(fd);
}
