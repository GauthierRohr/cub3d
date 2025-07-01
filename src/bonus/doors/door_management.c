#include "../../../includes/cub3d_bonus.h"

// Bascule l’état d’une porte à la position donnée
void    toggle_door(t_game *game, int map_x, int map_y)
{
    if (map_x >= 0 && map_x < game->map_width && map_y >= 0 && map_y < game->map_height)
    {
        if (game->doors[map_y][map_x] == 'D')
        {
            game->doors[map_y][map_x] = '0';
            play_sound(game, "door_open");
        }
        else if (game->doors[map_y][map_x] == '0')
            game->doors[map_y][map_x] = 'D';
    }
}
