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
	cout << "Question: [" << wd << "]\n";
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
	cout << "(loading)\n"; Sleep(1000);

	bool ope = true;
	while (ope) {
		vMain();

		int n = words.size();
		int rand_result = (rand() % n + rand() % n) % n;

		string answer = words[rand_result], hid = answer;
		vector<int> rand_res; int temp_rand;

		if (hid.length() <= 3) {
			hid = answer;
		}
		else for (int i = 1; i <= 3; i++) {
			temp_rand = rand() % hid.length();

			vector<int>::iterator fdnres = find(rand_res.begin(), rand_res.end(), temp_rand);
			if (fdnres == rand_res.end())
				rand_res.push_back(temp_rand);
			else i--;
		}
		for (int i = 0; i < hid.length(); i++)
			if (isalpha(hid[i]))
				hid[i] = '_';
		for (vector<int>::iterator iter = rand_res.begin(); iter != rand_res.end(); iter++)
			if (hid[*iter] == '_') hid[*iter] = answer[*iter];

		vWordView(hid);
		string answer_line; int line_number = 0;
		while (true) {
			line_number++;
			cout << "Guess " << line_number << "> ";
			getline(cin, answer_line);
			if (answer_line.empty()) getline(cin, answer_line);
			if (answer_line == "!") {
				cout << "Ans> " << answer << "\n";
				break;
			}
			if (answer_line != answer) {
				cout << "Incorrect answer!\n";

				for (int i = 1; i <= 1; i++) {
					temp_rand = rand() % hid.length();
					vector<int>::iterator fdnres = find(rand_res.begin(), rand_res.end(), temp_rand);
					if (fdnres == rand_res.end())
						rand_res.push_back(temp_rand);
					else i--;
				}
				if (hid[temp_rand] == '_') hid[temp_rand] = answer[temp_rand];
				vWordView(hid);

				if (rand_res.size() == hid.length()) break;
			} else {
				cout << "Bingo!\n";
				Sleep(1500); break;
			}
		}
	}

	in.close();
	
	cout << "\nPress any key to continue...\n";
	getch();
	return 0;
}
