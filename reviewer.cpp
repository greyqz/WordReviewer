/**************************
 * Word Reviewer
 * Au: GG
 * follow MIT LICENSE
 **************************/

#include <algorithm>
#include <conio.h>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <ctime>
#include <direct.h>
#include <fstream>
#include <io.h>
#include <iostream>
#include <sstream>
#include <string>
#include <windows.h>
using namespace std;

string FOLDER_PATH = "dic\\";
string DIC_PATH;
string DIC_NAME;
vector<string> words;

bool dirExists(const string& dirName_in) {
    int result = _access(dirName_in.c_str(), 0);
    if (result == 0) return true;   // this is a directory!
    else return false;    // this is not a directory!
}

void vMain() {
	system("cls");
	cout << "+-----------------------------------+\n";
	cout << "| Word Reviewer                     |\n";
	cout << "| Author: GG (2017.10)              |\n";
	cout << "+-----------------------------------+\n";
}

void vWordView(string wd) {
	cout << "  REVIEWING\n";
	cout << "     " << wd << endl;
}

int main() {
	srand(time(NULL));
	vMain();

	char buf[1000003];
	getcwd(buf, 1000000);
	DIC_PATH.assign(buf);

	cout << "Dictionary name: ";
	getline(cin, DIC_NAME);
	if (DIC_NAME.empty()) {
		cout << "[WARNING] No dictionary input.\n\nPress any key to continue...\n";
		getch(); return 0;
	}
	DIC_PATH = FOLDER_PATH + DIC_NAME;
	ifstream in(DIC_PATH);
	if (!in) {
		cout << "[WARNING] Doesn't exist.\n\nPress any key to continue...\n";
		getch(); return 0;
	}
	cout << "Dictionary [" << DIC_NAME << "] ";

	string line; 
	while (getline(in, line)) {
		words.push_back(line);
	}
	cout << "(loaded)\n";

	bool ope = true;
	while (ope) {
		int n = words.size();
		int rand_result = (rand() % n + rand() % n) % n;

		string hid = words[rand_result], answer = hid;
		int rand_res1 = rand() % hid.length(),
		    rand_res2 = rand() % hid.length(),
		    rand_res3 = rand() % hid.length(),
		    rand_res4 = rand() % hid.length(),
		    rand_res5 = rand() % hid.length();
		for (int i = 0; i < hid.length(); i++)
			if (isalpha(hid[i])
					&& i != rand_res1
					&& i != rand_res2
					&& i != rand_res3
					&& i != rand_res4
					&& i != rand_res5)
				hid[i] = '_';

		vWordView(hid);
		string answer_line; int line_number = 0;
		bool FirstTime = true;
		cout << "Type answer:\n";
		while (true) {
			line_number++;
			cout << "Guess " << line_number << "> ";
			getline(cin, answer_line);
			if (FirstTime && answer_line.empty()) getline(cin, answer_line);
			FirstTime = false;
			if (answer_line.empty()) {ope = false; break;}
			if (answer_line == "!") {
				cout << "Ans> " << answer << "\n";
				break;
			}
			if (answer_line != answer) {
				cout << "Incorrect guess!\n";
			} else {
				cout << "Bingo!\n"; break;
			}
		}
	}

	in.close();
	
	cout << "\nPress any key to continue...\n";
	getch();
	return 0;
}
