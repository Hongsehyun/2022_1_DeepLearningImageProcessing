//#include "opencv2/video/tracking.hpp"
//#include "opencv2/imgproc/imgproc.hpp"
//#include "opencv2/highgui/highgui.hpp"
//#include <ctype.h>
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

Mat image;
Point origin;
Rect selection;

bool selectObject = false;
bool trackObject = false;
int hmin = 0, hmax = 31, smin = 30, smax = 255, vmin = 0, vmax = 255;

/// On mouse event 
static void onMouse(int event, int x, int y, int, void*);

int main()
{
   bool bFlip = false;

   Mat image_disp, hsv, hue, mask, dst;
   vector<vector<Point> > contours;

   //VideoCapture cap(0);
   VideoCapture cap("C:/Users/sehye/source/repos/DLIP_2022/LAB/LAB(2)_Facial_Temperature_Measurement/IR_DEMO_cut.avi");
   int cam_W = 640;
   int cam_H = 480;

   cap.set(CAP_PROP_FRAME_WIDTH, cam_W);
   cap.set(CAP_PROP_FRAME_HEIGHT, cam_H);     // 카메라의 셋팅 변경

   Mat dst_track = Mat::zeros(cam_H, cam_W, CV_8UC3);

   // TrackBar 설정
   namedWindow("Source", 0);
   setMouseCallback("Source", onMouse, 0);
   createTrackbar("Hmin", "Source", &hmin, 179, 0);
   createTrackbar("Hmax", "Source", &hmax, 179, 0);
   createTrackbar("Smin", "Source", &smin, 255, 0);
   createTrackbar("Smax", "Source", &smax, 255, 0);
   createTrackbar("Vmin", "Source", &vmin, 255, 0);
   createTrackbar("Vmax", "Source", &vmax, 255, 0);


   while (true)
   {
      /**********  read a new frame from video  **********/
      bool bSuccess = cap.read(image);

      if (!bSuccess) {    // if not success, break loop
         cout << "Cannot find a frame from  video stream\n";
         break;
      }

      char c = (char)waitKey(10);
      if (c == 27)
         break;
      else if (c == 'r' || c == 'R')
         dst_track = Mat::zeros(cam_H, cam_W, CV_8UC3);
      else if (c == 'h' || c == 'H') {
         bFlip = !bFlip;     // Mirroring
      }
      // end of for(;;)

      if (bFlip) {
         flip(image, image, 1);
      }

      imshow("Source", image);


      /******** Convert BGR to HSV ********/
      // input mat: image
      // output mat: hsv
      cvtColor(image, hsv, COLOR_BGR2HSV);


      /******** Add Pre-Processing such as filtering etc  ********/
      // YOUR CODE GOES HERE
      // YOUR CODE GOES HERE


      /// set dst as the output of InRange
      inRange(hsv, Scalar(MIN(hmin, hmax), MIN(smin, smax), MIN(vmin, vmax)),
         Scalar(MAX(hmin, hmax), MAX(smin, smax), MAX(vmin, vmax)), dst);   // DST로 출력


      /******** Add Post-Processing such as morphology etc  ********/
      // YOUR CODE GOES HERE
      // YOUR CODE GOES HERE


      namedWindow("InRange", 0);
      imshow("InRange", dst);

      /// once mouse has selected an area bigger than 0
      if (trackObject)
      {
         trackObject = false;               // Terminate the next Analysis loop
         Mat roi_HSV(hsv, selection);          // Set ROI by the selection box      
         Scalar means, stddev;
         meanStdDev(roi_HSV, means, stddev);
         cout << "\n Selected ROI Means= " << means << " \n stddev= " << stddev;

         // Change the value in the trackbar according to Mean and STD //
         hmin = MAX((means[0] - stddev[0]), 0);
         hmax = MIN((means[0] + stddev[0]), 179);
         setTrackbarPos("Hmin", "Source", hmin);
         setTrackbarPos("Hmax", "Source", hmax);

         /******** Repeat for S and V trackbar ********/
         hmin = MAX((means[0] - stddev[0]), 0);
         hmax = MIN((means[0] + stddev[0]), 179);
         setTrackbarPos("Hmin", "Source", hmin);
         setTrackbarPos("Hmax", "Source", hmax);

         smin = MAX((means[1] - stddev[1]), 0);
         smax = MIN((means[1] + stddev[1]), 255);
         setTrackbarPos("smin", "Source", smin);
         setTrackbarPos("smax", "Source", smax);

         vmin = MAX((means[2] - stddev[2]), 0);
         vmax = MIN((means[2] + stddev[2]), 255);
         setTrackbarPos("vmin", "Source", vmin);
         setTrackbarPos("vmax", "Source", vmax);
      }


      if (selectObject && selection.area() > 0)  // Left Mouse is being clicked and dragged
      {
         // Mouse Drag을 화면에 보여주기 위함
         Mat roi_RGB(image_disp, selection);
         bitwise_not(roi_RGB, roi_RGB);
         imshow("Source", image_disp);
      }
      image.copyTo(image_disp);



      ///  Find All Contour   ///
      findContours(dst, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
      
      printf("%d\n", contours.size());
      if (contours.size() > 10)
      {
         /// Find the Contour with the largest area ///
         double maxArea = 0;
         int maxArea_idx = 0;

         for (int i = 0; i < contours.size(); i++)
            if (contourArea(contours[i]) > maxArea) {
               maxArea = contourArea(contours[i]);
               maxArea_idx = i;
            }

        
         /// Draw the Contour in Contour Box on Original Video///
         Rect boxPoint = boundingRect(contours[maxArea_idx]);
         rectangle(image_disp, boxPoint, Scalar(255, 0, 255), 3);
         drawContours(image_disp, contours, maxArea_idx, Scalar(0, 0, 255), 2, 8);
         namedWindow("Contour", 0);
         imshow("Contour", image_disp);
         
         /// Continue Drawing the Contour Box  ///
         rectangle(dst_track, boxPoint, Scalar(255, 0, 255), 3);
         namedWindow("Contour_Track", 0);
         imshow("Contour_Track", dst_track);
         dst_track *= 0.9;
      }

      putText(image_disp, "maxArea:", Point(10, 30), 2, 1, Scalar(0, 0, 255));
      putText(image_disp, to_string(contours.size()), Point(200, 30), 2, 1, Scalar(0, 0, 255));
      putText(image_disp, "Warning!", Point(500, 30), 2, 1, Scalar(0, 0, 255));
      namedWindow("Contour", 0);
      imshow("Contour", image_disp);

   }
   return 0;
}



/// On mouse event 
static void onMouse(int event, int x, int y, int, void*)
{
   if (selectObject)  // for any mouse motion
   {
      selection.x = MIN(x, origin.x);
      selection.y = MIN(y, origin.y);
      selection.width = abs(x - origin.x) + 1;
      selection.height = abs(y - origin.y) + 1;
      selection &= Rect(0, 0, image.cols, image.rows);  /// Bitwise AND  check selectin is within the image coordinate
   }

   switch (event)
   {
   case CV_EVENT_LBUTTONDOWN:
      selectObject = true;
      origin = Point(x, y);
      break;
   case CV_EVENT_LBUTTONUP:
      selectObject = false;
      if (selection.area())
         trackObject = true;
      break;
   }
}
