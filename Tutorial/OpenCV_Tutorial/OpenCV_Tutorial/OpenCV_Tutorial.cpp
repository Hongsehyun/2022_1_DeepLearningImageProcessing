/*------------------------------------------------------/
* Image Proccessing with Deep Learning
* OpenCV Tutorial: Matrix Operation
* Created: 2021-Spring
------------------------------------------------------*/
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
	/*  Create or Construct Mat  */
	Mat A(10, 10, CV_8UC3, Scalar::all(155));			// 0~255사이에 해당하는 가중치 값에 따라 회색조가 결정됨. 여기서는 155를 입력한 것 
	Mat B(A.size(), CV_8UC1);
	Mat C = Mat::zeros(A.size(), CV_8UC1);
	Mat D = Mat::ones(A.size(), CV_32FC1);

	cout << "MAT A: " << A << endl << endl;
	cout << "MAT B: " << B << endl << endl;
	cout << "MAT C: " << C << endl << endl;
	cout << "MAT D: " << D << endl << endl;


	/*  Get size of A (rows, cols)  */
	cout << "Size of A:  " << A.size() << endl;
	cout << "# of Rows of A:  " << A.rows << endl;
	cout << "# of Cols of A:  " << A.cols << endl;
	cout << "# of Channel of A:  " << A.channels() << endl;


	/*  Copy/Clone Mat A to E/F  */
	Mat E, F;
	A.copyTo(E);				// A를 E에다 Copy한다.		복사본을 만들기 위해서는 copyTo나 clone함수를 사용해야 한다.
	F = A.clone();				// E = A 이런식으로 하면, 주소가 공유되게 되면서 A에도 영향을 주게 된다.


	///*  Convert channel  */
	Mat img = imread("testImage.jpg");	// CV8UC3 Image
	Mat img_gray;
	cvtColor(img, img_gray, CV_BGR2GRAY);

	///*  Chnage image type (8UC1 32FC1)  */
	Mat img_32F;
	img_gray.convertTo(img_32F, CV_32FC1);
	imshow("img_32F", img_32F);

	cout << "img_32F: " << img_32F.channels() << endl << endl;

	waitKey(0);
}



/*
// SourceCode : 영상 출력하기
int main()
{
	//open the video camera no.0
	VideoCapture cap(0);
	if (!cap.isOpened()) // if not success, exit the programm
	{
		cout << "Cannot open the video cam\n";
		return -1;
	}

	namedWindow("MyVideo", CV_WINDOW_AUTOSIZE);				// 창 크기 조절
	while (1)												// 영상 처리 이므로 반복문 속에서 작업 진행
	{
		Mat frame;
		//read a new frame from video 
		bool bSuccess = cap.read(frame);
		if (!bSuccess) // if not success, break loop
		{
			cout << "Cannot find a frame from video stream\n";
			break;
		}
		imshow("MyVideo", frame);
		if (waitKey(10) == 27)    // wait for 'ESC' press for 30ms. If 'ESC' is pressed, break loop  [30ms간격으로 이미지를 바꿔가며 출력하도록 한다.]
		{					      // '27'이라는 숫자는 ASCII Code 값으로, 'ESC'에 해당한다.
			cout << "ESC key is pressed by user\n";
			break;
		}
	}
}
*/



/*
// SourceCode : Gray-Scale로 이미지 출력하기
int main() {

	// read image 
	String filename1 = "testImage.jpg";
	Mat img = imread(filename1);					// 받은 파일 원본 그대로 읽어오기
	Mat img_gray = imread("testImage.jpg", 0);		// 받은 파일은 Gray-Scale로 읽어오기

	// write image 
	String filename2 = "writeTest.jpg";
	imwrite(filename2, img);						// 파일 저장

	// display image 
	namedWindow("image", CV_WINDOW_AUTOSIZE);
	imshow("image", img);							// 컬러 출력

	namedWindow("image_gray", CV_WINDOW_AUTOSIZE);
	imshow("image_gray", img_gray);					// 흑백 출력

	waitKey(0);
}
*/



/*
// SourceCode : 상하반전 이미지 출력하기
int main()
{

	Mat img = imread("testImage.jpg");
	Mat flipedImg;
	flip(img, flipedImg, 0);  // 이미지 출력, 0 = 상하반전


	imshow("image", img);
	imshow("flipedImg", flipedImg);
	waitKey(0);
}
*/