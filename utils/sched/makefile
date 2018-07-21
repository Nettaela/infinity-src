# create makefile for sched 


#fPIC is required for shared objects - position independant code
DEBUG_FLAGS=  -ansi -pedantic-errors -Wall -Wextra -g -fPIC -I../
RELEASE_FLAGS=  -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3  -fPIC -I../
OFILES= task.o uid.o scheduler.o
OFILES_DEBUG= task.dbg.o uid.dbg.o scheduler.dbg.o



# execute clean, release, test
all: print.o libcreate libraries release test clean

#	make release #&& make test && make clean
libraries: libsched.so libsched_debug.so print.so


# compile all c files in release mode
release: libsched.so  
	gcc -I../ -L. -Wall -o a.out scheduler_test.c -lsched -Wl,-rpath=/home/rd47/Proj/src/utils/sched -ldl


print.o: print.c
	gcc $(DEBUG_FLAGS) print.c -c 

print.so: print.o
	gcc -shared print.o -o print.so

# compile all c files in debug mode
debug: libsched_debug.so 
	gcc -g -I../ -L. -Wall -o a.dbg.out scheduler_test.c -lsched -Wl,-rpath=/home/rd47/Proj/src/utils/sched -ldl

libcreate:
	cd .. && $(MAKE) libraries

	
#create release o files
uid.o: uid.c uid.h 
	gcc $(RELEASE_FLAGS) -c uid.c -o uid.o
 	
task.o: uid.c uid.h task.h task.c  
	gcc $(RELEASE_FLAGS) -c task.c -o task.o

scheduler.o: uid.o task.o scheduler.c scheduler.h  
	gcc $(RELEASE_FLAGS) -c scheduler.c -o scheduler.o

	
#create debug o files
uid.dbg.o: uid.c uid.h 
	gcc $(DEBUG_FLAGS) -c uid.c -o uid.dbg.o
 	
task.dbg.o: uid.c uid.h task.h task.c  
	gcc $(DEBUG_FLAGS) -c task.c -o task.dbg.o

scheduler.dbg.o: uid.dbg.o task.dbg.o scheduler.c scheduler.h  
	gcc $(DEBUG_FLAGS) -c scheduler.c -o scheduler.dbg.o

	
libsched.so: $(OFILES)
	gcc -shared $(OFILES) ../libutils.a -o libsched.so
	
libsched_debug.so: $(OFILES_DEBUG)
	gcc -shared $(OFILES_DEBUG) ../libutils_dbg.a -o libsched_debug.so


.PHONY:clean
clean:
	rm *.o 
	rm *.out

# create all test exe file of compiled data and execute them
test:
	./a.out "./print.so" PrintRecurring2





