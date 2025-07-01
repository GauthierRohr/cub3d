#include "../../../includes/cub3d_bonus.h"

// Sauvegarde la carte dans un fichier .cub
void    save_map_to_file(t_game *game, char *filename)
{
    int     fd;
    int     i;

    fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
        exit_error("Erreur création fichier carte");
    ft_putstr_fd("NO ./textures/north.xpm\n", fd);
    ft_putstr_fd("SO ./textures/south.xpm\n", fd);
    ft_putstr_fd("WE ./textures/west.xpm\n", fd);
    ft_putstr_fd("EA ./textures/east.xpm\n", fd);
    ft_putstr_fd("F 220,100,0\n", fd);
    ft_putstr_fd("C 225,30,0\n\n", fd);
    i = 0;
    while (i < game->map_height)
    {
        ft_putstr_fd(game->map[i], fd);
        ft_putstr_fd("\n", fd);
        i++;
    }
    close(fd);
}
