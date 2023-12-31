# Minishell - Project to remake a shell in c

# Compile informations
NAME	=	minishell
FLAGS	=	-Wall -Wextra -Werror -g

#All sources files to compile
SRC = src/

SRC_FILES	=	$(wildcard $(SRC)/*.c)
OBJS		=	$(addprefix $(SRC_FOLDER), $(SRC_FILES:.c=.o))

#Some colors
GREEN	=	\033[0;32m
RED		=	\033[0;31m
DEFAULT	=	\033[0m
ORANGE =   \033[0;33m

# Rules
%.o: %.c
	@echo "$(ORANGE) Compiling...$<$(DEFAULT)"
	@gcc $(FLAGS) -c $< -o $@

$(NAME):	$(OBJS)
	@clear
	@printf "$(GREEN)|  \/  (_)     (_)   | |        | | |\n"
	@printf "| .  . |_ _ __  _ ___| |__   ___| | |\n"
	@printf "| |\/| | | '_ \| / __| '_ \ / _ \ | |\n"
	@printf "| |  | | | | | | \__ \ | | |  __/ | |\n"
	@printf "\_|  |_/_|_| |_|_|___/_| |_|\___|_|_|\n"
	@printf "                                                  \n"
	@echo "$(ORANGE) Compiling minishell$(RED)...$(DEFAULT)"
	@gcc $(FLAGS) $(OBJS) -o $(NAME) -lreadline
	@echo "$(GREEN) $(NAME) is ready$(DEFAULT)"

all:	$(NAME)

clean:
	@echo "$(RED) Cleaning..$(NAME)$(DEFAULT)"
	@rm -rf $(OBJS)

fclean:		clean
	@rm -f $(NAME)
	@echo " $(RED)$(NAME) is cleaned$(DEFAULT)"

re:		fclean all
		@echo "$(ORANGE) $(NAME) recompiled successfully$(DEFAULT)"

norm:
	@echo "$(GREEN)Checking norm$(DEFAULT)"
	@norminette $(SRC_FOLDER) | grep -B 1 "Error" || echo "$(GREEN)Norme OK$(DEFAULT)"

.PHONY: all clean fclean re norm
	@echo "$(RED)Cleaning $(NAME)$(DEFAULT)"
	@rm -rf $(NAME)
