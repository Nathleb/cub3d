/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-biha <nle-biha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 21:04:38 by nle-biha          #+#    #+#             */
/*   Updated: 2021/05/17 14:17:33 by nle-biha         ###   ########.fr       */
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

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct	s_vars {
	void	*mlx;
	void	*win;
}				t_vars;

int		ft_strisdigit(const char *str);
char	*ft_strjoin_free(char *s1, char *s2);
int		get_next_line(int fd, char **line);
int 	get_tocall(char **split_space_line, t_mapinfo *mapinfo, int id);
int		get_pathname(char *pathname, t_mapinfo *mapinfo, int line_id);
int		get_resolution(char **xy, t_mapinfo *mapinfo);
int		get_color(char *rgb, t_mapinfo *mapinfo, int line_id);
int		build_map(char *line, t_mapinfo *mapinfo);
int		flood_fill(char **visited, int line, int col);
int 	is_validmap(t_mapinfo *mapinfo);
void    free_nulltermchartab(char **tab);
int     error_get(char *errmessage);
int		getinfo(int fd, t_mapinfo *mapinfo);
int		valid_mapfile(t_path mapfile);
void	parsing_init(t_mapinfo *mapinfo);
void    startgame(t_mapinfo mapinfo);

#endif
