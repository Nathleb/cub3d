/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cub3d.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-biha <nle-biha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 21:01:47 by nle-biha          #+#    #+#             */
/*   Updated: 2021/05/12 16:43:39 by nle-biha         ###   ########.fr       */
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

void parsing_init(t_mapinfo *mapinfo)
{
	int i;

	mapinfo->map = NULL;
	i = 0;
	while(i < 8)
		mapinfo->is_set[i++] = 0;
	mapinfo->starting_line = -1;
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

int main(int argc, char **argv)
{
	int fd;
	int i;

	t_mapinfo mapinfo;
	parsing_init(&mapinfo);
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
