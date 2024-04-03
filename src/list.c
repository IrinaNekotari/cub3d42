/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmascrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 08:17:55 by nmascrie          #+#    #+#             */
/*   Updated: 2024/04/03 08:17:56 by nmascrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

/**
 * Retire toutes les lignes vides a la fin de la chaine
*/
void	remove_tail(t_chain *c)
{
	while (c->next)
	{
		c = c->next;
	}
	if (emptyline(c->line))
	{
		cut_ligne(&c);
		remove_tail(c);
	}
	else
		return ;
}

/**
 * Coupe l'élément courant de la chaine.
*/
void	cut_ligne(t_chain **c)
{
	t_chain	*bck;

	bck = (*c);
	if (!bck)
		return ;
	if (bck->line)
		free(bck->line);
	if (bck->next)
	{
		(*c) = (*c)->next;
		if (bck->previous)
		{
			(*c)->previous = bck->previous;
			bck->previous->next = bck->next;
		}
		else
			(*c)->previous = NULL;
	}
	else if (bck->previous)
	{
		(*c) = (*c)->previous;
		(*c)->next = NULL;
	}
	free(bck);
}

/**
 * Boucle principale de la fonction to_chain
*/
void	do_things(t_chain **a, char **tmp, int fd)
{
	(*a)->line = (*tmp);
	(*tmp)[ft_strlen((*tmp)) - 1] = 0;
	(*a)->next = ft_calloc(1, sizeof(t_chain));
	(*a)->next->previous = (*a);
	(*a) = (*a)->next;
	(*tmp) = get_next_line(fd);
}

/**
 * Convertis un fichier ouvert en liste chainée
 * Supprime les \n a la fin de chaque ligne
*/
t_chain	*to_chain(char *path)
{
	int		fd;
	char	*tmp;
	t_chain	*a;
	t_chain	*b;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (ft_errmsg("File does not exist !"));
	tmp = get_next_line(fd);
	if (!tmp)
		return (ft_errmsg("Empty file !"));
	a = ft_calloc(1, sizeof(t_chain));
	a->previous = NULL;
	b = a;
	while (tmp)
		do_things(&a, &tmp, fd);
	a->next = NULL;
	cut_ligne(&a);
	close (fd);
	return (b);
}
