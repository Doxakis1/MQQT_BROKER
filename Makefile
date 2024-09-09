NAME = mqtt_broker

SRC = src/entry_point.c

OBJDIR = obj
BINDIR = bin
OFILES = $(SRC:%.c=$(OBJDIR)/%.o)

INCLUDES = -Iincludes

FLAGS = -Wall -Wextra -Werror -pedantic $(INCLUDES)

DEBUG_FLAGS = -g -fsanitize=address,undefined

.PHONY: all clean fclean re

all: $(BINDIR)/$(NAME)

$(BINDIR)/$(NAME): $(OFILES)
	@mkdir -p $(BINDIR)
	cc $(FLAGS) $(OFILES) -o $(BINDIR)/$(NAME)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(OBJDIR)/$(dir $<)
	cc $(FLAGS) -c -o $@ $<

clean:
	rm -f $(OFILES)

debug: $(OFILES)
	@mkdir -p $(BINDIR)
	cc $(FLAGS) $(DEBUG_FLAGS) $(OFILES) -o $(BINDIR)/$(NAME)

fclean: clean
	rm -f $(BINDIR)/$(NAME)

re: fclean all

