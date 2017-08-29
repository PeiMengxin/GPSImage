#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <windows.h>
#include <io.h>
#include <direct.h>
#include <iomanip>
#include <opencv2/opencv.hpp>
#include "DataStruct.h"

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	if (argc<3)
	{
		cout << "Usage: GPSImage.exe [videoNum] [n step frames]" << endl;
		cout << "Demo: GPSImage.exe 2 5" << endl;
		cout << "Press Space to start write images, press ESC to exit" << endl;
		return -1;
	}
	string num_str(argv[1]);

	_mkdir(num_str.c_str());

	stringstream ss;
	string image_name;

	int step = 5;

	if (argc == 3)
	{
		ss << argv[2];
		ss >> step;
	}

	string video_name(num_str+".avi");
	string gps_file_name(num_str+".txt");
	string gps_out_file_name(num_str+"/gps_" + num_str +"_"+ ss.str()+".txt");

	ifstream in_file;
	in_file.open(gps_file_name);
	if (!in_file.is_open())
	{
		cout << "gps file read failed";
		return -1;
	}

	ofstream out_file;
	out_file.open(gps_out_file_name);
	if (!out_file.is_open())
	{
		cout << "gps file write failed";
		return -1;
	}

	VideoCapture cap;
	cap.open(video_name);
	if (!cap.isOpened())
	{
		cout << "video open failed";
		return -1;
	}

	cv::Mat img;
	GPS gps_data;

	int frames = cap.get(CV_CAP_PROP_FRAME_COUNT);
	int frame = 0;

	out_file << setprecision(15);
	cout << setprecision(15) << endl;
	bool b_write = false;
	while (frame<frames)
	{
		cap >> img;
		in_file >> gps_data;

		if (b_write&&frame%step==0)
		{
			ss.clear();
			ss << num_str+"/GS_" << step << "_" << frame << ".jpg";
			ss >> image_name;
			imwrite(image_name, img); ss.clear();
			ss << "GS_" << step << "_" << frame << ".jpg";
			ss >> image_name;
			out_file << image_name << " " << gps_data << endl;
			cout << image_name << " " << gps_data << endl;
		}

		frame++;
		imshow(video_name, img);
		char c = waitKey(5);
		if (c==32)
		{
			b_write = true;
		}
		if (c==27)
		{
			break;
		}
	}
	
	in_file.close();
	out_file.close();

	return 0;
}