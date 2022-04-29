/*------------------------------------------------------/
* Image Proccessing with Deep Learning
* OpenCV : Threshold using Trackbar Demo
* Created: 2021-Spring
------------------------------------------------------*/

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;


// Global variables for Threshold
int threshold_value = 0;
int threshold_type = 0;
int morphology_type = 0;
int filter_type = 0;
int kernel_size = 7;

int const max_value = 255;
int const max_type = 4;
int const max_BINARY_value = 255;
int const max_FILTER_type = 4;
int const max_KERNEL_value = 100;

int Bolt_M5 = 0;
int Bolt_M6 = 0;
int Square_Nut_M5 = 0;
int Hexa_Nut_M5 = 0;
int Hexa_Nut_M6 = 0;

int mol_flag = 0;
int mol_cnt = 0;


// Global variables for Morphology
int element_shape = MORPH_RECT;		// MORPH_RECT, MORPH_ELIPSE, MORPH_CROSS
int n = 3;
Mat element = getStructuringElement(element_shape, Size(n, n));

Mat src, src_gray, src_gray_ft, dst, dst_morph;

// Trackbar strings
String window_name = "Threshold & Morphology Demo";
String trackbar_filter = "Filter Type: \n 0: None \n 1: Blur \n 2: MedianBlur \n 3: GaussianBlur \n 4: Laplacian";
String kernel_value = "Kernel Value";
String trackbar_type = "Thresh Type: \n 0: Binary \n 1: Binary Inverted \n 2: Truncate \n 3: To Zero \n 4: To Zero Invertd";
String trackbar_value = "Thresh Value";
String trackbar_morph = "Morph Type 0: None \n 1: erode \n 2: dilate \n 3: close \n 4: open";

// Function headers
void Threshold_Demo(int, void*);
void Morphology_Demo(int, void*);
void contour_Demo(const Mat& _src);
void Filter_Demo(int, void*);
Mat Laplacian_Filter(Mat& _src, int kernel_size);

int main()
{
	// Load an image
	src = imread("C:/Users/sehye/source/repos/Image/testImage/Lab_GrayScale_TestImage.jpg", IMREAD_COLOR);

	// Convert the image to Gray
	cvtColor(src, src_gray, CV_BGR2GRAY);

	// Create a window to display the results
	namedWindow(window_name, WINDOW_NORMAL);
	resizeWindow(window_name, Size(750, 750));

	// Create trackbar to choose type of threshold
	createTrackbar(trackbar_filter, window_name, &filter_type, max_FILTER_type, Filter_Demo);
	createTrackbar(kernel_value, window_name, &kernel_size, max_KERNEL_value, Filter_Demo);
	createTrackbar(trackbar_type, window_name, &threshold_type, max_type, Threshold_Demo);
	createTrackbar(trackbar_value, window_name, &threshold_value, max_value, Threshold_Demo);
	createTrackbar(trackbar_morph, window_name, &morphology_type, max_type, Morphology_Demo);

	// Call the function to initialize
	Filter_Demo(0, 0);
	Threshold_Demo(0, 0);
	Morphology_Demo(0, 0);

	// Wait until user finishes program
	while (true) {
		int c = waitKey(20);
		if (c == 27) break;
		else if (c == 'm' || c == 'M') mol_flag = 1;	// Apply morphology superimposedly
		else if (c == 'r' || c == 'R') mol_flag = 2;	// Reset 
		else if (c == 'f' || c == 'F') mol_flag = 3;	// Fix the Morphology state
	}
}

void Threshold_Demo(int, void*)	// default form of callback function for trackbar
{
	/*
	* 0: Binary
	* 1: Threshold Truncated
	* 2: Threshold to Zero
	* 3: Threshold to Zero Inverted
	*/
	threshold(src_gray_ft, dst, threshold_value, max_BINARY_value, threshold_type);
	imshow(window_name, dst);
}

