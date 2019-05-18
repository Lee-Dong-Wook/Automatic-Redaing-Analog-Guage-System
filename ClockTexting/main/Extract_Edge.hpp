#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

void Extract_Edge(Mat img, Mat& gray, Mat& th_img, Mat& morph) {

	Mat kernel(5, 25, CV_8UC1, Scalar(1));			//���� ���� ����ũ(��ȣ�� ���� �����ϰ� 5�� ,25���� ��ķ� �����ߴ�)

	cvtColor(img, gray, COLOR_BGR2GRAY);			//��ϵ� ���� ��ȭ 
	blur(gray, gray, Size(5, 5));					//��谡 �ƴ� �κ��� �����ϱ� ���ؼ� ���� ���� 
	Sobel(gray, gray, CV_8U, 1, 0, 3);				//�Һ� ���� ���� 

	threshold(gray, th_img, 120, 255, THRESH_BINARY);	//����ȭ ����, ���� ������ �����ϰ� 25x5ũ�� ����ũ�� �����. ���η� �� �������ϳ��� ���� ����.  
	morphologyEx(th_img, morph, MORPH_CLOSE, kernel);	//���� ���� ���� 

	imshow(" Original image ", img);
	imshow(" Threshold ", th_img);
	imshow("Dilation image ", morph);

	waitKey(0);

}
