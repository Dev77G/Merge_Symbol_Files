CC = g++
combine: main.o combine_files.o merge_larger_files.o merge_smaller_files.o 
	${CC} $^ -o $@

main.o: main.cpp combine.hpp Settings.txt
	${CC} -c main.cpp

combine_files.o: combine_files.cpp
	${CC} -c $^

merge_larger_files.o: merge_larger_files.cpp
	${CC} -c $^

merge_smaller_files.o: merge_smaller_files.cpp
	${CC} -c $^

clean:
	del *.o combine.exe