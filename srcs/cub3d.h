/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-biha <nle-biha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 21:04:38 by nle-biha          #+#    #+#             */
/*   Updated: 2021/03/29 00:51:24 by nle-biha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 64
# endif
# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
typedef struct s_resolution
{
	int res_x;
	int res_y;
}	t_resolution;

typedef struct s_color
{
	int R;
	int G;
	int B;
}	t_color;

typedef char* t_path;

typedef struct s_mapinfo
{
	t_resolution R;
	t_path NO;
	t_path SO;
	t_path WE;
	t_path EA;
	t_path S;
	t_color F;
	t_color C;
}		t_mapinfo;

char	*ft_strjoin_free(char *s1, char *s2);
int		get_next_line(int fd, char **line);
#endif
