CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -g -fsanitize=address
LDFLAGS = -g -fsanitize=address -lm

BUILD_DIR = build
OBJS_DIR = $(BUILD_DIR)/objs
DEPS_DIR = $(BUILD_DIR)/deps

PRECOMPILE = mkdir -p $(dir $@)
POSTCOMPILE = sleep 0

ifndef NODEPS

PRECOMPILE += ;mkdir -p $(dir $(DEPS_DIR)/$*)
CFLAGS += -MT $@ -MMD -MP -MF $(DEPS_DIR)/$*.Td
POSTCOMPILE += ;mv -f $(DEPS_DIR)/$*.Td $(DEPS_DIR)/$*.d && touch $@

endif

include src.mk

OBJS = $(patsubst src/%.c, $(OBJS_DIR)/%.o, $(SRCS))

all: hash_code

$(OBJS_DIR)/%.o: src/%.c Makefile
	@$(PRECOMPILE)
	$(CC) $(CFLAGS) -c -o $@ $<
	@$(POSTCOMPILE)

hash_code: $(OBJS_GAME) $(OBJS)

hash_code:
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

clean:
	rm -rf build

fclean: clean
	rm -rf hash_code

re:
	$(MAKE) fclean
	$(MAKE) all

include $(wildcard $(DEPS_DIR)/**/*.d)

.PHONY: all clean fclean re test
