// 프로젝트 명       : ClockTexting
// 프로젝트 목적     : openCV를 이용하여 아날로그 시계의 이미지를 처리하여 시간정보를 추출
// 스크립트 기능     : 이미지 전처리 
// 스크립트 명       : ImagePreprocessing.hpp
//					  1. ExtractCircleLine  : 원 검출 및 마스킹
//					  2. ContourRect		: 검출된 원의 외곽선 추출, 사각형 영역 설정, 영역 이외의 이미지 부분 제거 						
// openCV 버전      : 4.0.1 
// 작성 시작 일시    : 2019. 05. 18. 
// 마지막 수정 일시  : 2019. 06. 14.
// 작성자 및 수정자  : 이동욱 
// e-mail			: dongwookRaynor@gmail.com 
// github 링크		: https://github.com/Lee-Dong-Wook/ClockTexting

#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

void ExtractCircleLine(Mat origianl_img, Mat& mask_img) {
	
	Mat gray_img;																//그레이스케일 전처리 행렬 
	Mat hough_img;																//원 검출 행렬 		
	
	imshow(" 원본 이미지 ", origianl_img);										//원본이미지 출력 

	Size imgSize(280, 280);														 		
	resize(origianl_img, origianl_img, imgSize);								//각기 다른 해상도의 이미지를 특정 해상도 크기로 동일 변경 
	//imshow("resize", origianl_img);
	cvtColor(origianl_img, gray_img, COLOR_BGR2GRAY);							//컬러 이미지를 그레이 스케일 이미지로 변경 
 
	medianBlur(gray_img, hough_img, 5);											//미디언 블러를 사용하여 노이즈 제거 	
	

	vector<Vec3f>  circles;														//원 검출, float형 원소3개를 가지는 vector 변수 
	Point		   maskPoints;													//원의 x, y좌표를 받아오기 위한 좌표 
	int			   maskRadius = 0;													//원의 반지름을 받아오기 위한 값 
	
	//**** 호프변환 원 검출 **** 
	HoughCircles(hough_img, circles, HOUGH_GRADIENT, 1, 85, 50, 100, 0, 0);		//허프 변환                      20,50,35
																				//해상도 280x280에 대한 
																				//1 , 30 , 200, 50, 0, 0 은 280, 280 	
																				//4번째 매개변수는 건들지 x 
	for (size_t i = 0; i < circles.size(); i++) {								//검출된 원의 x, y 좌표, 반지름 추출 

		Point	center(cvRound(circles[i][0]), cvRound(circles[i][1]));			// x, y 좌표 
		int		radius = cvRound(circles[i][2]);								// 반지름
		
				maskPoints = center;											//좌표 저장	
				maskRadius = radius;											//반지름 저장 

		circle(origianl_img, center, radius, Scalar(0, 0, 255), 2, 8, 0);		//원그리기 
	}
	
	//**** 마스킹 작업 **** 																
	Mat mask(origianl_img.size(), CV_8UC1, Scalar(0));							//resizing 된 원본이미지크기의 마스크 
	
	circle(mask, maskPoints, maskRadius, Scalar(255, 255, 255), -1);			//검출된 원 크기 만큼 마스킹 
						
	bitwise_and(gray_img, gray_img, mask_img, mask);							//시간 추출에 컬러는 필요없으므로 	그레이스케일 이미지로 1채널짜리 마스크로 처리							
	
	//imshow("mask",mask);														//마스크	원본											
	//imshow("Hough Circle Transform", origianl_img);								//검출된 원 출력
	//imshow("masking image", mask_img);											//마스킹 된 이미지 
	
}//ExtractCircleLine


void ContourRect(Mat mask_img, Mat& contour_img){	
	
	int thresh = 50;
	Mat gaussian_img;																//가우시안블러 결과
									
	GaussianBlur(mask_img, gaussian_img, Size(5, 5), 2, 2);							//contour외곽선 추출을 위한 전처리
											 
	//imshow("가우시안 블러",gaussian_img);

	Canny(gaussian_img, gaussian_img, thresh, thresh * 2);							//엣지 검출		
																					//50, 100은 threshhold 
	//imshow("엣지검출", gaussian_img);

	//**** contour 가장 큰 외각선 추출 작업 **** 
	vector<vector<Point>> contours;													//검출될 외곽선 점 
	vector<Vec4i>		  hierarchy;
	Mat					  resize_img;												//외곽선 추출, 사각형 영역 지정 행렬 
	Rect				  rect;														//외곽선을 감싸는 사각형 영역 

	findContours(gaussian_img, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);		//원 내부 외곽선 무시, 특정 부분만 추출 
	
	resize_img = Mat::zeros(gaussian_img.size(), CV_8UC1);										//비트연산을 위한 사각형 마스크 	
	
	for (size_t i = 0; i < contours.size(); i++)		 
	{
		//drawContours(resize_img, contours, (int)i, Scalar(0,0,0), 2, LINE_8, hierarchy, 0);	//큰 외곽영역은 검은색으로 보이지 않게 함

		rect = boundingRect(contours[i]);														//외곽선 주위로 사각형 생성 
		
		rectangle(resize_img, rect, Scalar(0), 2);												//사각형이 직선으로 검출되지 않기 위해 검은색으로 지정			
	}

	bitwise_or(gaussian_img, resize_img, resize_img);											//전처리 이미지와 사각형 영역합치기 

	//**** 외곽선만큼 사이즈 축소 ****
	contour_img = resize_img(rect);																//사각형 영역만큼만 이미지 축소 

	//imshow("사각영역", resize_img);
	//imshow("외곽선 추출", contour_img);

}//ContourRect