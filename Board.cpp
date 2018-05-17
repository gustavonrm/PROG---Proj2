#include "Board.h"
//remember to insert the blanck cells and the shared letter and if the words has been inputted previously 😍
// PROG - MIEIC
// JAS
// Example of a program that prints colored characters on the console (in text mode)
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <windows.h>
#include <vector>
#include <fstream>

using namespace std;
//TODO: check words that cros sharing specific letters (last to thing to and i ll need to just the loading thing) NOOICE
//TODO: try to change when the porgram finished and if you have time, the 2 vectors for words and positions that print from the board file for a map (key=pos, val=word)
//TODO: improve remove func sa that can be sensitive to hashes and maintain shared chars
//TODO: Option 2 porgram load func that can read the text file and allocate it in a vector so that the board can be continued 
//TODO: build a func to print the board, avoiding copy and pasting always the same process
//TODO: on load add a counter to define private coordinates 

vector <vector <char> > table;						//board vector, used as a sample O......O
vector <string> words, coordenates; 						//words and coordenates to erase/check/etc... 

string upper(string input) {							//func to change all lower chars to upper if existent on the input 
	for (int i = 0; i < input.size(); i++) {
		if (97 <= input.at(i) && input.at(i) <= 122)
			input.at(i) = input.at(i) - 32;
		else if (65 <= input.at(i) && input.at(i) <= 90)
			input.at(i) = input.at(i);
		else {
			cout << "Invalid characters! " << endl;
			input = "";
			break;
		}
	}
	return input;
}

bool sharedLetters(string input, string coord) {

	int y = coord.at(0) - 65, x = coord.at(1) - 97;
	if (coord.at(2) == 'V') {
		for (int i = 0; i < input.size(); i++) {
			if (table[y][x] == '.')
				y++;
			else if (table[y][x] == input[i])
				y++;
			else if (table[y][x] != input[i])
				return false;
			else if (table[y][x] == '#')
				return false;
		}
		return true;
	}
	else if (coord.at(2) == 'H') {
		for (int i = 0; i < input.size(); i++) {
			if (table[y][x] == '.')
				x++;
			else if (table[y][x] == input[i])
				x++;
			else if (table[y][x] != input[i])
				return false;
			else if (table[y][x] == '#')
				return false;
		}
		return true;
	}
}


string LCD(string lcd) {						//func to maintain lcd case sense
	if (97 <= lcd.at(0) && lcd.at(0) <= 122)
		lcd.at(0) = lcd.at(0) - 32;
	if (65 <= lcd.at(1) && lcd.at(1) <= 90)
		lcd.at(1) = lcd.at(1) + 32;
	if (lcd.at(2) == 104 || lcd.at(2) == 118)
		lcd.at(2) = lcd.at(2) - 32;
	return lcd;
}
//==========================================================================================
//COLOR CODES: (alternative: use symbolic const’s)
#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define BROWN 6
#define LIGHTGRAY 7
#define DARKGRAY 8
#define LIGHTBLUE 9
#define LIGHTGREEN 10
#define LIGHTCYAN 11
#define LIGHTRED 12
#define LIGHTMAGENTA 13
#define YELLOW 14
#define WHITE 15
//==========================================================================================
void clrscr(void)
{
	COORD coordScreen = { 0, 0 }; // upper left corner
	DWORD cCharsWritten;
	DWORD dwConSize;
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hCon, &csbi);
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
	// fill with spaces
	FillConsoleOutputCharacter(hCon, TEXT(' '), dwConSize, coordScreen, &cCharsWritten);
	GetConsoleScreenBufferInfo(hCon, &csbi);
	FillConsoleOutputAttribute(hCon, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
	// cursor to upper left corner
	SetConsoleCursorPosition(hCon, coordScreen);
}
//==========================================================================================
// Position the cursor at column 'x', line 'y'
// The coodinates of upper left corner of the screen are (x,y)=(0,0)
void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
//==========================================================================================
// Set text color
void setcolor(unsigned int color)
{
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hcon, color);
}
//==========================================================================================
// Set text color & background
void setcolor(unsigned int color, unsigned int background_color)
{
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	if (background_color == BLACK)
		SetConsoleTextAttribute(hCon, color);
	else
		SetConsoleTextAttribute(hCon, color | BACKGROUND_BLUE | BACKGROUND_GREEN |
			BACKGROUND_RED);
}
//========================================================================================== 
//====================== Class Itself ======================================================
//==========================================================================================

