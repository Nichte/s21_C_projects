CC := gcc
CFLAGS := -Wall -Werror -Wextra 

TARGET = s21_cat
OBJS = s21_cat.o s21_cat_func.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

check:
	clang-format -n *.c *.h

repair:
	clang-format -i *.c *.h

test: all
	$(BASH) ./test_cat.sh
