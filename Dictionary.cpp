
#include "Dictionary.h"

/*==========================================================
=======================CONSTRUCTOR========================*/

void Dictionary::to_vec(string line)
{
	bool not_found = line.find(",") == string::npos;
	if (not_found)
		temp_vec.push_back(line);																							//copies the last word of the line to the vector
	else
	{
		temp_vec.push_back(line.substr(0, line.find(",")));																	//copies the word/words before the first comma to the vector
		line.erase(0, line.find(",") + 2);                      															//erases those words, the "," and the space
		to_vec(line);
	}
}

void Dictionary::simple_words(vector<string> vec)
{
	for (int i = 0; i<vec.size(); i++)
		for (int j = 0; j < vec.at(i).length(); j++)
		{
			if (vec.at(i).at(j) >= 'a'&& vec.at(i).at(j) <= 'z')
				vec.at(i).at(j) -= 32;							                 											//all lowercase letters become uppercase letters
			else if (vec.at(i).at(j) < 'A' || vec.at(i).at(j) > 'Z')        												//if it isn't a letter
			{
				vec.erase(vec.begin() + i);
				j = string::npos;			                       															//so it jumps to the next word
				i--;                                             															//so it doesn't skip a word
			}
		}
}

void Dictionary::to_map(vector<string> &temp_vec)
{
	string key = temp_vec.at(0);                                 														    //first word of the line becomes the key
	temp_vec.erase(temp_vec.begin());
	dictionary.insert((it, pair<string, vector<string>>(key, temp_vec)));  											        //the vector with the other words become the key's pair
}

Dictionary::Dictionary(string synonyms)
{
	string line;
	ifstream intext(synonyms);
	if (intext.is_open())
	{
		while (getline(intext, line))
		{
			temp_vec.push_back(line.substr(0, line.find(":")));   														    //copies first word from line to the vector
			line.erase(0, line.find(":") + 2);                    														    //deletes first word, the ":" and the space
			to_vec(line);																									//copies all te other words from the line to the vector
			simple_words(temp_vec);																						    //deletes all words that aren't simple
			to_map(temp_vec);
			temp_vec.clear();
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

 /*================================================================
 ============================= HELP =============================*/

vector<string> Dictionary::possible_words(vector<string> words)
{
	string word = words[0];
	words.erase(words.begin());
	vector<string> words_poss;
	/* first takes out the "#" in the begin and in the end (if they exist) */
	if (word[0] == '#')
		word.erase(0);
	for (int i = 0; i<word.size() - 1; i++)
		if (word[i] == '#')
			word.erase(i, word.size() - 1);
	if (word.at(word.size() - 1) == '#')
		word.erase(word.size() - 1);

	/* then it sees what words from the dictionary fit */
	for (it = dictionary.begin(); it != dictionary.end(); it++)
	{
		vector<string> synonyms = it->second;
		string first = it->first;

		if (first.size() <= word.size())
			words_poss.push_back(first);

		for (int i = 0; i < synonyms.size(); i++)
		{
			string second = synonyms[i];

			if (second.size() <= word.size())
				words_poss.push_back(second);
		}

	}

	/* removes every word that would change letters already on the board */
	for (int i = 0; i < words_poss.size(); i++)
	{
		string poss = words_poss[i];
		for (int j = 0; j < poss.size(); j++)
			if (word[j] != '.' && word[j] != poss[j])
			{
				words_poss.erase(words_poss.begin() + i);
				j = string::npos;
				i--;
			}
	}

	/* in the end removes every word that already is in the board or on the vector of the possible words */
	for (int i = 0; i < words.size(); i++)
		for (int j = 0; j < words_poss.size(); j++)
		{
			if (words_poss[j] == words[i])
			{
				words_poss.erase(words_poss.begin() + j);
				j = string::npos;
				i--;
			}
		}
	sort(words_poss.begin(),words_poss.end());
	for (int i = 0; i < words_poss.size(); i++)
	{
		if (words_poss.at(i) == words_poss.at(i+1))
		{
			words_poss.erase(words_poss.begin() + i);
			i--;
		}
	}

	return vector<string>();
}
//===============================================================