
NAME = cub3D

##################################

SRC_DIR	= src/
OBJ_DIR	= .obj/
INC_DIR	= includes/

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
				raycast.c wall_and_textures.c minimap.c
GRAFIC = $(addprefix 03_Grafic/, $(GRAFIC_FILES))

# --- 04 Moves ---
MOVES_FILES =	process_move.c utils.c move_render.c
MOVES = $(addprefix 04_Moves/, $(MOVES_FILES))

# --- Todos os arquivos fonte ---
SRC_FILES = $(PROCESS) $(PARSE) $(GRAFIC) $(MOVES)
SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))

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
	@echo "        ░░░       Thevaris &                       ░░░"
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

# Cleanup
clean:
	@rm -rf $(OBJ_DIR) 2>/dev/null || true
	@echo "$(YELLOW)🗑️ Object files removed$(RESET)"
	@cd libraries/libft && make clean > /dev/null 2>&1
	@cd minilibx-linux && make clean > /dev/null 2>&1

fclean: clean
	@rm -rf $(NAME) 2>/dev/null || true
	@echo "$(RED)❌ Executable $(NAME) removed$(RESET)"
	@cd libraries/libft && make fclean > /dev/null 2>&1

re: fclean all

.PHONY: all clean fclean re

# Rules for libraries (silent mode)
$(LIBFT):
	@echo "$(YELLOW)📚 Compiling libft...$(RESET)"
	$(SILENT_LIBFT)
	@echo "$(GREEN)✅ libft compiled$(RESET)"

$(LIBX):
	@echo "$(YELLOW)📚 Compiling minilibx...$(RESET)"
	$(SILENT_LIBX)
	@echo "$(GREEN)✅ minilibx compiled$(RESET)"
