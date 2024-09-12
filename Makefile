NAME = mqtt_broker


SRC = entry_point.c utilities.c 
SRCDIR = src
OBJDIR = obj
BINDIR = bin
OFILES = $(SRC:%.c=$(OBJDIR)/%.o)

INCLUDES = -Iincludes

FLAGS = -Wall -Wextra -Werror -Wpedantic $(INCLUDES)

DEBUG_FLAGS = -g -fsanitize=address,undefined

.PHONY: all clean fclean re

all: $(BINDIR)/$(NAME)

test: $(OFILES)
	@mkdir -p $(BINDIR)
	cc $(FLAGS) $(DEBUG_FLAGS) -Wl,-etestFunction -o $(BINDIR)/$(NAME) $(OFILES)
	
	

$(BINDIR)/$(NAME): $(OFILES)
	@mkdir -p $(BINDIR)
	cc $(FLAGS) -o $(BINDIR)/$(NAME) $(OFILES)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(OBJDIR)
	cc $(FLAGS) -c -o $@ $<

clean:
	rm -f $(OFILES)

debug: $(OFILES)
	@mkdir -p $(BINDIR)
	cc $(FLAGS) $(DEBUG_FLAGS) $(OFILES) -o $(BINDIR)/$(NAME)

fclean: clean
	rm -f $(BINDIR)/$(NAME)

re: fclean all

vpath %.c $(SRCDIR)/
