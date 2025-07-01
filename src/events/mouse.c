#include "../../includes/cub3d.h"

int handle_mouse(int x, int y, t_game *game)
{
    static int prev_x = -1;

    (void)game;
    if (prev_x == -1)
    {
        prev_x = x;
        return (0);
    }
#ifdef BONUS
    rotate_with_mouse(game, x);
#endif
    prev_x = x;
    (void)y;
    return (0);
}
