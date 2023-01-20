#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;



Mat img, imghsv, mask;

int Hmin = 57, Smin = 137, Vmin = 0;
int Hmax = 99, Smax = 255, Vmax = 230;


int main() {

	string path = "Task_resources/Color_image_detection.jpg";
    img = imread(path);
	cvtColor(img, imghsv, COLOR_BGR2HSV);

	/*namedWindow("Trackbar", (640, 200));

	createTrackbar("H Min", "Trackbar", &Hmin, 179);
	createTrackbar("H Max", "Trackbar", &Hmax, 179); 
	createTrackbar("S Min", "Trackbar", &Smin, 255);
	createTrackbar("S Max", "Trackbar", &Smax, 255);
	createTrackbar("V Min", "Trackbar", &Vmin, 255);
	createTrackbar("V Max", "Trackbar", &Vmax, 255);*/



		Scalar lower(Hmin, Smin, Vmin);
		Scalar upper(Hmax, Smax, Vmax);

		inRange(imghsv, lower, upper, mask);

		imshow("Test_image", img);
		imshow("HSV_image", imghsv);
		imshow("mask_image", mask);

		waitKey(0);

	
	return 0;

}