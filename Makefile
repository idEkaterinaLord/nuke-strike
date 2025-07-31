# Компилятор
CC = gcc

# Флаги компиляции
CFLAGS = -Wall -Wextra -O2

# Папки
SRC_DIR = src
BUILD_DIR = build

# Главный исходный файл и исполняемый файл
TARGET = $(BUILD_DIR)/nuke

# Все .c файлы проекта
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Все .o файлы
OBJS = $(SRCS:.c=.o)

# Правила
all: $(TARGET)

$(TARGET): $(SRCS)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean
