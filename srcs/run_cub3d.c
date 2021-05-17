/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cub3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-biha <nle-biha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 16:27:39 by nle-biha          #+#    #+#             */
/*   Updated: 2021/05/17 18:10:11 by nle-biha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	player_init(t_player *player, t_mapinfo mapinfo)
{
	player->posX = (double)mapinfo.starting_col;
	player->posY = (double)mapinfo.starting_line;
	player->dirX = -1;
	player->dirY = 0;
	player->planeX = 0;
	player->planeY = 0.66;
}

void	startgame(t_mapinfo mapinfo)
{
	t_vars	vars;
	t_player player;
	
	player_init(&player, mapinfo);
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, mapinfo.R[0], mapinfo.R[1], "Cub3D");	
	mlx_loop(vars.mlx);
}
