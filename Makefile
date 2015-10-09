CC				=	cc -g -O2 $(FLAGS)
FLAGS			=	-Wall -Wextra -Werror

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME			=	libft_malloc_$(HOSTTYPE).so
LN_NAME			=	libft_malloc.so

LIB				=	libft/libft.a
LIB_PATH		=	libft/

INC				=	inc
SRCS			=	src/malloc.c

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

$(NAME): $(LIB) $(OBJS)
	@$(CC) -o $@ $^ -L $(LIB_PATH) -lft
	@echo "Compiling" [ $(NAME) ] $(SUCCESS)

$(LN_NAME):
	@ln -s $(NAME) $@

$(LIB):
	@make -C $(LIB_PATH)

obj:
	@mkdir -p obj

obj/%.o: src/%.c $(INC)/malloc.h
	@$(CC) -o $@ -c $< -I $(LIB_PATH)includes -I $(INC)
	@echo "Linking" [ $< ] $(OK)

cleanln:
	@rm -f $(LN_NAME)

clean: cleanln
	@rm -f $(OBJS)
	@rm -rf obj
	@echo "Cleaning" [ $(NAME) ] "..." $(OK)

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIB_PATH) fclean
	@echo "Delete" [ $(NAME) ] $(OK)

re: fclean all

.PHONY: all clean fclean re