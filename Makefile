NAME			= webserv


INCLDIR		=	$(addsuffix /include, .)

INCFLAGS	=	$(addprefix -I , $(INCLDIR))

BUILDIR		=	build

OBJ			=	$(SRCS:%.c=$(BUILDIR)/%.o)

SRCS		=	$(addprefix src/,									\
												main.cpp			\
												Client.cpp			\
												Connection.cpp		\
												Config.cpp			\
												MessageHeaders.cpp	\
												Server.cpp			\
												ServerManager.cpp	\
												Uri.cpp				\
												Response.cpp		\
												Request.cpp			\
												utils.cpp			\
												Log.cpp			\
				)

DEPS			= $(SRCS:.cpp=.d)

CC				= c++

RM				= rm -f

CFLAGS		= -MMD -Wall -Wextra -Werror -std=c++98 -g

RM			=	/bin/rm -rf


# FG COLORS
DEFAULT		=	\033[0m
BLACK		=	\033[1;30m
RED			=	\033[1;31m
GREEN		=	\033[1;32m
YELLOW		=	\033[1;33m
BLUE		=	\033[1;34m
MAGENTA 	=	\033[1;35m
CYAN 		=	\033[1;36m
WHITE 		=	\033[1;107

# TERMCAPS
UP			=	\033[1A
DELETE		=	\033[2K
DELPREV		=	$(UP)$(DELETE)\r

# EMOJI
CHECK		=	\xE2\x9C\x94
CROSS		=	\xE2\x9D\x8C

# DISPLAY
HEAD_SIZE	=	32
NAME_SIZE	=	$(shell NAME='$(NAME)'; printf "$${\#NAME}")
PAD_WIDTH	=	$(shell printf "$$((($(HEAD_SIZE) - $(NAME_SIZE)) / 2))")
PAD_PREC	=	$(shell printf "$$(($(PAD_WIDTH) / 2))")
PAD_CHAR	=	\*
PAD_STR		=	$(shell printf '$(PAD_CHAR)%.0s' {1..$(PAD_WIDTH)})
LEFT_PAD	=	$(shell printf '%-*.*s' $(PAD_WIDTH) $(PAD_PREC) $(PAD_STR))
RIGHT_PAD	=	$(shell printf '%*.*s' $$(($(PAD_WIDTH) + $(NAME_SIZE) % 2)) $(PAD_PREC) $(PAD_STR))
BODY_WIDTH	=	$(shell printf "$$(($(HEAD_SIZE) - 1))")


all:			$(NAME)

$(BUILDIR)/%.o:	%.c
				@mkdir -p build/ $(addprefix build/, $(SRCS_DIR))
				@ printf "$(YELLOW)Compiling $@ and generating .o files...$(DEFAULT)\n"
				@$(CC) $(CFLAGS) $(DEFINE) $(INCFLAGS) -c $< -o $@
				@ printf '$(DELPREV)%-*s$(GREEN)$(CHECK)$(DEFAULT)\n' $(BODY_WIDTH) $(notdir $@)

$(NAME):		$(OBJ)
				@ printf "$(YELLOW)Linking source files and generating $@ binary...\n$(DEFAULT)"
				$(CC) $(CFLAGS) $(DEFINE) $(INCFLAGS) -o $@ $^
				@ printf "$(DELPREV)$(GREEN)Binary generated$(DEFAULT)\n"

clean:
				@printf "$(YELLOW)Deleting object files...$(DEFAULT)\n"
				@$(RM) *.d
				@printf "$(DELPREV)$(GREEN)Build files deleted\n"

fclean:			clean
				@printf "$(YELLOW)Deleting build directory...$(DEFAULT)\n"
				@$(RM) $(BUILDIR) $(NAME)
				@printf "$(DELPREV)$(GREEN)Build directory and binary deleted\n"

re:				fclean
				@$(MAKE) -s all

eval:			$(NAME)
				make clean
				reset
				valgrind --track-fds=yes ./$(NAME) myConf.conf

test:			c++ -pthread **/*.cpp -lgtest -lgtest_main && ./a.out

.PHONY:			all clean fclean re

-include ${DEPS}