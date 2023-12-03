NAME	:= chess

CC		:= c++
INCLUDE	:= ./libraries
FLAGS	= -Wall -Wextra -Werror -std=c++11 #to compile with c++11

SRCDIR	:= src
SRC		:= $(shell find $(SRCDIR) -name '*.cpp')

OBJDIR	:= obj
OBJ		:= $(SRC:%.cpp=$(OBJDIR)/%.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(FLAGS) -o $@ $^ -I $(INCLUDE)
	@echo "[$(NAME)] Compiled successfully!"

$(OBJDIR)/%.o: %.cpp
	@mkdir -p $(@D)
	@$(CC) $(FLAGS) -c $< -o $@ -I $(INCLUDE)

clean:
	@rm -rf $(OBJDIR)
	@echo "[$(NAME)] Removed object files!"

fclean: clean 
	@rm -f $(NAME)
	@echo "[$(NAME)] Removed executable file!"

re: fclean all

.PHONY: all clean fclean re
