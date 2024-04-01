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

#include "parser.h"

/**
 * Retourne la taille d'un tableau splitté
*/
int split_len(char **a)
{  
    int     i;

    i = 0;
    while (a[i])
        i++;
    return (i);
}

/**
 * Libere la zone mémoire associée a une liste de char *.
*/
void    free_split(char **a)
{
    int i;

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

/**
 * Coupe l'élément courant de la chaine.
*/
void    cut_ligne(t_chain **c)
{
    t_chain *bck;
    
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
 * Remplis l'imgset en fonction des premières lignes de la map
 * Retourne ERR_UNKNOWN_HEADER si l'une des entêtes n'est pas reconnue
 * Retourne -2 si l'entête possède trop de valeurs
 * Retourne -3 si l'entête possède pas assez de valeurs
 * Retourne -4 si une valeur RGB est invalide
 * Retourne 0 sinon
*/
int generate_imgset(t_chain *c, t_imgset *img)
{
    int     i;
    char    **li;

    i = 0;
    li = NULL;
    while (i < NB_ELEMENTS)
    {
        li = ft_split(c->line, ' ');
        if (split_len(li) > 2)
        {
            free_split(li);
            return (ERR_HEADER_TOO_LARGE);
        }
        else if (split_len(li) < 2)
        {
            free_split(li);
            return (ERR_HEADER_TOO_THIN);
        }
        if (ft_equals(li[0], "NO"))
            img->no = ft_strdup(li[1]);
        else if (ft_equals(li[0], "SO"))
            img->so = ft_strdup(li[1]);
        else if (ft_equals(li[0], "EA"))
            img->ea = ft_strdup(li[1]);
        else if (ft_equals(li[0], "WE"))
            img->we = ft_strdup(li[1]);
        else if (ft_equals(li[0], "C") && is_rgb(li[1]))
        {
            img->ceiling_img = NULL;
            img->ceiling_color = get_rgb(li[1]);
            if (img->ceiling_color == -1)
            {
                free_split(li);
                return (ERR_INVALID_RGB);
            }
        }
        else if (ft_equals(li[0], "C") && !is_rgb(li[1]))
        {
            img->ceiling_img = ft_strdup(li[1]);;
            img->ceiling_color = 0;
            if (ft_strchr(img->ceiling_img, ','))
            {
                free_split(li);
                return (ERR_INVALID_RGB);
            }
        }
        else if (ft_equals(li[0], "F") && is_rgb(li[1]))
        {
            img->floor_img = NULL;
            img->floor_color = get_rgb(li[1]);
            if (img->floor_color == -1)
            {
                free_split(li);
                return (ERR_INVALID_RGB);
            }
        }
        else if (ft_equals(li[0], "F") && !is_rgb(li[1]))
        {
            img->floor_img = ft_strdup(li[1]);
            img->floor_color = 0;
            if (ft_strchr(img->floor_img, ','))
            {
                free_split(li);
                return (ERR_INVALID_RGB);
            }
        }
        else
        {
            free_split(li);
            return (ERR_UNKNOWN_HEADER);
        }
        free_split(li);
        i++;
        c = c->next;
    }
    return (0);
}

/**
 * Renvoie le nombre de lignes de la map.
*/
int map_lines(t_chain *c)
{
    int i;
    int lines;

    i = 0;
    lines = 0;
    while (i < NB_ELEMENTS)
    {
        c = c->next;
        i++;
    }
    while (c)
    {
        c = c->next;
        lines++;
    }
    return (lines);
}

/**
 * Renvoie la plus grande longeur possible d'une ligne de la map
 * Incluant le \n
*/
int map_length(t_chain *c)
{
    int i;
    int len;

    i = 0;
    len = 0;
    while (i < NB_ELEMENTS)
    {
        c = c->next;
        i++;
    }
    while (c)
    {
        if ((int)ft_strlen(c->line) > len)
            len = (int)ft_strlen(c->line);
        c = c->next;
    }
    return (len);
}

/**
 * Récupère la map sous un format char**
*/
char    **generate_map(t_chain *c, int x, int y)
{
    int     i;
    char    **ret;

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
 * des caractères de map (0, 1, N, S, E, W), des whitespaces ou un retour a la ligne
 * Retourne 0 sinon
 * Cas croustillant extra particulier : 
*/
int is_line_map(char *l)
{
    int     i;

    i = 0;
    if (is_whitespace(l[0]) || (is_map_element(l[0]) && is_map_element(l[1])))
        return (1);
    while (l[i])
    {
        if (!is_map_element(l[i]) && !is_whitespace(l[i]) && l[i] != '\n' && l[i] != 0)
            return (0);
        i++;
    }
    return (1);
}

/**
 * Retire toutes les lignes vides a la fin de la chaine
*/
void    remove_tail(t_chain *c)
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
 * Inspecte la liste chainée. Note 0 les éléments qui sont de l'en-tête
 * note 1 les éléments de la map
 * Retire les lignes vides
 * retourne ERR_NOT_ENOUGH_HEADERS s'il n'y a pas assez d'en têtes
 * retourne ERR_TOO_MUCH_HEADERS s'il y en a trop (attendu : 6, définis par NB_ELEMENTS)
 * retourne ERR_EMPTY_LINE_IN_MAP s'il y a une ligne vide dans la map
 * retourne ERR_HEADER_IN_MAP s'il y a une ligne d'en tête dans la map
 * retourne 0 sinon
*/
int epure(t_chain *c)
{
    int nb_tete;
    int in_map;

    in_map = 0;
    nb_tete = 0;
    while (c)
    {
        if (emptyline(c->line))
        {
            if (in_map)
                return (ERR_EMPTY_LINE_IN_MAP);
            cut_ligne(&c);
            if (c->previous)
                c = c->previous;
        }
        else if ((c->line[0] == 'W') || !is_line_map(c->line))
        {
            if (in_map)
                return (ERR_HEADER_IN_MAP);
            nb_tete++;
        }
        else 
            in_map = 1;
        c = c->next;
    }
    if (nb_tete > NB_ELEMENTS)
        return (ERR_TOO_MUCH_HEADERS);
    if (nb_tete < NB_ELEMENTS)
        return (ERR_NOT_ENOUGH_HEADERS);
    return (0);
}

/**
 * Convertis un fichier ouvert en liste chainée
 * Supprime les \n a la fin de chaque ligne
*/
t_chain *to_chain(char *path)
{
    int     fd;
    char    *tmp;
    t_chain *a;
    t_chain *b;

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
    {
        a->line = tmp;
        tmp[ft_strlen(tmp) - 1] = 0;
        a->next = ft_calloc(1, sizeof(t_chain));
        a->next->previous = a;
        a = a->next;
        tmp = get_next_line(fd);
    }
    a->next = NULL;
    cut_ligne(&a);
    close (fd);
    return (b);
}

/**
 * Libère la mémoire associée a la structure de donnée.
*/
void    free_data(t_data *d, t_chain *c)
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
 * Génère une structure utilisable par le jeu.
 * Renvoie la structure générée.
*/
t_data  *generate_data(char *path)
{
    t_data *data;
    t_chain *values;
    int         code;

    values = to_chain(path);
    if (!values)
        return (NULL);
    data = ft_calloc(1, sizeof(t_data));
    remove_tail(values);
    while (emptyline(values->line))
        values = values->next;
    code = epure(values);
    if (code)
        return (data_error(code, data, values));
    data->img = ft_calloc(1, sizeof(t_imgset));
    code = generate_imgset(values, data->img);
    if (code)
        return (data_error(code, data, values));
    data->map_height = map_lines(values);
    data->map_width = map_length(values);
    data->map = generate_map(values, data->map_width, data->map_height);
    code = check_map(data);
    if (code)
        return (data_error(code, data, values));
    while (values->previous)
        values = values->previous;
    free_chain(values);
    return (data);
}