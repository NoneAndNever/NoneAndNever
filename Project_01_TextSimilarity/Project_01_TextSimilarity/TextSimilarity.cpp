#include "TextSimilarity.h"
#include "utf8_gbk.h"

#include <map>
#include <string>
#include <vector>

using namespace std;

TextSimilarity::TextSimilarity(
    const string& dict_path,
    const string& model_path,
    const string& user_dict_path,
    const string& idf_path,
    const string& stop_word_path)
    : jieba_(
        dict_path,
        model_path,
        user_dict_path,
        idf_path,
        stop_word_path)
{
    get_stop_word_table(stop_word_path.c_str());
    get_idf_words(idf_path.c_str());
}

void set_idf_word_maps(const char* origin_file_path, const char* target_file_path)
{
    
}

void TextSimilarity::get_idf_words(const char* idf_file) //得到IDF 
{
    ifstream isf(idf_file);
    if (!isf.is_open())
    {
        cout << "open file:" << idf_file << endl;
        return;
    }

    while (!isf.eof())
    {
        string str;
        double dbData;
        isf >> str >> dbData;
        idf_word_map_.insert(pair<string, double>(str, dbData));
    }
    isf.close();
}

void TextSimilarity::get_stop_word_table(const char* stop_word_file) //得到停用词表
{
    ifstream isf(stop_word_file);
    if (!isf.is_open())
    {
        cout << "open file:" << stop_word_file << endl;
        return;
    }

    while (!isf.eof())
    {
        string str;
        getline(isf, str);
        stop_word_set_.insert(str);
    }
    isf.close();
}

void TextSimilarity::set_word_frequency(const char* origin_article_path, const char* target_article_path)
{
    origin_word_frequency_ = get_word_frequency_from_file(origin_article_path);
    target_word_frequency_ = get_word_frequency_from_file(target_article_path);
}

unordered_map<string, double> TextSimilarity::get_word_frequency_from_file(const char* path) {
    ifstream input_file(path);
    if (!input_file.is_open()) {
        cerr << "无法从指定路径打开文件 - '"
            << path << "'" << endl;
        exit(EXIT_FAILURE);
    }
    string line;
    unordered_map<string, int> words_frequency;

    while (!input_file.eof())
    {
        getline(input_file, line);
        
        // GBK --> UTF8
        // line = gbk_utf8(line);
        
        vector<string> words;
        // 对文本当前行分词
        jieba_.Cut(line, words, true);
        // 统计词频
        for (const auto& word : words)
        {
            // 
            auto t = stop_word_set_.count(word);
            if (stop_word_set_.count(word) > 0) //count函数如果set中有这个词就返回1
                continue;
            // 统计词频
            if (words_frequency.count(word) > 0)
                words_frequency[word]++;
            else
                words_frequency[word] = 1;
        }
    }

    unordered_map<string, double> res;
    auto wfIter = words_frequency.begin();
    auto count = words_frequency.size();
    while (wfIter != words_frequency.end())
    {
        res.insert(
            pair<string, double>(wfIter->first, static_cast<double>(wfIter->second) / static_cast<double>(count)));
        ++wfIter;
    }
    return res;
}
