NAME        = cub3D
NAME_BONUS  = cub3D_bonus

##################################

SRC_DIR	= src/
OBJ_DIR	= .obj/
BONUS_DIR   = bonus/
BONUS_OBJ   = .obj_bonus/
INC_DIR	= Includes/
BONUS_INC   = bonus/

# --- 01 Process ---
PROCESS_FILES =	clean_process.c msg_error.c free_process.c getters.c \
				setters.c main.c
PROCESS = $(addprefix 01_Process/, $(PROCESS_FILES))

# --- 02 Parse ---
PARSE_FILES =	flood_map.c parse_assets.c parse_checkers.c \
				parse_validations.c parse_input.c parse_color.c\
				parse_extensions.c parse_map.c
PARSE = $(addprefix 02_Parse/, $(PARSE_FILES))

# --- 03 Grafic ---
GRAFIC_FILES =	draw_shapes.c get_map.c render.c vision_line.c \
				raycast.c raycast_render.c wall_and_textures.c
GRAFIC = $(addprefix 03_Grafic/, $(GRAFIC_FILES))

# --- 04 Moves ---
MOVES_FILES =	process_move.c move_player.c utils.c move_render.c
MOVES = $(addprefix 04_Moves/, $(MOVES_FILES))

# --- Todos os arquivos fonte ---
SRC_FILES = $(PROCESS) $(PARSE) $(GRAFIC) $(MOVES)
SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))

# ------- BONUS SOURCE FILES -------

# 01_Process bonus
BONUS_PROCESS_FILES = main_bonus.c textures_bonus.c setters_bonus.c clean_process_bonus.c
BONUS_PROCESS = $(addprefix 01_Process/, $(BONUS_PROCESS_FILES))

# 01_Process shared
BONUS_SHARED_PROCESS_FILES = msg_error.c getters.c free_process.c
BONUS_SHARED_PROCESS = $(addprefix 01_Process/, $(BONUS_SHARED_PROCESS_FILES))

# 02_Parse bonus
BONUS_PARSE_FILES = parse_map_bonus.c parse_map_utils_bonus.c flood_map_bonus.c
BONUS_PARSE = $(addprefix 02_Parse/, $(BONUS_PARSE_FILES))

# 02_Parse shared
BONUS_SHARED_PARSE_FILES = parse_assets.c parse_validations.c \
                            parse_input.c parse_color.c parse_extensions.c
BONUS_SHARED_PARSE = $(addprefix 02_Parse/, $(BONUS_SHARED_PARSE_FILES))

# 03_Grafic bonus
BONUS_GRAFIC_FILES = minimap_bonus.c minimap_render_bonus.c raycast_bonus.c \
					 raycast_render_bonus.c door_bonus.c door_render_bonus.c utils_bonus.c
BONUS_GRAFIC = $(addprefix 03_Grafic/, $(BONUS_GRAFIC_FILES))

# 03_Grafic shared
BONUS_SHARED_GRAFIC_FILES = draw_shapes.c get_map.c render.c vision_line.c \
                             wall_and_textures.c
BONUS_SHARED_GRAFIC = $(addprefix 03_Grafic/, $(BONUS_SHARED_GRAFIC_FILES))

# 04_Moves bonus
BONUS_MOVES_FILES = process_move_bonus.c move_player_bonus.c mouse_move_bonus.c
BONUS_MOVES = $(addprefix 04_Moves/, $(BONUS_MOVES_FILES))

# 04_Moves shared
BONUS_SHARED_MOVES_FILES = utils.c move_render.c
BONUS_SHARED_MOVES = $(addprefix 04_Moves/, $(BONUS_SHARED_MOVES_FILES))

# --- All bonus objects ---
BONUS_FROM_BONUS = $(BONUS_PROCESS) $(BONUS_PARSE) $(BONUS_GRAFIC) $(BONUS_MOVES)
BONUS_FROM_SRC   = $(BONUS_SHARED_PROCESS) $(BONUS_SHARED_PARSE) \
                   $(BONUS_SHARED_GRAFIC) $(BONUS_SHARED_MOVES)

