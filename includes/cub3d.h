/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-biha <nle-biha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 21:04:38 by nle-biha          #+#    #+#             */
/*   Updated: 2021/05/10 15:30:36 by nle-biha         ###   ########.fr       */
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
# include "../mlx_linux/mlx.h"
# define MAPCHAR "10NWES2 \n"
typedef int *t_resolution;

typedef int *t_color;

typedef char* t_path;

typedef struct s_mapinfo
{
	t_resolution	R;
	t_path			NO;
	t_path			SO;
	t_path			WE;
	t_path			EA;
	t_path			S;
	t_color 		F;
	t_color			C;
	int				is_set[8];
	char			**map;
	int				starting_line;
	int				starting_col;
	char			starting_orientation;
}		t_mapinfo;

int		ft_strisdigit(const char *str);
char	*ft_strjoin_free(char *s1, char *s2);
int		get_next_line(int fd, char **line);
#endif