void Morphology_Demo(int, void*)  // default form of callback function for trackbar
{
	/*
	* 0: None
	* 1: Erode
	* 2: Dilate
	* 3: Close
	* 4: Open
	*/
	switch (morphology_type) {
	case 0: dst.copyTo(dst_morph);	break;
	case 1: erode(dst, dst_morph, element); break;
	case 2: dilate(dst, dst_morph, element); break;
	case 3: morphologyEx(dst, dst_morph, CV_MOP_OPEN, element); break;
	case 4: morphologyEx(dst, dst_morph, CV_MOP_CLOSE, element); break;
	}
	if (mol_flag == 1) {
		dst_morph.copyTo(dst);
		mol_flag = 0;
		mol_cnt++;
		printf("Mol_count: %d\n", mol_cnt);
	}
	else if (mol_flag == 2) {
		src_gray.copyTo(dst);
		mol_flag = 0;
		mol_cnt = 0;
		printf("Mol_count: %d\n", mol_cnt);
	}
	imshow(window_name, dst_morph);
	contour_Demo(dst_morph);
}

void contour_Demo(const Mat& _src) {
	// Example code
	// src: binary image
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	/// Find contours
	findContours(_src, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
	//findContours(_src, contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

	/// Draw all contours excluding holes
	Mat drawing(_src.size(), CV_8U, Scalar(0));
	namedWindow("contour", WINDOW_NORMAL);
	//drawContours(drawing, contours, -1, Scalar(0), CV_FILLED);

	//cout << " Number of coins are =" << contours.size() << endl;

	for (int i = 0; i < contours.size(); i++)
	{
		printf(" * Contour[%d] -  Area OpenCV: %.2f - Length: %.2f \n", i, contourArea(contours[i]), arcLength(contours[i], true));
		drawContours(drawing, contours, i, Scalar(255), CV_FILLED, 8);
		if (arcLength(contours[i], true) > 500) {
			Bolt_M6++;
		}
		else if (arcLength(contours[i], true) > 390) {
			Bolt_M5++;
		}
		if (arcLength(contours[i], true) < 300 && contourArea(contours[i]) > 4000) {
			Hexa_Nut_M6 ++;
		}
		else if (arcLength(contours[i], true) < 300 && contourArea(contours[i]) > 2800) {
			Square_Nut_M5++;
		}
		else if (arcLength(contours[i], true) < 300 && contourArea(contours[i]) > 2000) {
			Hexa_Nut_M5++;
		}
	}
	printf("# of	Bolt	M5 : %d\n", Bolt_M5);
	printf("# of	Bolt	M6 : %d\n", Bolt_M6);
	printf("# of Square Nut M5 : %d\n", Square_Nut_M5);
	printf("# of	Hexa	M5 : %d\n", Hexa_Nut_M5);
	printf("# of	Hexa	M6 : %d\n", Hexa_Nut_M6);
	Bolt_M5 = 0;
	Bolt_M6 = 0;
	Square_Nut_M5 = 0;
	Hexa_Nut_M5 = 0;
	Hexa_Nut_M6 = 0;
	if (mol_flag == 3) {
		drawing.copyTo(dst);
		mol_flag == 0;
	}
	imshow("contour", drawing);
}

void Filter_Demo(int, void*) {
	/*
	* 0: None
	* 1: Blur
	* 2: MedianBlur
	* 3: GaussianBlur
	* 4: Laplacian
	*/
	switch (filter_type) {
	case 0: src_gray.copyTo(src_gray_ft); break;
	case 1: blur(src_gray, src_gray_ft, cv::Size(kernel_size, kernel_size), cv::Point(-1, -1)); break;
	case 2: medianBlur(src_gray, src_gray_ft, kernel_size); break;
	case 3: GaussianBlur(src_gray, src_gray_ft, cv::Size(kernel_size, kernel_size), 0, 0); break;
	case 4: Laplacian_Filter(src_gray, kernel_size); break;
	}
	imshow(window_name, src_gray_ft);
}

Mat Laplacian_Filter(Mat& _src, int kernel_size) {
	int scale = 1;
	int delta = 0;
	int ddepth = CV_16S;

	Laplacian(_src, src_gray_ft, ddepth, kernel_size, scale, delta, cv::BORDER_DEFAULT);
	_src.convertTo(_src, CV_16S);
	src_gray_ft = _src - src_gray_ft;
	src_gray_ft.convertTo(src_gray_ft, CV_8U);

	return src_gray_ft;
}

