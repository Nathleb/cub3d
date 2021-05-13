/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cub3d.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-biha <nle-biha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 21:01:47 by nle-biha          #+#    #+#             */
/*   Updated: 2021/05/13 15:58:06 by nle-biha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		allinfo_set(int *is_set)
{
	int i;

	i = 0;
	while (i < 8)
	{
		if (is_set[i] == 0)
			return (0);
		i++;
	}
	return (1);
}

void	parsing_init(t_mapinfo *mapinfo)
{
	int i;

	mapinfo->map = NULL;
	i = 0;
	while (i < 8)
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
	int		len;

	len = ft_strlen(line_descriptor);
	if (ft_strncmp("R", line_descriptor, len + 1) == 0)
		return (0);
	if (ft_strncmp("NO", line_descriptor, len + 1) == 0)
		return (1);
	if (ft_strncmp("SO", line_descriptor, len + 1) == 0)
		return (2);
	if (ft_strncmp("WE", line_descriptor, len + 1) == 0)
		return (3);
	if (ft_strncmp("EA", line_descriptor, len + 1) == 0)
		return (4);
	if (ft_strncmp("S", line_descriptor, len + 1) == 0)
		return (5);
	if (ft_strncmp("F", line_descriptor, len + 1) == 0)
		return (6);
	if (ft_strncmp("C", line_descriptor, len + 1) == 0)
		return (7);
	return (-1);
}

int		getinfo(int fd, t_mapinfo *mapinfo)
{
	char	*rl;
	char	**split_space_line;
	int		id;
	int		bo;

	bo = 1;
	while (get_next_line(fd, &rl) && bo == 1)
	{
		if (allinfo_set(mapinfo->is_set) && (bo = build_map(rl, mapinfo)) >= 0)
			continue;
		split_space_line = ft_split(rl, ' ');
		if (split_space_line[0] &&
	(id = getline_id(split_space_line[0])) != -1 && split_space_line[1])
			bo = get_tocall(split_space_line, mapinfo, id);
		else
			bo = error_get("Wrong descriptor or no value\n");
		free_nulltermchartab(split_space_line);
		free(rl);
	}
	if (bo == 0)
		free(rl);
	else
		build_map(rl, mapinfo);
	return (bo);
}
