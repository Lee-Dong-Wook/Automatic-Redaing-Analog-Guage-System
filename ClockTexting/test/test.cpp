
#include <opencv2/opencv.hpp>
#include "ImagePreprocessing.hpp"
#include <iostream>

using namespace std;
using namespace cv;

const int matSize = 5;															//이미지 개수  
const int frontArr = -1;														//배열 끝단 	 
Mat original_Image[matSize];													//원본 이미지 행렬 	
Mat gray_Image[matSize];														//그레이스케일 행렬		
Mat output_Image[matSize];														//결과 이미지 행렬 

int main() {

	cout << "========== 이미지 번호 조작 ========== " << endl << endl;
	cout << "조작키 : 키보드 방향키 ▲, 키보드 방향키 ▼, ESC : 종료" << endl << endl;

	for (int i = 1; i <= matSize; i++) {					    //Mat 행렬 내 원소 수 만큼 순회  

		string img_number = format("%d.png", i);				//파일명을 문자열로 받아옴

		original_Image[i] = imread(img_number, IMREAD_COLOR);
		if (!original_Image[i].data) {
			cout << "이미지 없음" << endl;
		}
		
		//CV_Assert(original_Image[i].data);										//이미지 예외처리 
	}

	Mat input(200, 200, CV_8U, Scalar(255));

	namedWindow(" 키보드 버튼 조작 ", WINDOW_NORMAL);
	imshow(" 키보드 버튼 조작 ", input);

	int index_num = 0;

	while (1) {															//방향키 조작 

		int key = waitKeyEx(0);

		if (key == 27) {												//ESC 입력 

			cout << "프로그램을 종료합니다. " << endl; break;
		}

		switch (key) {													//화살표를 입력받아 Mat배열에 있는 이미지 파일을 로드 

		case 0x260000:													//위쪽 방향키 
				index_num--;
			
			cout << " 위쪽 화살표 키 입력 " << endl;
			cout << "up index 번호 : " << index_num << endl << endl;

			//원본 이미지 	
			imshow("original", original_Image[index_num]);
			break;

		case 0x280000:													//아래쪽 방향키 
			
				index_num++;
			
			cout << " 아래쪽 화살표 키 입력 " << endl;
			cout << "down index 번호 : " << index_num << endl << endl;

			imshow("original", original_Image[index_num]);
			break;
		}
	}//while()

	waitKey();
	return 0;
}//main()






