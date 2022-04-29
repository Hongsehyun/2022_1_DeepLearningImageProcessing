/*------------------------------------------------------/
* Image Proccessing with Deep Learning
* OpenCV : Filter Demo - Video
* Created: 2021-Spring
------------------------------------------------------*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	/**********  open the video camera no.0  **********/
	VideoCapture cap(0);

	if (!cap.isOpened()){	// if not success, exit the programm
		cout << "Cannot open the video cam\n";
		return -1;
	}

	namedWindow("MyVideo", CV_WINDOW_AUTOSIZE);


	/**********  Variable Initialize  **********/
	/**********  Variable Initialize  **********/
	int key = 0;
	int filter_type = 0;
	int kernel_size = 5;

	// Laplacian Variable
	int scale = 1;
	int delta = 0;
	int ddepth = CV_16S;

	// Flip Variable
	bool bFlip = false;

	// Video View Variable
	int view = 1;



	while (1)
	{
		Mat src, dst;

		/**********  read a new frame from video  **********/
		bool bSuccess = cap.read(src);

		if (!bSuccess){ 	// if not success, break loop
			cout << "Cannot find a frame from  video stream\n";
			break;
		}
		
		key = waitKey(30);
		if (key == 27){  // wait for 'ESC' press for 30ms. If 'ESC' is pressed, break loop
			cout << "ESC key is pressed by user\n";
			break;
		}
		else if (key == 'b' || key == 'B'){
			filter_type = 1;	// blur
			view = 0;
		}
		else if (key == 'l' || key == 'L'){
			filter_type = 2;	// Laplacian
			view = 0;
		}
		else if (key == 'm' || key == 'M'){
			filter_type = 3;	// Median Blur
			view = 0;
		}
		else if (key == 'h' || key == 'H'){
			bFlip = !bFlip;  	// Mirroring
		}
		else if (key == 'z' || key == 'Z'){
			view = 1;		    // View Origin Video   // Initialize
			kernel_size = 5;
		}
		else
			src.copyTo(dst);

		// Control Scale
		if (key == 'u' || key == 'U'){
			kernel_size = kernel_size + 2;
		}
		else if (key == 'd' || key == 'D'){
			if (kernel_size == 1) kernel_size = 3;   // Prevent Error
			kernel_size = kernel_size - 2;
		}


		// Flip Screen
		if (bFlip) {
			flip(src, dst, 90);
			flip(src, src, 90);
		}

		// Define Filter Type
		if (filter_type == 1){
			blur(src, dst, cv::Size(kernel_size, kernel_size), cv::Point(-1, -1));
		}
		else if (filter_type == 2){
			Laplacian(src, dst, ddepth, kernel_size, scale, delta, BORDER_DEFAULT);
			src.convertTo(src, CV_16S);
			cv::Mat result_laplcaian = src - dst;
			result_laplcaian.convertTo(result_laplcaian, CV_8U);
			result_laplcaian.copyTo(dst);
		}
		else if (filter_type == 3){
			medianBlur(src, dst, kernel_size);
		}


		// Display
		if (view == 1) {
			imshow("MyVideo", src);
		}
		else
			imshow("MyVideo", dst);
	}
	return 0;
}
