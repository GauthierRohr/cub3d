#include "../../includes/cub3d.h"

// Compte les lignes non vides pour la taille de la carte
static int count_map_lines(t_list *lines)
{
    int count;
    t_list *current;

    count = 0;
    current = lines;
    ft_putstr_fd("Début count_map_lines\n", 1);
    if (!current)
        ft_putstr_fd("Liste lines vide\n", 1);
    while (current)
    {
        if (ft_strlen(current->content) > 1)
        {
            count++;
            ft_putstr_fd("Ligne comptée: ", 1);
            ft_putstr_fd(current->content, 1);
            ft_putstr_fd("\n", 1);
        }
        else
        {
            ft_putstr_fd("Ligne ignorée (trop courte): ", 1);
            ft_putstr_fd(current->content, 1);
            ft_putstr_fd("\n", 1);
        }
        current = current->next;
    }
    ft_putstr_fd("count_map_lines, count: ", 1);
    char *count_str = ft_itoa(count);
    ft_putstr_fd(count_str, 1);
    ft_putstr_fd("\n", 1);
    free(count_str);
    return (count);
}

// Alloue la carte et copie les lignes
static int allocate_map(t_game *game, t_list *lines)
{
    int i;
    t_list *current;

    ft_putstr_fd("Début allocate_map\n", 1);
    game->map_height = count_map_lines(lines);
    ft_putstr_fd("allocate_map, map_height: ", 1);
    char *height_str = ft_itoa(game->map_height);
    ft_putstr_fd(height_str, 1);
    ft_putstr_fd("\n", 1);
    free(height_str);
    if (game->map_height == 0)
        return (exit_error("Aucune ligne de carte valide"), 0);
    game->map = ft_calloc(game->map_height + 1, sizeof(char *));
    if (!game->map)
        return (exit_error("Erreur allocation game->map"), 0);
    i = 0;
    current = lines;
    while (current && i < game->map_height)
    {
        if (ft_strlen(current->content) > 1)
        {
            game->map[i] = ft_strdup(current->content);
            if (!game->map[i])
                return (exit_error("Erreur allocation ligne map"), 0);
            ft_putstr_fd("Copie ligne ", 1);
            char *i_str = ft_itoa(i);
            ft_putstr_fd(i_str, 1);
            ft_putstr_fd(": ", 1);
            ft_putstr_fd(game->map[i], 1);
            ft_putstr_fd("\n", 1);
            free(i_str);
            i++;
        }
        current = current->next;
    }
    return (1);
}

// Calcule la largeur maximale de la carte
static void set_map_width(t_game *game)
{
    int i;
    size_t len;

    game->map_width = 0;
    i = 0;
    while (i < game->map_height)
    {
        len = ft_strlen(game->map[i]);
        if (len > (size_t)game->map_width)
            game->map_width = len;
        i++;
    }
    ft_putstr_fd("set_map_width, map_width: ", 1);
    char *width_str = ft_itoa(game->map_width);
    ft_putstr_fd(width_str, 1);
    ft_putstr_fd("\n", 1);
    free(width_str);
}

// Parse la carte depuis la liste des lignes
int parse_map(t_list *lines, t_game *game)
{
    ft_putstr_fd("Début parse_map\n", 1);
    if (!allocate_map(game, lines))
        return (ft_lstclear(&lines, free), 0);
    set_map_width(game);
    if (!check_map(game))
    {
        ft_lstclear(&lines, free);
        free_game(game);
        return (0);
    }
    ft_lstclear(&lines, free);
    return (1);
}
