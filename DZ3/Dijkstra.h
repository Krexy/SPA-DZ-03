#pragma once

#include<SFML/Window.hpp>
#include<iostream>
#include<vector>

using namespace std;
using namespace sf;

//--------dijkstra--------
vector<pair<int, int>> pathD;        //Shortest pathD
bool sptSet[num][num];      //explored cells
void findmin(float dist[num][num], int& min_x, int& min_y) {
	float mini = FLT_MAX;
	for (int i = 0; i<num; i++)
		for (int j = 0; j<num; j++)
			if (sptSet[i][j] == false && dist[i][j]<mini) {
				mini = dist[i][j];
				min_x = i;
				min_y = j;
			}
}
void findpath(pair<int, int> previous[num][num], float dist[num][num], int dest_x, int dest_y, int source_x, int source_y) {
	cout << "\nLength of Dijkstra path is: " << dist[dest_x][dest_y] << endl;
	while (previous[dest_x][dest_y].first != source_x || previous[dest_x][dest_y].second != source_y) {        // both simultaneously equal to source coordinates
		sf::sleep(milliseconds(10));        //delay shortest pathD
		cout << "go to ->\n(" << previous[dest_x][dest_y].first << "," << previous[dest_x][dest_y].second << ") ";
		pathD.push_back(make_pair(previous[dest_x][dest_y].first, previous[dest_x][dest_y].second));
		int save_x = dest_x, save_y = dest_y;
		dest_x = previous[save_x][save_y].first;
		dest_y = previous[save_x][save_y].second;
	}
}
void dijkstra(int source_x, int source_y, int dest_x, int dest_y, int grid[num][num]) {
	pair<int, int> previous[num][num];
	float dist[num][num];
	for (int i = 0; i<num; i++)
		for (int j = 0; j<num; j++)
			dist[i][j] = FLT_MAX;
	dist[source_x][source_y] = 0.0;
	int found = 0;
	for (int i = 0; i<num && found == 0; i++)
		for (int j = 0; j<num && found == 0; j++) {
			int min_x = 0, min_y = 0;
			findmin(dist, min_x, min_y);
			sptSet[min_x][min_y] = true;
			if (sptSet[dest_x][dest_y] == true) {
				found = 1;
				break;
			}
			sf::sleep(milliseconds(1));        //delay exploration
											   //north
			if (grid[min_x - 1][min_y] == 1 && sptSet[min_x - 1][min_y] == false && dist[min_x - 1][min_y]>dist[min_x][min_y] + 1.0) {
				dist[min_x - 1][min_y] = dist[min_x][min_y] + 1.0;
				previous[min_x - 1][min_y] = make_pair(min_x, min_y);
			}
			//south
			if (grid[min_x + 1][min_y] == 1 && sptSet[min_x + 1][min_y] == false && dist[min_x + 1][min_y]>dist[min_x][min_y] + 1.0) {
				dist[min_x + 1][min_y] = dist[min_x][min_y] + 1.0;
				previous[min_x + 1][min_y] = make_pair(min_x, min_y);
			}
			//west
			if (grid[min_x][min_y - 1] == 1 && sptSet[min_x][min_y - 1] == false && dist[min_x][min_y - 1]>dist[min_x][min_y] + 1.0) {
				dist[min_x][min_y - 1] = dist[min_x][min_y] + 1.0;
				previous[min_x][min_y - 1] = make_pair(min_x, min_y);
			}
			//east:i,j+1
			if (grid[min_x][min_y + 1] == 1 && sptSet[min_x][min_y + 1] == false && dist[min_x][min_y + 1]>dist[min_x][min_y] + 1.0) {
				dist[min_x][min_y + 1] = dist[min_x][min_y] + 1.0;
				previous[min_x][min_y + 1] = make_pair(min_x, min_y);
			}
			//north-east:i-1,j+1
			if (grid[min_x - 1][min_y + 1] == 1 && sptSet[min_x - 1][min_y + 1] == false &&
				dist[min_x - 1][min_y + 1]>dist[min_x][min_y] + sqrt(2) && !(grid[min_x - 1][min_y] == 0 && grid[min_x][min_y + 1] == 0)) {
				dist[min_x - 1][min_y + 1] = dist[min_x][min_y] + sqrt(2);
				previous[min_x - 1][min_y + 1] = make_pair(min_x, min_y);
			}
			//south-east:i+1,j+1
			if (grid[min_x + 1][min_y + 1] == 1 && sptSet[min_x + 1][min_y + 1] == false &&
				dist[min_x + 1][min_y + 1]>dist[min_x][min_y] + sqrt(2) && !(grid[min_x + 1][min_y] == 0 && grid[min_x][min_y + 1] == 0)) {
				dist[min_x + 1][min_y + 1] = dist[min_x][min_y] + sqrt(2);
				previous[min_x + 1][min_y + 1] = make_pair(min_x, min_y);
			}
			//south-west:i+1,j-1
			if (grid[min_x + 1][min_y - 1] == 1 && sptSet[min_x + 1][min_y - 1] == false &&
				dist[min_x + 1][min_y - 1]>dist[min_x][min_y] + sqrt(2) && !(grid[min_x + 1][min_y] == 0 && grid[min_x][min_y - 1] == 0)) {
				dist[min_x + 1][min_y - 1] = dist[min_x][min_y] + sqrt(2);
				previous[min_x + 1][min_y - 1] = make_pair(min_x, min_y);
			}
			//north-west:i-1,j-1
			if (grid[min_x - 1][min_y - 1] == 1 && sptSet[min_x - 1][min_y - 1] == false &&
				dist[min_x - 1][min_y - 1]>dist[min_x][min_y] + sqrt(2) && !(grid[min_x - 1][min_y] == 0 && grid[min_x][min_y - 1] == 0)) {
				dist[min_x - 1][min_y - 1] = dist[min_x][min_y] + sqrt(2);
				previous[min_x - 1][min_y - 1] = make_pair(min_x, min_y);
			}
		}
	findpath(previous, dist, dest_x, dest_y, source_x, source_y);
}