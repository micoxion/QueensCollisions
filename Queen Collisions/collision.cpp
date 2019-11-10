// Queen Collisions
// Micaiah Soto
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;

struct position {
	position(int newX = 0, int newY = 0) {
		x = newX;
		y = newY;
	}
	int x;
	int y;
};

void main() {
	ifstream fin("collision.in");
	if (fin.is_open()) {
		ofstream fout("collision.out");
		vector<position> queenPositions;
		vector<int> matchedX, matchedY, matchedNESW, matchedNWSE;
		int boardSize, patternCount, k, x, y, s, t, matchY, matchX, matchDiagonal, collisions;

		fin >> boardSize >> patternCount;

		for (int i = 0; i < patternCount; i++) {
			fin >> k >> x >> y >> s >> t;
			if (k == 1) {
				queenPositions.push_back(position(x, y));
			}
			else {
				for (int j = 0; j < k; j++) {
					queenPositions.push_back(position(x + j * s, y + j * t));
				}
			}
		}

		while (boardSize != 0) {
			matchY = 0;
			matchX = 0;
			matchDiagonal = 0;
			matchedX.clear();
			matchedNESW.clear();
			matchedNWSE.clear();
			matchedY.clear();
			for (int i = 0; i < queenPositions.size(); i++) {
				for (int j = i + 1; j < queenPositions.size(); j++) {
					if (queenPositions[i].x == queenPositions[j].x && std::find(matchedX.begin(), matchedX.end(), j) == matchedX.end()) {
						matchX++;
						matchedX.push_back(j);
					}
					else if (queenPositions[i].y == queenPositions[j].y && std::find(matchedY.begin(), matchedY.end(), j) == matchedY.end()) {
						matchY++;
						matchedY.push_back(j);
					}
					
					else if (abs(queenPositions[i].y - queenPositions[j].y) == abs(queenPositions[i].x - queenPositions[j].x) && 
						((queenPositions[i].y - queenPositions[j].y < 0 && queenPositions[i].x - queenPositions[j].x < 0) ||
						(queenPositions[i].y - queenPositions[j].y > 0 && queenPositions[i].x - queenPositions[j].x > 0)) && 
						std::find(matchedNESW.begin(), matchedNESW.end(), j) == matchedNESW.end()) {
						matchDiagonal++;
						matchedNESW.push_back(j);
					}
					else if (abs(queenPositions[i].y - queenPositions[j].y) == abs(queenPositions[i].x - queenPositions[j].x) && 
						((queenPositions[i].y - queenPositions[j].y < 0 && queenPositions[i].x - queenPositions[j].x > 0) ||
						(queenPositions[i].y - queenPositions[j].y > 0 && queenPositions[i].x - queenPositions[j].x < 0)) &&
						std::find(matchedNWSE.begin(), matchedNWSE.end(), j) == matchedNWSE.end()) {
						matchDiagonal++;
						matchedNWSE.push_back(j);
					}
				}
			}
			collisions = matchY + matchX + matchDiagonal;
			

			queenPositions.clear();
			fout << collisions;
			fin >> boardSize >> patternCount;
			if (boardSize != 0) {
				fout << endl;
				for (int i = 0; i < patternCount; i++) {
					fin >> k >> x >> y >> s >> t;
					if (k == 1) {
						queenPositions.push_back(position(x, y));
					}
					else {
						for (int j = 0; j < k; j++) {
							queenPositions.push_back(position(x + j * s, y + j * t));
						}
					}
				}
			}
		}

		fout.close();
		fin.close();
	}
	else {
		cout << "Input file not found." << endl;
	}
}