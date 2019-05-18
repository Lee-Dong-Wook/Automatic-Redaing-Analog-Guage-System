// 프로젝트 명       : ClockTexting
// 프로젝트 목적     : openCV를 이용하여 아날로그 시계의 이미지를 처리하여 시간정보를 추출
// 스크립트 기능     : 이미지 전처리 
// 스크립트 명       : ImagePreprocessing.hpp
// openCV 버전      : 4.0.1 
// 작성 시작 일시    : 2019. 05. 18. 
// 마지막 수정 일시  : 2019. 05. 18.
// 작성자 및 수정자  : 이동욱 
// e-mail			: dongwookRaynor@gmail.com 
// github 링크		: https://github.com/Lee-Dong-Wook/ClockTexting

#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

void ShowImage(Mat img) {

	imshow("original image", img);
}
