/*------------------------------------------------------/
* Image Proccessing with Deep Learning
* OpenCV Tutorial: Basic Iamge Operation (Crop, Rotate, Resize)
* Created: 2021-Spring
------------------------------------------------------*/
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;


int main()
{
	// read image  
	Mat img_gray = imread("image.jpg", 0);   //graysacle
	Mat img = imread("image.jpg", 1);

	/* Option1 : Accesing using "at<type>(v,u)" */
	// For single channel img
	printf("%d", img_gray.at<uchar>(0, 0));

	// For RGB image
	printf("%d", img.at<Vec3b>(0, 0)[0]);
	printf("%d", img.at<Vec3b>(0, 0)[1]);
	printf("%d", img.at<Vec3b>(0, 0)[2]);

	//img.at<uchar>(10, 10) = 0;   // �� ������ �ε���, �� ������ ���Һ���.. ��ư �̷� ����.. �� ������ vec 3d �� �ؾ� �Ѵ�.
	img.at<Vec3b>(10, 10)[0] = 0;
	


	double avgVal = 0;
	for (int v = 0; v < img_gray.rows; v++) {
		for (int u = 0; u < img_gray.cols; u++) {
			avgVal += img_gray.at<uchar>(v, u);
		}
	}

	printf("\n");
	avgVal = (img_gray.rows + img_gray.cols)/avgVal;
	cout << "average intensity = " << avgVal << endl;
	printf("\n");



	/* Option2 : Accessing Using Pointer */
	// (Gray Image)
	int pixel_temp;
	for (int v = 0; v < img_gray.rows; v++)
	{
		uchar* img_data = img_gray.ptr<uchar>(v);
		for (int u = 0; u < img_gray.cols; u++)
		{
			pixel_temp = img_data[u];
		}
	}

	// (RGB Image)
	int pixel_temp_r, pixel_temp_g, pixel_temp_b;
	int cnt = 0;
	for (int v = 0; v < img.rows; v++)
	{
		uchar* img_data = img.ptr<uchar>(v);
		for (int u = 0; u < img.cols * img.channels(); u = u + 3)
		{
			pixel_temp_r = img_data[u];
			pixel_temp_g = img_data[u + 1];
			pixel_temp_b = img_data[u + 2];

			img_data[u] = 0;
			img_data[u+1] = 100;
			img_data[u+2] = 200;
		}
	}

	/* Option3 : Data Approach*/
	uchar* img_data = (uchar*)img_gray.data;
	int length = img_gray.rows * img_gray.cols * img_gray.channels();

	for (int i = 0; i < length; i++)
		pixel_temp = (int)img_data[i];

	waitKey(0);
}











/*
int main()
{
	//open the video camera no.0
	VideoCapture cap(0);
	if (!cap.isOpened()) // if not success, exit the programm
	{
		cout << "Cannot open the video cam\n";
		return -1;
	}
	
	bool bFlip = false;
	namedWindow("MyVideo", CV_WINDOW_AUTOSIZE);				// â ũ�� ����
	
	while (1)												// ���� ó�� �̹Ƿ� �ݺ��� �ӿ��� �۾� ����
	{
		Mat frame;
		//read a new frame from video
		bool bSuccess = cap.read(frame);
		if (!bSuccess) // if not success, break loop
		{
			cout << "Cannot find a frame from video stream\n";
			break;
		}

		// input key in
		int inKey = waitKey(30);

		// ����
		if (inKey == 27)    // wait for 'ESC' press for 30ms. If 'ESC' is pressed, break loop  [30ms�������� �̹����� �ٲ㰡�� ����ϵ��� �Ѵ�.]
		{					      // '27'�̶�� ���ڴ� ASCII Code ������, 'ESC'�� �ش��Ѵ�.
			cout << "ESC key is pressed by user\n";
			break;
		}

		else if (inKey == 'h' || inKey == 'H')
		{
			bFlip = !bFlip;
		}

		if(bFlip)
			flip(frame, frame, 90);
		
	// Display
	imshow("MyVideo", frame);
	}
}
*/



/*
int main()
{
	//  read image  
	Mat img = imread("testImage.jpg");
	imshow("img", img);

	//  Crop(Region of Interest)  
	Rect r(10, 10, 150, 150);	 // (x, y, width, height)  // (x,y)��ǥ���� �����Ͽ� width, height��ŭ�� ������ �����´�.
	Mat roiImg = img(r);
	imshow("roiImg", roiImg);

	//  Rotate  
	Mat rotImg;
	rotate(img, rotImg, ROTATE_90_CLOCKWISE);
	imshow("rotImg", rotImg);

	//  Resize  
	Mat resizedImg;
	resize(img, resizedImg, Size(1000, 100));
	imshow("resizedImg", resizedImg);

	waitKey(0);
}
*/
