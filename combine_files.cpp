#include "combine.hpp"
void combine_files(){
    int n = 100; // Default value to merge 100 small files to make one large file
    std::string LocationFrom, LocationTo, no_of_files_to_take;
    std::ifstream Setting("Settings.txt");
    //Taking the Path of Directories from which files have to be read and MultiplexedFile need to be created
    if(std::getline(Setting,LocationFrom)){
        LocationFrom = LocationFrom.substr(13);    
    }
    else{
        std::cout<<"Unable to open or read Setting File";
    }
    if(std::getline(Setting,LocationTo)){
        LocationTo = LocationTo.substr(11);    
    }
    else{
        std::cout<<"Unable to open or read Setting File";
    }
    //Optional to give third line in settings for defining the number of files to take for first step merge
    if(std::getline(Setting,no_of_files_to_take)){
        n = stoi(no_of_files_to_take.substr(2));
    }
    Setting.close();
    
    int i = 0;  //To keep count for sending not more than n files to merge
    std::vector<std::string> some_symbol_files_path , filenames , larger_files_path;
    // some_symbol_files_path will take symbol files till their count is n then send it to merge and clear itself
    // filenames are just symbol name of the files being sent to merge
    // larger_files_path will conatin the path to new merged file made from batch of n symbol files
    for (const auto &symbol_files : std::filesystem::directory_iterator(LocationFrom)) {
        some_symbol_files_path.push_back(symbol_files.path().string());
        std::string temp_filename = symbol_files.path().filename().string();
        filenames.push_back(temp_filename.substr(0,temp_filename.size()-4)); // used substr to remove .txt from filename
        i++;
        if(i == n){
            i = 0;
            larger_files_path.push_back(merge_smaller_files(some_symbol_files_path,filenames,LocationTo));
            some_symbol_files_path.clear();
            filenames.clear();
        }
    }
    // if total files are not perfectly divisible by our batch size n then some will be left so merging them 
    if(i!=0){
        std::string temp_LargeFile = merge_smaller_files(some_symbol_files_path,filenames,LocationTo); 
        larger_files_path.push_back(temp_LargeFile);
    }

    // Merging the large files to get final file at the desired location
    merge_larger_files(larger_files_path,LocationTo);

    // Removing the temporarily made large files
    for(std::string cleaning : larger_files_path){
        std::filesystem::remove(cleaning);
    }
}