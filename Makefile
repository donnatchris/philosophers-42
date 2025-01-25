# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/16 16:21:20 by christophed       #+#    #+#              #
#    Updated: 2025/01/25 07:18:41 by christophed      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Name of the executable for mandatory part
TARGET = philo

# Name of the executable for bonus part
BONUS = philo_bonus

# Directories for mandatory part
SRC_DIR = philo/src
UTILS_DIR = philo/utils
INC_DIR = philo/include
OBJ_DIR = obj/philo

# Directories for bonus part
BONUS_SRC_DIR = philo_bonus/src
BONUS_UTILS_DIR = philo_bonus/utils
BONUS_INC_DIR = philo_bonus/include
BONUS_OBJ_DIR = obj/philo_bonus

# Main file for mandatory part
MAIN = $(SRC_DIR)/main.c

# Main file for bonus part
BONUS_MAIN = $(BONUS_SRC_DIR)/main.c

# Sources files for mandatory part
SRC = \
	$(SRC_DIR)/error_manager.c \
	$(SRC_DIR)/limits.c \
	$(SRC_DIR)/points.c \
	$(SRC_DIR)/read_and_extract.c \
	$(SRC_DIR)/window_manager.c \
	$(SRC_DIR)/draw.c \
	$(SRC_DIR)/color_manager.c \
	$(SRC_DIR)/linux_functions.c \
	$(UTILS_DIR)/count_function.c \
	$(UTILS_DIR)/free_functions.c \
	$(UTILS_DIR)/ft_atoi_long.c \
	$(UTILS_DIR)/test_functions.c \
	$(MAIN)

# Sources files for bonus part
BONUS_SRC =	\
	$(BONUS_SRC_DIR)/bonus_error_manager.c \
	$(BONUS_SRC_DIR)/bonus_limits.c \
	$(BONUS_SRC_DIR)/bonus_points.c \
	$(BONUS_SRC_DIR)/bonus_read_and_extract.c \
	$(BONUS_UTILS_DIR)/bonus_count_function.c \
	$(BONUS_UTILS_DIR)/bonus_free_functions.c \
	$(BONUS_UTILS_DIR)/bonus_ft_atoi_long.c \
	$(BONUS_UTILS_DIR)/bonus_test_functions.c \
	$(BONUS_MAIN)

# Objects files for mandatory part
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Objects files for bonus part
BONUS_OBJ = $(BONUS_SRC:$(BONUS_SRC_DIR)/%.c=$(BONUS_OBJ_DIR)/%.o)


# Compilation options for MacOS or Linux
CFLAGS = -Wall -Wextra -Werror

# Compiler
CC = gcc

# Rule to compile the mandatory part
all: $(TARGET)
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

# Rule to compile the bonus part
bonus: $(BONUS)
$(BONUS): $(BONUS_OBJ)
	$(CC) $(CFLAGS) -o $(BONUS) $^


# Rules to compile the objects files of the mandatory part
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@
$(OBJ_DIR)/%.o: $(UTILS_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Rules to compile the objects files of the bonus part
$(BONUS_OBJ_DIR)/%.o: $(BONUS_SRC_DIR)/%.c
	@mkdir -p $(BONUS_OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BONUS_OBJ_DIR)/%.o: $(BONUS_UTILS_DIR)/%.c
	@mkdir -p $(BONUS_OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to clean the objects files
clean:
	rm -rf obj

# Rule to clean the objects files and the executables
fclean: clean
	rm -f $(TARGET) $(BONUS)

# Rule to recompile the project
re: fclean all

# Phony rule
.PHONY: all clean fclean re bonus
