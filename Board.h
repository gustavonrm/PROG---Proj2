#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include<string>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <windows.h>
#include <vector>
#include <fstream>
#include <map>

using namespace std; 

class Board
{
public:
	Board();
	Board(unsigned int x, unsigned int y);
	void Build(const int x, const int y);
	void Update(string pos,string word);
	void Erase(string word); 
	void Save(string dictionary);
	void Save(string dictionary, string file); 
	string Load();
	void Finish();
	~Board();
private:
	unsigned int x, y; 
	map<string, string> word_coordenates;
	map<string, string>::iterator it;
	friend string upper(string input);
	friend bool sharedLetters(string input,string coord); 
	friend string LCD(string lcd);
	//I am not using a showing fucntion beause it differs from function to function sometimes
};

#endif // 