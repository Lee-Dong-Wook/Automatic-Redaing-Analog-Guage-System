// ������Ʈ ��       : ClockTexting
// ������Ʈ ����     : openCV�� �̿��Ͽ� �Ƴ��α� �ð��� �̹����� ó���Ͽ� �ð������� ����
// ��ũ��Ʈ ��       : main.cpp
// ��ũ��Ʈ ���     : main �Լ�, ������ ����� �����ϴ� �κ� 
// openCV ����      : 4.0.1 
// �ۼ� ���� �Ͻ�    : 2019. 05. 18. 
// ������ ���� �Ͻ�  : 2019. 06. 04.
// �ۼ��� �� ������  : �̵��� 
// e-mail			: dongwookRaynor@gmail.com 
// github ��ũ		: https://github.com/Lee-Dong-Wook/ClockTexting 

#include <opencv2/opencv.hpp>
#include "ImagePreprocessing.hpp"
#include "ExtractTime.hpp"

using namespace std;
using namespace cv;

Mat original_Image;								//���� �Է� �̹���
Mat mask_Image;									//����ŷ ��� �̹���
Mat contour_image;								//�ܰ������� ��� �̹��� 
Mat line_Image;									//�� ���� ��� �̹��� 

int main() {

	original_Image = imread("2.jpg", IMREAD_COLOR);
	CV_Assert(original_Image.data);

	ExtractCircleLine(original_Image, mask_Image);			//�� ���� �� ����ŷ 

	Contour(mask_Image, contour_image);						//�ܰ��� ���� �� �簢�� �������� �� �̹��� ���  

	Extract_Hands(contour_image, line_Image, 3);				//�ð� �ٴ� ���� �� ������ ǥ�� 

	waitKey();
	return 0;

}//main()





