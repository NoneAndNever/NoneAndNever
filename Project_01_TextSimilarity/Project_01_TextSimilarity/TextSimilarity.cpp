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

// 获取idf表
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

// 获取停用词表
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

// 设置词频表
void TextSimilarity::set_word_frequency(const char* article_1_path, const char* article_2_path)
{
    t1_word_frequency_ = get_word_frequency_from_file(article_1_path);
    t2_word_frequency_ = get_word_frequency_from_file(article_2_path);
}

// 从文件中读取字符串并计算词频
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

// 比较函数
bool cmp_reverse(pair<string, double> lp, pair<string, double> rp) 
{
    return lp.second > rp.second;
}

// 排序函数（按照降序排列）
vector<pair<string, double>> TextSimilarity::sort_by_value_reverse(unordered_map<string, double>& word_frequency) 
{
    vector<pair<string, double>> wfvector(word_frequency.begin(), word_frequency.end());
    sort(wfvector.begin(), wfvector.end(), cmp_reverse);
    return wfvector;
}