Board::Board() {

}
Board::Board(unsigned int x, unsigned int y) {				//constructor locking the matrix index 
	this->x = x;
	this->y = y;
}
void Board::Build(const int x, const int y) {         //10/10 couldnt be better <3
	table.clear();
	table.resize(x, vector<char>(y, '.'));			//full vec based on a matrix and fill it with dots 
	char A = 64, a = 96;
	cout << "   ";
	for (int											//basic display, using for cicles in the matrix
		i = 0; i < y; i++) {
		setcolor(4);
		a++;
		cout << a << "  ";
	}
	cout << endl;
	for (int i = 0; i < x; i++) {
		setcolor(4);
		A++;
		cout << A << ' ';
		for (int j = 0; j < y; j++) {
			setcolor(0, 7);
			cout << ' ' << table[i][j] << ' ';
		}
		setcolor(15);
		cout << endl;
	}
}
Board::~Board()     //destructor bc yes...
{
}
//==========================================================================================
//========================== Board Manipulation ============================================
//==========================================================================================
void Board::Update(string pos, string word) { //i need to add a vector to save the words inputed for future reference -remove!
	word = upper(word); //transfrom everything into uppercases 
	pos = LCD(pos);

	bool flag = true;
	for (int i = 0; i < words.size(); i++) {			//check if the word has been previously entered 
		if (word == words.at(i))
			flag = false;
	}
	if (flag == true) {										//main process, update
		char A = 64, a = 96;
		int x = pos[0] - 65, y = pos[1] - 97;
		int size = word.size();
		int xsizemajor = x + size; int xsizeless = x - 1; //used for the blank spaces
		int ysizemajor = y + size; int ysizeless = y - 1;
		int Space = 0;
		if (pos[2] == 'H')  //distribute through line/columns 
			Space = this->y - y;
		else if (pos[2] == 'V')
			Space = this->x - x;
		if (Space < size)     //((H > this->x && V == 0) || (V > this->y && H == 0)) { //check if valid, tho this condition is fucking wrong pls change
			cout << "Word doesn't fit!" << endl;
		else if (sharedLetters(word, pos) == false)
			cout << "That word cannot be written!" << endl << endl; // generate problems on random lines...
		else {
			words.push_back(word);
			coordenates.push_back(pos);
			if (pos[2] == 'V') {
				//distribute through inside the vector line/columns    //need something to check if it valid to write the word
				for (int i = 0; i < size; i++) {		//write the word							//word can only be written if the board had '.' or shared letters
					table[x][y] = word[i];															//if has hashes cant write!
					x++;
				}
				if (xsizemajor < this->x) {					//hashes 
					if (table[xsizemajor][y] == '.')
						table[xsizemajor][y] = '#';
				}
				if (xsizeless >= 0) {						//hashes
					if (table[xsizeless][y] == '.')
						table[xsizeless][y] = '#';
				}
			}															//need to implement some kind of func capable 
			else if (pos[2] == 'H') {				//write the word				//of checking same letters and words, and a removal 
				for (int i = 0; i < size; i++) {
					table[x][y] = word[i];
					y++;
				}
				if (ysizemajor < this->y) {
					if (table[x][ysizemajor] == '.')			//hashes
						table[x][ysizemajor] = '#';
				}
				if (ysizeless >= 0) {
					if (table[x][ysizeless] == '.')				//hashes
						table[x][ysizeless] = '#';
				}
			}
		}
		cout << "   ";														//Same func used on build func, but this time using "this" to get privates 
		for (int i = 0; i < this->y; i++) {									// to not to confuse with x y declared on this func 
			setcolor(4);
			a++;
			cout << a << "  ";
		}
		cout << endl;
		for (int i = 0; i < this->x; i++) {
			setcolor(4);
			A++;
			cout << A << ' ';
			for (int j = 0; j < this->y; j++) {
				if (table[i][j] == '#') {
					setcolor(15, 0);
					cout << ' ' << table[i][j] << ' ';
				}
				else {
					setcolor(0, 7);
					cout << ' ' << table[i][j] << ' ';
				}
			}
			setcolor(15);
			cout << endl;
		}
	}
	if (flag == false)
		cout << "That word is already on the board! " << endl << endl;
}
void Board::Erase(string word) {						//functional 10/10  carefull bc it will be necessary to erase blank spaces 😢
	word = upper(word);
	bool flag = false;
	for (int i = 0; i < words.size(); i++) {
		if (words.at(i) == word) {
			string coord = coordenates.at(i);
			char A = 64, a = 96;
			int x = coord[0] - 65, y = coord[1] - 97; //get the precise coordenates 
			int size = word.size();
			if (coord[2] == 'V') { //distribute through inside the vector line/columns 
				for (int i = 0; i < size; i++) {
					table[x][y] = '.';
					x++;
				}
			}																						//need to implement some kind of func capable 
			else if (coord[2] == 'H') {																	//of checking same letters and words, and a removal 
				for (int i = 0; i < size; i++) {
					table[x][y] = '.';
					y++;
				}
			}
			words.erase(words.begin() + i);						//erase the word from  the allocator vector 
			coordenates.erase(coordenates.begin() + i);			//erase the LCD from  the allocator vec

			for (int i = 0; i < this->y; i++) {									// same procedures used on update, just to show the booard
				setcolor(4);													//its kinda of a sample func 
				a++;
				cout << a << "  ";
			}
			cout << endl;
			for (int i = 0; i < this->x; i++) {
				setcolor(4);
				A++;
				cout << A << ' ';
				for (int j = 0; j < this->y; j++) {
					setcolor(0, 7);
					cout << ' ' << table[i][j] << ' ';
				}
				setcolor(15);
				cout << endl;
			}
			flag = true;
			break;
		}
	}
	if (flag == false)
		cout << "That word is not on the board!" << endl;
}	 //had something to not to erase common letters on crossed words 
//==========================================================================================
//============= File Manipulation ==========================================================     status: 1st func done!, 2nd to be done
//==========================================================================================

