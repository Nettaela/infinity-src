# create makefile in utils to generate an archive (static) of all data struct: dlist, sorted_list, pqueue, 

DEBUG_FLAGS= -ansi -pedantic-errors -Wall -Wextra -g -fPIC
RELEASE_FLAGS= -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -fPIC
CFILES= dlist.c sorted_list.c p_queue.c 
HFILES= dlist.h sorted_list.h p_queue.h 
OFILES= dlist.o sorted_list.o p_queue.o
OFILES_DEBUG= dlist.dbg.o sorted_list.dbg.o p_queue.dbg.o
# execute clean, release, test



all: libraries release test clean

libraries: libutils.a libutils_dbg.a

#compile all c files in release mode
.PHONY: release
release: $(OFILES) p_queue_test.c
	gcc $(RELEASE_FLAGS) $(OFILES) p_queue_test.c -o a.out

# compile all c files in debug mode
.PHONY: debug
debug: $(OFILES_DEBUG) p_queue_test.c
	gcc $(DEBUG_FLAGS) $(OFILES_DEBUG) p_queue_test.c -o a.dbg.out

#create archive out of o files 
libutils.a:  $(OFILES)
	ar rcs libutils.a  $(OFILES)
	
libutils_dbg.a:  $(OFILES_DEBUG)
	ar rcs libutils_dbg.a  $(OFILES)
	
#create debug o files
dlist.dbg.o: $(CFILES_DEBUG) $(HFILES)
	gcc $(DEBUG_FLAGS) -c dlist.c -o dlist.dbg.o
	
sorted_list.dbg.o: $(CFILES_DEBUG) $(HFILES)
	gcc $(DEBUG_FLAGS) -c sorted_list.c -o sorted_list.dbg.o

p_queue.dbg.o: $(CFILES) $(HFILES)
	gcc $(DEBUG_FLAGS) -c p_queue.c -o p_queue.dbg.o

#create release o files
dlist.o: dlist.c dlist.h
	gcc $(RELEASE_FLAGS) -c dlist.c -o dlist.o
	
sorted_list.o: dlist.c dlist.h sorted_list.c sorted_list.h
	gcc $(RELEASE_FLAGS) -c sorted_list.c -o sorted_list.o

p_queue.o: $(CFILES) $(HFILES)
	gcc $(RELEASE_FLAGS) -c p_queue.c -o p_queue.o

.PHONY: clean
clean:
	rm *.a
	rm *.o
	rm *.out

#create all test exe file of compiled data and execute them
test: ./a.out 
	
a.out:release


