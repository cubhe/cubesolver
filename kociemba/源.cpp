#include<iostream>
#include"search.h"
int main() {
	/*����ֱ����const char ��ʼchar */
	char faceletss[]="RUURULDDLDFRRRFBBRLRBLFUDFLRDULDUFDFFBFDLBUUBBFURBLDBL" ;
	char *facelets = faceletss;
	char *sol = solution(facelets, 22, 200000, 0, "cache");
	std::cout << sol << std::endl;
	system("pause");
	return 0;
}