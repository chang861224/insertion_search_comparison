CC = g++
CPPFLAGS = -lm
EXE = main.exe
OBJS = main.o utils.o methods/SkipList.o methods/SortedArray.o methods/Treap.o

$(EXE) : $(OBJS)
	$(CC) $(CPPFLAGS) -o $(EXE) $(OBJS)

%.o : %.cpp
	$(CC) $(CPPFLAGS) -c -o $@ $<

clean :
	rm $(EXE) $(OBJS)
