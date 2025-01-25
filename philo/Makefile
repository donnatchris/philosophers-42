# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/16 16:21:20 by christophed       #+#    #+#              #
#    Updated: 2025/01/25 11:13:33 by christophed      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Name of the executable for mandatory part
TARGET = philo

# Directories for mandatory part
SRC_DIR = src
UTILS_DIR = utils
INC_DIR = include
OBJ_DIR = obj

# Main file for mandatory part
MAIN = $(SRC_DIR)/main.c

# Sources files for mandatory part
SRC = \
	$(SRC_DIR)/error_manager.c \
	$(SRC_DIR)/store_rules.c \
	$(UTILS_DIR)/free_functions.c \
	$(UTILS_DIR)/utils_functions.c \
	$(MAIN)

# Objects files for mandatory part
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Compilation options for MacOS or Linux
CFLAGS = -Wall -Wextra -Werror

# Compiler
CC = gcc

# Rule to compile the mandatory part
all: $(TARGET)
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

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
	rm -rf $(TARGET)

# Rule to recompile the project
re: fclean all

# Phony rule
.PHONY: all clean fclean re bonus