void Board::Save(string dictionary) {   //save fucntion in txt file done! 
	string name;
	ofstream save_file;

	name = "b000.txt";

	for (int i = 0; i < 999; i++) {
		string number;
		if (i < 10)
			number = "00" + to_string(i);
		else if (i >= 10 || i < 100)
			number = '0' + to_string(i);
		else if (i >= 100 || i <= 999)
			number = to_string(i);
		name = 'b' + number + ".txt";

		ifstream check_file(name);
		if (check_file.is_open()) {
		}
		else break;
	}
	save_file.open(name);
	save_file << "Dictionary file ? " << dictionary << endl << endl; // dictionary file name not file name , eventually change 
	for (int i = 0; i < this->x; i++) {

		for (int j = 0; j < this->y; j++) {
			save_file << table[i][j] << ' ';
		}
		save_file << endl;
	}
	save_file << endl;
	for (int i = 0; i < words.size(); i++) {									//func that shows the vectors 

		save_file << coordenates.at(i) << " " << words.at(i) << endl;
	}
	setcolor(10);
	cout << " file saved succefully! " << endl << endl;
	setcolor(15);
	save_file.close();

}
void Board::Save(string dictionary, string file) {
	ofstream save_file;
	save_file.open(file);
	save_file << "Dictionary file ? " << dictionary << endl << endl; // dictionary file name not file name , eventually change 
	for (int i = 0; i < this->x; i++) {

		for (int j = 0; j < this->y; j++) {
			save_file << table[i][j] << ' ';
		}
		save_file << endl;
	}
	save_file << endl;
	for (int i = 0; i < words.size(); i++) {									//func that shows the vectors 

		save_file << coordenates.at(i) << " " << words.at(i) << endl;
	}
	setcolor(10);
	cout << " file saved succefully! " << endl << endl;
	setcolor(15);
	save_file.close();

}
string Board::Load() {    //load fucntion working properly 
	table.clear();																				//clear table vector just for security
	words.clear();
	coordenates.clear();																		//the file always the follow this patter:
	string name, line, dictionary;																// 1st line dictionary file name, 2nd blanck, the dic starts on the 3rd line 
	ifstream load_file;																			//ending with a blanck line, the line by line showing pos and words from the board 
	string value;
	vector <char> letters;			//vector to allocate temporarily the board letters line by line 
	int x = 0, y = 0;
	cout << "Please enter name of the board your want to load: ";									//so...
	cin >> name;
	load_file.open(name);
	if (load_file.is_open()) {
		while (getline(load_file, line)) {												//push_back using using vectors, vector by vector pushback 
			if (!line.empty()) {
				if (line.at(0) == 'D' && line.at(1) == 'i') {
					dictionary = line.erase(0, 18);
					line = "...";		//(*) used to not to confilct with the coordenates and words vectors allocated on the vectors 
				}
				if (line.at(1) == ' ') {																//i am using a function to alocate lines on vector pushing back the content 
					letters.clear();																	//to the main vector table, which the matrix i want 
					for (int i = 0; i < line.size(); i++) {
						if (line.at(i) != ' ')
							letters.push_back(line.at(i));
					}
					table.push_back(letters);
					y++;
				}
				if ((line.at(1) >= 97 || line.at(1) <= 122) && line.at(1) != ' ' && (line.at(2) >= 65 || line.at(2) <= 90)) {  //allocate the coordenates and the words on the saving vectors 
					if (line != "...") {			//	(*) realted to the commment upstairs 		
						if (!line.empty()) {		//Used to erase all empty valid lines that were being allocated on the vector when loading the file 
							string pos;
							pos = line.substr(0, 3);
							coordenates.push_back(pos);
							line.erase(0, 4);
							words.push_back(line);
						}

					}
				}
			}
		}
		x = letters.size(); 																		//board display 
		this->x = x; this->y = y;
		char A = 64, a = 96;
		cout << "   ";
		for (int i = 0; i < this->y; i++) {
			setcolor(4);
			a++;
			cout << a << "  ";
		}
		cout << endl;
		for (int i = 0; i < this->x; i++) {
			setcolor(4);
			A++;
			cout << A << ' ';
			for (int j = 0; j < this->y; j++) {
				if (table[i][j] == '#') {
					setcolor(15, 0);
					cout << ' ' << table[i][j] << ' ';
				}
				else {
					setcolor(0, 7);
					cout << ' ' << table[i][j] << ' ';
				}
			}
			setcolor(15);
			cout << endl;
			load_file.close();
		}
		value = name + ' ' + dictionary;
		return  value;
	}
	else cout << "That file does not exist or cannot be opened! " << endl << endl;
}
