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

#include "../include/cube3d.h"

/**
 * Initialise toutes les valeurs de l'imgset a NULL ou 0.
*/
void	null_values(t_imgset **img)
{
	(*img)->no = NULL;
	(*img)->so = NULL;
	(*img)->we = NULL;
	(*img)->ea = NULL;
	(*img)->floor_img = NULL;
	(*img)->ceiling_img = NULL;
	(*img)->floor_color = 0;
	(*img)->ceiling_color = 0;
}

/**
 * Verifie si des valeurs de l'imgset n'ont pas
 * ete initialisees.
*/
int	has_null_values(t_imgset *img)
{
	if (!img->no)
		return (1);
	if (!img->so)
		return (1);
	if (!img->we)
		return (1);
	if (!img->ea)
		return (1);
	if (!img->floor_img && !img->floor_color)
		return (1);
	if (!img->ceiling_img && !img->ceiling_color)
		return (1);
	return (0);
}

/**
 * Retourne vrai si le charactere est un whitespace.
 * Adapte pour les besoins du parser
*/
int	is_whitespace(char c)
{
	if (c == ' ')
		return (1);
	if (c == '\n')
		return (1);
	return (0);
}

/**
 * Retourne vrai si la ligne est consideree vide par les
 * standards de cube 3D
*/
int	emptyline(char *c)
{
	int	i;

	i = 0;
	if (!c)
		return (1);
	while (c[i])
	{
		if (!is_whitespace(c[i]))
			return (0);
		i++;
	}
	return (1);
}

/**
 * Retourne vrai si les deux char* sont identiques.
*/
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
