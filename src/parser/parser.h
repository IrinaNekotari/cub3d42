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

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft.h"

# define NB_ELEMENTS 6

//DATA; REMPLACE CELUI DU PROJET PAR CELLE LA
//J'AI AJOUT LES IMAGES
//TODO : remplacer les char* en images de mlx

//Pour les images du sol/plafond :
//si les char* associés valent NULL, utilise les couleurs
typedef struct s_imgset
{
    char    *no;
    char    *so;
    char    *we;
    char    *ea;
    char    *floor_img;
    char    *ceiling_img;
    int     floor_color;
    int     ceiling_color;
}   t_imgset;

typedef struct s_data
{
        char **map;
        int player_x;
        int player_y;
        int map_width;
        int map_height;
        t_imgset img;
} t_data;

//Utilisé par le parser; tu peux laisser ça dedans
typedef struct s_chain
{
    char *line;
    struct s_chain *next;
    struct s_chain *previous;
}   t_chain;

typedef struct s_tuple
{
    char    *a;
    char    *b;
} t_tuple;

t_chain *to_chain(char *path);
t_chain     *ft_errmsg(char *msg);
void        free_chain(t_chain *chain);
int generate_imgset(t_chain *c, t_imgset *img);
int	is_whitespace(char c);
int	ft_equals(char *s1, char *s2);
int is_rgb(char *a);
int get_rgb(char *a);
int     emptyline(char *c);
int epure(t_chain *c);
void    remove_tail(t_chain *c);
void 		free_imgset(t_imgset *t);
#endif