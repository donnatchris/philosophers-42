# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/16 16:21:20 by christophed       #+#    #+#              #
#    Updated: 2025/02/06 14:10:26 by chdonnat         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Name of the executable for bonus part
TARGET = philo_bonus

# Directories for bonus part
SRC_DIR = src
UTILS_DIR = utils
INC_DIR = include
OBJ_DIR = obj

# Main file for bonus part
MAIN = $(SRC_DIR)/main.c

# Sources files for bonus part
SRC = \
	$(SRC_DIR)/close_program.c \
	$(SRC_DIR)/store_rules.c \
	$(SRC_DIR)/store_philosophers.c \
	$(SRC_DIR)/launch_simulation.c \
	$(SRC_DIR)/philosopher_life.c \
	$(SRC_DIR)/sem_functions.c \
	$(UTILS_DIR)/dclst1.c \
	$(UTILS_DIR)/utils_functions.c \
	$(MAIN)

# Objects files for bonus part
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Compilation options
CFLAGS = -Wall -Wextra -Werror

# Compiler
CC = cc

# Rule to compile the bonus part
all: $(TARGET)
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

# Rules to compile the objects files of the bonus part
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@
$(OBJ_DIR)/%.o: $(UTILS_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to clean the objects files
clean:
	rm -rf obj

# Rule to clean the objects files and the executables
fclean: clean
	rm -rf $(TARGET)

# Rule to recompile the project
re: fclean all

# Phony rule
.PHONY: all clean fclean re bonus
