/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-biha <nle-biha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 15:57:07 by nle-biha          #+#    #+#             */
/*   Updated: 2021/05/18 23:07:13 by nle-biha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int 	main(int argc, char **argv)
{
	int fd;
	int i;

	t_mapinfo mapinfo;
	parsing_init(&mapinfo);
	if (argc != 1 && argc != 2)
		return (error_get("Wrong number of arguments\n"));
	if (!valid_mapfile(argv[1]))
		return (error_get("Not a valid extension\n"));
	fd = open(argv[1], O_RDONLY);
	i = 0;
	if (getinfo(fd, &mapinfo) == 0)
	{
		free_nulltermchartab(mapinfo.map);
		return (error_get("Exiting...\n"));
	}
	if (!is_validmap(&mapinfo))
	{
		free_nulltermchartab(mapinfo.map);
		return (error_get("Invalid map\nExiting...\n"));
	}
	free_nulltermchartab(mapinfo.map);
	printf("%d %d\n", mapinfo.R[0],mapinfo.R[1]);
	printf("%s \n",mapinfo.NO);
	printf("%s \n",mapinfo.SO);
	printf("%s \n",mapinfo.WE);
	printf("%s \n",mapinfo.EA);
	printf("%s \n",mapinfo.S);
	printf("%d %d %d \n", mapinfo.F[0],mapinfo.F[1],mapinfo.F[2]);
	printf("%d %d %d \n", mapinfo.C[0],mapinfo.C[1],mapinfo.C[2]);
	printf("%d %d\n", mapinfo.starting_line, mapinfo.starting_col);
	printf("%c \n",mapinfo.starting_orientation);
	startgame(mapinfo);
}
