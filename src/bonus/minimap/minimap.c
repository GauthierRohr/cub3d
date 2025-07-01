#include "../../../includes/cub3d_bonus.h"

// Rend la minicarte
void    render_minimap(t_game *game)
{
    int x;
    int y;

    y = 0;
    while (y < game->map_height)
    {
        x = 0;
        while (x < game->map_width && game->map[y][x])
        {
            draw_minimap(game, x, y);
            x++;
        }
        y++;
    }
}