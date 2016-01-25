TARGET = queue
CPPFLAG = g++
OBJECTS = 3.o

all: $(TARGET)
	
%.o: %.cpp 
	$(CPPFLAG) $< -c

clean: 
	rm -rf *.o
	rm -rf *.out
	rm -rf queue

queue: $(OBJECTS)
	$(CPPFLAG) $(OBJECTS) -o $@

run: queue
	./queue

test: queue
	./queue < 1.in

push:
	git add --all
	git commit -m 'quick push'
	git push
