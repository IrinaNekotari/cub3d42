/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmascrie <nmascrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 02:25:39 by nmascrie          #+#    #+#             */
/*   Updated: 2024/04/01 02:25:42 by nmascrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	handle_code1(int code)
{
	if (code == ERR_NOT_ENOUGH_HEADERS)
		ft_printf("Not enough headers in file ! Expected : %d", NB_ELEMENTS);
	else if (code == ERR_TOO_MUCH_HEADERS)
		ft_printf("Too many headers in file ! Expected : %d", NB_ELEMENTS);
	else if (code == ERR_EMPTY_LINE_IN_MAP)
		ft_printf("Found empty line in map description !");
	else if (code == ERR_HEADER_IN_MAP)
		ft_printf("Found header in map description !");
}

static void	handle_code2(int code)
{
	if (code == ERR_UNKNOWN_HEADER)
		ft_printf("Found unknown header in description !");
	else if (code == ERR_HEADER_TOO_LARGE)
		ft_printf("Found too many arugments for header !");
	else if (code == ERR_HEADER_TOO_THIN)
		ft_printf("Found not enough arguments for header !");
	else if (code == ERR_INVALID_RGB)
		ft_printf("Found invalid RGB code !");
	else if (code == ERR_NON_UNIQUE_HEADER)
		ft_printf("An header has been duplicated !");
}

static void	handle_code3(int code)
{
	if (code == ERR_UNKNOWN_CHARS)
		ft_printf("Found unknown character in map !");
	else if (code == ERR_INVALID_ENTRIES)
		ft_printf("Found invalid number of entry points in map !");
	else if (code == ERR_UNCLOSED_MAP)
		ft_printf("Found unenclosed wall in map !");
	else if (code == ERR_FILE_NOT_FOUND)
		ft_printf("Couldn't find specified file !");
}

t_data	*data_error(int code, t_data *data, t_chain *values)
{
	ft_printf("[\x1b[31mERROR\x1b[37m] ");
	handle_code1(code);
	handle_code2(code);
	handle_code3(code);
	ft_printf(" (error code : %d)\n", code);
	free_data(data, values);
	return (NULL);
}

t_chain	*ft_errmsg(char *msg)
{
	ft_printf("[\x1b[31mERROR\x1b[37m]\n%s\n", msg);
	return (NULL);
}
