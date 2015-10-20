CC				=	cc -O2 $(FLAGS)
FLAGS			=	-Wall -Wextra -Werror

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME			=	libft_malloc_$(HOSTTYPE).so
LN_NAME			=	libft_malloc.so

INC				=	inc
SRCS			=	src/ft_perror.c				\
					src/ft_printf.c				\
					src/ft_puts.c				\
					src/ft_puts_plus.c			\
					src/region_utils.c			\
					src/region_utils_plus.c		\
					src/block_utils.c			\
					src/show_alloc.c			\
					src/malloc.c

OBJS			=	$(SRCS:src/%.c=obj/%.o)

# COLORS
C_NO			=	"\033[00m"
C_OK			=	"\033[35m"
C_GOOD			=	"\033[32m"
C_ERROR			=	"\033[31m"
C_WARN			=	"\033[33m"

# DBG MESSAGE
SUCCESS			=	$(C_GOOD)SUCCESS$(C_NO)
OK				=	$(C_OK)OK$(C_NO)

all: obj $(NAME) cleanln $(LN_NAME)

$(NAME): $(OBJS)
	@$(CC) -shared -o $@ $^
	@echo "Compiling" [ $(NAME) ] $(SUCCESS)

$(LN_NAME):
	@ln -s $(NAME) $@

obj:
	@mkdir -p obj

obj/%.o: src/%.c $(INC)/malloc.h
	@$(CC) -o $@ -c $< -I $(INC)
	@echo "Linking" [ $< ] $(OK)

cleanln:
	@rm -f $(LN_NAME)

clean: cleanln
	@rm -f $(OBJS)
	@rm -rf obj
	@echo "Cleaning" [ $(NAME) ] "..." $(OK)

fclean: clean
	@rm -f $(NAME)
	@echo "Delete" [ $(NAME) ] $(OK)

re: fclean all

.PHONY: all clean fclean re