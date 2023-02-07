#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>
#include <cmath>


using namespace std;
using namespace cv;


Mat img, imghsv, mask;


int main() 
{

	String path = "task_resources/Path_finder.jpg";

	img = imread(path);

	cvtColor(img, imghsv, COLOR_BGR2HSV);
	//applying mask to detect the arrow
	Scalar lower(0, 0, 181);
	Scalar upper(33, 255, 255);


	inRange(imghsv, lower, upper, mask);


	vector < vector<Point>> contour;
	vector < Vec4i > hierarchy;

	//finding all the possible contour to the masked image
	findContours(mask, contour, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);


	vector<vector<Point>> aprpoly;
	for (int i = 0; i < contour.size(); i++) {
		vector<Point> polygon;
		//approximating number of corners in the arrow to get the desired points
		approxPolyDP(contour[i], polygon, 10, true);
		aprpoly.push_back(polygon);
	}
	//drawing the contour to those points 
	drawContours(img, aprpoly, -1, Scalar(0, 255, 255));
	for (int i = 0; i < aprpoly.size(); i++) {

		cout << "contour" << i << " ";
		for (int j = 0; j < aprpoly[0].size(); j++) {

			Point point = aprpoly[0][j];
			cout << point.x << "," << point.y;

			cout << endl;
		}
	}

	Point p1 = aprpoly[0][2];
	Point p2 = aprpoly[0][5];

	//marking out the points needed to find the slope
	circle(img, p1, 5, Scalar(255,0,0), -1);
	circle(img, p2, 5, Scalar(255,0,0), -1);


	

	//finding out the angle 
	float Slope = (float)(p2.y - p1.y) / (p2.x - p1.x);
	double Angle = (atan(Slope)) * 180 / 3.145;
	cout << Angle << "\n";
	putText(img, to_string(Angle), Point(20, 50), FONT_HERSHEY_SCRIPT_SIMPLEX, 0.75, Scalar(255, 255, 255), 2);



	imshow("img", img);
	imshow("mask", mask);
		
	waitKey(0);

	return 0;
}