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
#include "cell.h"
#include "solver.h"
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

solver::solver(int lev, string &give) {
	finalSol = "";
}
void solver::run(cell mapX[][17], cell mapY[][17], int pX, int pY) {
	map1a.resize(17);
	map1b.resize(17);

	for (int i = 0; i < 17; i++)
		map1a[i].resize(17), map1b[i].resize(17);
	for (int i = 0; i < 17; i++) {
		for (int j = 0; j < 17; j++) {
			map1a[i][j] = mapX[i][j].getType();
			map1b[i][j] = mapY[i][j].getType();
		}
	}
	playerLocX = pX;
	playerLocY = pY;
	/*for (int i = 0; i < 17; i++) {
		for (int j = 0; j < 17; j++) {
			cout << map1b[i][j] << " ";
		} cout << endl;
	}*/
	string sol = "";
	getSolution(map1b, playerLocX, playerLocY, sol); // cout << "FOUND SOLUTION : " << endl;
	//else cout << "NO SOLUTION" << endl;
	//cout << finalSol << endl;
	//system("pause");
	//return 0;
}

string solver::getSol() {
	return finalSol;
}

bool solver::getSolution(vector<vector<int>> mapi, int playerXi, int playerYi, string soli)
{
	queue<pair< pair< vector<vector<int> >, string>, pair< int, int > > > q;
	pair< pair< vector<vector<int> >, string>, pair< int, int > > initial;
	initial.first.first = mapi;
	initial.first.second = soli;
	initial.second.first = playerXi;
	initial.second.second = playerYi;

	q.push(initial);

	while (!q.empty())
	{
		pair< pair< vector<vector<int> >, string>, pair< int, int > > top = q.front();
		vector<vector<int>> map = top.first.first;
		string sol = top.first.second;
		int playerX = top.second.first;
		int playerY = top.second.second;

		q.pop();
		if (gameWin(0, 0, map)) {
			finalSol = sol;
			return true;
		}
		pair<vector<vector<int> >, pair<int, int>> cur;
		cur.first = map;
		cur.second.first = playerX;
		cur.second.second = playerY;
		if (visited[cur])
			continue;
		visited[cur] = true;
		if (playerX < 16) {
			if (map1a[playerY][playerX + 1] != WALL) //Right
			{
				if (map[playerY][playerX + 1] == BOX)
				{
					if (playerX < 15) {
						if (map1a[playerY][playerX + 2] != WALL && (map[playerY][playerX + 2] != BOX))
						{
							swap(map[playerY][playerX + 1], map[playerY][playerX + 2]);
							/*if (getSolution(map, playerX + 1, playerY, sol + "R"))
							return true;*/
							if (!visited[make_pair(map, make_pair(playerX + 1, playerY))])
								q.push(make_pair(make_pair(map, sol + "R"), make_pair(playerX + 1, playerY)));
							swap(map[playerY][playerX + 1], map[playerY][playerX + 2]);
						}
					}
				}
				else
				{
					if (!visited[make_pair(map, make_pair(playerX + 1, playerY))])
						q.push(make_pair(make_pair(map, sol + "R"), make_pair(playerX + 1, playerY)));
					/*if (getSolution(map, playerX + 1, playerY, sol + "R"))
					return true;*/
				}
			}
		}
		if (playerX > 0) {
			if (map1a[playerY][playerX - 1] != WALL) //Left
			{
				if (map[playerY][playerX - 1] == BOX)
				{
					if (playerX > 1) {

						if (map1a[playerY][playerX - 2] != WALL && (map[playerY][playerX - 2] != BOX))
						{
							swap(map[playerY][playerX - 1], map[playerY][playerX - 2]);
							if (!visited[make_pair(map, make_pair(playerX - 1, playerY))])
								q.push(make_pair(make_pair(map, sol + "L"), make_pair(playerX - 1, playerY)));
							//if (getSolution(map, playerX - 1, playerY, sol + "L"))
							//		return true;
							swap(map[playerY][playerX - 1], map[playerY][playerX - 2]);
						}
					}
				}
				else
				{
					if (!visited[make_pair(map, make_pair(playerX - 1, playerY))])
						q.push(make_pair(make_pair(map, sol + "L"), make_pair(playerX - 1, playerY)));
					//if (getSolution(map, playerX - 1, playerY, sol + "L"))
					//	return true;
				}
			}
		}

		if (playerY < 16) {
			if (map1a[playerY + 1][playerX] != WALL)
			{
				if (map[playerY + 1][playerX] == BOX)
				{
					if (playerY < 15) {
						if (map1a[playerY + 2][playerX] != WALL && (map[playerY + 2][playerX] != BOX))
						{
							swap(map[playerY + 1][playerX], map[playerY + 2][playerX]);
							if (!visited[make_pair(map, make_pair(playerX, playerY + 1))])
								q.push(make_pair(make_pair(map, sol + "D"), make_pair(playerX, playerY + 1)));
							//if (getSolution(map, playerX, playerY + 1, sol + "D"))
							//	return true;
							swap(map[playerY + 1][playerX], map[playerY + 2][playerX]);
						}
					}
				}
				else
				{
					if (!visited[make_pair(map, make_pair(playerX, playerY + 1))])
						q.push(make_pair(make_pair(map, sol + "D"), make_pair(playerX, playerY + 1)));
					//if (getSolution(map, playerX, playerY + 1, sol + "D"))
					//	return true;
				}
			}
		}
		if (playerY > 0) {
			if (map1a[playerY - 1][playerX] != WALL) //Up
			{
				if (map[playerY - 1][playerX] == BOX)
				{
					if (playerY > 1) {
						if (map1a[playerY - 2][playerX] != WALL && (map[playerY - 2][playerX] != BOX))
						{
							swap(map[playerY - 1][playerX], map[playerY - 2][playerX]);
							if (!visited[make_pair(map, make_pair(playerX, playerY - 1))])
								q.push(make_pair(make_pair(map, sol + "U"), make_pair(playerX, playerY - 1)));
							//if (getSolution(map, playerX, playerY - 1, sol + "U"))
							//	return true;
							swap(map[playerY - 1][playerX], map[playerY - 2][playerX]);
						}
					}
				}
				else
				{
					if (!visited[make_pair(map, make_pair(playerX, playerY - 1))])
						q.push(make_pair(make_pair(map, sol + "U"), make_pair(playerX, playerY - 1)));
					//if (getSolution(map, playerX, playerY - 1, sol + "U"))
					//	return true;
				}
			}
		}
	}
	return false;
}

