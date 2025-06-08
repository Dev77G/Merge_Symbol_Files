#include "combine.hpp"

void combine_files(){
    int n = 1;
    std::string LocationFrom, LocationTo, threads_use, no_of_files_to_take;
    std::ifstream Setting("Settings.txt");
    //Taking the Path of Directories from which files have to be read and MultiplexedFile need to be created
    
    if(std::getline(Setting,LocationFrom)){
        LocationFrom = LocationFrom.substr(13);    
    }
    else{
        std::cout<<"In 1st line of Settings.txt Unable to LocationFrom use syntax : \"LocationFrom=c:\\Users\\Dev\\OneDrive\\Desktop\\SymbolFiles\"";
        return;
    }

    if(std::getline(Setting,LocationTo)){
        LocationTo = LocationTo.substr(11);    
    }
    else{
        std::cout<<"In 2nd line of Settings.txt Unable to read LocationTo use syntax : \"LocationTo=c:\\Users\\Dev\\OneDrive\\Desktop\\MergedFile\"";
        return;
    }

    if(std::getline(Setting,threads_use)){
        std::string sema_count_str = threads_use.substr(8);
        std::regex pattern(R"(\d+)");
        if(std::regex_match(sema_count_str, pattern) && sema_count_str.size() < 9){
            sema_count = stoi(sema_count_str);
            //Putting limits to thread counts   
            sema_count = sema_count > std::thread::hardware_concurrency() ? std::thread::hardware_concurrency() : sema_count < 1 ? 1 : sema_count;
        }
        else{
            std::cout<<"In 3rd line of Settings.txt provide some value for thread counts or put : \"threads=-1\"";
            return;
        }        
    }
    else{
        std::cout<<"In 3rd line of Settings.txt provide some value for thread counts or put : \"threads=-1\"";
        return;
    }
        
    if(std::getline(Setting,no_of_files_to_take)){
        std::string n_str = no_of_files_to_take.substr(2); 
        std::regex pattern(R"(\d+)");
        if(std::regex_match(n_str, pattern) && n_str.size() < 9){
            n = stoi(n_str);
            //Putting limits to n (root of number of files)   
            n = n > 1020 ? 1020 : n < 1 ? 1 : n;
        }
        else{
            std::cout<<"In 4th line of Settings.txt provide some value for root of number of files or puta : \"n=-1\"";
            return;
        }        
    }
    else{
        std::cout<<"In 4th line of Settings.txt provide some value for root of number of files or puta : \"n=-1\"";
        return;
    }
    Setting.close();    

    int i = 0;  //To keep count for sending not more than n files to merge
    std::vector<std::string> some_symbol_files_path , filenames , larger_files_path;
    // some_symbol_files_path will take symbol files till their count is n then send it to merge and clear itself
    // filenames are just symbol name of the files being sent to merge
    // larger_files_path will conatin the path to new merged file made from batch of n symbol files
    
    std::vector<std::thread> threadmsf; //thread vector to call merge_smaller_files    
    for (const auto &symbol_files : std::filesystem::directory_iterator(LocationFrom)) {
        some_symbol_files_path.push_back(symbol_files.path().string());
        std::string temp_filename = symbol_files.path().filename().string();
        filenames.push_back(temp_filename.substr(0,temp_filename.size()-4)); // used substr to remove .txt from filename
        i++;
        if(i == n){
            i = 0;
            threadmsf.emplace_back(merge_smaller_files,some_symbol_files_path,filenames,std::ref(LocationTo),std::ref(larger_files_path));
            some_symbol_files_path.clear();
            filenames.clear();
        }
    }
    // if total files are not perfectly divisible by our batch size n then some will be left so merging them 
    if(i!=0){
        Wait();
        threadmsf.emplace_back(merge_smaller_files,some_symbol_files_path,filenames,std::ref(LocationTo),std::ref(larger_files_path));
    }
    
    //Joining every thread
    for(auto& t : threadmsf) {
        if(t.joinable()) 
        t.join();
    }
    
    // Merging the large files to get final file at the desired location
    merge_larger_files(larger_files_path,LocationTo);
    
    // Removing the temporarily made large files
    for(std::string cleaning : larger_files_path){
        std::filesystem::remove(cleaning);
    }

    return;
}