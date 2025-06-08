#ifndef COMBINE
#define COMBINE 

#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <string>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <filesystem>
#include <regex>

extern std::mutex mtx;
extern std::condition_variable cv;
extern int sema_count;

void Wait();
void Notify();

void combine_files();
void merge_smaller_files(std::vector<std::string> some_symbol_files_path, std::vector<std::string> filenames, std::string &LocationTo, std::vector<std::string> &larger_files_path);
void merge_larger_files(std::vector<std::string> &larger_files_path, std::string &LocationTo);

#endif // COMBINE