CC:= g++
CFLAGS:= -ansi -pedantic -Wall -O2
INCLUDES:= -Iinclude/ 
SRCS:= document.cpp featurevector.cpp tokeniser.cpp vocabulary.cpp	\
perceptest.cpp
OBJS:= $(SRCS:.cpp=.o)
MAIN:= perceptest

.PHONY: depend clean

all: $(MAIN)

$(MAIN): $(OBJS) 
	$(CC) $(CFLAGS) $(INCLUDES) -lboost_filesystem-mt-1_35 -o $(MAIN) $(OBJS) 

# this is a suffix replacement rule for building .o's from .c's it
# uses automatic variables $<: the name of the prerequisite of the
# rule(a .c file) and $@: the name of the target of the rule (a .o
# file) (see the gnu make manual section about automatic variables)
.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) $< -c -o $@

clean:
	$(RM) *.o *~ $(MAIN)

depend: $(SRCS)
	makedepend $(INCLUDES) $^



