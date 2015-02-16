/*
 * Gradient.cpp
 *
 *  Created on: Feb 13, 2015
 *      Author: yuengdelahoz
 */
#include <cv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <math.h>       /* sqrt */

using namespace cv;
using namespace std;

class Gradient {
public:
	enum Operator {
		ROBERTS, SOBEL, PREWITT, LOG
	};

	Mat CalculateGradient(Mat img, int op, int T) {
		// Image size
		int width = img.cols;
		int height = img.rows;

		// Values to rescale gradient output
		int min = 0;

		//Output Image range
		int minR = 0;
		int maxR = 255;
		// Starting Border Pixel
		int stPix = 0;
		// Masks
		Mat Gx, Gy, G;

		// Edge Image. Initialize to zero
		Mat dst = Mat::zeros(img.size(), CV_8UC1);
		Mat temp = Mat::zeros(img.size(), CV_16U);


		if (op == ROBERTS) {
			// Masks
			Gx = (Mat_<double>(2, 2) << 1, 0, 0, -1);
			Gy = (Mat_<double>(2, 2) << 0, -1, 1, 0);
			stPix = 0;

		} else if (op == SOBEL) {
			// Masks
			Gx = (Mat_<double>(3, 3) << -1, 0, 1, -2, 0, 2, -1, 0, 1);
			Gy = (Mat_<double>(3, 3) << 1, 2, 1, 0, 0, 0, -1, -2, -1);
			stPix = 1;

		} else if (op == PREWITT) {
			// Masks
			Gx = (Mat_<double>(3, 3) << -1, 0, 1, -1, 0, 1, -1, 0, 1);
			Gy = (Mat_<double>(3, 3) << 1, 1, 1, 0, 0, 0, -1, -1, -1);
			stPix = 1;

		} else if (op == LOG) {
			// Mask
			G =
					(Mat_<double>(5, 5) << 0, 0, -1, 0, 0, 0, -1, -2, -1, 0, -1, -2, 16, -2, -1, 0, -1, -2, -1, 0, 0, 0, -1, 0, 0);

			//G = (Mat_<double>(3, 3) << -1, -1, -1, -1, 8, -1, -1, -1, -1);
			stPix = 2;
		}
		// Convolve Mask with image
		int maxV = 0;
		for (int i = stPix; i < height - stPix; i++) {
			for (int j = stPix; j < width - stPix; j++) {

				double EdgeValue = 0;
				double EdgeValuex = 0;
				double EdgeValuey = 0;

				if (op == LOG) {

					// Convolve Mask with center Pixel's Neighborhood
					for (int k = -2; k <= 2; k++) {
						for (int m = -2; m <= 2; m++) {
							int pix = img.at<uchar>(i + k, j + m) * 1;
							int kernel = G.at<double>(k + 2, m + 2) * 1;
							EdgeValue = EdgeValue + pix * kernel;
						}

					}

					// Magnitude of the gradient
					EdgeValue = abs(EdgeValue);
					if (EdgeValue > maxV)
						maxV = EdgeValue;


					//cout << " Dst Value: "<< dst.at<uchar>(i, j)*1 <<endl;
				} else if (op == ROBERTS) {

					// Convolve Mask with center Pixel's Neighborhood
					for (int k = 0; k <= 1; k++) {
						for (int m = 0; m <= 1; m++) {

							EdgeValuex = img.at<uchar>(i + k, j + m)
									* Gx.at<double>(k, m) + EdgeValuex;

							EdgeValuey = img.at<uchar>(i + k, j + m)
									* Gy.at<double>(k, m) + EdgeValuey;

						}

					}
					// Magnitude of the gradient
					EdgeValue = sqrt(pow(EdgeValuex, 2) + pow(EdgeValuey, 2));

				} else {
					// Convolve Mask with center Pixel's Neighborhood
					for (int k = -1; k <= 1; k++) {
						for (int m = -1; m <= 1; m++) {

							EdgeValuex = img.at<uchar>(i + k, j + m)
									* Gx.at<double>(k + 1, m + 1) + EdgeValuex;

							EdgeValuey = img.at<uchar>(i + k, j + m)
									* Gy.at<double>(k + 1, m + 1) + EdgeValuey;

						}

					}
					// Magnitude of the gradient
					EdgeValue = sqrt(pow(EdgeValuex, 2) + pow(EdgeValuey, 2));

				}
				temp.at<ushort>(i, j) = EdgeValue;
				if (EdgeValue > maxV)
					maxV = EdgeValue;

			}
		}

		for (int i = stPix; i < height - stPix; i++) {
			for (int j = stPix; j < width - stPix; j++) {
				double EdgeValue = temp.at<ushort>(i, j)*1;

				//cout << EdgeValue <<endl;
				// rescaling ranges to -->[0,255]

				EdgeValue = (EdgeValue - min) * (maxR - minR)
						/ ((maxV - min) + minR);
				if (op!=LOG) {
					if (EdgeValue >T)
						dst.at<uchar>(i, j) = 255;
				}
				else
					dst.at<char>(i, j) = EdgeValue;

			}
		}

		return dst;

	}
};
/*// rescaling ranges to -->[0,255]
 EdgeValue = (EdgeValue - min) * (maxR - minR)
 / ((max - min) + minR);*/
