/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmascrie <nmascrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 02:06:09 by nmascrie          #+#    #+#             */
/*   Updated: 2024/03/29 02:06:10 by nmascrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

/**
 * Retourne une valeur hexa en fonction des trois valeurs de rouge, vert et bleus
 * Retourne -1 si l'une des valeurs entrées est invalide
*/
int	colorpicker(int r, int g, int b)
{
	int	color;

	color = 0;
	if (r < 0 || g < 0 || b < 0 || r > 255 || g > 255 || b > 255)
		return (-1);
	color = color | (b << 0);
	color = color | (g << 8);
	color = color | (r << 16);
	return (color);
}

/**
 * Verifie si le char* est au format RGB, c'est a dire
 * qu'il possede uniquement 3 valeurs separees par des
 * virgules
*/
int	is_rgb(char *a)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (a[i])
	{
		if (a[i] == ',' && a[i + 1] && a[i + 1] != ',')
			count++;
		i++;
	}
	if (count == 2)
		return (1);
	else
		return (0);
}

/**
 * Retourne vrai si le char* n'est compose que de chiffres.
*/
static int	is_valid_num(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

/**
 * Cree une valeur hexadecimale de couleur a partir du
 * char * recu en argument. Si le char * de contient
 * pas de code RGB valide, retourne -1.
*/
int	get_rgb(char *a)
{
	int			color;
	char		**split;

	split = ft_split(a, ',');
	if (!is_valid_num(split[0]) || !is_valid_num(split[1])
		|| !is_valid_num(split[2]))
	{
		free_split(split);
		return (-1);
	}
	color = colorpicker(ft_atoi(split[0]),
			ft_atoi(split[1]), ft_atoi(split[2]));
	free_split(split);
	ft_printf("Found color : %x\n", color);
	return (color);
}
