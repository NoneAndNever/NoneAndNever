#ifndef  TEXT_SIMILARITY
#define TEXT_SIMILARITY
#endif

#include "cppjieba/Jieba.hpp"

using namespace std;

class TextSimilarity {
public:
	TextSimilarity(
	const string& dict_path, 
	const string& model_path,
	const string& user_dict_path, 
	const string& idf_path, 
	const string& stop_word_path
	);
	
	void get_stop_word_table(const char* stop_word_file);
	void get_idf_words(const char* idf_file);
	
private:
	// 分词对象
	cppjieba::Jieba jieba_;
	// 停用词 
	std::unordered_set<string> stop_word_set_;
	// IDF表
	unordered_map<string, double> idf_word_map_;
	// 词频表
	unordered_map<string, double> t1_word_frequency_;
	unordered_map<string, double> t2_word_frequency_;
	// 相似度
	double similarity_ = -1;
	int _maxWordNumber = 20;


public:
	void set_word_frequency(const char* article_1_path, const char* article_2_path);
	
	unordered_map<string, double> get_word_frequency_from_file(const char* path);

	vector<pair<string, double>> sort_by_value_reverse(unordered_map<string, double>& wf);

	void select_aim_words(vector<pair<string, double>>& wfvec, unordered_set<string>& wset);

	vector<double> get_one_hot(unordered_set<string>& wset, unordered_map<string, double>& wf);

	double cosine(vector<double> oneHot1, vector<double> oneHot2);

	double get_cosine(const char* article_1_path, const char* article_2_path);
};