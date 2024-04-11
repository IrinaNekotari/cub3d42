/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmascrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 08:48:30 by nmascrie          #+#    #+#             */
/*   Updated: 2024/04/03 08:48:31 by nmascrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

/**
 * Renvoie 1 si le char est un élément de map correct (1, 0, N, S, E, W)
 * Renvoie 0 sinon
 * Possibilité d'ajouts de charactères, genre un ennemi ou des pièces
 * ajout des caractères bonus : 
 * D pour porte (DOOR)
 * B pour décos (BARREL)
 * K pour clé (KEY)
 * X pour sortie (EXIT)
 * V pour les méchants (EVIL)
*/
int	is_map_element(char c)
{
	if (c == '1' || c == '0')
		return (1);
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	if (c == 'D' || c == 'B' || c == 'K' || c == 'X' || c == 'V')
		return (1);
	return (0);
}

/**
 * Récupère la map sous un format char**
*/
char	**generate_map(t_chain *c, int x, int y)
{
	int		i;
	char	**ret;

	i = 0;
	while (i < NB_ELEMENTS)
	{
		c = c->next;
		i++;
	}
	ret = ft_calloc(x * (y + 1), sizeof(char));
	i = 0;
	while (i < y)
	{
		ret[i] = ft_strdup(c->line);
		c = c->next;
		i++;
	}
	return (ret);
}

/**
 * Retourne 1 si la map est une map de ligne, c'est a dire qu'elle ne possède que
 * des caractères de map (0, 1, N, S, E, W)
 * des whitespaces ou un retour a la ligne
 * Retourne 0 sinon
 * Cas croustillant extra particulier : 
*/
int	is_line_map(char *l)
{
	int	i;

	i = 0;
	if (is_whitespace(l[0])
		|| (is_map_element(l[0]) && is_map_element(l[1])))
		return (1);
	while (l[i])
	{
		if (!is_map_element(l[i]) && !is_whitespace(l[i])
			&& l[i] != '\n' && l[i] != 0)
			return (0);
		i++;
	}
	return (1);
}
