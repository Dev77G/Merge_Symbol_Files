# Merge_Symbol_Files

## Overview
This project provides a script in C++ to merge multiple symbol files into a single file, with an added column Symbol (Name of the files) and the lines in merged file will be sorted in order of timestamp (first column) then symbol name if the files given to merge have their rows sorted in order of timestamp.
This project ensures efficient processing and management of large datasets with symbol information.

## Features
- Merge multiple symbol files into one, for N files sqrt(N) files will be opened at once so more than 1 million files can be merged at once
- Optimized for high-performance processing using multi-threading

## How to use
- Download the repo and open it in terminal
- Use command "make" to create an executable file combine.exe
- Execute the combine.exe using command "start combine.exe" for windows and "./combine.exe" for linux
- Use command "make clean" to delete object files and combine.exe (works only for windows)
- In linux use command "rm -rf .o combine.exe" or make necessary changes in the MakeFile

## Do not forget to make changes in the Settings.txt file :
- Set the paths in first two lines as path from where files have to be merged and the path where new file has to be created
- In the third line set threads = number of threads you want to use or put -1 or 1
- In the fourth line set n = approximate value of square root of total files need to be merged or put -1 or 1