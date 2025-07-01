#include "../../../includes/cub3d_bonus.h"

// Vérifie si la nouvelle position est valide (pas de collision)
int check_collision(t_game *game, double new_x, double new_y)
{
    int map_x;
    int map_y;

    map_x = (int)new_x;
    map_y = (int)new_y;
    if (map_x < 0 || map_x >= game->map_width || map_y < 0 || map_y >= game->map_height)
        return (0);
    if (game->map[map_y][map_x] == '1' || game->doors[map_y][map_x] == 'D')
        return (0);
    return (1);
}
