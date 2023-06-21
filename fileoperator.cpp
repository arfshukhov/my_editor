#include <fileoperator.h>
#include <fstream>
#include <iomanip>

std::string read_file(std::string path){
    std::ifstream fin(path);
    std::string text = "";
    char line;
    while (fin.get(line))
    {
        text+=line;
    }
    //getline(fin, text);
    fin.close();
    return text;
}

void write_file(std::string text, std::string path){
    std::ofstream fout(path);
    fout << text;
    fout.close();
}
