#include "../includes/cub3d.h"

int main(int argc, char **argv)
{
    t_game game;

    if (argc != 2)
        exit_error("Usage: ./cub3D <map.cub>");
    ft_putstr_fd("Début main\n", 1);
    init_game(&game);
    if (!parse_config(argv[1], &game))
    {
        ft_putstr_fd("Erreur dans parse_config\n", 1);
        free_game(&game);
        return (1);
    }
    init_mlx(&game);
#ifdef BONUS
    ft_putstr_fd("Appel init_bonus\n", 1);
    init_bonus(&game);
#endif
    mlx_hook(game.win, 2, 1L<<0, handle_keypress, &game);
    mlx_hook(game.win, 17, 0, handle_window_close, &game);
    mlx_loop_hook(game.mlx, render_frame, &game);
    mlx_loop(game.mlx);
    return (0);
}
