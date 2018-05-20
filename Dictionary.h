#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <vector>


using namespace std;

class Dictionary
{
public:
	Dictionary(string synonyms);
	bool Check_if_valid(string word);
	void possible_words(string word);
private:
	ifstream intext;
	vector <string> temp_vec;
	map < string, vector <string> > dictionary;
	map < string, vector <string> >::iterator it;
	void to_map(vector<string> &temp_vec);
	void to_vec(string line);
	void simple_words(vector<string> vec);
	vector<string> words_poss;
};
#endif