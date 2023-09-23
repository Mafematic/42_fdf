# Compiler and flags
CC = gcc
CFLAGS = -g -Wall -Werror -Wextra
LDFLAGS = -Lmlx -lmlx -lXext -lX11 -lm

# Source dir and files
SRC_DIR = src
SRCS = src/main.c src/get_next_line.c src/get_next_line_utils.c src/ft_split.c src/ft_substr.c src/ft_strdup.c src/ft_strlen.c \
	src/ft_atoi.c src/open_close_window.c src/initialize_grid.c src/parse_file.c src/open_close_file.c src/find_min_max_iso.c \
	src/adapt_isopixel_to_window.c src/draw_line.c src/draw_grid.c src/create_element.c src/free_grid.c src/find_rows_cols.c \
	src/parse_file2.c src/free_words.c src/handle.c

# Bouns dir and files
BONUS_DIR = bonus
BONUS_SRCS = bonus/main.c bonus/get_next_line.c bonus/get_next_line_utils.c bonus/ft_split.c src/ft_substr.c bonus/ft_strdup.c bonus/ft_strlen.c \
	bonus/ft_atoi.c bonus/open_close_window.c bonus/initialize_grid.c bonus/parse_file.c bonus/open_close_file.c bonus/find_min_max_iso.c \
	bonus/adapt_isopixel_to_window.c bonus/draw_line.c bonus/draw_grid.c bonus/create_element.c bonus/free_grid.c bonus/find_rows_cols.c \
	bonus/parse_file2.c bonus/free_words.c bonus/handle.c

# Object files
OBJ_DIR = obj
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
BONUS_OBJS = $(BONUS_SRCS:$(BONUS_DIR)/%.c=$(OBJ_DIR)/bonus_%.o)

# Output binary
TARGET = fdf
BONUS_TARGET = fdf_bonus

# Phony targets
.PHONY: all clean fclean re bonus

# Default target (all)
all: $(TARGET)

# Linking the program
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

# Compilation rule for object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Compilation rule for object files for bonus build
$(OBJ_DIR)/bonus_%.o: $(BONUS_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Clean object files and executable
clean:
	rm -rf $(OBJ_DIR)

# Remove all generated files
fclean: clean
	rm -f $(TARGET) $(BONUS_TARGET)

# Rebuild everything
re: fclean all

# Bonus target
bonus: $(BONUS_TARGET)

# Linking the program for bonus build (only if object files are updated)
$(BONUS_TARGET): $(BONUS_OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

