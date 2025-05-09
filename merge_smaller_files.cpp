#include "combine.hpp"

std::atomic<int> counter(1);

std::string merge_smaller_files(std::vector<std::string>&some_symbol_files_path, std::vector<std::string> &filenames, std::string &LocationTo){
    int n = some_symbol_files_path.size();
    // using smart pointers to open and point to n files
    std::vector<std::unique_ptr<std::ifstream>> files; 
    for (std::string &single_file : some_symbol_files_path) {
        auto file = std::make_unique<std::ifstream>(single_file);
        if (file->is_open()) {
            files.push_back(std::move(file));
        }
    }
    // min priority queue to access the data in ascending order
    // format : {TimestampSymbol#line_from_file , pointer number}
    // Using this format the lines come out in asc order of TimeStamp , Symbol 
    // used # to handle files with same prefix like BANK , BANKNIFTY 
    // for same timestamp BANK should come first so used # as ASCII(#) < ASCII(A-Z)       
    std::priority_queue<std::pair<std::string,int>,std::vector<std::pair<std::string,int>>,std::greater<std::pair<std::string,int>>>somelines;
    std::string line , ToSortBy , LineToWrite;
    // storing the first line of n symbol files in the priority queue (not the column names) 
    for(int i = 0 ; i < n ; i++){
        if(std::getline(*files[i],line)){
            // just reading and ignoring the first line with column names    
        }
        else{
            std::cout<<"Some Symbol Files are Empty\n";
            continue;
        }
        if(std::getline(*files[i],line)){
            // ToSortBy contains : TimeStampSymbol#
            ToSortBy = line.substr(0,23) + filenames[i] + "#";
            // LineToWrite contains : TimestampSymbol#fina_line_to_be_written
            LineToWrite = ToSortBy + filenames[i] + ", " + line;
            // As this is not final file so added prefix ToSortBy before every line to help us later while merging these files
            somelines.push({LineToWrite , i});            
        }
        else{
            std::cout<<"Some Symbol Files are Empty\n";
        }
    }
    // used atomic variable to name file so if multithreading is used then also no conflicts in naming file are seen 
    int x = counter++;
    // temporarily made new file containg n symbol files with naming as : 1.txt, 2.txt, ...
    std::string new_filename = LocationTo + "\\" + std::to_string(x) + ".txt"; 
    std::ofstream new_file(new_filename);
    if (new_file.is_open()) {
        // will write to new file till priority queue is empty and queue will have atmost n lines at any point of time
        while(!somelines.empty()){
            auto top_element = somelines.top();
            somelines.pop();
            //temporary new files will have lines like this:2021-03-05 10:00:00.123CSCO#2021-03-05 10:00:00.123, 46.14, 120, NYSE_ARCA, Ask
            new_file <<top_element.first << "\n";
            int i = top_element.second;
            // reading and storing another line from same file from which current line is taken
            if(std::getline(*files[i],line)){
                ToSortBy = line.substr(0,23) + filenames[i] + "#";            
                LineToWrite = ToSortBy + filenames[i] + ", " + line;
                somelines.push({LineToWrite , i});            
            }
        }
        new_file.close();
    }
    else {
        std::cout << "Failed to create the file to combine smaller text files.\n";
    }
    // return the path of new temporary large file
    return new_filename;
}