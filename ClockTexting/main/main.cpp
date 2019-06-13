// ������Ʈ ��       : ClockTexting
// ������Ʈ ����     : openCV�� �̿��Ͽ� �Ƴ��α� �ð��� �̹����� ó���Ͽ� �ð������� ����
// ��ũ��Ʈ ��       : main.cpp
// ��ũ��Ʈ ���     : main �Լ�(������ ����� �����ϴ� �κ�, ������ �ð��� �̹���ȭ)  
// openCV ����      : 4.0.1 
// �ۼ� ���� �Ͻ�    : 2019. 05. 18. 
// ������ ���� �Ͻ�  : 2019. 06. 14.
// �ۼ��� �� ������  : �̵��� 
// e-mail			: dongwookRaynor@gmail.com 
// github ��ũ		: https://github.com/Lee-Dong-Wook/ClockTexting 

#include <opencv2/opencv.hpp>
#include "ImagePreprocessing.hpp"
#include "ExtractTime.hpp"

using namespace std;
using namespace cv;

Mat _original_Image;								//���� �Է� �̹���
Mat _mask_Image;									//����ŷ ��� �̹���
Mat _contour_image;									//�ܰ������� ��� �̹��� 
Mat _line_Image;									//�� ���� ��� �̹��� 
Mat _result(350,650,CV_8UC3,Scalar(0,0,0));			//��� ��� �̹��� 
int _HOURS	 = 0;									//��
int _MINUTES = 0;									//��

int main() {

	
	_original_Image = imread("2.jpg", IMREAD_COLOR);
	CV_Assert(_original_Image.data);

	ExtractCircleLine(_original_Image, _mask_Image);						//�� ���� �� ����ŷ 

	ContourRect(_mask_Image, _contour_image);								//�ܰ��� ���� �� �簢�� �������� �� �̹��� ���  

	Extract_Hands(_contour_image, _line_Image, 3, _HOURS, _MINUTES);		//�ð� �ٴ� ���� �� ������ ǥ��
																			//���� ������ ������ ��ź��Ʈ �Լ��� �̿��� ������ ��� �� �ð� ����  

	string time = to_string(_HOURS) + " : " + to_string(_MINUTES);			//������ �ð� �ؽ�Ʈ ȭ 

	Point  textPoint;														//�ð��� ����� ��ġ 									
		   textPoint.x = _result.cols / 7;
 	       textPoint.y = _result.rows / 2;

	putText(_result, time, textPoint, FONT_HERSHEY_DUPLEX, 5, Scalar(255,255,255));

	imshow("result", _result);
	waitKey();
	return 0;

}//main()





