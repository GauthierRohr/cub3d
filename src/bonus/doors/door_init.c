#include "../../../includes/cub3d_bonus.h"

// Vérifie si une position est valide pour une porte
static int is_valid_door_position(t_game *game, int y, int x)
{
    if (x <= 0 || x >= game->map_width - 1 || y <= 0 || y >= game->map_height - 1)
        return (0);
    // Accepte les portes existantes ('D') ou les espaces vides ('0')
    if (game->map[y][x] != 'D' && game->map[y][x] != '0')
        return (0);
    // Vérifie les murs horizontalement (1 à gauche et à droite)
    if (game->map[y][x - 1] == '1' && game->map[y][x + 1] == '1')
        return (1);
    // Vérifie les murs verticalement (1 au-dessus et en-dessous)
    if (game->map[y - 1][x] == '1' && game->map[y + 1][x] == '1')
        return (1);
    return (0);
}

// Initialise les portes
void init_doors(t_game *game)
{
    int x;
    int y;
    int door_count;

    ft_putstr_fd("Entrée init_doors, map_height: ", 1);
    char *height_str = ft_itoa(game->map_height);
    ft_putstr_fd(height_str, 1);
    ft_putstr_fd(", map_width: ", 1);
    char *width_str = ft_itoa(game->map_width);
    ft_putstr_fd(width_str, 1);
    ft_putstr_fd("\n", 1);
    free(height_str);
    free(width_str);

    if (!game->map || game->map_height < 3 || game->map_width < 3)
        exit_error("Map trop petite pour placer une porte");

    // Compter les portes
    door_count = 0;
    y = 0;
    while (y < game->map_height)
    {
        if (!game->map[y])
            exit_error("Ligne de carte non initialisée");
        x = 0;
        while (x < (int)ft_strlen(game->map[y]))
        {
            if (game->map[y][x] == 'D')
            {
                if (!is_valid_door_position(game, y, x))
                {
                    char err_msg[100];
                    char *y_str = ft_itoa(y);
                    char *x_str = ft_itoa(x);
                    ft_strcat(err_msg, "Position de porte invalide à [");
                    ft_strcat(err_msg, y_str);
                    ft_strcat(err_msg, "][");
                    ft_strcat(err_msg, x_str);
                    ft_strcat(err_msg, "]");
                    free(y_str);
                    free(x_str);
                    exit_error(err_msg);
                }
                door_count++;
            }
            x++;
        }
        y++;
    }
    ft_putstr_fd("door_count: ", 1);
    char *door_str = ft_itoa(door_count);
    ft_putstr_fd(door_str, 1);
    ft_putstr_fd("\n", 1);
    free(door_str);

    // Allouer game->doors
    if (door_count > 0)
    {
        game->doors = ft_calloc(game->map_height + 1, sizeof(char *));
        if (!game->doors)
            exit_error("Erreur allocation portes");
        y = 0;
        while (y < game->map_height)
        {
            game->doors[y] = ft_calloc(game->map_width + 1, sizeof(char));
            if (!game->doors[y])
                exit_error("Erreur allocation ligne portes");
            ft_memset(game->doors[y], '0', game->map_width);
            x = 0;
            while (x < (int)ft_strlen(game->map[y]))
            {
                if (game->map[y][x] == 'D')
                    game->doors[y][x] = 'D';
                x++;
            }
            y++;
        }
    }
}
