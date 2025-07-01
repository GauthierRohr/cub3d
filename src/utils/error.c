#include "../../includes/cub3d.h"

// Affiche un message d’erreur et quitte
void    exit_error(char *msg)
{
    ft_putstr_fd("Error\n", 2);
    ft_putstr_fd(msg, 2);
    ft_putstr_fd("\n", 2);
    exit(1);
}
