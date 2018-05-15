#include "Dictionary.h"
/*==========================================================
=======================CONSTRUCTOR========================*/

void Dictionary::to_vec(string line)
{
	int found = line.find(",");
	if (found == string::npos)
		temp_vec.push_back(line);                                //copies the last word of the line to the vector
	else
	{
		temp_vec.push_back(line.substr(0, line.find(",")));      //copies the word/words before the first comma to the vector
		line.erase(0, line.find(",") + 2);                       //erases those words, the "," and the space
		to_vec(line);
	}
}

void Dictionary::simple_words(vector<string> vec)
{
	for (int i = 0; i<vec.size(); i++)
		for (int j = 0; j < vec.at(i).length(); j++)
		{
			if (vec.at(i).at(j) >= 'a'&& vec.at(i).at(j) <= 'z')
			{
				vec.at(i).at(j) -= 32;                            //all lowercase letters become uppercase letters
			}
			else if (vec.at(i).at(j) < 'A' || vec.at(i).at(j) > 'Z')         //if it isn't a letter
			{
				vec.erase(vec.begin() + i);                       //erases the word/words that aren't simple
				j = 0;                                            //j equals to 0 so it can start the next word
			}
		}
}

void Dictionary::to_map(vector<string> &temp_vec)
{
	string key = temp_vec.at(0);                                  //first word of the line becomes the key
	temp_vec.erase(temp_vec.begin());
	dictionary.insert((it, pair<string, vector<string>>(key, temp_vec)));        //the vector with the other words become the key's pair
}

Dictionary::Dictionary(string synonyms)
{
	string line;
	ifstream intext(synonyms);
	if (intext.is_open())
	{
		while (getline(intext, line))
		{
			temp_vec.push_back(line.substr(0, line.find(":")));   //copies first word from line to the vector
			line.erase(0, line.find(":") + 2);                    //deletes first word, the ":" and the space
			to_vec(line);
			simple_words(temp_vec);
			to_map(temp_vec);
			temp_vec.clear();                                     //clears vector so the new line can be added
		}
		intext.close();
	}

	else cout << "Unable to open file";
}//===============================================================

 /*================================================================
 ==============CHECKS IF THE WORD IS POSSIBLE====================*/
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
}//===============================================================

vector<string> Dictionary::possible_words(string word)
{
	vector<string> words;
	for (it = dictionary.begin(); it != dictionary.end(); it++)
	{
		vector<string> synonyms = it->second;
		string first = it->first;
		for (int i = 0; i < first.size(); i++)
		{
			if (i == first.size() && word.at(i) == first.at(i) || i == first.size() && word.at(i) == '#')
				words.push_back(first); 
			else if (word.at(i) != first.at(i) && word.at(i) != '.' || word.at(i) == '#'&& i != first.size())
				i = string::npos;
		}

		for (int i = 0; i < synonyms.size(); i++)
		{
			string second = synonyms.at(i);
			for (int l = 0; l < second.size(); l++)
			{
				if (l == second.size() && word.at(l) == second.at(l)|| l == second.size() && word.at(l) == '#')
					words.push_back(second); 
				else if (word.at(i) != second.at(l) && word.at(i) != '.' || word.at(i) == '#'&&l != second.size())
					l = string::npos;
			}
		}
	}
	return words;
}

