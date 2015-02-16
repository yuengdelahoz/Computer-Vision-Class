#include <highgui.h>
#include <stdlib.h> //rand, srand
#include <iostream>
#include "Gradient.cpp"
#include "Dataset.cpp"

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	Gradient op;
	Dataset db;
	Mat * orig_ds;
	Mat * noisy_5_ds;
	Mat * noisy_10_ds;
	Mat * noisy_25_ds;
	Mat * noisy_50_ds;

	// Create Dataset
	orig_ds = db.CreateDS();

	// addNoise (dataset, sigma)
	noisy_5_ds = db.addNoise(orig_ds, 5);
	noisy_10_ds = db.addNoise(orig_ds, 10);
	noisy_25_ds = db.addNoise(orig_ds, 25);
	noisy_50_ds = db.addNoise(orig_ds, 50);
	string path = "src/Project Two/output_";

	Mat dst1, dst2, dst3, dst4;
	int k = 0;
	//iterate over all of the images in folder input_images
	for (int i = 0; i < 10; i++) {

		// calculateGradient (sourceImage, Operator, Threshold). No noise.
		dst1 = op.CalculateGradient(orig_ds[i], Gradient::ROBERTS, 30);
		dst2 = op.CalculateGradient(orig_ds[i], Gradient::SOBEL, 40);
		dst3 = op.CalculateGradient(orig_ds[i], Gradient::PREWITT, 60);
		dst4 = op.CalculateGradient(orig_ds[i], Gradient::LOG, -1);

		// Save Edge Detector Images
		imwrite(path + "roberts/roberts_img0" + to_string(i) + "_no_noise_.png",
				dst1);
		imwrite(path + "sobel/sobel_img0" + to_string(i) + "_no_noise_.png",
				dst2);
		imwrite(path + "prewitt/prewitt_img0" + to_string(i) + "_no_noise_.png",
				dst3);
		imwrite(path + "log/log_img0" + to_string(i) + "_no_noise_.png", dst4);

		//Images with noise. Sigma = 5.
		// calculateGradient (sourceImage, Operator, Threshold)
		dst1 = op.CalculateGradient(noisy_5_ds[i], Gradient::ROBERTS, 30);
		dst2 = op.CalculateGradient(noisy_5_ds[i], Gradient::SOBEL, 40);
		dst3 = op.CalculateGradient(noisy_5_ds[i], Gradient::PREWITT, 60);
		dst4 = op.CalculateGradient(noisy_5_ds[i], Gradient::LOG, -1);

		// Save Edge Detector Images
		imwrite(path + "roberts/roberts_img0" + to_string(i) + "_noise_5_.png",
				dst1);
		imwrite(path + "sobel/sobel_img0" + to_string(i) + "_noise_5_.png",
				dst2);
		imwrite(path + "prewitt/prewitt_img0" + to_string(i) + "_noise_5_.png",
				dst3);
		imwrite(path + "log/log_img0" + to_string(i) + "_noise_5_.png", dst4);

		//Images with noise. Sigma = 10.
		// calculateGradient (sourceImage, Operator, Threshold)
		dst1 = op.CalculateGradient(noisy_10_ds[i], Gradient::ROBERTS, 30);
		dst2 = op.CalculateGradient(noisy_10_ds[i], Gradient::SOBEL, 40);
		dst3 = op.CalculateGradient(noisy_10_ds[i], Gradient::PREWITT, 60);
		dst4 = op.CalculateGradient(noisy_10_ds[i], Gradient::LOG, -1);

		// Save Edge Detector Images without noise
		imwrite(path + "roberts/roberts_img0" + to_string(i) + "_noise_10_.png",
				dst1);
		imwrite(path + "sobel/sobel_img0" + to_string(i) + "_noise_10_.png",
				dst2);
		imwrite(path + "prewitt/prewitt_img0" + to_string(i) + "_noise_10_.png",
				dst3);
		imwrite(path + "log/log_img0" + to_string(i) + "_noise_10_.png", dst4);

		//Images with noise. Sigma = 25.
		// calculateGradient (sourceImage, Operator, Threshold)
		dst1 = op.CalculateGradient(noisy_25_ds[i], Gradient::ROBERTS, 30);
		dst2 = op.CalculateGradient(noisy_25_ds[i], Gradient::SOBEL, 40);
		dst3 = op.CalculateGradient(noisy_25_ds[i], Gradient::PREWITT, 60);
		dst4 = op.CalculateGradient(noisy_25_ds[i], Gradient::LOG, -1);

		// Save Edge Detector Images
		imwrite(path + "roberts/roberts_img0" + to_string(i) + "_noise_25_.png",
				dst1);
		imwrite(path + "sobel/sobel_img0" + to_string(i) + "_noise_25_.png",
				dst2);
		imwrite(path + "prewitt/prewitt_img0" + to_string(i) + "_noise_25_.png",
				dst3);
		imwrite(path + "log/log_img0" + to_string(i) + "_noise_25_.png", dst4);

		//Images with noise. Sigma = 50.
		// calculateGradient (sourceImage, Operator, Threshold)
		dst1 = op.CalculateGradient(noisy_50_ds[i], Gradient::ROBERTS, 30);
		dst2 = op.CalculateGradient(noisy_50_ds[i], Gradient::SOBEL, 40);
		dst3 = op.CalculateGradient(noisy_50_ds[i], Gradient::PREWITT, 60);
		dst4 = op.CalculateGradient(noisy_50_ds[i], Gradient::LOG, -1);

		// Save Edge Detector Images
		imwrite(path + "roberts/roberts_img0" + to_string(i) + "_noise_50_.png",
				dst1);
		imwrite(path + "sobel/sobel_img0" + to_string(i) + "_noise_50_.png",
				dst2);
		imwrite(path + "prewitt/prewitt_img0" + to_string(i) + "_noise_50_.png",
				dst3);
		imwrite(path + "log/log_img0" + to_string(i) + "_noise_50_.png", dst4);

		Mat tmp1, tmp2, tmp3, tmp4;
		//Smooth Input Images with a gaussian filter. Mask size 5, sigma and mean = 0
		GaussianBlur(noisy_5_ds[i], tmp1, Size(5, 5), 0, 0, BORDER_DEFAULT);
		GaussianBlur(noisy_10_ds[i], tmp2, Size(5, 5), 0, 0, BORDER_DEFAULT);
		GaussianBlur(noisy_25_ds[i], tmp3, Size(5, 5), 0, 0, BORDER_DEFAULT);
		GaussianBlur(noisy_50_ds[i], tmp4, Size(5, 5), 0, 0, BORDER_DEFAULT);

		// Save Edge Detector Images
		imwrite(path + "noise/img0" + to_string(i) + "_noise_05.png", tmp1);
		imwrite(path + "noise/img0" + to_string(i) + "_noise_10.png", tmp2);
		imwrite(path + "noise/img0" + to_string(i) + "_noise_25.png", tmp3);
		imwrite(path + "noise/img0" + to_string(i) + "_noise_50.png", tmp4);

		//Images with noise. Sigma = 5.
		// calculateGradient (sourceImage, Operator, Threshold)
		dst1 = op.CalculateGradient(tmp1, Gradient::ROBERTS, 30);
		dst2 = op.CalculateGradient(tmp1, Gradient::SOBEL, 40);
		dst3 = op.CalculateGradient(tmp1, Gradient::PREWITT, 60);
		dst4 = op.CalculateGradient(tmp1, Gradient::LOG, -1);

		// Save Edge Detector Images
		imwrite(
				path + "roberts/roberts_img0" + to_string(i)
						+ "_smoothed_noise_5_.png", dst1);
		imwrite(
				path + "sobel/sobel_img0" + to_string(i)
						+ "_smoothed_noise_5_.png", dst2);
		imwrite(
				path + "prewitt/prewitt_img0" + to_string(i)
						+ "_smoothed_noise_5_.png", dst3);
		imwrite(path + "log/log_img0" + to_string(i) + "_smoothed_noise_5_.png",
				dst4);

		//Images with noise. Sigma = 10.
		// calculateGradient (sourceImage, Operator, Threshold)
		dst1 = op.CalculateGradient(tmp2, Gradient::ROBERTS, 30);
		dst2 = op.CalculateGradient(tmp2, Gradient::SOBEL, 40);
		dst3 = op.CalculateGradient(tmp2, Gradient::PREWITT, 60);
		dst4 = op.CalculateGradient(tmp2, Gradient::LOG, -1);

		// Save Edge Detector Images without noise
		imwrite(
				path + "roberts/roberts_img0" + to_string(i)
						+ "_smoothed_noise_10_.png", dst1);
		imwrite(
				path + "sobel/sobel_img0" + to_string(i)
						+ "_smoothed_noise_10_.png", dst2);
		imwrite(
				path + "prewitt/prewitt_img0" + to_string(i)
						+ "_smoothed_noise_10_.png", dst3);
		imwrite(
				path + "log/log_img0" + to_string(i)
						+ "_smoothed_noise_10_.png", dst4);

		//Images with noise. Sigma = 25.
		// calculateGradient (sourceImage, Operator, Threshold)
		dst1 = op.CalculateGradient(tmp3, Gradient::ROBERTS, 30);
		dst2 = op.CalculateGradient(tmp3, Gradient::SOBEL, 40);
		dst3 = op.CalculateGradient(tmp3, Gradient::PREWITT, 60);
		dst4 = op.CalculateGradient(tmp3, Gradient::LOG, -1);

		// Save Edge Detector Images
		imwrite(
				path + "roberts/roberts_img0" + to_string(i)
						+ "_smoothed_noise_25_.png", dst1);
		imwrite(
				path + "sobel/sobel_img0" + to_string(i)
						+ "_smoothed_noise_25_.png", dst2);
		imwrite(
				path + "prewitt/prewitt_img0" + to_string(i)
						+ "_smoothed_noise_25_.png", dst3);
		imwrite(
				path + "log/log_img0" + to_string(i)
						+ "_smoothed_noise_25_.png", dst4);

		//Images with noise. Sigma = 50.
		// calculateGradient (sourceImage, Operator, Threshold)
		dst1 = op.CalculateGradient(tmp4, Gradient::ROBERTS, 30);
		dst2 = op.CalculateGradient(tmp4, Gradient::SOBEL, 40);
		dst3 = op.CalculateGradient(tmp4, Gradient::PREWITT, 60);
		dst4 = op.CalculateGradient(tmp4, Gradient::LOG, -1);

		// Save Edge Detector Images
		imwrite(
				path + "roberts/roberts_img0" + to_string(i)
						+ "_smoothed_noise_50_.png", dst1);
		imwrite(
				path + "sobel/sobel_img0" + to_string(i)
						+ "_smoothed_noise_50_.png", dst2);
		imwrite(
				path + "prewitt/prewitt_img0" + to_string(i)
						+ "_smoothed_noise_50_.png", dst3);
		imwrite(
				path + "log/log_img0" + to_string(i)
						+ "_smoothed_noise_50_.png", dst4);
		k++;
	}

	return 0;
}

