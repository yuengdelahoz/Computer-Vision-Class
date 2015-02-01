/*
 * Stack.cpp
 *
 *  Created on: Jan 30, 2015
 *      Author: yuengdelahoz
 */
#include <iostream>
#include "Pixel.cpp"


using namespace std;

	class Stack {
	public:
		Pixel *Head;
		int length;

		Stack(Pixel *Head) {
			this->Head = Head;
			length=1;
		}
		void insert(Pixel *pix) {
			pix->next = Head;
			Head = pix;
			length++;
		}

		Pixel* pop() {
			if (Head==0) return 0;
			Pixel *temp;
			temp = Head;
			Head = temp->next;
			length--;
			return temp;
		}

		bool isEmpty(){
			if (length==0) return true;
			else return false;
		}

		void Print() {
			Pixel * temp = this->Head;
			cout << "\nSTACK MEMBERS" <<endl;
			while (temp!= 0) {
				cout << "Node(" << temp->x << "," << temp->y <<")-->"<<endl;
				temp = temp->next;
				if (temp==0) cout<<"END" <<endl;
			}
		}
	};



	/*Pixel *pix = new Pixel(0, 0);
		Stack s(pix);
		int x, z;
		z = 0;
		while (z == 0) {
			cout << "Option" << endl;

			cin >> x;
			switch (x) {
			case 1: {
				int i = rand() % 100;
				int j = rand() % 100;
				Pixel *px = new Pixel(i, j);
				srand(i * j);
				s.insert(px);
				s.Print();
				break;

			}
			case 2: {
				Pixel *t = s.pop();
				if (t==0){
					cout << "Stack empty" <<endl;
				}else{
					s.Print();
				}
				break;
			}
			case 3: {
				s.Print();
				break;
			}
			case 4: {
				z = 0;
				break;
			}
			}

		}*/
