/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_open.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmascrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 08:34:37 by nmascrie          #+#    #+#             */
/*   Updated: 2024/04/03 08:34:39 by nmascrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

static int	part_one(t_imgset *img)
{
	int	fd;

	fd = open(img->no, O_RDONLY);
	if (fd == -1)
		return (ERR_FILE_NOT_FOUND);
	close (fd);
	fd = open(img->so, O_RDONLY);
	if (fd == -1)
		return (ERR_FILE_NOT_FOUND);
	close (fd);
	fd = open(img->ea, O_RDONLY);
	if (fd == -1)
		return (ERR_FILE_NOT_FOUND);
	close (fd);
	fd = open(img->we, O_RDONLY);
	if (fd == -1)
		return (ERR_FILE_NOT_FOUND);
	close (fd);
	return (0);
}

static int	part_two(t_imgset *img)
{
	int	fd;

	if (img->ceiling_img)
	{
		fd = open(img->ceiling_img, O_RDONLY);
		if (fd == -1)
			return (ERR_FILE_NOT_FOUND);
		close (fd);
	}
	if (img->floor_img)
	{
		fd = open(img->floor_img, O_RDONLY);
		if (fd == -1)
			return (ERR_FILE_NOT_FOUND);
		close(fd);
	}
	return (0);
}

/**
 * Verifie si les fichiers spécifiées existes.
 * Renvoie 0 s'ils existent
 * Renvoie ERR_FILE_NOT_FOUND sinon
*/
int	check_exists(t_imgset *img)
{
	if (part_one(img))
		return (ERR_FILE_NOT_FOUND);
	if (part_two(img))
		return (ERR_FILE_NOT_FOUND);
	return (0);
}
