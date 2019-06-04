// ������Ʈ ��       : ClockTexting
// ������Ʈ ����     : openCV�� �̿��Ͽ� �Ƴ��α� �ð��� �̹����� ó���Ͽ� �ð������� ����
// ��ũ��Ʈ ���     : �̹��� ��ó�� 
// ��ũ��Ʈ ��       : ImagePreprocessing.hpp
//					  1. HoughCircleLine : �� ���� �� ����ŷ
//					  2. Contour         : ����� ���� �ܰ��� ����, �簢�� ���� ����, ���� �̿��� �̹��� �κ� ���� 						
// openCV ����      : 4.0.1 
// �ۼ� ���� �Ͻ�    : 2019. 05. 18. 
// ������ ���� �Ͻ�  : 2019. 06. 04.
// �ۼ��� �� ������  : �̵��� 
// e-mail			: dongwookRaynor@gmail.com 
// github ��ũ		: https://github.com/Lee-Dong-Wook/ClockTexting

#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

void ExtractCircleLine(Mat origianl_img, Mat& mask_img) {
	
	Mat gray_img;													    //�׷��̽����� ��ó�� ��� 
	Mat hough_img;														//�������� ���� ��� 		
	
	imshow("original image", origianl_img);								//�����̹��� ��� 

	Size imgSize(280, 280);
	resize(origianl_img, origianl_img, imgSize);							//���� �ٸ� �ػ��� �̹����� Ư�� �ػ� ũ��� ���� ���� 

	cvtColor(origianl_img, gray_img, COLOR_BGR2GRAY);						//�÷� �̹����� �׷��� ������ �̹����� ���� 
 
	medianBlur(gray_img, hough_img, 5);										//�̵�� ���� ����Ͽ� ������ ���� 	
	
	vector<Vec3f>  circles;													//�������� ���� float�� ����3���� ������ vector ���� 
	Point		   maskPoints;												//���� x, y��ǥ�� �޾ƿ��� ���� ��ǥ 
	int			   maskRadius;												//���� �������� �޾ƿ��� ���� �� 
	
	//**** ȣ����ȯ �� ���� **** 
	HoughCircles(hough_img, circles, HOUGH_GRADIENT, 1, 30, 200, 50, 0, 0);  //���� ��ȯ  
																			//�ػ� 280x280�� ���� 
																			//1 , 30 , 200, 50, 0, 0 �� 280, 280 	
	
	for (size_t i = 0; i < circles.size(); i++) {							//����� ���� x, y ��ǥ, ������ ���� 

		Point	center(cvRound(circles[i][0]), cvRound(circles[i][1]));		// x, y ��ǥ 
		int		radius = cvRound(circles[i][2]);						    // ������
		
				maskPoints = center;
				maskRadius = radius;

		circle(origianl_img, center, radius, Scalar(0, 0, 255), 2, 8, 0);	//���׸��� - ���� �߱׷����� Ȯ���ϱ� ���� 
	}
	
	//**** ����ŷ �۾� **** 																
	Mat mask(origianl_img.size(), CV_8UC1, Scalar(0));						//resizing �� �����̹���ũ���� ����ũ 
	
	circle(mask, maskPoints, maskRadius, Scalar(255, 255, 255), -1);		//����� �� ũ�� ��ŭ ����ŷ 
							//�������� ������ ���� ���� /double(1.5)

	bitwise_and(gray_img, gray_img, mask_img, mask);						//�ð� ���⿡ �÷��� �ʿ�����Ƿ� 	�׷��̽����� �̹����� 1ä��¥�� ����ũ�� ó��							
	
	imshow("mask",mask);													//����ũ	����											
	imshow("Hough Circle Transform", origianl_img);							//����� �� ���
	imshow("masking image", mask_img);										//����ŷ �� �̹��� 
	
}//ExtractCircleLine


void Contour(Mat mask_img, Mat& contour_img){	
	
	int thresh = 50;
	Matx <uchar, 3, 3> mask;
	
	mask << 0, 1, 0,
			1, 1, 1,
			0, 1, 0;

	Mat median_img, morph_img;

	GaussianBlur(mask_img, median_img, Size(5, 5), 2, 2);
	//medianBlur(mask_img, median_img, 5);										//contour�ܰ��� ������ ���� ��ó�� 
	
	imshow("�̵�� ��",median_img);
	//morphologyEx(mask_img, morph_img, MORPH_GRADIENT, mask);

	//Mat morph_gradient,morph_open; 
	//morph_gradient = median_img + morph_img;

	//imshow("morphological Gradient", morph_gradient);

	/*morphologyEx(morph_gradient, morph_open, MORPH_OPEN, mask);

	imshow("MORPH_OPEN", morph_open);*/

	Canny(median_img, median_img, thresh, thresh * 2);							//100, 150�� threshhold 
	imshow("��������", median_img);


	//**** contour ���� ū �ܰ��� ���� �۾� **** 
	vector<vector<Point>> contours;																//����� �ܰ��� �� 			
	vector<Vec4i>		  hierarchy;
	Mat					  resize_img;															//�ܰ��� ����, �簢�� ���� ���� ��� 
	Rect				  rect;																	//�ܰ����� ���δ� �簢�� ���� 

	findContours(median_img, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);			//�ܰ��� ���� 

	resize_img = Mat::zeros(median_img.size(), CV_8UC1);
	
	for (size_t i = 0; i < contours.size(); i++)		 
	{
		//drawContours(resize_img, contours, (int)i, Scalar(0,0,0), 2, LINE_8, hierarchy, 0);	//ū �ܰ������� ���������� ������ �ʰ� ��

		rect = boundingRect(contours[i]);														//�ܰ��� ������ �簢�� ���� 
		
		rectangle(resize_img, rect, Scalar(0), 2);											//�簢���� �������� ������� �ʱ� ���� ���������� ����			
	}

	bitwise_or(median_img, resize_img, resize_img);

	//**** �ܰ�����ŭ ������ ��� ****
	contour_img = resize_img(rect);

	imshow("�簢����", resize_img);
	imshow("�ܰ��� ����", contour_img);

}//Contour