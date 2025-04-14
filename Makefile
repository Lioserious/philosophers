# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/14 16:02:52 by lihrig            #+#    #+#              #
#    Updated: 2025/04/14 16:07:24 by lihrig           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
#################### PROJECT CONFIGURATION #####################################
################################################################################
# Compilers and flags
CC = cc
CC_FLAGS = -Wall -Werror -Wextra
RM = rm -rf

# Targets
SERVER = server
CLIENT = client
SERVER_BONUS = server_bonus
CLIENT_BONUS = client_bonus

################################################################################
#################### DIRECTORIES ##############################################
################################################################################
OBJ_DIR = _obj
LIBFT_DIR = lib/Libft
LIBFT = $(LIBFT_DIR)/libft.a
INC_DIRS := $(LIBFT_DIR)

vpath %.h $(INC_DIRS)

################################################################################
#################### SOURCE FILES #############################################
################################################################################
# Source and Object Files
SRC_FILES = server.c client.c
SRC_FILES_BONUS = server_bonus.c client_bonus.c

################################################################################
#################### OBJECT FILES ############################################
################################################################################
OBJS = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:%.c=%.o))
OBJS_BONUS = $(addprefix $(OBJ_DIR)/, $(SRC_FILES_BONUS:%.c=%.o))

################################################################################
#################### COMPILATION FLAGS ######################################
################################################################################
CFLAGS := $(CC_FLAGS) -g -MMD -MP $(addprefix -I, $(INC_DIRS))

# OS-specific configuration
UNAME := $(shell uname)
ifeq ($(UNAME), Darwin) # macOS
	LDFLAGS := -L$(LIBFT_DIR) -lft
else ifeq ($(UNAME), Linux) # Linux
	LDFLAGS := -L$(LIBFT_DIR) -lft
else # Windows/Default
	LDFLAGS := -L$(LIBFT_DIR) -lft
endif

################################################################################
#################### RULES ###################################################
################################################################################
# Default target
all: $(OBJ_DIR) libft $(SERVER) $(CLIENT)

# Create object directory
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Rule to compile .c files into .o files
$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@mkdir -p $(@D)
	@echo "\033[0;32mCompiling $<...\033[0m"
	@$(CC) $(CFLAGS) -c $< -o $@

# Rule to create the executables
$(SERVER): $(OBJ_DIR)/server.o $(LIBFT)
	@echo "\033[0;32mCompiling $(SERVER)...\033[0m"
	$(CC) $(CFLAGS) $(OBJ_DIR)/server.o -o $(SERVER) $(LDFLAGS)
	@echo "\033[0;32mSuccessful Compilation of $(SERVER)\033[0m"

$(CLIENT): $(OBJ_DIR)/client.o $(LIBFT)
	@echo "\033[0;32mCompiling $(CLIENT)...\033[0m"
	$(CC) $(CFLAGS) $(OBJ_DIR)/client.o -o $(CLIENT) $(LDFLAGS)
	@echo "\033[0;32mSuccessful Compilation of $(CLIENT)\033[0m"

$(SERVER_BONUS): $(OBJ_DIR)/server_bonus.o $(LIBFT)
	@echo "\033[0;32mCompiling $(SERVER_BONUS)...\033[0m"
	$(CC) $(CFLAGS) $(OBJ_DIR)/server_bonus.o -o $(SERVER_BONUS) $(LDFLAGS)
	@echo "\033[0;32mSuccessful Compilation of $(SERVER_BONUS)\033[0m"

$(CLIENT_BONUS): $(OBJ_DIR)/client_bonus.o $(LIBFT)
	@echo "\033[0;32mCompiling $(CLIENT_BONUS)...\033[0m"
	$(CC) $(CFLAGS) $(OBJ_DIR)/client_bonus.o -o $(CLIENT_BONUS) $(LDFLAGS)
	@echo "\033[0;32mSuccessful Compilation of $(CLIENT_BONUS)\033[0m"

# Build Libft (if not already built)
libft: $(LIBFT)
$(LIBFT):
	@echo "\033[0;32mCompiling libft..\033[0m"
	@$(MAKE) -C $(LIBFT_DIR)

# Bonus Instructions
bonus: $(OBJ_DIR) libft $(SERVER_BONUS) $(CLIENT_BONUS)

# Clean up object files and executables
clean:
	@echo "\033[0;32mCleaning object files...\033[0m"
	@$(RM) $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@echo "\033[0;32mRemoving executables...\033[0m"
	@$(RM) $(SERVER) $(CLIENT) $(SERVER_BONUS) $(CLIENT_BONUS)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo "\033[0;32mRemoved files successfully\033[0m"

re: fclean all

# Debug test with Valgrind
debug: CFLAGS += -g
debug: re
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(SERVER)

# Compile with Address Sanitizer
san: CFLAGS += -fsanitize=address -g
san: LDFLAGS += -fsanitize=address
san: re

.PHONY: all clean fclean re libft bonus debug san