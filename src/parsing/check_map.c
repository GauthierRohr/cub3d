//check_map.c
#include "../../includes/cub3d.h"

// Vérifie si un caractère est valide
// static int is_valid_char(char c)
// {
//     return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' ||
//             c == 'W' || c == ' ' || c == 'D');
// }

static int flood_fill(t_game *game, int **visited, int y, int x)
{
    if (y < 0 || y >= game->map_height)
        return (0);
    if (x < 0 || x >= (int)ft_strlen(game->map[y]))
        return (1);
    if (visited[y][x] || game->map[y][x] == '1' || game->map[y][x] == ' ')
        return (1);
    visited[y][x] = 1;
    if (!flood_fill(game, visited, y - 1, x))
        return (0);
    if (!flood_fill(game, visited, y + 1, x))
        return (0);
    if (!flood_fill(game, visited, y, x - 1))
        return (0);
    if (!flood_fill(game, visited, y, x + 1))
        return (0);
    return (1);
}

// Strip newline and carriage return characters from the end of a string
static void strip_line_endings(char *str)
{
    int len;
    
    if (!str)
        return;
    len = ft_strlen(str);
    while (len > 0 && (str[len - 1] == '\n' || str[len - 1] == '\r'))
    {
        str[len - 1] = '\0';
        len--;
    }
}

// Vérifie la position du joueur
static int check_player(t_game *game, int *player_count)
{
    int i;
    int j;

    i = 0;
    *player_count = 0; // Initialize player count
    
    ft_putstr_fd("Début check_player\n", 1);
    
    // First, strip line endings from all map lines
    while (i < game->map_height)
    {
        if (game->map[i])
            strip_line_endings(game->map[i]);
        i++;
    }
    
    i = 0;
    while (i < game->map_height)
    {
        j = 0;
        while (j < (int)ft_strlen(game->map[i])) // Use actual string length, not map_width
        {
            char c = game->map[i][j];
            
            // Debug: print character being checked
            if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
            {
                ft_putstr_fd("Joueur trouvé: ", 1);
                ft_putchar_fd(c, 1);
                ft_putstr_fd(" à position [", 1);
                char *i_str = ft_itoa(i);
                ft_putstr_fd(i_str, 1);
                ft_putstr_fd("][", 1);
                char *j_str = ft_itoa(j);
                ft_putstr_fd(j_str, 1);
                ft_putstr_fd("]\n", 1);
                free(i_str);
                free(j_str);
                
                (*player_count)++;
                // Store player position
                game->player.pos.x = j + 0.5;
                game->player.pos.y = i + 0.5;
                // Set player direction based on character
                if (c == 'N') {
                    game->player.dir.x = 0;
                    game->player.dir.y = -1;
                } else if (c == 'S') {
                    game->player.dir.x = 0;
                    game->player.dir.y = 1;
                } else if (c == 'E') {
                    game->player.dir.x = 1;
                    game->player.dir.y = 0;
                } else if (c == 'W') {
                    game->player.dir.x = -1;
                    game->player.dir.y = 0;
                }
            }
            
            // Check if character is valid
            if (c != '0' && c != '1' && c != 'N' && c != 'S' && 
                c != 'E' && c != 'W' && c != ' ')
            {
                ft_putstr_fd("Caractère invalide trouvé: '", 1);
                ft_putchar_fd(c, 1);
                ft_putstr_fd("' (ASCII: ", 1);
                char *ascii_str = ft_itoa((int)c);
                ft_putstr_fd(ascii_str, 1);
                ft_putstr_fd(") à position [", 1);
                char *i_str = ft_itoa(i);
                ft_putstr_fd(i_str, 1);
                ft_putstr_fd("][", 1);
                char *j_str = ft_itoa(j);
                ft_putstr_fd(j_str, 1);
                ft_putstr_fd("]\n", 1);
                free(ascii_str);
                free(i_str);
                free(j_str);
                return (exit_error("Caractère invalide dans la carte"), 0);
            }
            
            j++;
        }
        
        // Check borders after processing the entire line
        // Check top and bottom borders
        if (i == 0 || i == game->map_height - 1)
        {
            int k = 0;
            while (k < (int)ft_strlen(game->map[i]))
            {
                char c = game->map[i][k];
                if (c != '1' && c != ' ')
                    return (exit_error("Carte non entourée de murs (bordure horizontale)"), 0);
                k++;
            }
        }
        
        // Check left and right borders
        if (ft_strlen(game->map[i]) > 0)
        {
            // Left border
            if (game->map[i][0] != '1' && game->map[i][0] != ' ')
                return (exit_error("Carte non entourée de murs (bordure gauche)"), 0);
            
            // Right border
            int last_idx = ft_strlen(game->map[i]) - 1;
            if (last_idx >= 0 && game->map[i][last_idx] != '1' && game->map[i][last_idx] != ' ')
                return (exit_error("Carte non entourée de murs (bordure droite)"), 0);
        }
        
        i++;
    }
    
    ft_putstr_fd("Nombre de joueurs trouvés: ", 1);
    char *count_str = ft_itoa(*player_count);
    ft_putstr_fd(count_str, 1);
    ft_putstr_fd("\n", 1);
    free(count_str);
    
    return (*player_count == 1);
}

static int is_map_closed(t_game *game)
{
    int **visited;
    int i, result;

    visited = malloc(sizeof(int *) * game->map_height);
    if (!visited)
        exit_error("Erreur malloc visited");
    i = 0;
    while (i < game->map_height)
    {
        visited[i] = ft_calloc(game->map_width, sizeof(int));
        if (!visited[i])
            exit_error("Erreur malloc ligne visited");
        i++;
    }
    result = flood_fill(game, visited, (int)game->player.pos.y, (int)game->player.pos.x);
    i = 0;
    while (i < game->map_height)
        free(visited[i++]);
    free(visited);
    if (!result)
        return (exit_error("Carte non entourée de murs"), 0);
    return (1);
}

// Vérifie la validité de la carte
int check_map(t_game *game)
{
    int player_count;

    ft_putstr_fd("check_map, map_height: ", 1);
    char *height_str = ft_itoa(game->map_height);
    ft_putstr_fd(height_str, 1);
    ft_putstr_fd(", map_width: ", 1);
    char *width_str = ft_itoa(game->map_width);
    ft_putstr_fd(width_str, 1);
    ft_putstr_fd("\n", 1);
    free(height_str);
    free(width_str);

    player_count = 0;
    if (game->map_height < 3 || game->map_width < 3)
        return (exit_error("Carte trop petite"), 0);
    if (!game->map)
        return (exit_error("Carte non initialisée"), 0);
    if (!check_player(game, &player_count))
        return (exit_error("Joueur invalide ou absent"), 0);
    if (!is_map_closed(game))
        return (exit_error("Carte non entourée de murs"), 0);
    return (1);
}
