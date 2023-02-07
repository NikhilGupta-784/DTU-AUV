#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>


using namespace std;
using namespace cv;


Mat img, imgGray, imgBlur, imgcan, imgdil;


void getcontours(Mat imgDil, Mat Img) {

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;


	//finding countours using teh inbuild function 
	findContours(imgdil,contours,hierarchy,RETR_EXTERNAL,CHAIN_APPROX_SIMPLE);


	vector<vector<Point>> Conpoly(contours.size());
	vector<Rect> bound(contours.size());
	
	
	//applying condition to get the area of each individual shapes 
	for (int i = 0; i < contours.size(); i++)
	{
		int area = contourArea(contours[i]);
		cout << area << "\n";


		string type;

		drawContours(img, Conpoly, 1, Scalar(0, 255, 255), 2);
		//applying contour to triangle having area above 1000
		if (area > 1000) 
		{
			float peri = arcLength(contours[i], true);
			//approximating number corners needed in each shape
			approxPolyDP(contours[i], Conpoly[i], 0.02 * peri, true);
			
			cout << Conpoly[i].size() << endl;

			int Corner = (int)Conpoly[i].size();

			if (Corner == 3) { 
				if (area == 5082) {
					//drawing contour 
					drawContours(img, Conpoly, i, Scalar(0, 0, 255), 2);
				}
				type = "Triangle\n";
			}
			else if (Corner == 4) { type = "Rectangle\n"; }
			else if (Corner > 4) { type = "Circle\n"; }

			
			bound[i] = boundingRect(Conpoly[i]);
			rectangle(img, bound[i].tl(), bound[i].br(), Scalar(0, 255, 0), 3);
			putText(img, type, {bound[i].x, bound[i].y - 5 }, FONT_HERSHEY_PLAIN, 0.75, Scalar(255, 0, 0), 2);
			
		}

	
	}

}


int main() {

	string path = "Task_resources/Shapes.jpg";
	img = imread(path);

	//converting rgb image to canny image for easy detection of borders

	cvtColor(img, imgGray, COLOR_BGR2GRAY);
	GaussianBlur(imgGray, imgBlur, Size(3, 3), 5, 0);
	Canny(imgBlur, imgcan, 25, 75);

	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	dilate(imgcan, imgdil, kernel);


	//calling the function to get the contours 
	getcontours(imgdil, img);

	imshow("Detected img", img);
	imshow("Image Gray", imgGray);
	imshow("Image blur", imgBlur);
	imshow("Image canny", imgcan);
	imshow("image dil", imgdil);

	waitKey(0);

	return 0;
}