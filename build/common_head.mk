# Compiler
CC=gcc
AR=ar
LD=ld

# Global Path
SERVER=$(ROOT)/server
CLIENT=$(ROOT)/client
LIB=$(ROOT)/lib
COMMON=$(ROOT)/include
INCLUDE=-I$(COMMON)

# Prefix and Suffix
LIB_PREFIX=lib_
LIB_SUFFIX=.a

define make_subdir
        @for subdir in $(SUBDIRS); do\
                ( cd $$subdir && make $1 )\
        done;
endef
