.RECIPEPREFIX := $() $()
CXX = g++
RM = rm -f
# CXXFLAGS=-Wall -std=c++20
# LDLIBS=-lwthttp -lwt -lwtdbo -lwtdbosqlite3
CPPFLAGS = -Wall -std=c++20
LDLIBS = -lwthttp -lwt -lwtdbo -lwtdbosqlite3

SRC_DIR = src
SRCS = $(wildcard $(addsuffix /*.cpp, $(SRC_DIR)))
OBJS = $(subst .cpp,.o,$(SRCS))

all: main

main: $(OBJS)
    $(CXX) $(LDFLAGS) -o main $(OBJS) $(LDLIBS)

depend: .depend

.depend: $(SRCS)
    $(RM) ./.depend
    $(CXX) $(CPPFLAGS) -MM $^>>./.depend;

clean:
    $(RM) $(OBJS)

distclean: clean
    $(RM) *~ .depend

include .depend
