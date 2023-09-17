#include "include/cppjieba/Jieba.hpp"
#include "utf8_gbk.h"
#include <fstream>

using namespace std;

const char* const DICT_PATH = "./dict/jieba.dict.utf8";
const char* const HMM_PATH = "./dict/hmm_model.utf8";
const char* const USER_DICT_PATH = "./dict/user.dict.utf8";
const char* const IDF_PATH = "./dict/idf.utf8";
const char* const STOP_WORD_PATH = "./dict/stop_words.utf8";

//从文件读取字符串
string ReadFileIntoString(const char* path) {
    ostringstream ss;
    ifstream input_file(path);
    if (!input_file.is_open()) {
        cerr << "无法从指定路径打开文件 - '"
            << path << "'" << endl;
        exit(EXIT_FAILURE);
    }
    ss << input_file.rdbuf();
    return ss.str();
}


int main(int argc, char** argv) {
    cppjieba::Jieba jieba(DICT_PATH,
        HMM_PATH,
        USER_DICT_PATH,
        IDF_PATH,
        STOP_WORD_PATH);


    string origin = (ReadFileIntoString(*(argv + 1)));
    string copy = ReadFileIntoString(*(argv + 2));
    string result;

    return EXIT_SUCCESS;
}
