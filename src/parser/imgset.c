/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imgset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmascrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 08:50:59 by nmascrie          #+#    #+#             */
/*   Updated: 2024/04/03 08:51:00 by nmascrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	truc(int code, char ***li)
{
	free_split(*li);
	return (code);
}

void	move_up(char ***li, int *i, t_chain **c)
{
	free_split(*li);
	*i += 1;
	(*c) = (*c)->next;
}

int	samere(t_imgset **img, char ***li)
{
	if (part_one_img(img, *li))
		return (1);
	if (part_two_img(img, *li))
		return (1);
	if (part_three_img(img, *li) == 1)
		return (1);
	if (part_four_img(img, *li) == 1)
		return (1);
	return (0);
}

/**
 * Remplis l'imgset en fonction des premières lignes de la map
 * Retourne ERR_UNKNOWN_HEADER si l'une des entêtes n'est pas reconnue
 * Retourne -2 si l'entête possède trop de valeurs
 * Retourne -3 si l'entête possède pas assez de valeurs
 * Retourne -4 si une valeur RGB est invalide
 * Retourne 0 sinon
*/
int	generate_imgset(t_chain *c, t_imgset *img)
{
	int		i;
	char	**li;

	i = 0;
	li = NULL;
	null_values(&img);
	while (i < NB_ELEMENTS)
	{
		li = ft_split(c->line, ' ');
		if (split_len(li) > 2)
			return (truc(ERR_HEADER_TOO_LARGE, &li));
		else if (split_len(li) < 2)
			return (truc(ERR_HEADER_TOO_THIN, &li));
		if (!samere(&img, &li))
		{
			if (!part_three_img(&img, li) || !part_four_img(&img, li))
				return (truc(ERR_INVALID_RGB, &li));
			return (truc(ERR_UNKNOWN_HEADER, &li));
		}
		move_up(&li, &i, &c);
	}
	if (has_null_values(img))
		return (ERR_NON_UNIQUE_HEADER);
	return (0);
}
