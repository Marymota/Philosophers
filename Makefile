NAME				:=	philo

PATH_SRC			:=	src
PATH_BUILD			:=	build

SRCS				:=	$(shell find $(PATH_SRC) -name *.c)
OBJS				:=	$(SRCS:%.c=$(PATH_BUILD)/%.o)
DEPS				:=	$(OBJS:.o=.d)
INC_DIRS			:=	$(shell find $(PATH_SRC) -type d)

CC					:=	gcc

FLAG_WARNING		:=	-Wall -Wextra -Werror
FLAG_INC			:=	$(addprefix -I, $(INC_DIRS))
FLAG_MAKEFILE		:=	-MMD -MP
FLAG_DEBUG			:=	-g
FLAG_PTHREAD		:=	-pthread
FLAG_OPTIMIZATION	:=	-03
FLAGS_COMP			:=	$(FLAG_WARNING) $(FLAG_INC) $(FLAG_MAKEFILE) $(FLAG_DEBUG) $(FLAG_PTHREAD) $(FLAD_MEM_LEAK)

FLAD_MEM_LEAK		:=	-fsanitize=address
FLAG_RACE_CONDITION	:=	-fsanitize=thread

RM					:=	rm -rf

_YELLOW				:=	\e[38;5;184m
_GREEN				:=	\e[38;5;46m
_RESET				:=	\e[0m
_INFO				:=	[$(_YELLOW)INFO$(_RESET)]
_SUCCESS			:=	[$(_GREEN)SUCCESS$(_RESET)]

all:					init $(NAME)
						@ printf "$(_SUCCESS) Compilation done\n"
					
init:
						@ printf "$(_INFO) Initialize $(NAME)\n"

$(NAME):				$(OBJS)
						@ $(CC) $(FLAGS_COMP) -o $@ $(OBJS)

$(PATH_BUILD)/%.o:		%.c
						@ mkdir -p $(dir $@)
						@ $(CC) $(FLAGS_COMP) -c $< -o $@

bonus:					all

clean:					
						@ $(RM) $(PATH_BUILD)
						@ printf "$(_INFO) Deleted files and directory\n"

fclean:					clean
						@ $(RM) $(NAME)

re: 					fclean all

debug:					FLAGS_COMP += $(FLAG_RACE_CONDITION)
debug:					re

normH:
						@ norminette $(shell find $(PATH_SRC) -name *.h)

normC:					
						@ norminette $(SRCS)

norm:					normH normC

.PHONY:					all clean fclean re

-include $(DEPS)