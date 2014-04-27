export ROOT:=$(shell pwd)
export BUILD:=$(shell pwd)/build
include $(BUILD)/common_head.mk

SUBDIRS=lib server client

INT_MODULE:=lib
.PHONY:$(INT_MODULE)

# Build Flags
DEFS+=-DSTD_POSIX_INTERFACE
LIBS=-Xlinker --start-group \
	$(LIB)/lib_error

TCP_SERVER=tcp_server
TCP_CLIENT=tcp_client
SERVER_SRCS=$(SERVER)/tcp_server.c
CLIENT_SRCS=$(CLIENT)/tcp_client.c
SERVER_OBJS=$(SERVER_SRCS:.c=.o)
CLIENT_OBJS=$(CLIENT_SRCS:.c=.o)

all: $(TCP_SERVER) $(TCP_CLIENT)

$(TCP_SERVER): $(INT_MODULE) $(SERVER_OBJS)
	@echo "---------------------------------------"; \
	echo "	Making $@"; \
	echo "---------------------------------------";
	$(CC) -o $@ $(SERVER_OBJS) $(LIBS)

$(TCP_CLIENT): $(INT_MODULE) $(CLIENT_OBJS)
	@echo "---------------------------------------"; \
        echo "  Making $@"; \
        echo "---------------------------------------";
	$(CC) -o $@ $(CLIENT_OBJS) $(LIBS)

$(INT_MODULE):
	@echo "---------------------------------------"; \
	echo "	Making $@"; \
	echo "---------------------------------------";
	$(MAKE) -C $@

$(SERVER_OBJS):%.o:%.c
	@echo "---------------------------------------"; \
        echo "  Making $@"; \
        echo "---------------------------------------";
	$(CC) $(INCLUDE) $(DEFS) $(CFLAGS) -c $< -o $@

$(CLIENT_OBJS):%.o:%.c
	@echo "---------------------------------------"; \
        echo "  Making $@"; \
        echo "---------------------------------------";
	$(CC) $(INCLUDE) $(DEFS) $(CFLAGS) -c $< -o $@

clean:
	@echo "---------------------------------------"; \
	echo "	Making $@ for all"; \
	echo "---------------------------------------";
	@list='$(INT_MODULE)'; for subdir in $$list; do \
		(cd $$subdir && $(MAKE) clean); \
	done
	-rm -f $(TCP_SERVER) $(TCP_CLIENT) $(SERVER_OBJS) $(CLIENT_OBJS) $(DEPS)
