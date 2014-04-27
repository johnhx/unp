include $(BUILD)/common_head.mk

TAGT:=lib_error
SRCS=error.c
DEFS+=-DSTD_POSIX_INTERFACE

OBJS:=$(SRCS:.c=.o)
DEPS:=$(SRCS:.c=.d)

.PHONY:
$(TAGT):$(OBJS)
	@echo "---------------------------------------"; \
	echo "	Making $@"; \
	echo "---------------------------------------"; \
	$(AR) rcs $@ $^

$(OBJS):%.o:%.c
	@echo "---------------------------------------"; \
	echo "    Making $@"; \
	echo "---------------------------------------";
	$(CC) $(INCLUDE) $(DEFS) $(CFLAGS) -c $< -o $@

clean:
	@echo "---------------------------------------"; \
	echo "	Making $@ for $(TAGT)"; \
	echo "---------------------------------------";
	-rm -f $(TAGT) $(OBJS) $(DEPS)
