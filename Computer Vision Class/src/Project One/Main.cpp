#include <cv.h>
#include <highgui.h>
#include <stdlib.h> //rand, srand
#include <time.h>        time
#include <iostream>
#include "Dataset.cpp"
#include "Features.cpp"

using namespace cv;
using namespace std;

/*int main(int argc, char** argv) {
	Mat * orig_ds;
	Mat * noisy_5_ds;
	Mat * noisy_10_ds;
	Mat * noisy_25_ds;
	Mat * noisy_50_ds;
	Dataset db;
	orig_ds = db.CreateDS();
	noisy_5_ds = db.addNoise(orig_ds, 5);
	noisy_10_ds = db.addNoise(orig_ds, 10);
	noisy_25_ds = db.addNoise(orig_ds, 25);
	noisy_50_ds = db.addNoise(orig_ds, 50);
	Mat image;

	Features s;
	int **cm;
	cm = s.dsClassify(noisy_25_ds);
	cout << endl;
	cout << endl;

	double accuracy =0;
	for (int i = 0; i < 14; i++) {
		for (int j = 0; j < 14; j++) {
			if (cm[i][j] == 0)
				cout << "000-";

			else if (cm[i][j] > 0 && cm[i][j] < 10)
				cout << "00" << cm[i][j] << "-";
			else if (cm[i][j] >= 10 &&cm[i][j] <100)
				cout << "0" << cm[i][j] << "-";
			else
				cout << cm[i][j] << "-";
			if (i==j) accuracy = accuracy +cm[i][j];
		}
		cout << endl;
	}

	cout << "System's Accuracy: " << (accuracy/1400)*100 << "%" <<endl;

}*/

