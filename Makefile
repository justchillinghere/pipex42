NAME := pipex

MAIN_FILE := pipex.c
TEST_MAIN_FILE := test.c

LIBFT = libftprintf.a
LIBFT_DIR = ./libftprintf
LIBFT_FILE = $(LIBFT_DIR)/$(LIBFT)
LIBFT_INC_FLAGS = -I$(LIBFT_DIR)/include -I$(LIBFT_DIR)/libft/include
LIBFT_LIB_FLAGS = -L$(LIBFT_DIR) -lftprintf

CRITERION_FLAGS := -I/opt/homebrew/include/criterion -L/opt/homebrew/lib -lcriterion

SRC_DIR := src
OBJS_DIR := obj
INC_DIR := include

HEADERS := $(addprefix $(INC_DIR)/, \
				pipex.h \
				)

SRC_TESTS_DIR := $(SRC_DIR)/tests
SRC_TESTS := $(wildcard $(SRC_TESTS_DIR)/*.c)

vpath %.c \
	$(SRC_DIR)

SRCS := $(filter-out $(SRC_DIR)/$(MAIN_FILE), $(wildcard $(SRC_DIR)/*.c))
OBJS := $(addprefix $(OBJS_DIR)/, $(notdir $(SRCS:.c=.o)))
MAIN_OBJ := $(OBJS_DIR)/$(notdir $(MAIN_FILE:.c=.o))

TEST_OBJ := $(addprefix $(OBJS_DIR)/, $(notdir $(SRC_TESTS:.c=.o)))

CC := cc
CFLAGS := -Wall -Wextra -Werror

all : $(NAME)

$(NAME) : $(LIBFT_FILE) $(HEADERS) $(OBJS) $(MAIN_OBJ) $(TEST_OBJ)
	$(CC) $(CFLAGS) -I$(INC_DIR) $(LIBFT_INC_FLAGS) $(LIBFT_LIB_FLAGS) $(OBJS) $(MAIN_OBJ) -o $(NAME)

$(OBJS_DIR)/%.o : %.c
	$(info $(shell mkdir -p $(OBJS_DIR)))
	$(CC) $(CFLAGS) -I $(INC_DIR) $(LIBFT_INC_FLAGS) -c $< -o $@

$(LIBFT): $(LIBFT_FILE)

$(LIBFT_FILE):
	@make --silent --no-print-directory -C $(LIBFT_DIR)
	@printf "Created printflibft\n"

$(LIBFT)_clean:
	@make --silent --no-print-directory -C $(LIBFT_DIR) clean

$(LIBFT)_fclean:
	@make --silent --no-print-directory -C $(LIBFT_DIR) fclean

bonus: $(NAME)

test : $(NAME) 
	$(CC) $(CFLAGS) -I$(INC_DIR) $(LIBFT_INC_FLAGS) $(LIBFT_LIB_FLAGS) $(CRITERION_FLAGS) $(OBJS) $(TEST_OBJ) -o test.out
	@printf "TestResult:\n"
	@./test.out
	@rm test.out

clean : $(LIBFT)_clean
	@rm -f $(OBJS)
	@printf "Clean done\n"

fclean : $(LIBFT)_fclean clean
	@rm -f $(NAME)
	@printf "Fclean done\n"

re : fclean all

.PHONY: all clean fclean re bonus test