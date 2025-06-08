CC = g++
CXXFLAGS = -std=c++20
combine: main.o combine_files.o merge_larger_files.o merge_smaller_files.o semaphore.o
	${CC} ${CXXFLAGS} $^ -o $@

main.o: main.cpp combine.hpp Settings.txt
	${CC} ${CXXFLAGS} -c main.cpp

combine_files.o: combine_files.cpp
	${CC} ${CXXFLAGS} -c $^

merge_larger_files.o: merge_larger_files.cpp
	${CC} ${CXXFLAGS} -c $^

merge_smaller_files.o: merge_smaller_files.cpp
	${CC} ${CXXFLAGS} -c $^

semaphore.o: semaphore.cpp
	${CC} ${CXXFLAGS} -c $^

clean:
	del *.o combine.exe