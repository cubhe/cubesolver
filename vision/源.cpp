#include<iostream>
#include<string>
#include"vision.h"
using namespace std;
int main() {
	string color=ReadColor();
	if (color.length() != 0) {
		cout <<color<< endl;
	}
	else {
		cout << "ReadColor Failed!\ncheck your code!" << endl;
	}
	return 0;
}