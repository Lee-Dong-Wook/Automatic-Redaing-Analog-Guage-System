// 프로젝트 명       : ClockTexting
// 프로젝트 목적     : openCV를 이용하여 아날로그 시계의 이미지를 처리하여 시간정보를 추출
// 스크립트 명       : main.cpp
// 스크립트 기능     : main 함수(구현한 기능을 실행하는 부분, 추출한 시간을 이미지화)  
// openCV 버전      : 4.0.1 
// 작성 시작 일시    : 2019. 05. 18. 
// 마지막 수정 일시  : 2019. 06. 14.
// 작성자 및 수정자  : 이동욱 
// e-mail			: dongwookRaynor@gmail.com 
// github 링크		: https://github.com/Lee-Dong-Wook/ClockTexting 

#include <opencv2/opencv.hpp>
#include "ImagePreprocessing.hpp"
#include "ExtractTime.hpp"

using namespace std;
using namespace cv;

Mat _original_Image;								//원본 입력 이미지
Mat _mask_Image;									//마스킹 출력 이미지
Mat _contour_image;									//외곽선추출 출력 이미지 
Mat _line_Image;									//선 추출 출력 이미지 
Mat _result(350,650,CV_8UC3,Scalar(0,0,0));			//결과 출력 이미지 
int _HOURS	 = 0;									//시
int _MINUTES = 0;									//분

int main() {

	
	_original_Image = imread("2.jpg", IMREAD_COLOR);
	CV_Assert(_original_Image.data);

	ExtractCircleLine(_original_Image, _mask_Image);						//원 추출 및 마스킹 

	ContourRect(_mask_Image, _contour_image);								//외곽선 추출 및 사각형 영역지정 후 이미지 축소  

	Extract_Hands(_contour_image, _line_Image, 3, _HOURS, _MINUTES);		//시계 바늘 추출 후 선으로 표시
																			//선의 끝점과 원점을 역탄젠트 함수를 이용해 각도를 계산 후 시간 리턴  

	string time = to_string(_HOURS) + " : " + to_string(_MINUTES);			//리턴한 시간 텍스트 화 

	Point  textPoint;														//시간을 출력할 위치 									
		   textPoint.x = _result.cols / 7;
 	       textPoint.y = _result.rows / 2;

	putText(_result, time, textPoint, FONT_HERSHEY_DUPLEX, 5, Scalar(255,255,255));

	imshow("result", _result);
	waitKey();
	return 0;

}//main()





