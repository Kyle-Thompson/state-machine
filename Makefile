# all:
# 	clang++ --std=c++2b main.cpp -o sm_testing

# variants: traffic_light/states/green_light.cpp traffic_light/states/yellow_light.cpp traffic_light/states/red_light.cpp


proj_dir := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

CC        = clang++
STDLIB    = -stdlib=libc++
CFLAGS    = -std=c++2b
CFDEBUG   = -Wall -g
CFWARN    = -Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic
CFWARN   += -Wno-padded -Wno-c++20-compat
CFWARN   += -Wno-exit-time-destructors -Wno-ctad-maybe-unsupported
CFREL     = -O2

EXEC = sm_testing
# SRCS = $(shell find . -path ./lib -prune -o -name "*.cpp" -print)
SRCS = $(shell fd --extension cpp)
OBJS = ${SRCS:.cpp=.o}

all: ${EXEC}

.cpp.o:
	${CC} ${LIBS} ${STDLIB} ${CFLAGS} -o $@ -c $<

${EXEC}: ${OBJS}
	${CC} ${STDLIB} -o ${EXEC} ${OBJS} ${LDFLAGS}

debug: ${EXEC}
debug: CFLAGS += ${CFDEBUG}

warnings: ${EXEC}
warnings: CFLAGS += ${CFDEBUG} ${CFWARN}

release: ${EXEC}
release: CFLAGS += ${CFREL}

clean:
	rm -f ./*.o ./traffic_light/states/*.o ./*.1
	rm -f ./${EXEC}

.PHONY: all debug warnings release clean install
