
// 프로젝트 명       : ClockTexting
// 프로젝트 목적     : openCV를 이용하여 아날로그 시계의 이미지를 처리하여 시간정보를 추출
// 스크립트 명       : main.cpp
// 스크립트 기능     : main 함수, 구현한 기능을 실행하는 부분 
// openCV 버전      : 4.0.1 
// 작성 시작 일시    : 2019. 05. 18. 
// 마지막 수정 일시  : 2019. 05. 18.
// 작성자 및 수정자  : 이동욱 
// e-mail			: dongwookRaynor@gmail.com 
// github 링크		: https://github.com/Lee-Dong-Wook/ClockTexting 


#include <opencv2/opencv.hpp>
#include "Extract_Edge.hpp"
#include "ImagePreprocessing.hpp"
#include <iostream>

using namespace std;
using namespace cv;


Mat img_arr[3];															//샘플 이미지 행렬 	

int main() {

	cout << "========== 이미지 번호 조작 ========== " << endl << endl;

	for (int i = 1; i <= 3; i++) {					    //Mat 행렬 내 원소 수 만큼 순회  

		string img_number = format("%d.jpg", i);

		img_arr[i]		  = imread(img_number, 1);
		CV_Assert(img_arr[i].data);										//이미지 예외처리 
	}

	Mat input(200, 200, CV_8U, Scalar(255));
	imshow("키보드 이벤트", input);

	int index_num = 0;

	while (1) {															//방향키 조작 

		int key = waitKeyEx(0);

		if (key == 27) {												//ESC 입력 

			cout << "프로그램을 종료합니다. " << endl; break;
		}

		switch (key) {													//화살표를 입력받아 Mat배열에 있는 이미지 파일을 로드 

		case 0x260000:													//위쪽 방향키 
			if ((index_num < 4) && (index_num > 1)) {

				index_num--;
			}

			cout << " 위쪽 화살표 키 입력 " << endl;
			cout << "up index 번호 : " << index_num << endl << endl;

			ShowImage(img_arr[index_num]);
			break;

		case 0x280000:													//아래쪽 방향키 
			if ((index_num >= 0) && (index_num < 3)) {

				index_num++;
			}

			cout << " 아래쪽 화살표 키 입력 " << endl;
			cout << "down index 번호 : " << index_num << endl << endl;

			ShowImage(img_arr[index_num]);
			break;
		}
	}//while()

	waitKey();
	return 0;
}//main()





