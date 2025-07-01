/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grohr <grohr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:46:58 by grohr             #+#    #+#             */
/*   Updated: 2025/07/01 11:48:11 by grohr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char     *g_static_str = NULL;

char    *ft_add_line(int fd, char *str)
{
    char    *buffer;
    ssize_t bytes_read;

    buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (!buffer)
        return (NULL);
    bytes_read = 1;
    while ((ft_strchr_g(str, '\n') == 0) && bytes_read > 0)
    {
        bytes_read = read(fd, buffer, BUFFER_SIZE);
        if (bytes_read == -1)
        {
            ft_putstr_fd("Erreur lecture fichier\n", 1);
            free(str);
            free(buffer);
            return (NULL);
        }
        buffer[bytes_read] = '\0';
        ft_putstr_fd("Bytes lus: ", 1);
        char *bytes_str = ft_itoa(bytes_read);
        ft_putstr_fd(bytes_str, 1);
        ft_putstr_fd("\nBuffer: ", 1);
        ft_putstr_fd(buffer, 1);
        ft_putstr_fd("\n", 1);
        free(bytes_str);
        str = ft_strjoin_g(str, buffer);
    }
    free(buffer);
    return (str);
}

char    *get_next_line(int fd)
{
    char    *line;

    if (BUFFER_SIZE <= 0 || fd < 0)
    {
        ft_putstr_fd("Erreur: BUFFER_SIZE <= 0 ou fd < 0\n", 1);
        return (NULL);
    }
    ft_putstr_fd("Début get_next_line, fd: ", 1);
    char *fd_str = ft_itoa(fd);
    ft_putstr_fd(fd_str, 1);
    ft_putstr_fd("\n", 1);
    free(fd_str);
    g_static_str = ft_add_line(fd, g_static_str);
    if (!g_static_str)
        return (NULL);
    line = ft_next_line(g_static_str);
    g_static_str = ft_remove_str_1st_line(g_static_str);
    return (line);
}

char    **get_static_str(void)
{
    return (&g_static_str);
}

void    free_gnl_static(void)
{
    char    **ptr;

    ptr = get_static_str();
    if (*ptr)
    {
        free(*ptr);
        *ptr = NULL;
    }
}
