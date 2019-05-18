#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

void Extract_Edge(Mat img, Mat& gray, Mat& th_img, Mat& morph) {

	Mat kernel(5, 25, CV_8UC1, Scalar(1));			//열림 연산 마스크(번호판 모양과 유사하게 5행 ,25열의 행렬로 구성했다)

	cvtColor(img, gray, COLOR_BGR2GRAY);			//명암도 영상 변화 
	blur(gray, gray, Size(5, 5));					//경계가 아닌 부분을 제거하기 위해서 블러링 수행 
	Sobel(gray, gray, CV_8U, 1, 0, 3);				//소벨 에지 검출 

	threshold(gray, th_img, 120, 255, THRESH_BINARY);	//이진화 수행, 열림 연산을 수행하고 25x5크기 마스크를 사용함. 가로로 긴 영역을하나로 묶는 역할.  
	morphologyEx(th_img, morph, MORPH_CLOSE, kernel);	//열람 연산 수행 

	imshow(" Original image ", img);
	imshow(" Threshold ", th_img);
	imshow("Dilation image ", morph);

	waitKey(0);

}
