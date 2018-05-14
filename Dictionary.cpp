#include "Dictionary.h"

void Dictionary::to_vec(string line)
{
	int found = line.find(",");
	if (found == string::npos)
	{
		temp_vec.push_back(line);
		line.clear();
	}
	else
	{
		temp_vec.push_back(line.substr(0, line.find(",")));
		line.erase(0, line.find(",") + 2);
		to_vec(line);
	}
}

void Dictionary::simple_words(vector<string> vec)
{
	for (int i = 0; i<vec.size(); i++)
		for (int j = 0; j < vec.at(i).length(); j++)
		{
			if(vec.at(i).at(j)>='a'&& vec.at(i).at(j)<='z')
			{
				char c;
				c = vec.at(i).at(j);
				c = c - 32;
				vec.at(i).at(j) = c;
			}
			else if (vec.at(i).at(j) < 'A' || vec.at(i).at(j) > 'Z')
			{
				j = string::npos;
				vec.erase(vec.begin() + i);
				i--;
			}			
		}
}

void Dictionary::to_map(vector<string> &temp_vec)
{
	string key = temp_vec.at(0);
	temp_vec.erase(temp_vec.begin());
	dictionary.insert((it, pair<string, vector<string>>(key, temp_vec)));
}

Dictionary::Dictionary(string synonyms)
{
	string line;
	ifstream intext(synonyms);
	if (intext.is_open())
	{
		while (getline(intext, line))
		{
			temp_vec.clear();
			temp_vec.push_back(line.substr(0, line.find(":")));
			line.erase(0, line.find(":") + 2);
			to_vec(line);
			simple_words(temp_vec);
			to_map(temp_vec);
		}
		intext.close();
	}

	else cout << "Unable to open file";
}

bool Dictionary::Check_if_valid(string word)
{
	for (it = dictionary.begin(); it != dictionary.end(); it++)
	{
		if (it->first == word)
			return true;
		vector<string> synonyms = it->second;
		for (int i = 0; i < synonyms.size(); i++)
			if (synonyms.at(i) == word)
				return true;
	}
	return false;
}

vector<string> Dictionary::possible_words(string word)
{
	vector<string> words;
	for (it = dictionary.begin(); it != dictionary.end(); it++)
	{
		vector<string> synonyms = it->second;
		string first = it->first;
		for (int i = 0; i < first.size(); i++)
		{
			if (word.at(i) != first.at(i) && word.at(i) != '#')
				i = string::npos;
			else if (i + 1 == first.size() && word.at(i) == first.at(i))
				words.push_back(first);
		}

		for (int i = 0; i < synonyms.size(); i++)
		{
			string second = synonyms.at(i);
			for (int l = 0; l < second.size(); l++)
			{
				if (word.at(i) != second.at(l) && word.at(i) != '#')
					l = string::npos;
				if (l + 1 == second.size() && word.at(l) == second.at(l))
					words.push_back(second);
			}
		}
	}
	return words;
}

