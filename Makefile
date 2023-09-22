# Compiler and flags
CC = gcc
CFLAGS = -g
LDFLAGS = -Lmlx -lmlx -lXext -lX11 -lm

# Source files
SRC_DIR = src
SRCS = src/main.c src/get_next_line.c src/get_next_line_utils.c src/ft_split.c src/ft_substr.c src/ft_strdup.c src/ft_strlen.c \
	src/ft_atoi.c src/open_window.c src/initialize_grid.c src/parse_file.c src/open_close_file.c src/find_min_max_iso.c \
	src/adapt_isopixel_to_window.c src/draw_line.c src/draw_grid.c src/create_element.c src/free_grid.c src/find_rows_cols.c

# Object files
OBJ_DIR = obj
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Output binary
TARGET = fdf_me

# Phony targets
.PHONY: all clean fclean re

# Default target (all)
all: $(TARGET)

# Linking the program
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

# Compilation rule for object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Clean object files and executable
clean:
	rm -rf $(OBJ_DIR)

# Remove all generated files
fclean: clean
	rm -f $(TARGET)

# Rebuild everything
re: fclean all
