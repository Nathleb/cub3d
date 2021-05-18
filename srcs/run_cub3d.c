/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cub3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-biha <nle-biha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 16:27:39 by nle-biha          #+#    #+#             */
/*   Updated: 2021/05/18 23:36:56 by nle-biha         ###   ########.fr       */
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

int	load_textures(t_mapinfo mapinfo, t_game *game)
{
	if ((game->wallNO.img = mlx_xpm_file_to_image(game->mlx, mapinfo.NO, &(game->wallNO.texture_w), &(game->wallNO.texture_h))) != NULL  &&
	(game->wallSO.img = mlx_xpm_file_to_image(game->mlx, mapinfo.SO, &(game->wallSO.texture_w), &(game->wallSO.texture_h))) != NULL &&
	(game->wallEA.img = mlx_xpm_file_to_image(game->mlx, mapinfo.EA, &(game->wallEA.texture_w), &(game->wallEA.texture_h))) != NULL &&
	(game->wallWE.img = mlx_xpm_file_to_image(game->mlx, mapinfo.WE, &(game->wallWE.texture_w), &(game->wallWE.texture_h))) != NULL &&
	(game->spriteS.img = mlx_xpm_file_to_image(game->mlx, mapinfo.S, &(game->spriteS.texture_w), &(game->spriteS.texture_h))))
		return (1);
	printf("fail load texture");
	return (0);
}

void	init_window(t_mapinfo mapinfo)
{
	(void)mapinfo;
	return ;
}

void	startgame(t_mapinfo mapinfo)
{
	t_player player;
	t_game game;
	//void	*img;
	//char	*relative_path = "./test.xpm";
	//int		img_width;
	//int		img_height;

	player_init(&player, mapinfo);
	game.mlx = mlx_init();
	//game.win = mlx_new_window(vars.mlx, mapinfo.R[0], mapinfo.R[1], "Cub3D");	
	load_textures(mapinfo, &game);
	/*mlx_loop(vars.mlx);
	while(!done)
	{

	}*/
}
