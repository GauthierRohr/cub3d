#include "../../../includes/cub3d_bonus.h"

// Fait pivoter le joueur avec la souris
void    rotate_with_mouse(t_game *game, int x)
{
    static int  last_x = -1;
    double      angle;
    double      old_dir_x;
    double      old_plane_x;

    if (last_x == -1)
        last_x = x;
    angle = (x - last_x) * game->player.rot_speed * 0.01;
    old_dir_x = game->player.dir.x;
    game->player.dir.x = game->player.dir.x * cos(angle) - game->player.dir.y * sin(angle);
    game->player.dir.y = old_dir_x * sin(angle) + game->player.dir.y * cos(angle);
    old_plane_x = game->player.plane.x;
    game->player.plane.x = game->player.plane.x * cos(angle) - game->player.plane.y * sin(angle);
    game->player.plane.y = old_plane_x * sin(angle) + game->player.plane.y * cos(angle);
    last_x = x;
}
