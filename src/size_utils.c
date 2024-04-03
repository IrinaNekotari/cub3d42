/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmascrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 08:16:14 by nmascrie          #+#    #+#             */
/*   Updated: 2024/04/03 08:16:16 by nmascrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

/**
 * Retourne la taille d'un tableau splitté
*/
int	split_len(char **a)
{
	int	i;

	i = 0;
	while (a[i])
		i++;
	return (i);
}

/**
 * Renvoie le nombre de lignes de la map.
*/
int	map_lines(t_chain *c)
{
	int	i;
	int	lines;

	i = 0;
	lines = 0;
	while (i < NB_ELEMENTS)
	{
		c = c->next;
		i++;
	}
	while (c)
	{
		c = c->next;
		lines++;
	}
	return (lines);
}

/**
 * Renvoie la plus grande longeur possible d'une ligne de la map
 * Incluant le \n
*/
int	map_length(t_chain *c)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (i < NB_ELEMENTS)
	{
		c = c->next;
		i++;
	}
	while (c)
	{
		if ((int)ft_strlen(c->line) > len)
			len = (int)ft_strlen(c->line);
		c = c->next;
	}
	return (len);
}
