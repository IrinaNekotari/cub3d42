/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmascrie <nmascrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 00:52:27 by nmascrie          #+#    #+#             */
/*   Updated: 2024/03/29 00:52:36 by nmascrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/**
 * Renvoie 1 si le char est un élément de map correct (1, 0, N, S, E, W)
 * Renvoie 0 sinon
 * Possibilité d'ajouts de charactères, genre un ennemi ou des pièces
*/
int is_map_element(char c)
{
    if (c == '1' || c == '0')
        return (1);
    if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
        return (1);
    return (0);
}

void        free_chain(t_chain *chain)
{
    if (!chain)
        return ;
    if (chain->line)
        free(chain->line);
    if (chain->next)
        free_chain(chain->next);
    free(chain);
}

void 		free_imgset(t_imgset *t)
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

int	is_whitespace(char c)
{
	if (c == ' ')
		return (1);
	if (c == '\t')
		return (1);
	if (c == '\r')
		return (1);
	if (c == '\n')
		return (1);
	if (c == '\v')
		return (1);
	if (c == '\f')
		return (1);
	return (0);
}

int     emptyline(char *c)
{
    int     i;

    i = 0;
    if (!c)
        return (1);
    while (c[i])
    {
        if (!is_whitespace(c[i]) || c[i] != '\n')
            return (0);
        i++;
    }
    return (1);
}

t_chain     *ft_errmsg(char *msg)
{
    ft_printf("[\x1b[31mERROR\x1b[37m] %s\n", msg);
    return (NULL);
}

int	ft_equals(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	if (s1[i] != s2[i])
		return (0);
	return (1);
}