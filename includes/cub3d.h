#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include "../minilibx_opengl_20191021/mlx.h"
# include "libft.h"
# include "structs.h"
#ifdef BONUS
# include "cub3d_bonus.h"
#endif

// Key codes (macOS)
# define KEY_W          13
# define KEY_S          1
# define KEY_A          0
# define KEY_D          2
# define KEY_LEFT       123
# define KEY_RIGHT      124
# define KEY_ESC        53
# define KEY_E          14

// Player constants
# define MOVE_SPEED     0.1
# define ROT_SPEED      0.05

// Parsing
int     parse_config(char *file, t_game *game);
int     parse_map(t_list *lines, t_game *game);
int     check_map(t_game *game);

// Raycasting
void    init_player(t_game *game);
void    perform_raycasting(t_game *game);
double  deg_to_rad(double degrees);
void    init_ray(t_game *game, t_ray *ray, int x);
void    calc_step(t_game *game, t_ray *ray);
void    calc_perp_dist(t_game *game, t_ray *ray);

// Rendering
void    init_mlx(t_game *game);
int     render_frame(void *game);
int     load_textures(t_game *game);
void    draw_column(t_game *game, int x, t_ray *ray);

// Events
int     handle_keypress(int keycode, t_game *game);
int     handle_mouse(int x, int y, t_game *game);
int     handle_window_close(void *game);

// Utils
void    exit_error(char *msg);
void    free_game(t_game *game);
void    init_game(t_game *game);
void    exit_game(t_game *game);

#endif