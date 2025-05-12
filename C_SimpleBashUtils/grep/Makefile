CC := gcc
CFLAGS := -Wall -Werror -Wextra 

TARGET = s21_grep
OBJS = s21_grep.o s21_grep_func.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET).exe

check:
	clang-format -n *.c *.h

repair:
	clang-format -i *.c *.h

test: all
	$(BASH) ./test_grep.sh

