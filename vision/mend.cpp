/*
Because my camera can not recognize all the color on the cube
So i write this code show you how to mend the cube.
there are three steps: MendCenter,MendCorner,MendEdge.
1.MendCenter
Center blocks' position is 4 13 22 31 40 49 in the string
2.MendCorner
Corner is consist of 3 color and there are 8 bolcks in a cube.
1°.I collect the posision of Corners , and Save it in 3 array called A B C.
the positions are:(0,36,47)(2,11,45)(6,18,38)(8,9,20)(24,27,44)(15,26,29)(33,42,53)(17,35,51)
2°.I find which block is complete and sign the incomplete blocks. The date is saved in Corner array.
the order of the array is:WGR WRB WBO WOG YGO YOB YBR YRG
3°.(this is the core operation) in the cube there are only two corner blocks share two same color
With this knowledge , as long as one of them is affirmatory , the other one is defined.
3.MendEdge
Edge blocks is consist of 2 color and there are 12 blocks in a cube.
1°.just like what I do in the MendConer function, I collect the position of 12 blocks ,
saving it in A B arraies.the positions are :
( 1 ,46)( 3 ,37)( 5 ,10)( 7 ,19)
(28,25)(30,43)(32,16)(34,52)
(12,23)(14,48)(50,39)(21,41)
2°.Match it with me template to find which block i lost;
template:WR  WG WO WB
YR  YG  YO  YB
GO OB  BR  BG
3°.As for edge blocks, there are 4 blocks share one color so if 3 of these are defined
we can know the color of the last one.
My teamates are always busy . So I wrote the 600+lines alone QAQ。
*/
#include<iostream>
#include<string>
using namespace std;
int convert(char a) {
	//URFDLB WRGYOB 123456 遵循某种玄学
	switch (a)
	{
	case 'W' :
		return 4;
	case 'R':
		return 13;
	case 'G':
		return 22;
	case 'Y':
		return 31;
	case 'O':
		return 40;
	case 'B':
		return 49;
	default:
		return 0;
	}


}
void ChangeColor(string & str) {
	string temp(str);
	for (int i = 4; i < 50; i += 9) {

		if (temp[i] == 'Y') {
			/*
			012
			345
			678
			630
			741
			852
			*/
			char temp1 = temp[i - 4];
			temp[i - 4] = temp[i + 2];
			temp[i + 2] = temp[i + 4];
			temp[i + 4] = temp[i - 2];
			temp[i - 2] = temp1;
			char temp2 = temp[i - 3];
			temp[i - 3] = temp[i - 1];
			temp[i - 1] = temp[i + 3];
			temp[i + 3] = temp[i + 1];
			temp[i + 1] = temp2;
		}
		if (temp[i] == 'W') {
			/*
			012         258
			345         147
			678         036
			*/
			char temp1 = temp[i - 4];
			temp[i - 4] = temp[i - 2];
			temp[i - 2] = temp[i + 4];
			temp[i + 4] = temp[i + 2];
			temp[i + 2] = temp1;
			char temp2 = temp[i - 3];
			temp[i - 3] = temp[i + 1];
			temp[i + 1] = temp[i + 3];
			temp[i + 3] = temp[i - 1];
			temp[i - 1] = temp2;
		}
		for (int j = -4; j <= 4; j++) {
			str[convert(temp[i]) + j] = temp[i + j];
		}
	}
} 
void MendCubeCenter(string & str) {
	str[4] = 'W';
	str[13] = 'R';
	str[22] = 'G';
	str[31] = 'Y';
	str[40] = 'O';
	str[49] = 'B';
}
void MendCubeCorner(string & str) {
	/*
	(0,36,47)(2,11,45)(6,18,38)(8,9,20)
	(24,27,44)(15,26,29)(33,42,53)(17,35,51)

	WGR WGO WBR WBO
	YGR  YGO  YBR  YBO
	*/
	int corner[8] = { 0 };
	int A[8] = { 0,  2,   6,  8, 24,15,33,17 };
	int B[8] = { 36,11,18, 9, 27,26,42,35 };
	int C[8] = { 47,45,38,20,44,29,53,51 };
	for (int i = 0; i < 8; i++) {
		if (str[A[i]] == 'W' || str[B[i]] == 'W' || str[C[i]] == 'W') {
			if (str[A[i]] == 'G' || str[B[i]] == 'G' || str[C[i]] == 'G') {
				if (str[A[i]] == 'R' || str[B[i]] == 'R' || str[C[i]] == 'R') {
					corner[0] = 1;
				}
				else if (str[A[i]] == 'O' || str[B[i]] == 'O' || str[C[i]] == 'O') {
					corner[1] = 1;
				}
			}
			else if (str[A[i]] == 'B' || str[B[i]] == 'B' || str[C[i]] == 'B') {
				if (str[A[i]] == 'R' || str[B[i]] == 'R' || str[C[i]] == 'R') {
					corner[2] = 1;
				}
				else if (str[A[i]] == 'O' || str[B[i]] == 'O' || str[C[i]] == 'O') {
					corner[3] = 1;
				}
			}
		}
		else if (str[A[i]] == 'Y' || str[B[i]] == 'Y' || str[C[i]] == 'Y') {
			if (str[A[i]] == 'G' || str[B[i]] == 'G' || str[C[i]] == 'G') {
				if (str[A[i]] == 'R' || str[B[i]] == 'R' || str[C[i]] == 'R') {
					corner[4] = 1;
				}
				else if (str[A[i]] == 'O' || str[B[i]] == 'O' || str[C[i]] == 'O') {
					corner[5] = 1;
				}
			}
			else if (str[A[i]] == 'B' || str[B[i]] == 'B' || str[C[i]] == 'B') {
				if (str[A[i]] == 'R' || str[B[i]] == 'R' || str[C[i]] == 'R') {
					corner[6] = 1;
				}
				else if (str[A[i]] == 'O' || str[B[i]] == 'O' || str[C[i]] == 'O') {
					corner[7] = 1;
				}
			}
		}
	}

	cout << "corner: ";
	for (size_t i = 0; i < 8; i++)
		cout << corner[i] << " ";
	cout << endl;

	for (int i = 0; i < 8; i++) {
		/*缺失了哪一块哪一个面*/
		if (str[A[i]] == ' ') {
			/*这个面是什么颜色*/
			if (str[B[i]] == 'W' || str[C[i]] == 'W') {
				if (str[B[i]] == 'R' || str[C[i]] == 'R') {
					if (corner[0] == 0 && corner[2] == 1)
						str[A[i]] = 'G';
					else if (corner[0] == 1 && corner[2] == 0)
						str[A[i]] = 'B';
				}
				else if (str[B[i]] == 'G' || str[C[i]] == 'G') {
					if (corner[0] == 0 && corner[1] == 1)
						str[A[i]] = 'R';
					else if (corner[0] == 1 && corner[1] == 0)
						str[A[i]] = 'O';
				}
				else if (str[B[i]] == 'O' || str[C[i]] == 'O')
				{
					if (corner[1] == 0 && corner[3] == 1)
						str[A[i]] = 'G';
					else if (corner[1] == 1 && corner[3] == 0)
						str[A[i]] = 'B';
				}
				else if (str[B[i]] == 'B' || str[C[i]] == 'B') {
					if (corner[2] == 0 && corner[3] == 1)
						str[A[i]] = 'R';
					else if (corner[2] == 1 && corner[3] == 0)
						str[A[i]] = 'O';
				}
			}
			else if (str[B[i]] == 'Y' || str[C[i]] == 'Y') {
				if (str[B[i]] == 'R' || str[C[i]] == 'R') {
					if (corner[4] == 0 && corner[6] == 1)
						str[A[i]] = 'G';
					else if (corner[4] == 1 && corner[6] == 0)
						str[A[i]] = 'B';
				}
				else if (str[B[i]] == 'G' || str[C[i]] == 'G') {
					if (corner[4] == 0 && corner[5] == 1)
						str[A[i]] = 'R';
					else if (corner[4] == 1 && corner[5] == 0)
						str[A[i]] = 'O';
				}
				else if (str[B[i]] == 'O' || str[C[i]] == 'O')
				{
					if (corner[5] == 0 && corner[7] == 1)
						str[A[i]] = 'G';
					else if (corner[5] == 1 && corner[7] == 0)
						str[A[i]] = 'B';
				}
				else if (str[B[i]] == 'B' || str[C[i]] == 'B') {
					if (corner[6] == 0 && corner[7] == 1)
						str[A[i]] = 'R';
					else if (corner[6] == 1 && corner[7] == 0)
						str[A[i]] = 'O';
				}
			}
			else if (str[B[i]] == 'G' || str[C[i]] == 'G') {
				if (str[B[i]] == 'R' || str[C[i]] == 'R') {
					if (corner[0] == 0 && corner[4] == 1)
						str[A[i]] = 'W';
					else if (corner[0] == 1 && corner[4] == 0)
						str[A[i]] = 'Y';
				}
				else if (str[B[i]] == 'O' || str[C[i]] == 'O') {
					if (corner[1] == 0 && corner[5] == 1)
						str[A[i]] = 'W';
					else if (corner[1] == 1 && corner[5] == 0)
						str[A[i]] = 'Y';
				}
			}
			else if (str[B[i]] == 'B' || str[C[i]] == 'B') {
				if (str[B[i]] == 'R' || str[C[i]] == 'R') {
					if (corner[2] == 0 && corner[6] == 1)
						str[A[i]] = 'W';
					else if (corner[2] == 1 && corner[6] == 0)
						str[A[i]] = 'Y';
				}
				else if (str[B[i]] == 'O' || str[C[i]] == 'O') {
					if (corner[3] == 0 && corner[7] == 1)
						str[A[i]] = 'W';
					else if (corner[3] == 1 && corner[7] == 0)
						str[A[i]] = 'Y';
				}
			}
		}
		else if (str[B[i]] == ' ') {
			if (str[A[i]] == 'W' || str[C[i]] == 'W') {
				if (str[A[i]] == 'R' || str[C[i]] == 'R') {
					if (corner[0] == 0 && corner[2] == 1)
						str[B[i]] = 'G';
					else if (corner[0] == 1 && corner[2] == 0)
						str[B[i]] = 'B';
				}
				else if (str[A[i]] == 'G' || str[C[i]] == 'G') {
					if (corner[0] == 0 && corner[1] == 1)
						str[B[i]] = 'R';
					else if (corner[0] == 1 && corner[1] == 0)
						str[B[i]] = 'O';
				}
				else if (str[A[i]] == 'O' || str[C[i]] == 'O')
				{
					if (corner[1] == 0 && corner[3] == 1)
						str[B[i]] = 'G';
					else if (corner[1] == 1 && corner[3] == 0)
						str[B[i]] = 'B';
				}
				else if (str[A[i]] == 'B' || str[C[i]] == 'B') {
					if (corner[2] == 0 && corner[3] == 1)
						str[B[i]] = 'R';
					else if (corner[2] == 1 && corner[3] == 0)
						str[B[i]] = 'O';
				}
			}
			else if (str[A[i]] == 'Y' || str[C[i]] == 'Y') {
				if (str[A[i]] == 'R' || str[C[i]] == 'R') {
					if (corner[4] == 0 && corner[6] == 1)
						str[B[i]] = 'G';
					else if (corner[4] == 1 && corner[6] == 0)
						str[B[i]] = 'B';
				}
				else if (str[A[i]] == 'G' || str[C[i]] == 'G') {
					if (corner[4] == 0 && corner[5] == 1)
						str[B[i]] = 'R';
					else if (corner[4] == 1 && corner[5] == 0)
						str[B[i]] = 'O';
				}
				else if (str[A[i]] == 'O' || str[C[i]] == 'O')
				{
					if (corner[5] == 0 && corner[7] == 1)
						str[B[i]] = 'G';
					else if (corner[5] == 1 && corner[7] == 0)
						str[B[i]] = 'B';
				}
				else if (str[A[i]] == 'B' || str[C[i]] == 'B') {
					if (corner[6] == 0 && corner[7] == 1)
						str[B[i]] = 'R';
					else if (corner[6] == 1 && corner[7] == 0)
						str[B[i]] = 'O';
				}
			}
			else if (str[A[i]] == 'G' || str[C[i]] == 'G') {
				if (str[A[i]] == 'R' || str[C[i]] == 'R') {
					if (corner[0] == 0 && corner[4] == 1)
						str[B[i]] = 'W';
					else if (corner[0] == 1 && corner[4] == 0)
						str[B[i]] = 'Y';
				}
				else if (str[A[i]] == 'O' || str[C[i]] == 'O') {
					if (corner[1] == 0 && corner[5] == 1)
						str[B[i]] = 'W';
					else if (corner[1] == 1 && corner[5] == 0)
						str[B[i]] = 'Y';
				}
			}
			else if (str[A[i]] == 'B' || str[C[i]] == 'B') {
				if (str[A[i]] == 'R' || str[C[i]] == 'R') {
					if (corner[2] == 0 && corner[6] == 1)
						str[B[i]] = 'W';
					else if (corner[2] == 1 && corner[6] == 0)
						str[B[i]] = 'Y';
				}
				else if (str[A[i]] == 'O' || str[C[i]] == 'O') {
					if (corner[3] == 0 && corner[7] == 1)
						str[B[i]] = 'W';
					else if (corner[3] == 1 && corner[7] == 0)
						str[B[i]] = 'Y';
				}
			}
		}
		else if (str[C[i]] == ' ') {
			if (str[B[i]] == 'W' || str[A[i]] == 'W') {
				if (str[B[i]] == 'R' || str[A[i]] == 'R') {
					if (corner[0] == 0 && corner[2] == 1)
						str[C[i]] = 'G';
					else if (corner[0] == 1 && corner[2] == 0)
						str[C[i]] = 'B';
				}
				else if (str[B[i]] == 'G' || str[A[i]] == 'G') {
					if (corner[0] == 0 && corner[1] == 1)
						str[C[i]] = 'R';
					else if (corner[0] == 1 && corner[1] == 0)
						str[C[i]] = 'O';
				}
				else if (str[B[i]] == 'O' || str[A[i]] == 'O')
				{
					if (corner[1] == 0 && corner[3] == 1)
						str[C[i]] = 'G';
					else if (corner[1] == 1 && corner[3] == 0)
						str[C[i]] = 'B';
				}
				else if (str[B[i]] == 'B' || str[A[i]] == 'B') {
					if (corner[2] == 0 && corner[3] == 1)
						str[C[i]] = 'R';
					else if (corner[2] == 1 && corner[3] == 0)
						str[C[i]] = 'O';
				}
			}
			else if (str[B[i]] == 'Y' || str[A[i]] == 'Y') {
				if (str[B[i]] == 'R' || str[A[i]] == 'R') {
					if (corner[4] == 0 && corner[6] == 1)
						str[C[i]] = 'G';
					else if (corner[4] == 1 && corner[6] == 0)
						str[C[i]] = 'B';
				}
				else if (str[B[i]] == 'G' || str[A[i]] == 'G') {
					if (corner[4] == 0 && corner[5] == 1)
						str[C[i]] = 'R';
					else if (corner[4] == 1 && corner[5] == 0)
						str[C[i]] = 'O';
				}
				else if (str[B[i]] == 'O' || str[A[i]] == 'O')
				{
					if (corner[5] == 0 && corner[7] == 1)
						str[C[i]] = 'G';
					else if (corner[5] == 1 && corner[7] == 0)
						str[C[i]] = 'B';
				}
				else if (str[B[i]] == 'B' || str[A[i]] == 'B') {
					if (corner[6] == 0 && corner[7] == 1)
						str[C[i]] = 'R';
					else if (corner[6] == 1 && corner[7] == 0)
						str[C[i]] = 'O';
				}
			}
			else if (str[B[i]] == 'G' || str[A[i]] == 'G') {
				if (str[B[i]] == 'R' || str[A[i]] == 'R') {
					if (corner[0] == 0 && corner[4] == 1)
						str[C[i]] = 'W';
					else if (corner[0] == 1 && corner[4] == 0)
						str[C[i]] = 'Y';
				}
				else if (str[B[i]] == 'O' || str[A[i]] == 'O') {
					if (corner[1] == 0 && corner[5] == 1)
						str[C[i]] = 'W';
					else if (corner[1] == 1 && corner[5] == 0)
						str[C[i]] = 'Y';
				}
			}
			else if (str[B[i]] == 'B' || str[A[i]] == 'B') {
				if (str[B[i]] == 'R' || str[A[i]] == 'R') {
					if (corner[2] == 0 && corner[6] == 1)
						str[C[i]] = 'W';
					else if (corner[2] == 1 && corner[6] == 0)
						str[C[i]] = 'Y';
				}
				else if (str[B[i]] == 'O' || str[A[i]] == 'O') {
					if (corner[3] == 0 && corner[7] == 1)
						str[C[i]] = 'W';
					else if (corner[3] == 1 && corner[7] == 0)
						str[C[i]] = 'Y';
				}
			}
		}
	}
}
void MendCubeEdge(string &str) {
	/*(1,46)(3,37)(5,10)(7,19)(28,25)(30,43)(32,16)(34,52)(12,23)(14,48)(50,39)(21,41)
	WG WR WB WO  YG YR YB YO  GR GO BR BO*/
	int A[12] = { 1,  3,   5,  7, 28,30,32,34,12,14,50,21 };
	int B[12] = { 46,37,10,19,25,43,16,52,23,48,39,41 };
	int edge[12] = { 0 };
	for (int i = 0; i < 12; i++) {
		if (str[A[i]] == 'W' || str[B[i]] == 'W') {
			if (str[A[i]] == 'G' || str[B[i]] == 'G') {
				edge[0] = 1;
			}
			else if (str[A[i]] == 'R' || str[B[i]] == 'R') {
				edge[1] = 1;
			}
			else if (str[A[i]] == 'B' || str[B[i]] == 'B') {
				edge[2] = 1;
			}
			else if (str[A[i]] == 'O' || str[B[i]] == 'O') {
				edge[3] = 1;
			}
		}
		else if (str[A[i]] == 'Y' || str[B[i]] == 'Y') {
			if (str[A[i]] == 'G' || str[B[i]] == 'G') {
				edge[4] = 1;
			}
			else if (str[A[i]] == 'R' || str[B[i]] == 'R') {
				edge[5] = 1;
			}
			else if (str[A[i]] == 'B' || str[B[i]] == 'B') {
				edge[6] = 1;

			}
			else if (str[A[i]] == 'O' || str[B[i]] == 'O') {
				edge[7] = 1;
			}

		}
		else if (str[A[i]] == 'G' || str[B[i]] == 'G') {
			if (str[A[i]] == 'R' || str[B[i]] == 'R') {
				edge[8] = 1;
			}
			else if (str[A[i]] == 'O' || str[B[i]] == 'O') {
				edge[9] = 1;
			}
		}
		else if (str[A[i]] == 'B' || str[B[i]] == 'B') {
			if (str[A[i]] == 'R' || str[B[i]] == 'R') {
				edge[10] = 1;
			}
			else if (str[A[i]] == 'O' || str[B[i]] == 'O') {
				edge[11] = 1;
			}
		}
	}

	cout << "edge: ";
	for (int i = 0; i < 12; i++)
		cout << edge[i] << " ";
	cout << endl;

	for (int i = 0; i < 12; i++) {
		/*找到是哪一块空缺*/
		if (str[A[i]] == ' ' || str[B[i]] == ' ') {
			/*找到是A面的空缺还是B面的空缺*/
			if (str[A[i]] == ' ') {
				if (str[B[i]] == 'W') {
					if (edge[0] == 0 && edge[1] == 1 && edge[2] == 1 && edge[3] == 1)
						str[A[i]] = 'G';
					else if (edge[0] == 1 && edge[1] == 0 && edge[2] == 1 && edge[3] == 1)
						str[A[i]] = 'R';
					else if (edge[0] == 1 && edge[1] == 1 && edge[2] == 0 && edge[3] == 1)
						str[A[i]] = 'B';
					else if (edge[0] == 1 && edge[1] == 1 && edge[2] == 1 && edge[3] == 0)
						str[A[i]] = 'O';
				}
				else if (str[B[i]] == 'G') {
					if (edge[0] == 0 && edge[4] == 1 && edge[8] == 1 && edge[9] == 1)
						str[A[i]] = 'W';
					else if (edge[0] == 1 && edge[4] == 0 && edge[8] == 1 && edge[9] == 1)
						str[A[i]] = 'Y';
					else if (edge[0] == 1 && edge[4] == 1 && edge[8] == 0 && edge[9] == 1)
						str[A[i]] = 'R';
					else if (edge[0] == 1 && edge[4] == 1 && edge[8] == 1 && edge[9] == 0)
						str[A[i]] = 'O';

				}
				else if (str[B[i]] == 'R') {
					if (edge[1] == 0 && edge[5] == 1 && edge[8] == 1 && edge[10] == 1)
						str[A[i]] = 'W';
					else if (edge[1] == 1 && edge[5] == 0 && edge[8] == 1 && edge[10] == 1)
						str[A[i]] = 'Y';
					else if (edge[1] == 1 && edge[5] == 1 && edge[8] == 0 && edge[10] == 1)
						str[A[i]] = 'G';
					else if (edge[1] == 1 && edge[5] == 1 && edge[8] == 1 && edge[10] == 0)
						str[A[i]] = 'B';
				}
				else if (str[B[i]] == 'O') {
					if (edge[3] == 0 && edge[7] == 1 && edge[9] == 1 && edge[11] == 1) {
						str[A[i]] = 'W';
					}
					else if (edge[3] == 1 && edge[7] == 0 && edge[9] == 1 && edge[11] == 1)
						str[A[i]] = 'Y';
					else if (edge[3] == 1 && edge[7] == 1 && edge[9] == 0 && edge[11] == 1)
						str[A[i]] = 'R';
					else if (edge[3] == 1 && edge[7] == 1 && edge[9] == 1 && edge[1] == 0)
						str[A[i]] = 'O';
				}
				else if (str[B[i]] == 'B') {
					if (edge[2] == 0 && edge[6] == 1 && edge[10] == 1 && edge[11] == 1)
						str[A[i]] = 'W';
					else if (edge[2] == 1 && edge[6] == 0 && edge[10] == 1 && edge[11] == 1)
						str[A[i]] = 'Y';
					else if (edge[2] == 1 && edge[6] == 1 && edge[10] == 0 && edge[11] == 1)
						str[A[i]] = 'R';
					else if (edge[2] == 1 && edge[6] == 1 && edge[10] == 1 && edge[11] == 0)
						str[A[i]] = 'O';

				}
				else if (str[B[i]] == 'Y') {
					if (edge[4] == 0 && edge[5] == 1 && edge[6] == 1 && edge[7] == 1)
						str[A[i]] = 'G';
					else if (edge[4] == 1 && edge[5] == 0 && edge[6] == 1 && edge[7] == 1)
						str[A[i]] = 'R';
					else if (edge[4] == 1 && edge[5] == 1 && edge[6] == 0 && edge[7] == 1)
						str[A[i]] = 'B';
					else if (edge[4] == 1 && edge[5] == 1 && edge[6] == 1 && edge[7] == 0)
						str[A[i]] = 'O';
				}
			}
			/*B面空缺*/
			else if (str[B[i]] == ' ') {
				if (str[A[i]] == 'W') {
					if (edge[0] == 0 && edge[1] == 1 && edge[2] == 1 && edge[3] == 1)
						str[B[i]] = 'G';
					else if (edge[0] == 1 && edge[1] == 0 && edge[2] == 1 && edge[3] == 1)
						str[B[i]] = 'R';
					else if (edge[0] == 1 && edge[1] == 1 && edge[2] == 0 && edge[3] == 1)
						str[B[i]] = 'B';
					else if (edge[0] == 1 && edge[1] == 1 && edge[2] == 1 && edge[3] == 0)
						str[B[i]] = 'O';
				}
				else if (str[A[i]] == 'G') {
					if (edge[0] == 0 && edge[4] == 1 && edge[8] == 1 && edge[9] == 1)
						str[B[i]] = 'W';
					else if (edge[0] == 1 && edge[4] == 0 && edge[8] == 1 && edge[9] == 1)
						str[B[i]] = 'Y';
					else if (edge[0] == 1 && edge[4] == 1 && edge[8] == 0 && edge[9] == 1)
						str[B[i]] = 'R';
					else if (edge[0] == 1 && edge[4] == 1 && edge[8] == 1 && edge[9] == 0)
						str[B[i]] = 'O';

				}
				else if (str[A[i]] == 'R') {
					if (edge[1] == 0 && edge[5] == 1 && edge[8] == 1 && edge[10] == 1)
						str[B[i]] = 'W';
					else if (edge[1] == 1 && edge[5] == 0 && edge[8] == 1 && edge[10] == 1)
						str[B[i]] = 'Y';
					else if (edge[1] == 1 && edge[5] == 1 && edge[8] == 0 && edge[10] == 1)
						str[B[i]] = 'G';
					else if (edge[1] == 1 && edge[5] == 1 && edge[8] == 1 && edge[10] == 0)
						str[B[i]] = 'B';
				}
				else if (str[A[i]] == 'O') {
					if (edge[3] == 0 && edge[7] == 1 && edge[9] == 1 && edge[11] == 1) {
						str[B[i]] = 'W';
					}
					else if (edge[3] == 1 && edge[7] == 0 && edge[9] == 1 && edge[11] == 1)
						str[B[i]] = 'Y';
					else if (edge[3] == 1 && edge[7] == 1 && edge[9] == 0 && edge[11] == 1)
						str[B[i]] = 'R';
					else if (edge[3] == 1 && edge[7] == 1 && edge[9] == 1 && edge[1] == 0)
						str[B[i]] = 'O';
				}
				else if (str[A[i]] == 'B') {
					if (edge[2] == 0 && edge[6] == 1 && edge[10] == 1 && edge[11] == 1)
						str[B[i]] = 'W';
					else if (edge[2] == 1 && edge[6] == 0 && edge[10] == 1 && edge[11] == 1)
						str[B[i]] = 'Y';
					else if (edge[2] == 1 && edge[6] == 1 && edge[10] == 0 && edge[11] == 1)
						str[B[i]] = 'R';
					else if (edge[2] == 1 && edge[6] == 1 && edge[10] == 1 && edge[11] == 0)
						str[B[i]] = 'O';

				}
				else if (str[A[i]] == 'Y') {
					if (edge[4] == 0 && edge[5] == 1 && edge[6] == 1 && edge[7] == 1)
						str[B[i]] = 'G';
					else if (edge[4] == 1 && edge[5] == 0 && edge[6] == 1 && edge[7] == 1)
						str[B[i]] = 'R';
					else if (edge[4] == 1 && edge[5] == 1 && edge[6] == 0 && edge[7] == 1)
						str[B[i]] = 'B';
					else if (edge[4] == 1 && edge[5] == 1 && edge[6] == 1 && edge[7] == 0)
						str[B[i]] = 'O';
				}
			}
		}
	}
}
/*
(0,36,47)(2,11,45)(6,18,38)(8,9,20)
(24,27,44)(15,26,29)(33,42,53)(17,35,51)

WGR WRB WBO WOG
YGO YOB YBR YRG

(1,46)(3,37)(5,10)(7,19)
(28,25)(30,43)(32,16)(34,52)
(12,23)(14,48)(50,39)(21,41)

WR WG WO WB
YR YG YO YB
GO OB BR BG

*/
