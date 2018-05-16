#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include<string>

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
	void Load();

	~Board();
private:
	unsigned int x, y; 
	friend string upper(string input);
	friend bool sharedLetters(string input,string coord); 
	friend string LCD(string lcd);
};

#endif // 