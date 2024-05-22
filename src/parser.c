/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmascrie <nmascrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 00:52:41 by nmascrie          #+#    #+#             */
/*   Updated: 2024/03/29 00:52:44 by nmascrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

static int	epure_line(int *in_map, int *nb_tete, t_chain **c)
{
	if (emptyline((*c)->line))
	{
		if (*in_map)
			return (ERR_EMPTY_LINE_IN_MAP);
		cut_ligne(c);
		if ((*c)->previous)
			(*c) = (*c)->previous;
	}
	else if (((*c)->line[0] == 'W') || ((*c)->line[0] == 'E')
		|| ((*c)->line[0] == 'N') || ((*c)->line[0] == 'S')
		|| !is_line_map((*c)->line))
	{
		if (*in_map)
			return (ERR_HEADER_IN_MAP);
		*nb_tete += 1;
	}
	else
		*in_map = 1;
	return (0);
}

/**
 * Inspecte la liste chainée. Note 0 les éléments qui sont de l'en-tête
 * note 1 les éléments de la map
 * Retire les lignes vides
 * retourne ERR_NOT_ENOUGH_HEADERS s'il n'y a pas assez d'en têtes
 * retourne ERR_TOO_MUCH_HEADERS s'il y en a trop
 * (attendu : 6, définis par NB_ELEMENTS)
 * retourne ERR_EMPTY_LINE_IN_MAP s'il y a une ligne vide dans la map
 * retourne ERR_HEADER_IN_MAP s'il y a une ligne d'en tête dans la map
 * retourne 0 sinon
*/
int	epure(t_chain *c)
{
	int	nb_tete;
	int	in_map;
	int	code;

	in_map = 0;
	nb_tete = 0;
	while (c)
	{
		code = epure_line(&in_map, &nb_tete, &c);
		if (code)
			return (code);
		c = c->next;
	}
	if (nb_tete > NB_ELEMENTS)
		return (ERR_TOO_MUCH_HEADERS);
	if (nb_tete < NB_ELEMENTS)
		return (ERR_NOT_ENOUGH_HEADERS);
	return (0);
}

static int	second_part(t_chain **values, t_data **data)
{
	int	code;

	(*data)->map_height = map_lines((*values));
	(*data)->map_width = map_length((*values));
	(*data)->map = generate_map((*values),
			(*data)->map_width, (*data)->map_height);
	if (!(*data)->map)
		return (ERR_MAP_EMPTY);
	code = check_map((*data));
	if (code)
		return (code);
	code = check_exists((*data)->img);
	if (code)
		return (code);
	return (0);
}

/**
 * Génère une structure utilisable par le jeu.
 * Renvoie la structure générée.
*/
t_data	*generate_data(char *path)
{
	t_data	*data;
	t_chain	*values;
	int		code;

	values = to_chain(path);
	if (!values)
		return (NULL);
	data = ft_calloc(1, sizeof(t_data));
	remove_tail(values);
	while (emptyline(values->line))
		values = values->next;
	if (!test_headers(values))
		return (data_error(ERR_UNKNOWN_HEADER, data, values));
	code = epure(values);
	if (code)
		return (data_error(code, data, values));
	data->img = ft_calloc(1, sizeof(t_imgset));
	code = generate_imgset(values, data->img);
	if (code)
		return (data_error(code, data, values));
	code = second_part(&values, &data);
	if (code)
		return (data_error(code, data, values));
	free_chain(values);
	return (data);
}
