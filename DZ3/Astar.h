#pragma once
#include<SFML/Window.hpp>
#include<iostream>
#include<set>

using namespace std;
using namespace sf;

//--------Astar--------
typedef pair<int, int> Pair;
typedef pair<float, pair<int, int>> Ppair;
bool closedList[num][num];
vector<Pair> pathA;
struct cell {
	int parent_x, parent_y;
	float f, g, h;
	cell() : f(FLT_MAX), g(FLT_MAX), h(FLT_MAX), parent_x(-1), parent_y(-1) {};
};
bool isDestination(int row, int col, Pair dest) {
	if (row == dest.first && col == dest.second)
		return true;
	else
		return false;
}
float calculateHvalue(int row, int col, Pair dest) {
	int dx = abs(dest.first - row);
	int dy = abs(dest.second - col);
	return abs(dx - dy) + sqrt(2)*min(dx, dy);       //Diagonal D=1,D2=sqrt(2)
}
void tracePath(Pair source, Pair dest, cell cellDetails[][num]) {
	int i = cellDetails[dest.first][dest.second].parent_x, j = cellDetails[dest.first][dest.second].parent_y;
	while (!(i == source.first && j == source.second)) {
		sf::sleep(milliseconds(10));        //delay shortest path
		cout << i << "," << j << " to -> \n";
		pathA.push_back(make_pair(i, j));
		//pathSum=pathSum+cellDetails[i][j].g;
		int temp_i = i;
		int temp_j = j;
		i = cellDetails[temp_i][temp_j].parent_x;     //Solved substitution bug
		j = cellDetails[temp_i][temp_j].parent_y;
	}
	cout << "\nLength of A* path(g) is: " << cellDetails[dest.first][dest.second].g << endl;
}
void Astar(Pair source, Pair dest, int grid[][num]) {
	set<Ppair> openList;
	cell cellDetails[num][num];
	int i = source.first, j = source.second;
	cellDetails[i][j].f = 0.0;
	cellDetails[i][j].g = 0.0;
	cellDetails[i][j].h = 0.0;
	cellDetails[i][j].parent_x = i;
	cellDetails[i][j].parent_y = j;
	openList.insert(make_pair(0.0, make_pair(i, j)));
	bool destFound = false;
	while (!openList.empty()) {
		Ppair p = *openList.begin();
		openList.erase(openList.begin());
		int i = p.second.first, j = p.second.second;
		closedList[i][j] = true;
		sf::sleep(milliseconds(1));        //delay exploration
		if (isDestination(i, j, dest) == true) {
			cout << "Destination Found\n";
			destFound = true;
			break;      //out of while loop
		}
		// North:i-1,j
		if (grid[i - 1][j] == 1 && closedList[i - 1][j] == false) {
			cell successor;
			successor.g = cellDetails[i][j].g + 1.0;
			successor.h = calculateHvalue(i - 1, j, dest);
			successor.f = successor.g + successor.h;
			successor.parent_x = i;
			successor.parent_y = j;
			if (cellDetails[i - 1][j].g>successor.g) {        //Not in openList or bigger 'g' in openList
				cellDetails[i - 1][j] = successor;
				openList.insert(make_pair(successor.f, make_pair(i - 1, j)));
			}
		}
		// East:i,j+1
		if (grid[i][j + 1] == 1 && closedList[i][j + 1] == false) {
			cell successor;
			successor.g = cellDetails[i][j].g + 1.0;
			successor.h = calculateHvalue(i, j + 1, dest);
			successor.f = successor.g + successor.h;
			successor.parent_x = i;
			successor.parent_y = j;
			if (cellDetails[i][j + 1].g>successor.g) {        //Not in openList or bigger 'g' in openList
				cellDetails[i][j + 1] = successor;
				openList.insert(make_pair(successor.f, make_pair(i, j + 1)));
			}
		}
		// South:i+1,j
		if (grid[i + 1][j] == 1 && closedList[i + 1][j] == false) {
			cell successor;
			successor.g = cellDetails[i][j].g + 1.0;
			successor.h = calculateHvalue(i + 1, j, dest);
			successor.f = successor.g + successor.h;
			successor.parent_x = i;
			successor.parent_y = j;
			if (cellDetails[i + 1][j].g>successor.g) {        //Not in openList or bigger 'g' in openList
				cellDetails[i + 1][j] = successor;
				openList.insert(make_pair(successor.f, make_pair(i + 1, j)));
			}
		}
		// West:i,j-1
		if (grid[i][j - 1] == 1 && closedList[i][j - 1] == false) {
			cell successor;
			successor.g = cellDetails[i][j].g + 1.0;
			successor.h = calculateHvalue(i, j - 1, dest);
			successor.f = successor.g + successor.h;
			successor.parent_x = i;
			successor.parent_y = j;
			if (cellDetails[i][j - 1].g>successor.g) {        //Not in openList or bigger 'g' in openList
				cellDetails[i][j - 1] = successor;
				openList.insert(make_pair(successor.f, make_pair(i, j - 1)));
			}
		}
		// North-East:i-1,j+1
		if (grid[i - 1][j + 1] == 1 && closedList[i - 1][j + 1] == false && !(grid[i - 1][j] == 0 && grid[i][j + 1] == 0)) {      //not simultaneously blocked
			cell successor;
			successor.g = cellDetails[i][j].g + sqrt(2);
			successor.h = calculateHvalue(i - 1, j + 1, dest);
			successor.f = successor.g + successor.h;
			successor.parent_x = i;
			successor.parent_y = j;
			if (cellDetails[i - 1][j + 1].g>successor.g) {        //Not in openList or bigger 'g' in openList
				cellDetails[i - 1][j + 1] = successor;
				openList.insert(make_pair(successor.f, make_pair(i - 1, j + 1)));
			}
		}
		// South-East:i+1,j+1
		if (grid[i + 1][j + 1] == 1 && closedList[i + 1][j + 1] == false && !(grid[i + 1][j] == 0 && grid[i][j + 1] == 0)) {
			cell successor;
			successor.g = cellDetails[i][j].g + sqrt(2);
			successor.h = calculateHvalue(i + 1, j + 1, dest);
			successor.f = successor.g + successor.h;
			successor.parent_x = i;
			successor.parent_y = j;
			if (cellDetails[i + 1][j + 1].g>successor.g) {        //Not in openList or bigger 'g' in openList
				cellDetails[i + 1][j + 1] = successor;
				openList.insert(make_pair(successor.f, make_pair(i + 1, j + 1)));
			}
		}
		// South-West:i+1,j-1
		if (grid[i + 1][j - 1] == 1 && closedList[i + 1][j - 1] == false && !(grid[i + 1][j] == 0 && grid[i][j - 1] == 0)) {
			cell successor;
			successor.g = cellDetails[i][j].g + sqrt(2);
			successor.h = calculateHvalue(i + 1, j - 1, dest);
			successor.f = successor.g + successor.h;
			successor.parent_x = i;
			successor.parent_y = j;
			if (cellDetails[i + 1][j - 1].g>successor.g) {        //Not in openList or bigger 'g' in openList
				cellDetails[i + 1][j - 1] = successor;
				openList.insert(make_pair(successor.f, make_pair(i + 1, j - 1)));
			}
		}
		// North-West:i-1,j-1
		if (grid[i - 1][j - 1] == 1 && closedList[i - 1][j - 1] == false && !(grid[i - 1][j] == 0 && grid[i][j - 1] == 0)) {
			cell successor;
			successor.g = cellDetails[i][j].g + sqrt(2);
			successor.h = calculateHvalue(i - 1, j - 1, dest);
			successor.f = successor.g + successor.h;
			successor.parent_x = i;
			successor.parent_y = j;
			if (cellDetails[i - 1][j - 1].g>successor.g) {        //Not in openList or bigger 'g' in openList
				cellDetails[i - 1][j - 1] = successor;
				openList.insert(make_pair(successor.f, make_pair(i - 1, j - 1)));
			}
		}

	}
	if (destFound == false)
		cout << "Destination cell not found.\n";
	else
		tracePath(source, dest, cellDetails);
}