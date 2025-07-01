NAME = cub3D
CC = gcc
FLAGS = -Wall -Wextra -Werror -g
MLX_FLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
SDL_FLAGS = -L/opt/homebrew/lib -lSDL2_mixer
INCLUDES = -Iincludes -I$(LIBFT_DIR) -I$(MLX_DIR) -I/opt/homebrew/include/SDL2
MLX_DIR = minilibx_opengl_20191021
LIBFT_DIR = libft

# Répertoires
SRC_DIR = src/
OBJ_DIR = obj/
BONUS_DIR = src/bonus/

# Sources partie obligatoire
SRCS = main.c \
       parsing/parse_config.c \
       parsing/parse_map.c \
       parsing/check_map.c \
       raycasting/raycasting.c \
       raycasting/player.c \
       raycasting/math_utils.c \
       rendering/render.c \
       rendering/textures.c \
       rendering/draw.c \
       events/keyboard.c \
       events/mouse.c \
       events/window.c \
       utils/error.c \
	   utils/exit.c \
       utils/memory.c \
       utils/init.c
SRC = $(addprefix $(SRC_DIR),$(SRCS))
OBJ = $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRC))

# Sources bonus
BONUS_SRCS = wall_collision/collision.c \
             minimap/minimap.c \
             minimap/minimap_render.c \
             doors/door_init.c \
             doors/door_management.c \
             doors/door_render.c \
             animations/sprite.c \
             animations/sprite_animation.c \
             mouse_rotation/mouse_control.c \
             map_generator/map_generator.c \
             map_generator/map_utils.c \
             audio/audio_init.c \
             audio/audio_events.c \
             bonus_init.c \
             bonus_utils.c
BONUS_SRC = $(addprefix $(SRC_DIR)bonus/,$(BONUS_SRCS))
BONUS_OBJ = $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(BONUS_SRC))

# Librairies
MLX = $(MLX_DIR)/libmlx.a
LIBFT = $(LIBFT_DIR)/libft.a

# Couleurs
RED     = \033[31m
GREEN   = \033[32m
YELLOW  = \033[0;33m
BLUE    = \033[34m
PURPLE  = \033[0;35m
CYAN    = \033[36m
RESET   = \033[0m

TOTAL := $(words $(OBJ))
COUNT = $(words $^)

# Barre de progression
define PROGRESS_BAR
	$(eval COMPILED += 1)
	$(eval PERCENT := $(shell echo $$(( $(COMPILED) * 100 / $(TOTAL) ))))
	@printf "\r$(CYAN)[cub3D]$(RESET): Compilation... %-20s %3d%% " \
	$$(printf '$(GREEN)%0.s▮$(RESET)' $$(seq 1 $$(($(PERCENT) / 5)))) \
	$(PERCENT)
endef

# Règles
all: COMPILED=0
all: $(NAME)
	@echo "\n$(CYAN)[cub3D]$(RESET):$(GREEN) Compilation terminée ! 🥳$(RESET)"

bonus: COMPILED=0
bonus: FLAGS += -DBONUS
bonus: TOTAL=$(words $(OBJ) $(BONUS_OBJ))
bonus: $(LIBFT) $(OBJ_DIR) $(OBJ) $(BONUS_OBJ)
	@if [ -f $(MLX_DIR)/Makefile ]; then \
		$(MAKE) -s -C $(MLX_DIR); \
	fi
	@$(CC) $(FLAGS) $(INCLUDES) $(OBJ) $(BONUS_OBJ) -L$(LIBFT_DIR) -lft $(MLX_FLAGS) $(SDL_FLAGS) -o $(NAME)
	@echo "\n$(CYAN)[cub3D]$(RESET):$(GREEN) Compilation bonus réussie ! 🎉$(RESET)"

$(LIBFT):
	@if [ -f $(LIBFT_DIR)/Makefile ]; then \
		$(MAKE) -s -C $(LIBFT_DIR); \
		echo "\n$(GREEN) Création de la bibliothèque libft.a... $(RESET)"; \
		echo "$(GREEN) La bibliothèque libft.a a été créée avec succès ! $(RESET)"; \
	fi

$(NAME): $(LIBFT) $(OBJ_DIR) $(OBJ)
	@if [ -f $(MLX_DIR)/Makefile ]; then \
		$(MAKE) -s -C $(MLX_DIR); \
	fi
	@$(CC) $(FLAGS) $(INCLUDES) $(OBJ) -L$(LIBFT_DIR) -lft $(MLX_FLAGS) -o $(NAME)
	@echo "\n$(GREEN) Compilation de cub3D réussie ! $(RESET)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR) $(OBJ_DIR)parsing $(OBJ_DIR)raycasting $(OBJ_DIR)rendering $(OBJ_DIR)events $(OBJ_DIR)utils \
		$(OBJ_DIR)bonus/wall_collision $(OBJ_DIR)bonus/minimap $(OBJ_DIR)bonus/doors \
		$(OBJ_DIR)bonus/animations $(OBJ_DIR)bonus/mouse_rotation $(OBJ_DIR)bonus/map_generator \
		$(OBJ_DIR)bonus/audio
	@$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@
	$(PROGRESS_BAR)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@if [ -f $(MLX_DIR)/Makefile ]; then $(MAKE) -s -C $(MLX_DIR) clean; fi
	@if [ -f $(LIBFT_DIR)/Makefile ]; then $(MAKE) -s -C $(LIBFT_DIR) clean; fi
	@echo "$(CYAN)[cub3D]$(RESET):$(GREEN) Fichiers objets => Cleaned!$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@if [ -f $(LIBFT_DIR)/Makefile ]; then $(MAKE) -s -C $(LIBFT_DIR) fclean; fi
	@echo "$(CYAN)[cub3D]$(RESET):$(GREEN) Exécutable => Cleaned!$(RESET)"

re: fclean all

# Commandes fun
flex:
	@echo "🎉 Flexing those muscles! 📸"
	@sleep 0.5
	@echo "\n    ${RED}✨ ᕙ(⇀‸↼‶)ᕗ ✨${RESET}\n"
	@sleep 0.5
	@echo "\n    ${GREEN}   ᕙ(✧ڡ✧)ᕗ  ${RESET}\n"
	@sleep 0.5
	@echo "\n    ${YELLOW}⚡️ ᕙ(^▽^)ᕗ ⚡️${RESET}\n"
	@sleep 0.5
	@echo "\n    ${BLUE}   ᕦ(ò_óˇ)ᕤ  ${RESET}\n"
	@sleep 0.5
	@echo "\n    ${PURPLE}💥 ᕙ(▀̿̿Ĺ̯̿̿▀̿ ̿)ᕗ 💥${RESET}\n"
	@sleep 0.5
	@echo "\n🏆 Flex session complete! I'm a fcking boss!"

seum:
	@echo "\n ${RED}   ༼;´༎ຶ ۝ ༎ຶ༽ ${RESET}\n"
	@sleep 0.5
	@echo "\n ${GREEN}   (˚ ˃̣̣̥⌓˂̣̣̥ ) ${RESET}\n"
	@sleep 0.5
	@echo "\n ${CYAN}╭∩╮( •̀_•́ )╭∩╮${RESET}\n"
	@sleep 0.5
	@echo "\n ${PURPLE}   (ﾉಥ益ಥ) ${RESET}\n"
	@sleep 0.5
	@echo "\n ${YELLOW}   ᶠᶸᶜᵏᵧₒᵤ!${RESET}\n"
	@sleep 0.5

.PHONY: all clean fclean re bonus flex seum