/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmascrie <nmascrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 01:00:53 by nmascrie          #+#    #+#             */
/*   Updated: 2024/03/29 01:00:55 by nmascrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <unistd.h>
# include <fcntl.h>
# include "libft.h"

# define NB_ELEMENTS 6

# define ERR_NOT_ENOUGH_HEADERS 1
# define ERR_TOO_MUCH_HEADERS 2
# define ERR_EMPTY_LINE_IN_MAP 3
# define ERR_HEADER_IN_MAP 4
# define ERR_UNKNOWN_HEADER 5
# define ERR_HEADER_TOO_LARGE 6
# define ERR_HEADER_TOO_THIN 7
# define ERR_INVALID_RGB 8
# define ERR_UNKNOWN_CHARS 9
# define ERR_INVALID_ENTRIES 10
# define ERR_UNCLOSED_MAP 11
# define ERR_NON_UNIQUE_HEADER 12
# define ERR_FILE_NOT_FOUND 404

//DATA; REMPLACE CELUI DU PROJET PAR CELLE LA
//J'AI AJOUT LES IMAGES
//TODO : remplacer les char* en images de mlx

//Pour les images du sol/plafond :
//si les char* associés valent NULL, utilise les couleurs
typedef struct s_imgset
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*floor_img;
	char	*ceiling_img;
	int		floor_color;
	int		ceiling_color;
}	t_imgset;

typedef struct s_data
{
	int			player_x;
	int			player_y;
	int			map_width;
	int			map_height;
	char		player_orientation;
	char		**map;
	t_imgset	*img;
}	t_data;

//Utilisé par le parser; tu peux laisser ça dedans
typedef struct s_chain
{
	char			*line;
	struct s_chain	*next;
	struct s_chain	*previous;
}	t_chain;

int		ft_equals(char *s1, char *s2);
int		is_whitespace(char c);
int		is_rgb(char *a);
int		is_line_map(char *l);
int		is_map_element(char c);
int		get_rgb(char *a);
int		emptyline(char *c);
int		check_map(t_data *d);
int		map_length(t_chain *c);
int		map_lines(t_chain *c);
int		split_len(char **a);
int		check_exists(t_imgset *img);
int		epure(t_chain *c);
int		generate_imgset(t_chain *c, t_imgset *img);
int		has_null_values(t_imgset *img);
int		part_one_img(t_imgset **img, char **li);
int		part_two_img(t_imgset **img, char **li);
int		part_three_img(t_imgset **img, char **li);
int		part_four_img(t_imgset **img, char **li);

void	get_positions(t_data *data);
void	remove_tail(t_chain *c);
void	cut_ligne(t_chain **c);
void	free_chain(t_chain *chain);
void	free_imgset(t_imgset *t);
void	free_data(t_data *d, t_chain *c);
void	free_split(char **a);
void	null_values(t_imgset **img);

char	**generate_map(t_chain *c, int x, int y);

t_data	*generate_data(char *path);
t_data	*data_error(int code, t_data *data, t_chain *values);
t_chain	*to_chain(char *path);

t_chain	*ft_errmsg(char *msg);

#endif