NAME	:= pacman

CC		:= clang++

DEPS	:= Entity.hpp
SRCS	:= main.cpp Entity.cpp
OBJS	:= $(SRCS:%.cpp=%.o)

all: $(NAME)

$(NAME): $(OBJS)
	@ $(CC) -o $@ $^ -lncurses

%.o: %.cpp $(DEPS)
	@ $(CC) -c $< -o $@

clean:
	@ rm -f $(OBJS)

fclean: clean
	@ rm -f $(NAME)

re: fclean all
