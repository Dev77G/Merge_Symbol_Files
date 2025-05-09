#include "combine.hpp"

// similar function like merge_smaller_files 
void merge_larger_files(std::vector<std::string>&larger_files_path, std::string &LocationTo){
    int n = larger_files_path.size();
    std::vector<std::unique_ptr<std::ifstream>> files;
    for (std::string &single_file : larger_files_path) {
        auto file = std::make_unique<std::ifstream>(single_file);
        if (file->is_open()) {
            files.push_back(std::move(file));
        }
    }
    std::priority_queue<std::pair<std::string,int>,std::vector<std::pair<std::string,int>>,std::greater<std::pair<std::string,int>>>somelines;
    std::string line , ToSortBy , LineToWrite;
    for(int i = 0 ; i < n ; i++){
        // no need to remove/ignore first line this time as there are no column names in temporary large files
        if(std::getline(*files[i],line)){
            somelines.push({line , i});            
        }
        else{
            std::cout<<"Some Large Files are Empty\n";
        }
    }
    std::string new_filename = LocationTo + "\\MultiplexedFile.txt"; 
    std::ofstream new_file(new_filename);
    if (new_file.is_open()) {
        // writing the column names to final file 
        new_file << "Symbol, Timestamp, Price, Size, Exchange, Type\n";
        while(!somelines.empty()){
            //due to "TimeStampSymbol#" the lines will come out in asc order
            auto top_element = somelines.top();
            somelines.pop();
            // removing the part till #
            int special_char_ind = top_element.first.find('#');
            std::string final_line = top_element.first.substr(special_char_ind+1);
            // writing the lines to final file
            new_file << final_line << "\n";
            int i = top_element.second;
            if(std::getline(*files[i],line)){
                somelines.push({line , i});            
            }
        }
        new_file.close();
    }
    else {
        std::cout << "Failed to create the file to combine larger text files.\n";
    }
    return;
}