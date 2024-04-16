/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmascrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 08:09:27 by nmascrie          #+#    #+#             */
/*   Updated: 2024/04/03 08:09:29 by nmascrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

/**
 * Libere la zone memoire associee a la liste chainee.
*/
void	free_chain(t_chain *chain)
{
	if (!chain)
		return ;
	while (chain->previous)
		chain = chain->previous;
	while (chain)
	{
		if (chain->line)
			free(chain->line);
		if (!chain->next)
			break ;
		chain = chain->next;
		free(chain->previous);
	}
	free(chain);
}

/**
 * Libère la mémoire associée a la structure de donnée.
*/
void	free_data(t_data *d, t_chain *c)
{
	if (c)
		free_chain(c);
	if (!d)
		return ;
	free_split(d->map);
	free_imgset(d->img);
	free(d);
}

/**
 * Libere la memoire associee a l'imgset.
*/
void	free_imgset(t_imgset *t)
{
	if (!t)
		return ;
	if (t->ceiling_img)
		free(t->ceiling_img);
	if (t->floor_img)
		free(t->floor_img);
	if (t->no)
		free(t->no);
	if (t->so)
		free(t->so);
	if (t->ea)
		free(t->ea);
	if (t->we)
		free(t->we);
	free(t);
}

/**
 * Libere la zone mémoire associée a une liste de char *.
*/
void	free_split(char **a)
{
	int	i;

	i = 0;
	if (!a)
		return ;
	while (a[i])
	{
		free(a[i]);
		i++;
	}
	free(a);
}
