/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmascrie <nmascrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 00:52:53 by nmascrie          #+#    #+#             */
/*   Updated: 2024/03/29 00:52:58 by nmascrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/**
 * Vérifie si la map a des charactères inconnus.
 * Retourne 0 si la map n'a que des caractères valides.
 * Retourne 1 sinon.
*/
int map_has_unknown(char **m)
{
    int i;
    int j;

    i = 0;
    while (m[i])
    {
        j = 0;
        while (m[i][j])
        {
            if (!is_map_element(m[i][j]) && !is_whitespace(m[i][j]))
                return (1);
            j++;
        }
        i++;
    }
    return (0);
}

/**
 * Vérifie si la map contient un seul et unique caractère joueur.
 * Renvoie 0 si la map n'a qu'un seul et unique joueur.
 * Renvoie 1 sinon.
*/
int map_has_players(char **m)
{
    int i;
    int j;
    int count;

    i = 0;
    count = 0;
    while (m[i])
    {
        j = 0;
        while (m[i][j])
        {
            if (m[i][j] == 'N' || m[i][j] == 'S' || m[i][j] == 'E' || m[i][j] == 'W')
                count++;
            j++;
        }
        i++;
    }
    if (count == 1)
        return (0);
    else 
        return (1);
}

static int megacheck(int i, int j, char **m)
{
    if (!is_map_element(m[i][j + 1]))
        return (1);
    if (!is_map_element(m[i][j - 1]))
        return (1);
    if (!is_map_element(m[i + 1][j]))
        return (1);
    if (!is_map_element(m[i - 1][j]))
        return (1);
    return (0);
}

/**
 * Check si la map est fermée.
 * LOGIQUE : Pour que la map soit considérée fermée, il faut que chaque case non
 * mur (0 ou joueur) soit entourée d'une autre case non mur ou d'un mur.
 * Renvoie 0 si la map est fermée.
 * Renvoie 1 si la map est fermée.
*/
int map_isnt_close(char **m)
{
    int i;
    int j;

    i = 0;
    while (m[i])
    {
        j = 0;
        while (m[i][j])
        {
            if (m[i][j] == '0' || m[i][j] == 'N' || m[i][j] == 'S'
                || m[i][j] == 'E' || m[i][j] == 'W')
            {
                if (j == 0 || i == 0 || m[i][j + 1] == 0 || !m[i + 1])
                    return (1);
                if (megacheck(i, j, m))
                    return (1);
            }
            j++;
        }
        i++;
    }
    return (0);
}

/**
 * Regarde dans la map, et récupère la position et l'orientation initiale du joueur.
*/
void get_positions(t_data *data)
{
    int i;
    int j;

    i = 0;
    while (data->map[i])
    {
        j = 0;
        while (data->map[i][j])
        {
            if (data->map[i][j] == 'N' || data->map[i][j] == 'S' || data->map[i][j] == 'E' || data->map[i][j] == 'W')
            {
                data->player_x = j;
                data->player_y = i;
                data->player_orientation = data->map[i][j];
                return ;
            }
            j++;
        }
        i++;
    }
}

/**
 * Effectue les vérifications sur la carte, et génére le point de départ.
 * Retourne 0 si tout va bien.
 * Retourne -1 si la map a des caractères inconus.
 * Retourne -2 si le joueur a plusieurs points d'entrée ou aucun.
 * Retourne -3 si la map n'est pas fermée.
*/
int check_map(t_data *d)
{
    if (map_has_unknown(d->map))
        return (-1);
    if (map_has_players(d->map))
        return (-2);
    if (map_isnt_close(d->map))
        return (-3);
    get_positions(d);
    return (0);
}
