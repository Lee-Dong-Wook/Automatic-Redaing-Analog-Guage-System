// 프로젝트 명       : ClockTexting
// 프로젝트 목적     : openCV를 이용하여 아날로그 시계의 이미지를 처리하여 시간정보를 추출
// 스크립트 명       : main.cpp
// 스크립트 기능     : main 함수, 구현한 기능을 실행하는 부분 
// openCV 버전      : 4.0.1 
// 작성 시작 일시    : 2019. 05. 18. 
// 마지막 수정 일시  : 2019. 06. 04.
// 작성자 및 수정자  : 이동욱 
// e-mail			: dongwookRaynor@gmail.com 
// github 링크		: https://github.com/Lee-Dong-Wook/ClockTexting 

#include <opencv2/opencv.hpp>
#include "ImagePreprocessing.hpp"
#include "ExtractTime.hpp"

using namespace std;
using namespace cv;

Mat original_Image;								//원본 입력 이미지
Mat mask_Image;									//마스킹 출력 이미지
Mat contour_image;								//외곽선추출 출력 이미지 
Mat line_Image;									//선 추출 출력 이미지 

int main() {

	original_Image = imread("2.jpg", IMREAD_COLOR);
	CV_Assert(original_Image.data);

	ExtractCircleLine(original_Image, mask_Image);			//원 추출 및 마스킹 

	Contour(mask_Image, contour_image);						//외곽선 추출 및 사각형 영역지정 후 이미지 축소  

	Extract_Hands(contour_image, line_Image, 3);				//시계 바늘 추출 후 선으로 표시 

	waitKey();
	return 0;

}//main()





