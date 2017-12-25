
defs = -D__USE_INLINE__

objects_src = init.cpp
program_src = test.cpp list.cpp list2.cpp

objects = $(objects_src:.cpp=.o)

programs = $(program_src:.cpp=.exe)

ALL: $(programs) $(objects)

%.exe:	%.cpp init.o
		g++ $(defs) -o $@ $(@:.exe=.cpp) init.o

%.o:		%.cpp
		g++ -c $(defs) -o $@ $< 

clean:
		delete #?(.o|.exe)
