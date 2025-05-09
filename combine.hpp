#ifndef COMBINE
#define COMBINE 

#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <string>
#include <queue>
#include <tuple>
#include <atomic>
#include <functional>
#include <filesystem>

void combine_files();
std::string merge_smaller_files(std::vector<std::string> &some_symbol_files_path, std::vector<std::string> &filenames, std::string &LocationTo);
void merge_larger_files(std::vector<std::string> &larger_files_path, std::string &LocationTo);

#endif // COMBINE