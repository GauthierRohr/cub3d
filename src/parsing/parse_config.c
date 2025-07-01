#include "../../includes/cub3d.h"
#include <errno.h>
#include <string.h>

// Vérifie si une ligne est un identifiant de texture
static int is_texture_id(char *line)
{
    if (!line)
        return (0);
    return (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0 ||
            ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0);
}

// Vérifie si une ligne est un identifiant de couleur
static int is_color_id(char *line)
{
    if (!line)
        return (0);
    return (ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0);
}

// Parse les textures depuis une ligne
static int parse_texture(char *line, t_textures *textures)
{
    char *path;

    ft_putstr_fd("Début parse_texture: ", 1);
    ft_putstr_fd(line, 1);
    path = ft_strtrim(line + 3, " \t");
    if (!path)
        return (exit_error("Erreur allocation chemin texture"), 0);
    if (ft_strncmp(line, "NO ", 3) == 0)
    {
        if (textures->north)
            free(textures->north);
        textures->north = path;
    }
    else if (ft_strncmp(line, "SO ", 3) == 0)
    {
        if (textures->south)
            free(textures->south);
        textures->south = path;
    }
    else if (ft_strncmp(line, "WE ", 3) == 0)
    {
        if (textures->west)
            free(textures->west);
        textures->west = path;
    }
    else if (ft_strncmp(line, "EA ", 3) == 0)
    {
        if (textures->east)
            free(textures->east);
        textures->east = path;
    }
    else
    {
        free(path);
        return (exit_error("Identifiant texture invalide"), 0);
    }
    return (1);
}

// Parse les couleurs depuis une ligne
static int parse_color(char *line, t_game *game)
{
    char **rgb;
    int color;
    int r, g, b;

    ft_putstr_fd("Début parse_color: ", 1);
    ft_putstr_fd(line, 1);
    rgb = ft_split(line + 2, ',');
    if (!rgb || !rgb[0] || !rgb[1] || !rgb[2])
        return (free_split(rgb), exit_error("Couleur invalide"), 0);
    r = ft_atoi(rgb[0]);
    g = ft_atoi(rgb[1]);
    b = ft_atoi(rgb[2]);
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
        return (free_split(rgb), exit_error("Valeurs RGB hors limites"), 0);
    color = (r << 16) | (g << 8) | b;
    if (line[0] == 'F')
        game->floor_color = color;
    else if (line[0] == 'C')
        game->ceil_color = color;
    else
        return (free_split(rgb), exit_error("Identifiant couleur invalide"), 0);
    free_split(rgb);
    return (1);
}

// Compte et initialise les sprites
static void init_sprites(t_game *game)
{
    size_t y;
    size_t x;
    int i;

    ft_putstr_fd("Entrée init_sprites, map_height: ", 1);
    char *height_str = ft_itoa(game->map_height);
    ft_putstr_fd(height_str, 1);
    ft_putstr_fd(", map_width: ", 1);
    char *width_str = ft_itoa(game->map_width);
    ft_putstr_fd(width_str, 1);
    ft_putstr_fd("\n", 1);
    free(height_str);
    free(width_str);

    // Loguer la carte
    y = 0;
    while (y < (size_t)game->map_height)
    {
        ft_putstr_fd("Map ligne ", 1);
        char *y_str = ft_itoa(y);
        ft_putstr_fd(y_str, 1);
        ft_putstr_fd(": ", 1);
        if (game->map[y])
            ft_putstr_fd(game->map[y], 1);
        else
            ft_putstr_fd("(null)", 1);
        ft_putstr_fd("\n", 1);
        free(y_str);
        y++;
    }

    game->sprite_count = 0;
    if (!game->map)
        exit_error("Carte non initialisée");
    y = 0;
    while (y < (size_t)game->map_height)
    {
        if (!game->map[y])
            exit_error("Ligne de carte non initialisée");
        x = 0;
        while (x < ft_strlen(game->map[y]))
        {
            if (game->map[y][x] == 'S')
            {
                game->sprite_count++;
                ft_putstr_fd("Sprite trouvé à [", 1);
                char *y_str = ft_itoa(y);
                ft_putstr_fd(y_str, 1);
                ft_putstr_fd("][", 1);
                char *x_str = ft_itoa(x);
                ft_putstr_fd(x_str, 1);
                ft_putstr_fd("]\n", 1);
                free(y_str);
                free(x_str);
            }
            x++;
        }
        y++;
    }
    ft_putstr_fd("sprite_count après comptage: ", 1);
    char *count_str = ft_itoa(game->sprite_count);
    ft_putstr_fd(count_str, 1);
    ft_putstr_fd("\n", 1);
    free(count_str);

    if (game->sprite_count > 0)
    {
        game->sprites = ft_calloc(game->sprite_count, sizeof(t_sprite));
        if (!game->sprites)
            exit_error("Erreur allocation sprites");
        i = 0;
        y = 0;
        while (y < (size_t)game->map_height)
        {
            x = 0;
            while (x < ft_strlen(game->map[y]))
            {
                if (game->map[y][x] == 'S')
                {
                    if (i >= game->sprite_count)
                        exit_error("Erreur: trop de sprites détectés");
                    game->sprites[i].pos.x = x + 0.5;
                    game->sprites[i].pos.y = y + 0.5;
                    i++;
                }
                x++;
            }
            y++;
        }
    }
}

// Parse le fichier .cub
int parse_config(char *file, t_game *game)
{
    int fd;
    char *line;
    t_list *lines;
    char *full_path;

    ft_putstr_fd("Début parse_config\n", 1);
    full_path = ft_strdup(file);
    if (!full_path)
        return (exit_error("Erreur allocation chemin"), 0);
    ft_putstr_fd("Chemin fichier: ", 1);
    ft_putstr_fd(full_path, 1);
    ft_putstr_fd("\n", 1);
    fd = open(full_path, O_RDONLY);
    if (fd < 0)
    {
        ft_putstr_fd("Erreur ouverture fichier: ", 1);
        ft_putstr_fd(full_path, 1);
        ft_putstr_fd(": ", 1);
        ft_putstr_fd(strerror(errno), 1);
        ft_putstr_fd("\n", 1);
        free(full_path);
        return (exit_error("Erreur ouverture fichier"), 0);
    }
    free(full_path);
    lines = NULL;
    line = get_next_line(fd);
    if (!line)
    {
        ft_putstr_fd("Aucune ligne lue (fichier vide ou erreur)\n", 1);
        close(fd);
        return (exit_error("Fichier vide ou erreur de lecture"), 0);
    }
    while (line)
    {
        ft_putstr_fd("Ligne lue: ", 1);
        ft_putstr_fd(line, 1);
        if (ft_strlen(line) > 1 && !is_texture_id(line) && !is_color_id(line))
        {
            ft_putstr_fd("Ajoutée à lines\n", 1);
            ft_lstadd_back(&lines, ft_lstnew(line));
        }
        else if (is_texture_id(line) && !parse_texture(line, &game->textures))
            return (free(line), ft_lstclear(&lines, free), close(fd), 0);
        else if (is_color_id(line) && !parse_color(line, game))
            return (free(line), ft_lstclear(&lines, free), close(fd), 0);
        else
            free(line);
        line = get_next_line(fd);
    }
    close(fd);
    if (!lines)
    {
        ft_putstr_fd("Aucune ligne de carte ajoutée à lines\n", 1);
        return (exit_error("Aucune ligne de carte valide"), 0);
    }
    if (!parse_map(lines, game))
        return (ft_lstclear(&lines, free), exit_error("Erreur dans parse_map"), 0);
    init_sprites(game);
    return (1);
}
