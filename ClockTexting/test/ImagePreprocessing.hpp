// ������Ʈ ��       : ClockTexting
// ������Ʈ ����     : openCV�� �̿��Ͽ� �Ƴ��α� �ð��� �̹����� ó���Ͽ� �ð������� ����
// ��ũ��Ʈ ���     : �̹��� ��ó�� 
// ��ũ��Ʈ ��       : ImagePreprocessing.hpp
//					  1. ExtractCircleLine  : �� ���� �� ����ŷ
//					  2. ContourRect		: ����� ���� �ܰ��� ����, �簢�� ���� ����, ���� �̿��� �̹��� �κ� ���� 						
// openCV ����      : 4.0.1 
// �ۼ� ���� �Ͻ�    : 2019. 05. 18. 
// ������ ���� �Ͻ�  : 2019. 06. 14.
// �ۼ��� �� ������  : �̵��� 
// e-mail			: dongwookRaynor@gmail.com 
// github ��ũ		: https://github.com/Lee-Dong-Wook/ClockTexting

#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

void ExtractCircleLine(Mat origianl_img, Mat& mask_img) {
	
	Mat gray_img;																//�׷��̽����� ��ó�� ��� 
	Mat hough_img;																//�� ���� ��� 		
	
	imshow(" ���� �̹��� ", origianl_img);										//�����̹��� ��� 

	Size imgSize(280, 280);														 		
	resize(origianl_img, origianl_img, imgSize);								//���� �ٸ� �ػ��� �̹����� Ư�� �ػ� ũ��� ���� ���� 
	//imshow("resize", origianl_img);
	cvtColor(origianl_img, gray_img, COLOR_BGR2GRAY);							//�÷� �̹����� �׷��� ������ �̹����� ���� 
 
	medianBlur(gray_img, hough_img, 5);											//�̵�� ���� ����Ͽ� ������ ���� 	
	

	vector<Vec3f>  circles;														//�� ����, float�� ����3���� ������ vector ���� 
	Point		   maskPoints;													//���� x, y��ǥ�� �޾ƿ��� ���� ��ǥ 
	int			   maskRadius = 0;													//���� �������� �޾ƿ��� ���� �� 
	
	//**** ȣ����ȯ �� ���� **** 
	HoughCircles(hough_img, circles, HOUGH_GRADIENT, 1, 85, 50, 100, 0, 0);		//���� ��ȯ                      20,50,35
																				//�ػ� 280x280�� ���� 
																				//1 , 30 , 200, 50, 0, 0 �� 280, 280 	
																				//4��° �Ű������� �ǵ��� x 
	for (size_t i = 0; i < circles.size(); i++) {								//����� ���� x, y ��ǥ, ������ ���� 

		Point	center(cvRound(circles[i][0]), cvRound(circles[i][1]));			// x, y ��ǥ 
		int		radius = cvRound(circles[i][2]);								// ������
		
				maskPoints = center;											//��ǥ ����	
				maskRadius = radius;											//������ ���� 

		circle(origianl_img, center, radius, Scalar(0, 0, 255), 2, 8, 0);		//���׸��� 
	}
	
	//**** ����ŷ �۾� **** 																
	Mat mask(origianl_img.size(), CV_8UC1, Scalar(0));							//resizing �� �����̹���ũ���� ����ũ 
	
	circle(mask, maskPoints, maskRadius, Scalar(255, 255, 255), -1);			//����� �� ũ�� ��ŭ ����ŷ 
						
	bitwise_and(gray_img, gray_img, mask_img, mask);							//�ð� ���⿡ �÷��� �ʿ�����Ƿ� 	�׷��̽����� �̹����� 1ä��¥�� ����ũ�� ó��							
	
	//imshow("mask",mask);														//����ũ	����											
	//imshow("Hough Circle Transform", origianl_img);								//����� �� ���
	//imshow("masking image", mask_img);											//����ŷ �� �̹��� 
	
}//ExtractCircleLine


void ContourRect(Mat mask_img, Mat& contour_img){	
	
	int thresh = 50;
	Mat gaussian_img;																//����þȺ� ���
									
	GaussianBlur(mask_img, gaussian_img, Size(5, 5), 2, 2);							//contour�ܰ��� ������ ���� ��ó��
											 
	//imshow("����þ� ��",gaussian_img);

	Canny(gaussian_img, gaussian_img, thresh, thresh * 2);							//���� ����		
																					//50, 100�� threshhold 
	//imshow("��������", gaussian_img);

	//**** contour ���� ū �ܰ��� ���� �۾� **** 
	vector<vector<Point>> contours;													//����� �ܰ��� �� 
	vector<Vec4i>		  hierarchy;
	Mat					  resize_img;												//�ܰ��� ����, �簢�� ���� ���� ��� 
	Rect				  rect;														//�ܰ����� ���δ� �簢�� ���� 

	findContours(gaussian_img, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);		//�� ���� �ܰ��� ����, Ư�� �κи� ���� 
	
	resize_img = Mat::zeros(gaussian_img.size(), CV_8UC1);										//��Ʈ������ ���� �簢�� ����ũ 	
	
	for (size_t i = 0; i < contours.size(); i++)		 
	{
		//drawContours(resize_img, contours, (int)i, Scalar(0,0,0), 2, LINE_8, hierarchy, 0);	//ū �ܰ������� ���������� ������ �ʰ� ��

		rect = boundingRect(contours[i]);														//�ܰ��� ������ �簢�� ���� 
		
		rectangle(resize_img, rect, Scalar(0), 2);												//�簢���� �������� ������� �ʱ� ���� ���������� ����			
	}

	bitwise_or(gaussian_img, resize_img, resize_img);											//��ó�� �̹����� �簢�� ������ġ�� 

	//**** �ܰ�����ŭ ������ ��� ****
	contour_img = resize_img(rect);																//�簢�� ������ŭ�� �̹��� ��� 

	//imshow("�簢����", resize_img);
	//imshow("�ܰ��� ����", contour_img);

}//ContourRect