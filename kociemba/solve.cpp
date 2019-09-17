//#include <stdio.h>
//#include <stdlib.h>
//#include "search.h"
//
//int main(int argc, char **argv)
//{
//	argc = 2;
//	argv[1] = "RUURULDDLDFRRRFBBRLRBLFUDFLRDULDUFDFFBFDLBUUBBFURBLDBL";
//    if (argc > 1) {
//        char patternized[64];
//        char* facelets = argv[1];
//        if (argc > 2) {
//            patternize(facelets, argv[2], patternized);
//            facelets = patternized;
//        }
//        char *sol = solution(
//            facelets,
//            21,
//            1000,
//            0,
//            "cache"
//        );
//        if (sol == NULL) {
//            puts("Unsolvable cube!");
//            return 2;
//        }
//        puts(sol);
//        free(sol);
//		system("pause");
//        return 0;
//    } else {
//        return 1;
//    }
//}
