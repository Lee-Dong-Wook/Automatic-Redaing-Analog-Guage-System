// ������Ʈ ��       : ClockTexting
// ������Ʈ ����     : openCV�� �̿��Ͽ� �Ƴ��α� �ð��� �̹����� ó���Ͽ� �ð������� ����
// ��ũ��Ʈ ���     : �̹��� ��ó�� 
// ��ũ��Ʈ ��       : ImagePreprocessing.hpp
// openCV ����      : 4.0.1 
// �ۼ� ���� �Ͻ�    : 2019. 05. 18. 
// ������ ���� �Ͻ�  : 2019. 05. 18.
// �ۼ��� �� ������  : �̵��� 
// e-mail			: dongwookRaynor@gmail.com 
// github ��ũ		: https://github.com/Lee-Dong-Wook/ClockTexting

#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

void ShowImage(Mat img) {

	imshow("original image", img);
}
