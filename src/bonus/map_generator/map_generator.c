#include "../../../includes/cub3d_bonus.h"

// Génère une carte aléatoire simple
void    generate_random_map(t_game *game)
{
    int i;
    int j;

    game->map_width = 10;
    game->map_height = 10;
    game->map = ft_calloc(game->map_height + 1, sizeof(char *));
    if (!game->map)
        exit_error("Erreur allocation carte");
    i = 0;
    while (i < game->map_height)
    {
        game->map[i] = ft_calloc(game->map_width + 1, sizeof(char));
        if (!game->map[i])
            exit_error("Erreur allocation ligne carte");
        j = 0;
        while (j < game->map_width)
        {
            if (i == 0 || i == game->map_height - 1 || j == 0 || j == game->map_width - 1)
                game->map[i][j] = '1';
            else
                game->map[i][j] = '0';
            j++;
        }
        i++;
    }
    game->map[2][2] = 'N'; // Position joueur
}
