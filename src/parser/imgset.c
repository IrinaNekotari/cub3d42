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
		if (split_len(li) != 2)
		{
			free_split(li);
			if (split_len(li) > 2)
				return (ERR_HEADER_TOO_LARGE);
			else
				return (ERR_HEADER_TOO_THIN);
		}
		if (part_one(&img, li) || part_two(&img, li))
		{
			free_split(li);
			i++;
			c = c->next;
			continue ;
		}
		else if (part_three(&img, li) == 1 || part_four(&img, li) == 1)
		{
			free_split(li);
			i++;
			c = c->next;
			continue ;
		}
		else if (!part_three(&img, li) || !part_four(&img, li))
		{
			free_split(li);
			return (ERR_INVALID_RGB);
		}
		else
		{
			free_split(li);
			return (ERR_UNKNOWN_HEADER);
		}
		free_split(li);
		i++;
		c = c->next;
	}
	if (has_null_values(img))
		return (ERR_NON_UNIQUE_HEADER);
	return (0);
}
