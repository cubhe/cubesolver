#include<iostream>
#include"search.h"
int main() {
	/*不能直接用const char 初始char */
	char faceletss[]="RUURULDDLDFRRRFBBRLRBLFUDFLRDULDUFDFFBFDLBUUBBFURBLDBL" ;
	char *facelets = faceletss;
	char *sol = solution(facelets, 22, 200000, 0, "cache");
	std::cout << sol << std::endl;
	system("pause");
	return 0;
}