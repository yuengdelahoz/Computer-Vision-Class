/*
 * Pixel.cpp
 *
 *  Created on: Jan 30, 2015
 *      Author: yuengdelahoz
 */
#include <iostream>

using namespace std;

class Pixel {

public:
	int x, y;
	bool visited;
	Pixel *next;
	int ID;
	int pixValue;
	bool inStack = false;
	//Default Constructor

	Pixel() {
		static int rnd=0;
		ID = rnd++;
		this->visited = false;
		next = NULL;
	}
	// Constructor initializing variable.
	Pixel(int x, int y) {
		static int rnd;
		ID = rnd++;
		this->x = x;
		this->y = y;
		this->visited = false;
		next = NULL;
	}
};