BONUS_SRC_A = $(addprefix $(BONUS_DIR), $(BONUS_FROM_BONUS))
BONUS_SRC_B = $(addprefix $(SRC_DIR), $(BONUS_FROM_SRC))

BONUS_OBJ_A = $(patsubst $(BONUS_DIR)%.c, $(BONUS_OBJ)bonus/%.o, $(BONUS_SRC_A))
BONUS_OBJ_B = $(patsubst $(SRC_DIR)%.c, $(BONUS_OBJ)src/%.o, $(BONUS_SRC_B))

ALL_BONUS_OBJ = $(BONUS_OBJ_A) $(BONUS_OBJ_B)

# --- Compiler and flags ---
CC = cc -g
CFLAGS = -Wall -Wextra -Werror
MINILXFLAGS = -L ./minilibx-linux -lmlx -Ilmlx -lXext -lX11 -lbsd -no-pie -lm

# --- Libraries ---
LIBFT = ./libraries/libft/libft.a
LIBX = ./minilibx-linux/libmlx_Linux.a

# --- Colors for messages ---
GREEN = \033[38;5;47m
YELLOW = \033[38;5;226m
RED = \033[38;5;196m
PURPLE = \033[38;5;129m
CYAN = \033[38;5;51m
RESET = \033[0m

# --- Silent modes ---
SILENT_LIBFT = @cd libraries/libft && make > /dev/null 2>&1
SILENT_LIBX = @cd minilibx-linux && make > /dev/null 2>&1
SILENT_COMPILE = @$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@ 2>/dev/null || \
                 (echo "$(RED)❌ Error compiling $<$(RESET)" && exit 1)

################
#      ▜       #
#  ▛▘▌▌▐ █▌▛▘  #
#  ▌ ▙▌▐▖▙▖▄▌  #
################

all: $(LIBFT) $(PRINTF) $(LIBX) $(NAME)

# Main rule
$(NAME): $(OBJ)
	@echo "$(YELLOW)🔗 Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LIBX) $(MINILXFLAGS) -o $(NAME) 2>/dev/null || \
	 (echo "$(RED)❌ Linker error$(RESET)" && exit 1)
	@echo "$(GREEN)✅ Executable $(NAME) Successfully created$(RESET)"
	@echo "$(PURPLE)"
	@echo "          ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░"
	@echo "        ░░░       Thevaris & Thenriqu              ░░░"
	@echo "      ░░     ┌────────────────────────────────────┐  ░░"
	@echo "     ░░     /│                                   /│   ░░"
	@echo "    ░░     / │                                  / │    ░░"
	@echo "   ░░     /  │                                 /  │     ░░"
	@echo "  ░░     /   │                                /   │      ░░"
	@echo " ░░     /    │                               /    │       ░░"
	@echo "░░     ┌─────┼──────────────────────────────┐     │        ░░"
	@echo "░      │     │                              │     │         ░"
	@echo "░      │     │          CUB3D               │     │         ░"
	@echo "░░     │     │         3D ENGINE            │     │        ░░"
	@echo " ░░    │     └──────────────────────────────┼─────┘       ░░"
	@echo "  ░░   │    /                               │    /       ░░"
	@echo "   ░░  │   /                                │   /       ░░"
	@echo "    ░░ │  /                                 │  /       ░░"
	@echo "     ░░│ /                                  │ /       ░░"
	@echo "      ░│/                                   │/       ░░"
	@echo "      ░└────────────────────────────────────┘        ░"
	@echo "      ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░"
	@echo "$(RESET)"

# Rule for compiling objects
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)🔨 Compiling $(notdir $<)...$(RESET)"
	$(SILENT_COMPILE)

# ------ BONUS ------

bonus: $(LIBFT) $(LIBX) $(NAME_BONUS)

$(NAME_BONUS): $(ALL_BONUS_OBJ)
	@echo "$(CYAN)🔗 Linking $(NAME_BONUS)...$(RESET)"
	@$(CC) $(CFLAGS) $(ALL_BONUS_OBJ) $(LIBFT) $(LIBX) $(MINILXFLAGS) \
	 -o $(NAME_BONUS) 2>/dev/null || \
	 (echo "$(RED)❌ Linker error (bonus)$(RESET)" && exit 1)
	@echo "$(GREEN)✅ $(NAME_BONUS) created (minimap + mouse + doors [E key])$(RESET)"
	@echo "$(PURPLE)"
	@echo "          ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░"
	@echo "        ░░░       Thevaris & Thenriqu              ░░░"
	@echo "      ░░     ┌────────────────────────────────────┐  ░░"
	@echo "     ░░     /│                                   /│   ░░"
	@echo "    ░░     / │                                  / │    ░░"
	@echo "   ░░     /  │                                 /  │     ░░"
	@echo "  ░░     /   │                                /   │      ░░"
	@echo " ░░     /    │                               /    │       ░░"
	@echo "░░     ┌─────┼──────────────────────────────┐     │        ░░"
	@echo "░      │     │                              │     │         ░"
	@echo "░      │     │        CUB3D BONUS           │     │         ░"
	@echo "░░     │     │         3D ENGINE            │     │        ░░"
	@echo " ░░    │     └──────────────────────────────┼─────┘       ░░"
	@echo "  ░░   │    /                               │    /       ░░"
	@echo "   ░░  │   /                                │   /       ░░"
	@echo "    ░░ │  /                                 │  /       ░░"
	@echo "     ░░│ /                                  │ /       ░░"
	@echo "      ░│/                                   │/       ░░"
	@echo "      ░└────────────────────────────────────┘        ░"
	@echo "      ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░"
	@echo "$(RESET)"

# Compile bonus files from bonus/
$(BONUS_OBJ)bonus/%.o: $(BONUS_DIR)%.c
	@mkdir -p $(dir $@)
	@echo "$(CYAN)🔨 [bonus] Compiling $(notdir $<)...$(RESET)"
	@$(CC) $(CFLAGS) -I$(BONUS_INC) -c $< -o $@ 2>/dev/null || \
	 (echo "$(RED)❌ Error compiling $<$(RESET)" && exit 1)

# Compile shared files from src/ for bonus (using bonus header)
$(BONUS_OBJ)src/%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	@echo "$(CYAN)🔨 [bonus/shared] Compiling $(notdir $<)...$(RESET)"
	@$(CC) $(CFLAGS) -I$(BONUS_INC) -c $< -o $@ 2>/dev/null || \
	 (echo "$(RED)❌ Error compiling $<$(RESET)" && exit 1)

# Cleanup
clean:
	@rm -rf $(OBJ_DIR) $(BONUS_OBJ) 2>/dev/null || true
	@echo "$(YELLOW)🗑️ Object files removed$(RESET)"
	@cd libraries/libft && make clean > /dev/null 2>&1
	@cd minilibx-linux && make clean > /dev/null 2>&1

fclean: clean
	@rm -rf $(NAME) $(NAME_BONUS) 2>/dev/null || true
	@echo "$(RED)❌ Executable $(NAME) $(NAME_BONUS) removed$(RESET)"
	@cd libraries/libft && make fclean > /dev/null 2>&1

re: fclean all

re_bonus: fclean bonus

.PHONY: all clean fclean re bonus re_bonus

# Rules for libraries (silent mode)
$(LIBFT):
	@echo "$(YELLOW)📚 Compiling libft...$(RESET)"
	$(SILENT_LIBFT)
	@echo "$(GREEN)✅ libft compiled$(RESET)"

$(LIBX):
	@echo "$(YELLOW)📚 Compiling minilibx...$(RESET)"
	$(SILENT_LIBX)
	@echo "$(GREEN)✅ minilibx compiled$(RESET)"
