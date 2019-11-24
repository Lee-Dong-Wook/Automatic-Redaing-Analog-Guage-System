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

const int matSize = 5;								//이미지 개수  
Mat original_Image[matSize];													//원본 이미지 행렬 	
Mat gray_Image[matSize];														//그레이스케일 행렬		
Mat output_Image[matSize];														//결과 이미지 행렬 
double _ANGLE = 0.0f;
int index_num = 0;
Mat save_Ori[matSize];
Mat save_Hands[matSize];
Mat save_Result[matSize];
		

//Mat _original_Image[matSize];								//원본 입력 이미지
//Mat _mask_Image[matSize];									//마스킹 출력 이미지
//Mat _contour_image[matSize];								//외곽선추출 출력 이미지 
//Mat _line_Image[matSize];									//선 추출 출력 이미지 
//Mat _result(350,650,CV_8UC3,Scalar(0,0,0));		//결과 출력 이미지 
//int _HOURS	 = 0;								//시
//int _MINUTES = 0;									//분


int main() {
	
	
	cout << endl << endl; 
	cout << "조작키 : 키보드 방향키 ▲, 키보드 방향키 ▼, ESC : 종료" << endl << endl;

	for (int i = 1; i <= matSize; i++) {					    //Mat 행렬 내 원소 수 만큼 순회  

		string img_number = format("%d.png", i);				//파일명을 문자열로 받아옴

		original_Image[i] = imread(img_number, IMREAD_COLOR);
		CV_Assert(original_Image[i].data);										//이미지 예외처리 
		save_Ori[i] = original_Image[i];

		ExtractCircleLine(original_Image[i], original_Image[i]);						//원 추출 및 마스킹
		
		ContourRect(original_Image[i], original_Image[i]);								//외곽선 추출 및 사각형 영역지정 후 이미지 축소  

		Extract_Hands(original_Image[i], original_Image[i], 2, _ANGLE);					//선의 끝점과 원점을 역탄젠트 함수를 이용해 각도를 계산 후 시간 리턴
		save_Hands[i] = original_Image[i];

		Mat		result(350, 650, CV_8UC3, Scalar(0, 0, 0));
		Point	textPoint;														//시간을 출력할 위치 	
		string	angle = to_string(_ANGLE);
								
		textPoint.x = result.cols / 150;
		textPoint.y = result.rows / 3;

		putText(result, angle, textPoint, FONT_HERSHEY_DUPLEX, 5, Scalar(255, 255, 255));
		save_Result[i] = result.clone();

	}

	Mat input(200, 200, CV_8U, Scalar(255));

	namedWindow(" 키보드 버튼 조작 ", WINDOW_NORMAL);
	imshow(" 키보드 버튼 조작 ", input);

	

	while (1) {															//방향키 조작 

		int key = waitKeyEx(0);

		if (key == 27) {												//ESC 입력 

			cout << "프로그램을 종료합니다. " << endl; break;
		}

		switch (key) {													//화살표를 입력받아 Mat배열에 있는 이미지 파일을 로드 

		case 0x260000:													//위쪽 방향키 
			if (index_num > 0) {
				index_num--;

				//cout << " 위쪽 화살표 키 입력 " << endl;
				//cout << "up index 번호 : " << index_num << endl << endl;
			}
		

			break;

		case 0x280000:													//아래쪽 방향키 
			
			if (index_num < 6) {
				index_num++;

				//cout << " 아래쪽 화살표 키 입력 " << endl;
				//cout << "down index 번호 : " << index_num << endl << endl;
			}
			else{
				index_num = 0;
			}
				
			break;
		}
		if (index_num >0 && index_num < 6) {
			
			imshow("원본", save_Ori[index_num]);
			imshow("바늘 추출", save_Hands[index_num]);
			imshow("결과", save_Result[index_num]);

		}
		
	}//while()

	waitKey();
	return 0;

}//main()





