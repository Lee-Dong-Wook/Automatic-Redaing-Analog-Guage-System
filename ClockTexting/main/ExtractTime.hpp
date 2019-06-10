#pragma once
// 프로젝트 명       : ClockTexting
// 프로젝트 목적     : openCV를 이용하여 아날로그 시계의 이미지를 처리하여 시간정보를 추출
// 스크립트 기능     : 전처리 된 이미지에서 시계바늘 검출 후 각도를 계산하여 시간 추출  
// 스크립트 명       : ExtractTime.hpp
//					  1. draw_houghLines : 검출 된 침을 이미지에 선으로 그리는 함수 	
//					  2. ExtractHands    : 시계 몸통에서 시침과 분침을 추출 
// openCV 버전      : 4.0.1 
// 작성 시작 일시    : 2019. 06. 02.
// 마지막 수정 일시  : 2019. 06. 05.
// 작성자 및 수정자  : 이동욱 
// e-mail			: dongwookRaynor@gmail.com 
// github 링크		: https://github.com/Lee-Dong-Wook/ClockTexting

#include <opencv2/opencv.hpp>
#include "ImagePreprocessing.hpp"

using namespace std;
using namespace cv;

void draw_Lines(Mat gray, Mat& bgr, vector<Vec4i> lines, int nline);				//전방 선언 

void Extract_Hands(Mat gray, Mat &bgr, int nline) {

	double rho = 1;																		//수직거리 	
	double theta = CV_PI / 180;	

	/*Size imgSize(200, 200);
	resize(contour_img, contour_img, imgSize);*/

	cvtColor(gray, bgr, COLOR_GRAY2BGR);												//gray는 전처리가 된 바이너리 이미지 채널 1개
																						//bgr는 //gray의 채널을 gray -> BGR
	vector<Vec4i> lines;																// 검출된 선 
	HoughLinesP(gray, lines, rho, theta, 50, 50, 10);									//확률적 호프 변환 

	draw_Lines(gray, bgr, lines, nline);												//검출 된 선을 그리기 
																						//마지막 인자는 그릴 선 개수 

	
}

void draw_Lines(Mat gray, Mat& bgr, vector<Vec4i> lines, int nline) {

	Vec4i li;

	for (size_t i = 0; i < min((int)lines.size(), nline); i++)							//라인의 크기와 nline을 비교해서 적은 수를 정해 for문 반복 
	{
		li = lines[i];

		if (i == 2) {
			line(bgr, Point(li[0], li[1]), Point(li[2], li[3]), Scalar(0, 0, 255), 1, LINE_AA);			//시침 추출 
		}
		else {
			line(bgr, Point(li[0], li[1]), Point(li[2], li[3]), Scalar(0, 255, 0), 1, LINE_AA);			//분침 추출 
		}		
	}
	imshow("시침 분침 표시 ", bgr);
	
}

void calc_Angle() {

}

void calc_Time() {

}


