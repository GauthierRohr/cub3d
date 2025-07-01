#include "../../includes/cub3d.h"

int handle_keypress(int keycode, t_game *game)
{
    double new_x = game->player.pos.x;
    double new_y = game->player.pos.y;

    if (keycode == KEY_W)
    {
        new_x += cos(game->player.angle) * MOVE_SPEED;
        new_y += sin(game->player.angle) * MOVE_SPEED;
#ifdef BONUS
        if (check_collision(game, new_x, new_y))
            return (0);
#endif
        game->player.pos.x = new_x;
        game->player.pos.y = new_y;
    }
    else if (keycode == KEY_S)
    {
        new_x -= cos(game->player.angle) * MOVE_SPEED;
        new_y -= sin(game->player.angle) * MOVE_SPEED;
#ifdef BONUS
        if (check_collision(game, new_x, new_y))
            return (0);
#endif
        game->player.pos.x = new_x;
        game->player.pos.y = new_y;
    }
    else if (keycode == KEY_A)
    {
        new_x += cos(game->player.angle - M_PI_2) * MOVE_SPEED;
        new_y += sin(game->player.angle - M_PI_2) * MOVE_SPEED;
#ifdef BONUS
        if (check_collision(game, new_x, new_y))
            return (0);
#endif
        game->player.pos.x = new_x;
        game->player.pos.y = new_y;
    }
    else if (keycode == KEY_D)
    {
        new_x += cos(game->player.angle + M_PI_2) * MOVE_SPEED;
        new_y += sin(game->player.angle + M_PI_2) * MOVE_SPEED;
#ifdef BONUS
        if (check_collision(game, new_x, new_y))
            return (0);
#endif
        game->player.pos.x = new_x;
        game->player.pos.y = new_y;
    }
    else if (keycode == KEY_LEFT)
        game->player.angle -= ROT_SPEED;
    else if (keycode == KEY_RIGHT)
        game->player.angle += ROT_SPEED;
    else if (keycode == KEY_ESC)
        exit_game(game);
#ifdef BONUS
    else if (keycode == KEY_E)
        toggle_door(game, (int)(game->player.pos.x + cos(game->player.angle)), (int)(game->player.pos.y + sin(game->player.angle)));
#endif
    return (0);
}