/*
	John Ayad, 900150853
	Monica Fahmy, 900142228
	Youssef Ibrahim, 900142576
	Youssef Nassar
	All Rights Reserved.

	CS110 - Spring 2016 - Dr. Howaida Ismail
	Sokoban
*/
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <unordered_map>
#include <queue>
#define BOX 3
#define WALL 1
#define TARGET 2
using namespace std;

/* DFS
struct state
{
int plX, plY;
vector<vector<int>> map;
bool operator < (const state& other)const
{
return plX < other.plX && plY < other.plY;
}
};*/

class solver
{
private:
	vector<vector<int>>map1b;
	vector<vector<int> > map1a;
	map<pair<vector<vector<int> >, pair<int, int>>, bool> visited;
	string finalSol;
	int playerLocX, playerLocY;
	ifstream ip;
public:
	solver(int, string&);
	void run(cell[][17], cell[][17], int, int);
	string getSol();
	bool gameWin(int i, int j, vector<vector<int> >& map);
	bool getSolution(vector<vector<int>> map, int playerX, int playerY, string sol);
};
