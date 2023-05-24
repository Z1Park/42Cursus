NAME = test
CXX = c++
CPPFLAGS = -std=c++98 -Wall -Wextra -Werror
RM = rm -rf
SRCS = main.cpp
OBJS = $(SRCS:.cpp=.o)

all : $(NAME)

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re :
	make fclean
	make all

%.o:%.cpp
	$(CXX) $(CPPFLAGS) -o $@ -c $<

$(NAME) : $(OBJS)
	$(CXX) $(CPPFLAGS) -o $@ $^

.PHONY : all clean fclean re bonus
