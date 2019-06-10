#pragma once
// ������Ʈ ��       : ClockTexting
// ������Ʈ ����     : openCV�� �̿��Ͽ� �Ƴ��α� �ð��� �̹����� ó���Ͽ� �ð������� ����
// ��ũ��Ʈ ���     : ��ó�� �� �̹������� �ð�ٴ� ���� �� ������ ����Ͽ� �ð� ����  
// ��ũ��Ʈ ��       : ExtractTime.hpp
//					  1. draw_houghLines : ���� �� ħ�� �̹����� ������ �׸��� �Լ� 	
//					  2. ExtractHands    : �ð� ���뿡�� ��ħ�� ��ħ�� ���� 
// openCV ����      : 4.0.1 
// �ۼ� ���� �Ͻ�    : 2019. 06. 02.
// ������ ���� �Ͻ�  : 2019. 06. 05.
// �ۼ��� �� ������  : �̵��� 
// e-mail			: dongwookRaynor@gmail.com 
// github ��ũ		: https://github.com/Lee-Dong-Wook/ClockTexting

#include <opencv2/opencv.hpp>
#include "ImagePreprocessing.hpp"

using namespace std;
using namespace cv;

void draw_Lines(Mat gray, Mat& bgr, vector<Vec4i> lines, int nline);				//���� ���� 

void Extract_Hands(Mat gray, Mat &bgr, int nline) {

	double rho = 1;																		//�����Ÿ� 	
	double theta = CV_PI / 180;	

	/*Size imgSize(200, 200);
	resize(contour_img, contour_img, imgSize);*/

	cvtColor(gray, bgr, COLOR_GRAY2BGR);												//gray�� ��ó���� �� ���̳ʸ� �̹��� ä�� 1��
																						//bgr�� //gray�� ä���� gray -> BGR
	vector<Vec4i> lines;																// ����� �� 
	HoughLinesP(gray, lines, rho, theta, 50, 50, 10);									//Ȯ���� ȣ�� ��ȯ 

	draw_Lines(gray, bgr, lines, nline);												//���� �� ���� �׸��� 
																						//������ ���ڴ� �׸� �� ���� 

	
}

void draw_Lines(Mat gray, Mat& bgr, vector<Vec4i> lines, int nline) {

	Vec4i li;

	for (size_t i = 0; i < min((int)lines.size(), nline); i++)							//������ ũ��� nline�� ���ؼ� ���� ���� ���� for�� �ݺ� 
	{
		li = lines[i];

		if (i == 2) {
			line(bgr, Point(li[0], li[1]), Point(li[2], li[3]), Scalar(0, 0, 255), 1, LINE_AA);			//��ħ ���� 
		}
		else {
			line(bgr, Point(li[0], li[1]), Point(li[2], li[3]), Scalar(0, 255, 0), 1, LINE_AA);			//��ħ ���� 
		}		
	}
	imshow("��ħ ��ħ ǥ�� ", bgr);
	
}

void calc_Angle() {

}

void calc_Time() {

}