bool solver::gameWin(int i, int j, vector<vector<int> >& map1b) {
	for (int i = 0; i < 17; i++) {
		for (int j = 0; j < 17; j++) {
			if (map1b[i][j] == 3 && map1a[i][j] != TARGET)
				return false;
		}
	}
	return true;
}

/* DFS
bool getSolution(vector<vector<int>> map, int playerX, int playerY, string sol) {
if (gameWin(0, 0, map)) {
finalSol = sol;
return true;
}
else
{
pair<vector<vector<int> >, pair<int, int>> cur;
cur.first = map;
cur.second.first = playerX;
cur.second.second = playerY;
if (visited[cur])
return false;
visited[cur] = true;
if (playerX < 16) {
if (map1a[playerY][playerX + 1] != WALL) //Right
{
if (map[playerY][playerX + 1] == BOX)
{
if (playerX < 15) {
if (map1a[playerY][playerX + 2] != WALL && (map[playerY][playerX + 2] != BOX))
{
swap(map[playerY][playerX + 1], map[playerY][playerX + 2]);
if (getSolution(map, playerX + 1, playerY, sol + "R"))
return true;
swap(map[playerY][playerX + 1], map[playerY][playerX + 2]);
}
}
}
else
{
if (getSolution(map, playerX + 1, playerY, sol + "R"))
return true;
}
}
}
if (playerX > 0) {
if (map1a[playerY][playerX - 1] != WALL) //Left
{
if (map[playerY][playerX > 1] == BOX)
{
if (playerX > 1) {
if (map1a[playerY][playerX - 2] != WALL && (map[playerY][playerX - 2] != BOX))
{
swap(map[playerY][playerX - 1], map[playerY][playerX - 2]);
if (getSolution(map, playerX - 1, playerY, sol + "L"))
return true;
swap(map[playerY][playerX - 1], map[playerY][playerX - 2]);
}
}
}
else
{
if (getSolution(map, playerX - 1, playerY, sol + "L"))
return true;
}
}
}

if (playerY < 16) {
if (map1a[playerY + 1][playerX] != WALL)
{
if (map[playerY + 1][playerX] == BOX)
{
if (playerY < 15) {
if (map1a[playerY + 2][playerX] != WALL && (map[playerY + 1][playerX] != BOX))
{
swap(map[playerY + 1][playerX], map[playerY + 2][playerX]);
if (getSolution(map, playerX, playerY + 1, sol + "D"))
return true;
swap(map[playerY + 1][playerX], map[playerY + 2][playerX]);
}
}
}
else
{
if (getSolution(map, playerX, playerY + 1, sol + "D"))
return true;
}
}
}
if (playerY > 0) {
if (map1a[playerY - 1][playerX] != WALL) //Up
{
if (map[playerY - 1][playerX] == BOX)
{
if (playerY > 1) {
if (map1a[playerY - 2][playerX] != WALL && (map[playerY - 2][playerX] != BOX))
{
swap(map[playerY - 1][playerX], map[playerY - 2][playerX]);
if (getSolution(map, playerX, playerY - 1, sol + "U"))
return true;
swap(map[playerY - 1][playerX], map[playerY - 2][playerX]);
}
}
}
else
{
if (getSolution(map, playerX, playerY - 1, sol + "U"))
return true;
}
}
}

}
return false;
}*/

