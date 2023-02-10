#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace cv;

void getcontours(Mat mask, Mat img)
{
	vector<vector<Point>> contours;
	vector<Vec4i> heirarchy;

	findContours(mask, contours, heirarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

	vector<vector<Point>> Conpoly(contours.size());
	vector<Rect> bound(contours.size());

	for (int i = 0; i < contours.size(); i++)
	{
		int area = contourArea(contours[i]);
		float peri = arcLength(contours[i], true);
		cout << area << "\n";
		cout << peri <<"  p \n";

		approxPolyDP(contours[i], Conpoly[i], 0.02 * peri, true);
		
		//condition to concentrate on required contour
		if (area > 150)
		{
			
			bound[i] = boundingRect(Conpoly[i]);

			/*cout << Conpoly[i] << "c" << endl;*/

			cout << bound[i].area() << "b" << endl;

		
			drawContours(img, Conpoly, i, Scalar(0, 255, 0), 2);

			// applying bounding rectangle to needed area
			if (area>400) 
			{

				//rectangle(img, bound[i].tl(), bound[i].br(), Scalar(0, 0, 255), 2);
				
				 /*int x1 = bound[0].x;
				 int y1 = bound[0].y;
				 int x2 = bound[2].x + bound[2].width;
				 int y2 = bound[2].y + bound[2].height;
				 cout << x1 << " " << y1 << endl;
				 cout << x2 << " " << y2;*/
				 

				int x1 = (bound[0].x + bound[2].x) / 2;
				rectangle(img, bound[0].tl(), bound[2].br(), Scalar(0, 0, 255), 2);//rectangle 
				int y1 = bound[2].height / 2 + bound[2].y;
				cout << x1 << " " << y1;
				circle(img, { x1,y1 }, 4, Scalar(0, 0, 255), 5); //drawing circle at the center
			}
		

		}
		
		
	}

}



Mat img, imggray,imgblur,imgcan,imgdil,imghsv,mask;

/*int Hmin = 57, Smin = 137, Vmin = 0;
int Hmax = 99, Smax = 255, Vmax = 230;*/


int main()
{
	//loading image 
	String Path = "task_resources/gate_detection.jpeg";

	img = imread(Path);


	//detecting required color
	/*namedWindow("Trackbar", (640, 200));

	createTrackbar("H Min", "Trackbar", &Hmin, 179);
	createTrackbar("H Max", "Trackbar", &Hmax, 179);
	createTrackbar("S Min", "Trackbar", &Smin, 255);
	createTrackbar("S Max", "Trackbar", &Smax, 255);
	createTrackbar("V Min", "Trackbar", &Vmin, 255);
	createTrackbar("V Max", "Trackbar", &Vmax, 255);

	//applying changes of trackbar onto the image

	
	while (true)
	{
	Scalar lower(Hmin, Smin, Vmin);
	Scalar upper(Hmax, Smax, Vmax);

	inRange(imghsv, lower, upper, mask);

	imshow("Test_image", img);
	imshow("HSV_image", imghsv);
	imshow("mask_image", mask);

	waitKey(1);
	}
	*/


	cvtColor(img, imghsv, COLOR_BGR2HSV);

	Scalar lower(0, 89, 36);
	Scalar upper(28, 255, 255);

	inRange(imghsv, lower, upper, mask);
	imshow("Mask_image", mask);


	//calling function to find center of the gate
	getcontours(mask, img);

	imshow("detected_image", img);
	waitKey(0);

	return 0;
}