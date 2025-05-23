#################### PROJECT CONFIGURATION #####################################
################################################################################
# Compilers and flags
CC = cc
CC_FLAGS = -Wall -Werror -Wextra -pthread
RM = rm -rf

# Targets
NAME = philo

################################################################################
#################### DIRECTORIES ##############################################
################################################################################
OBJ_DIR = _obj

################################################################################
#################### SOURCE FILES #############################################
################################################################################
SRC_FILES = main.c utils.c routine.c monitor.c routine_helper.c utils_sec.c \
			init_data.c
################################################################################
#################### OBJECT FILES ############################################
################################################################################
OBJS = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:%.c=%.o))

################################################################################
#################### COMPILATION FLAGS ######################################
################################################################################
CFLAGS := $(CC_FLAGS) -g -MMD -MP

# OS-specific configuration
UNAME := $(shell uname)
ifeq ($(UNAME), Darwin) # macOS
	LDFLAGS :=
else ifeq ($(UNAME), Linux) # Linux
	LDFLAGS :=
else # Windows/Default
	LDFLAGS :=
endif

################################################################################
#################### RULES ###################################################
################################################################################

# Default target
all: $(OBJ_DIR) $(NAME)

# Create object directory
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Rule to compile .c files into .o files
$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@mkdir -p $(@D)
	@echo "\033[0;32mCompiling $<...\033[0m"
	@$(CC) $(CFLAGS) -c $< -o $@

# Rule to create the executable
$(NAME): $(OBJS)
	@echo "\033[0;32mCompiling $(NAME)...\033[0m"
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)
	@echo "\033[0;32mSuccessful Compilation of $(NAME)\033[0m"

# Clean up object files
clean:
	@echo "\033[0;32mCleaning object files...\033[0m"
	@$(RM) $(OBJ_DIR)

# Clean up object files and executable
fclean: clean
	@echo "\033[0;32mRemoving executable...\033[0m"
	@$(RM) $(NAME)
	@echo "\033[0;32mRemoved files successfully\033[0m"

# Rebuild project
re: fclean all

# Debug with Valgrind
debug: CFLAGS += -g
debug: re
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME)

# Address Sanitizer build
san: CFLAGS += -fsanitize=address -g
san: LDFLAGS += -fsanitize=address
san: re

.PHONY: all clean fclean re debug san