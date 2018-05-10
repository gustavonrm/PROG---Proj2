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
		if (option == 1) {
			cout << "------------------------------------" << endl;
			cout << "CREATE A PUZZLE" << endl;
			cout << "------------------------------------" << endl;
			/*cout << "Dictionary file name ? ";
			string file;
			cin >> file;
			Dictionary dictionary(file);
			cout << endl;*/
			cout << "Board Size (lines columns) ? ";
			int x, y;
			cin >> x >> y;
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
						puzzle.Save();
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
					cout << endl << "==================" << endl << "HELP" << endl << "==================" << endl;
					cout << "Word ? "; string w; cin >> w; cout << endl;
					//dictionary.possible_words(w);
				}
				else //if (dictionary.Check_if_valid(word) == true) add when dictionary is fucntional 
					puzzle.Update(in, word);

			} while (in != "#");

		}
		if (option == 2) {
			cout << "Coming soon..." << endl;
		}
	} while (option != 0);

	return 0;

}


