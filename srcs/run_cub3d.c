/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cub3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-biha <nle-biha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 16:27:39 by nle-biha          #+#    #+#             */
/*   Updated: 2021/05/17 17:28:51 by nle-biha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	startgame(t_mapinfo mapinfo)
{
	t_vars	vars;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, mapinfo.R[0], mapinfo.R[1], "Cub3D");
	
	mlx_loop(vars.mlx);
}
