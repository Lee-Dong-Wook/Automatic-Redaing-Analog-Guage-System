
// ������Ʈ ��       : ClockTexting
// ������Ʈ ����     : openCV�� �̿��Ͽ� �Ƴ��α� �ð��� �̹����� ó���Ͽ� �ð������� ����
// ��ũ��Ʈ ��       : main.cpp
// ��ũ��Ʈ ���     : main �Լ�, ������ ����� �����ϴ� �κ� 
// openCV ����      : 4.0.1 
// �ۼ� ���� �Ͻ�    : 2019. 05. 18. 
// ������ ���� �Ͻ�  : 2019. 05. 18.
// �ۼ��� �� ������  : �̵��� 
// e-mail			: dongwookRaynor@gmail.com 
// github ��ũ		: https://github.com/Lee-Dong-Wook/ClockTexting 


#include <opencv2/opencv.hpp>
#include "Extract_Edge.hpp"
#include "ImagePreprocessing.hpp"
#include <iostream>

using namespace std;
using namespace cv;


Mat img_arr[3];															//���� �̹��� ��� 	

int main() {

	cout << "========== �̹��� ��ȣ ���� ========== " << endl << endl;

	for (int i = 1; i <= 3; i++) {					    //Mat ��� �� ���� �� ��ŭ ��ȸ  

		string img_number = format("%d.jpg", i);

		img_arr[i]		  = imread(img_number, 1);
		CV_Assert(img_arr[i].data);										//�̹��� ����ó�� 
	}

	Mat input(200, 200, CV_8U, Scalar(255));
	imshow("Ű���� �̺�Ʈ", input);

	int index_num = 0;

	while (1) {															//����Ű ���� 

		int key = waitKeyEx(0);

		if (key == 27) {												//ESC �Է� 

			cout << "���α׷��� �����մϴ�. " << endl; break;
		}

		switch (key) {													//ȭ��ǥ�� �Է¹޾� Mat�迭�� �ִ� �̹��� ������ �ε� 

		case 0x260000:													//���� ����Ű 
			if ((index_num < 4) && (index_num > 1)) {

				index_num--;
			}

			cout << " ���� ȭ��ǥ Ű �Է� " << endl;
			cout << "up index ��ȣ : " << index_num << endl << endl;

			ShowImage(img_arr[index_num]);
			break;

		case 0x280000:													//�Ʒ��� ����Ű 
			if ((index_num >= 0) && (index_num < 3)) {

				index_num++;
			}

			cout << " �Ʒ��� ȭ��ǥ Ű �Է� " << endl;
			cout << "down index ��ȣ : " << index_num << endl << endl;

			ShowImage(img_arr[index_num]);
			break;
		}
	}//while()

	waitKey();
	return 0;
}//main()





