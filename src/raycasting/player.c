#include "../../includes/cub3d.h"

// Initialise la direction du joueur selon son orientation
static void set_player_direction(t_game *game, char orient)
{
    if (orient == 'N')
    {
        game->player.dir.x = 0;
        game->player.dir.y = -1;
        game->player.plane.x = 0.66;
        game->player.plane.y = 0;
    }
    else if (orient == 'S')
    {
        game->player.dir.x = 0;
        game->player.dir.y = 1;
        game->player.plane.x = -0.66;
        game->player.plane.y = 0;
    }
    else if (orient == 'E')
    {
        game->player.dir.x = 1;
        game->player.dir.y = 0;
        game->player.plane.x = 0;
        game->player.plane.y = 0.66;
    }
    else if (orient == 'W')
    {
        game->player.dir.x = -1;
        game->player.dir.y = 0;
        game->player.plane.x = 0;
        game->player.plane.y = -0.66;
    }
}

// Initialise les paramètres du joueur
void    init_player(t_game *game)
{
    int i;
    int j;

    game->player.move_speed = 0.1;
    game->player.rot_speed = 0.05;
    i = 0;
    while (i < game->map_height)
    {
        j = 0;
        while (game->map[i][j])
        {
            if (game->map[i][j] == 'N' || game->map[i][j] == 'S' ||
                game->map[i][j] == 'E' || game->map[i][j] == 'W')
            {
                set_player_direction(game, game->map[i][j]);
                game->map[i][j] = '0';
                return;
            }
            j++;
        }
        i++;
    }
}
