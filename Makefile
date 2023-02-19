SRCS			= main.cpp \
				  src/sockets/SimpleSocket.cpp \
				  src/sockets/ListeningSocket.cpp \
				  src/sockets/ConnectingSocket.cpp \
				  src/sockets/BindingSocket.cpp

OBJS			= $(SRCS:.cpp=.o)
DEPS			= $(SRCS:.cpp=.d)

CXX				= c++
RM				= rm -f
CXXFLAGS		= -MMD -Wall -Wextra -Werror -std=c++98

NAME			= webserv

all:			$(NAME)

$(NAME):		$(OBJS)
				$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

clean:
				$(RM) $(OBJS) $(DEPS)

fclean:			clean
				$(RM) $(NAME)

eval:			$(NAME)
				make clean
				reset
				valgrind ./$(NAME)


re:				fclean $(NAME)

.PHONY:			all clean fclean re test eval

-include ${DEPS}