/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_mapinfo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-biha <nle-biha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 16:09:13 by nle-biha          #+#    #+#             */
/*   Updated: 2021/05/13 15:56:48 by nle-biha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		get_color(char *rgb, t_mapinfo *mapinfo, int line_id)
{
	char	**colors;
	int		i;
	int		rgbvalue[3];
	int		iserr;

	i = 0;
	iserr = 0;
	colors = ft_split(rgb, ',');
	while (colors && colors[i])
		i++;
	if (i != 3)
		iserr = 1;
	i = -1;
	while (++i < 3 && iserr != 1 && (rgbvalue[i] = ft_atoi(colors[i])) >= 0)
		if (!ft_strisdigit(colors[i]) || rgbvalue[i] > 255)
			iserr = 1;
	free_nulltermchartab(colors);
	if (iserr)
		return (error_get("Wrong color argument\n"));
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
	while (++i < 2 && iserr != 1)
	{
		sizes[i] = ft_atoi(xy[i + 1]);
		if (!ft_strisdigit(xy[i + 1]) || sizes[i] <= 0)
			iserr = 1;
	}
	if (iserr)
		return (error_get("Wrong resolution argument\n"));
	mapinfo->R = sizes;
	return (1);
}

int		get_pathname(char *pathname, t_mapinfo *mapinfo, int line_id)
{
	int iserr;

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

int		get_tocall(char **split_space_line, t_mapinfo *mapinfo, int id)
{
	if (mapinfo->is_set[id] == 0)
	{
		mapinfo->is_set[id] = 1;
		if (id == 0)
			return (get_resolution(split_space_line, mapinfo));
		else if (id > 5)
			return (get_color(split_space_line[1], mapinfo, id));
		else
			return (get_pathname(split_space_line[1], mapinfo, id));
	}
	else
		return (error_get("Descriptor appears multiple times"));
}
