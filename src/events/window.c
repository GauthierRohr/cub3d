#include "../../includes/cub3d.h"

// Ferme la fenêtre et quitte proprement
int handle_window_close(void *param)
{
    t_game *game = (t_game *)param;
    free_game(game);
    exit(0);
    return (0);
}
