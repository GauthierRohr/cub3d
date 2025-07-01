#ifndef STRUCTS_H
# define STRUCTS_H

# include "/opt/homebrew/include/SDL2/SDL_mixer.h"

typedef struct s_vec2
{
    double x;
    double y;
} t_vec2;

typedef struct s_ray
{
    t_vec2  dir;
    t_vec2  map;
    t_vec2  side_dist;
    t_vec2  delta_dist;
    int     step_x;
    int     step_y;
    int     hit;
    int     side;
    double  perp_dist;
    double  camera_x;
    int     wall_type;
} t_ray;

typedef struct s_player
{
    t_vec2  pos;
    t_vec2  dir;
    t_vec2  plane;
    double  angle;      // Angle de rotation du joueur
    double  move_speed;
    double  rot_speed;
} t_player;

typedef struct s_textures
{
    void    *north;
    void    *south;
    void    *west;
    void    *east;
    int     width;
    int     height;
} t_textures;

typedef struct s_audio
{
#ifdef BONUS
    Mix_Music *bg_music;
    Mix_Chunk *footstep;
    Mix_Chunk *door_open;
#else
    void    *bg_music;
    void    *footstep;
    void    *door_open;
#endif
} t_audio;

typedef struct s_sprite
{
    t_vec2  pos;
    void    **frames;
    int     frame_count;
    int     frame;
    double  anim_speed;
} t_sprite;

typedef struct s_game
{
    void        *mlx;
    void        *win;
    void        *img;
    char        *img_data;
    int         img_bpp;
    int         img_line_len;
    int         img_endian;
    int         win_width;
    int         win_height;
    int         floor_color;
    int         ceil_color;
    char        **map;
    char        **doors;
    int         map_width;
    int         map_height;
    t_player    player;
    t_textures  textures;
    t_audio     audio;
    t_sprite    *sprites;
    int         sprite_count;
} t_game;

#endif