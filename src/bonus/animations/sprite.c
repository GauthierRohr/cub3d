#include "../../../includes/cub3d_bonus.h"

// Charge les textures des sprites
void load_sprites(t_game *game)
{
    int i;

    ft_putstr_fd("Entrée load_sprites, sprite_count: ", 1);
    char *count_str = ft_itoa(game->sprite_count);
    ft_putstr_fd(count_str, 1);
    ft_putstr_fd("\n", 1);
    free(count_str);
    if (game->sprite_count < 1 || !game->map)
        return;
    if (!game->sprites)
    {
        game->sprites = ft_calloc(game->sprite_count, sizeof(t_sprite));
        if (!game->sprites)
            exit_error("Erreur allocation sprites");
    }
    i = 0;
    while (i < game->sprite_count)
    {
        game->sprites[i].frame_count = 2;
        game->sprites[i].frames = ft_calloc(game->sprites[i].frame_count, sizeof(void *));
        if (!game->sprites[i].frames)
            exit_error("Erreur allocation frames sprite");
        game->sprites[i].frames[0] = mlx_xpm_file_to_image(game->mlx, "./textures/sprite1_frame1.xpm", &game->textures.width, &game->textures.height);
        game->sprites[i].frames[1] = mlx_xpm_file_to_image(game->mlx, "./textures/sprite1_frame2.xpm", &game->textures.width, &game->textures.height);
        if (!game->sprites[i].frames[0] || !game->sprites[i].frames[1])
            exit_error("Erreur chargement textures sprite");
        game->sprites[i].frame = 0;
        game->sprites[i].anim_speed = 0.1;
        // Conserver les positions définies dans parse_config
        i++;
    }
}
