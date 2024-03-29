#include<iostream>
#include<string>
#include "Board.h"
#include"Dictionary.h"


using namespace std;
//TODO add colors for an easier and friendlier interface and 
//TODO ctrl-z error flag stop program 
//TODO: verything is case sensitive but the programs ends if receives a wrong input except the ctrl on the options menu... 

int main() {
	//variables 
	int option;
	//console 
	cout << "CROSSWORDS PUZZLE CREATOR" << endl;
	cout << "===========================================" << endl << endl;
	cout << "INSTRUCTIONS:" << endl << endl;
	cout << "Position ( LCD / CTRL-Z = stop )" << endl;
	cout << " LCD stands for  Line Column and Direction" << endl;
	cout << "----------------------------------------------------" << endl << endl;
	cout << "OPTIONS:" << endl;
	cout << "1 - Create puzzle" << endl;
	cout << "2 - Resume puzzle" << endl;
	cout << "0 - Exit" << endl << endl;
	do {
		cout << "Option ? ";
		cin >> option;
		while (cin.fail()) {
			cin.clear();
			std::cin.ignore(256, ' ');
			cout << "Option ? ";
			cin >> option;
		}

		if (option == 1) {
			cout << "------------------------------------" << endl;
			cout << "CREATE A PUZZLE" << endl;
			cout << "------------------------------------" << endl;
			cout << "Dictionary file name ? ";
			string file;
			cin >> file;
			Dictionary dictionary(file);
			cout << endl;
			cout << "Board Size (lines columns) ? ";
			int x, y;
			cin >> x >> y;
			string s;
			while (cin.fail())
			{
				cin.clear();
				std::cin.ignore(256, ' ');
				cout << "Board Size (lines columns) ? ";
				cin >> x >> y;
			}
			cout << endl;
			Board puzzle(x, y);
			puzzle.Build(x, y);
			//playing update cicle 
			string in, word;
			do {
				cout << "Position ( LCD  / CTRL-Z = stop (for test use #) ) ? "; cin >> in; cout << endl;
				if (cin.fail()) {
					cin.clear();
					cin.ignore();
					cout << "Would you like to save your board before stoping it (Y/N) ? ";			//ctrl-z end working  😀
					char answer;
					cin >> answer;
					if (answer == 'Y' || answer == 'y')
						puzzle.Save(file);
					else if (answer == 'N' || answer == 'n')
						cout << "File not saved. " << endl << endl;

					break;
				}
				//check word with class dic 
				cout << "Word ( - = remove / ? = help ) .. ? "; cin >> word; cout << endl;
				if (word == "-") {
					string  hellraiser;
					cout << "Insert the word, that would you would foundly like to erase ? ";
					cin >> hellraiser;
					puzzle.Erase(hellraiser);
				}
				else if (word == "?") {
					char A = 65, a = 97;
					cout << endl << "==================" << endl << "HELP" << endl << "==================" << endl;
					vector<string> words_poss = dictionary.possible_words(puzzle.Line_help(in));
					for (int i = 0; i < words_poss.size(); i++)
						cout << words_poss[i] << "; ";
					cout << endl << endl;
				}
				else if (dictionary.Check_if_valid(word) == true)
					puzzle.Update(in, word);
				else if (dictionary.Check_if_valid(word) == false)
					cout << "Word doesn't belong to the dictionary! " << endl << endl;

			} while (in != "#");

		}
		if (option == 2) {
			Board puzzle(0, 0);
			string values, fileL, dictionaryL;
			values = puzzle.Load();
			string in, word;
			fileL = values.substr(0, 8); dictionaryL = values.erase(0, 9);
			Dictionary LoadDictionary(dictionaryL);
			do {
				cout << "Position ( LCD  / CTRL-Z = stop (for test use #) ) ? "; cin >> in; cout << endl;
				if (cin.fail()) {
					cin.ignore();
					cin.clear();
					puzzle.Save(dictionaryL, fileL); //overload save function 
					break;
				}
				//check word with class dic 
				cout << "Word ( - = remove / ? = help ) .. ? "; cin >> word; cout << endl;
				if (word == "-") {
					string  hellraiser;
					cout << "Insert the word, that would you would foundly like to erase ? ";
					cin >> hellraiser;
					puzzle.Erase(hellraiser);
				}
				else if (word == "?") {

				}
				else if (LoadDictionary.Check_if_valid(word) == true)
					puzzle.Update(in, word);
				else if (LoadDictionary.Check_if_valid(word) == false)
					cout << "Word doesn't belong to the dictionary! " << endl << endl;
			} while (in != "#");
		}
	} while (option != 0);

	return 0;

}