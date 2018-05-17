#pragma once
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
	vector<string> possible_words(string word);
private:
	ifstream intext;
	vector <string> temp_vec;
	map < string, vector <string> > dictionary;
	map < string, vector <string> >::iterator it;
	void to_map(vector<string> &temp_vec);
	void to_vec(string line);
	void simple_words(vector<string> vec);
};
