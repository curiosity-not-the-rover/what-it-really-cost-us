#define _UNICODE
#include <iostream>
#include <vector>
#include <experimental/random>
#include <array>
#include <locale>
#include <string>
#include <unistd.h>
//https://www.youtube.com/watch?v=JoxQVHlcvi4
//                                 ^ soundtrack!!!

using namespace std;
string q = u8"\x3F";
vector<string> q2(5, q);
vector<vector<string>> where_maybe(5, q2);
int urx = 0;
int ury = 0;
array<string, 11> whole_set = {u8"\xE2\x94\x80", u8"\xE2\x94\x82", u8"\xE2\x94\x8C", u8"\xE2\x94\x90", u8"\xE2\x94\x94", u8"\xE2\x94\x98", u8"\xE2\x94\x9C", u8"\xE2\x94\xA4", u8"\xE2\x94\xAC", u8"\xE2\x94\xB4", u8"\xE2\x94\xBC"};
void draw_gradual(array<int,2> max, int daycount) {
	int size_bound_lower[2] = {urx, ury};
	int size_bound_upper[2] = {urx, ury};
	int min[2] = {0,0};
	if (max[0] > 10) {min[0] = max[0] - 10;}
	if (max[1] > 10) {min[1] = max[1] - 10;}
	cout << min[0] << ',' << min[1] << '\n';
	bool whole_map_drawn = false;
	cin.ignore();
	while (whole_map_drawn == false) {
		cout <<"\033[2J\033[1;1H";
		cout << "\n\n";
		cout << "	Your status is: Tired. This is hardcoded. You can't do shit about it.\n";
		cout << "	Day: " << daycount << endl;
		whole_map_drawn = true;
		cout << "	" ;
		cout << "-";
		for (int l = 0; l < size_bound_upper[0]-size_bound_lower[0]; l++) {cout << "-";}
		cout << "\n";
		cout << " 	"<< " ";
		for (int l = 0; l < size_bound_upper[0]-size_bound_lower[0]; l++) {cout << l;}
		cout << '\n';
		for (int i = size_bound_lower[1]; i < size_bound_upper[1]; i++) {
			cout <<"	"<< (i - size_bound_lower[1]);
			for (int j = size_bound_lower[0]; j < size_bound_upper[0]; j++) {
				if (i == ury && j == urx) {cout << "\033[7;5;1m"<<where_maybe[i][j]<<"\033[0m";}
				else {cout << where_maybe[i][j];}
				usleep(max[0]*1000);
			}
			cout << '\n';
			usleep(max[1]*10000);
		}
		if (size_bound_upper[0] < max[0]) {
			size_bound_upper[0]++;
			whole_map_drawn = false;
		}
		if (size_bound_upper[1] < max[1]) {
			size_bound_upper[1]++;
			whole_map_drawn = false;
		}
		if (size_bound_lower[0] > min[0]) {
			size_bound_lower[0]--;
			whole_map_drawn = false;
		}
		if (size_bound_lower[1] > min[1]) {
			size_bound_lower[1]--;
			whole_map_drawn = false;
		}
		if (whole_map_drawn == false) {
			cout << "it's still loading...\n\nbastard. give it time. it's tired.\n";
			usleep((max[0]+max[1])*100000);}
	}
	whole_map_drawn = false;
}

char up_test[7] = {'\x82','\x94','\x98','\x9c', '\xa4', '\xb4', '\xbc'};
char down_test[7] = {'\x82', '\x8c','\x90','\x9c','\xa4','\xac','\xbc'};
char r_test[7] = {'\x80','\x8c','\x94','\x9c','\xac','\xb4','\xbc'};
char l_test[7] = {'\x80','\x90','\x98','\xa4','\xac','\xb4','\xbc'};
char validmoves[4] = {'w','a','s','d'};
char* test2[4] = {up_test, l_test, down_test, r_test};
int umove(char inner, char test) {
	int move = 0;
	for (int i = 0; i < 4; i++) {
		if (inner == validmoves[i]) {
			for (int j = 0; j < 7; j++) {
				if (test2[i][j] == test) {
					move += i;
					move++;
				}
			}
		}
	}
	return move;
}
int movetest(int inn, char test) {
	int movex = 0;
	for (int j = 0; j < 7; j++) {
		if (test2[inn][j] == test) {
			movex = inn;
			movex++;
		}
	}
	return movex;
}
void gameloop() {
	int directions = experimental::randint(0,10);
	int padx = experimental::randint(0,4);
	int pady = experimental::randint(0,4);
	int daycount = 0;
	urx = padx;
	ury = pady;
   	where_maybe[ury][urx] = whole_set[directions];
	while(true) {
		char urpain = where_maybe[ury][urx][2];
		int vertical_bound = where_maybe.size();
		int horizontal_bound = where_maybe[0].size();
		draw_gradual({horizontal_bound, vertical_bound}, daycount);
		cout << "true coordinates: " << urx << ", " << ury << endl;
		char inner;
		cin >> inner;
		int move = umove(inner, urpain);
		if (move > 0) {
			if (move == 4) {urx++;}
			if (move == 3) {ury++;}
			if (move == 2) {urx--;}
			if (move == 1) {ury--;}
			vector<string> newline(horizontal_bound,q);
			if (ury >= vertical_bound) {
				where_maybe.insert(where_maybe.end(), newline);
				vertical_bound++;
			} else if (ury < 0) {
				where_maybe.insert(where_maybe.begin(), newline);
				vertical_bound++;
				ury++;
			}
			if (urx >= horizontal_bound) {
				for (int i = 0; i < vertical_bound; i++) {where_maybe[i].insert(where_maybe[i].end(), q);}
				horizontal_bound++;
			} else if (urx < 0) {
				for (int i = 0; i < vertical_bound; i++) {where_maybe[i].insert(where_maybe[i].begin(), q);}
				horizontal_bound++;
				urx++;
			}
			while (where_maybe[ury][urx] == u8"\x3F") {
				int newmove;
				if (move <= 2) {newmove = move + 2;}
				else if (move > 2) {newmove = move - 2;}
				newmove--;
				srand(time(nullptr));
				int test_case = experimental::randint(0, 10);
				string test_this0 = whole_set[test_case];
				char test_this1 = test_this0[2];
				int valid = movetest(newmove, test_this1);
				if (valid > 0) {where_maybe[ury][urx] = test_this0;}
			}
		}
		daycount++;
	}
}
void titlescreen() {
	cout << "\033[2J\033[1;1H";
	cout << "	A game (read: neo-art project for a post-interactive age) by TOO_AMBITIOUS\n";
	cin.ignore();
	cout << "			what_it_really_cost_us_in_the_end_\n";
	cin.ignore();
	cout << "			(it cost way too much, by the way)\n";
	cin.ignore();
	cout << "\033[2J\033[1;1H";
}

int main() {
	cout << "Hi, if you're reading this, the game isn't done yet. You can probably tell. \n";
	cout << "I'm really sorry for what you're about to see, there's not much I can do about this mess now though. \n";
    	cout << "Good luck. And press enter to continue if you ever think you're stuck.\n";
	cin.ignore();
//    	for(int i = 0; i < 11; i++){cout << whole_set[i] << endl;}
//	cin.ignore();
    	titlescreen();
    	srand(time(nullptr));
    	gameloop();
    	cout << "if u see this, thats a big oopsie right there!!";
}
