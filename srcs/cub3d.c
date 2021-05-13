/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-biha <nle-biha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 15:57:07 by nle-biha          #+#    #+#             */
/*   Updated: 2021/05/13 15:57:45 by nle-biha         ###   ########.fr       */
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
		return (error_get("Exiting..."));
	while (mapinfo.map[i])
	{
		printf("%d : %s\n",i, mapinfo.map[i]);
		i++;
	}
	if (!is_validmap(&mapinfo))
		error_get("Invalid map\n");
}

