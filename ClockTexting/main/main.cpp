// ������Ʈ ��       : ClockTexting
// ������Ʈ ����     : openCV�� �̿��Ͽ� �Ƴ��α� �ð��� �̹����� ó���Ͽ� �ð������� ����
// ��ũ��Ʈ ��       : main.cpp
// ��ũ��Ʈ ���     : main �Լ�(������ ����� �����ϴ� �κ�, ������ �ð��� �̹���ȭ)  
// openCV ����      : 4.0.1 
// �ۼ� ���� �Ͻ�    : 2019. 05. 18. 
// ������ ���� �Ͻ�  : 2019. 06. 14.
// �ۼ��� �� ������  : �̵��� 
// e-mail			: dongwookRaynor@gmail.com 
// github ��ũ		: https://github.com/Lee-Dong-Wook/ClockTexting 

#include <opencv2/opencv.hpp>
#include "ImagePreprocessing.hpp"
#include "ExtractTime.hpp"

using namespace std;
using namespace cv;

const int matSize = 5;								//�̹��� ����  
Mat original_Image[matSize];													//���� �̹��� ��� 	
Mat gray_Image[matSize];														//�׷��̽����� ���		
Mat output_Image[matSize];														//��� �̹��� ��� 
double _ANGLE = 0.0f;
int index_num = 0;
Mat save_Ori[matSize];
Mat save_Hands[matSize];
Mat save_Result[matSize];
		

//Mat _original_Image[matSize];								//���� �Է� �̹���
//Mat _mask_Image[matSize];									//����ŷ ��� �̹���
//Mat _contour_image[matSize];								//�ܰ������� ��� �̹��� 
//Mat _line_Image[matSize];									//�� ���� ��� �̹��� 
//Mat _result(350,650,CV_8UC3,Scalar(0,0,0));		//��� ��� �̹��� 
//int _HOURS	 = 0;								//��
//int _MINUTES = 0;									//��


int main() {
	
	
	cout << endl << endl; 
	cout << "����Ű : Ű���� ����Ű ��, Ű���� ����Ű ��, ESC : ����" << endl << endl;

	for (int i = 1; i <= matSize; i++) {					    //Mat ��� �� ���� �� ��ŭ ��ȸ  

		string img_number = format("%d.png", i);				//���ϸ��� ���ڿ��� �޾ƿ�

		original_Image[i] = imread(img_number, IMREAD_COLOR);
		CV_Assert(original_Image[i].data);										//�̹��� ����ó�� 
		save_Ori[i] = original_Image[i];

		ExtractCircleLine(original_Image[i], original_Image[i]);						//�� ���� �� ����ŷ
		
		ContourRect(original_Image[i], original_Image[i]);								//�ܰ��� ���� �� �簢�� �������� �� �̹��� ���  

		Extract_Hands(original_Image[i], original_Image[i], 2, _ANGLE);					//���� ������ ������ ��ź��Ʈ �Լ��� �̿��� ������ ��� �� �ð� ����
		save_Hands[i] = original_Image[i];

		Mat		result(350, 650, CV_8UC3, Scalar(0, 0, 0));
		Point	textPoint;														//�ð��� ����� ��ġ 	
		string	angle = to_string(_ANGLE);
								
		textPoint.x = result.cols / 150;
		textPoint.y = result.rows / 3;

		putText(result, angle, textPoint, FONT_HERSHEY_DUPLEX, 5, Scalar(255, 255, 255));
		save_Result[i] = result.clone();

	}

	Mat input(200, 200, CV_8U, Scalar(255));

	namedWindow(" Ű���� ��ư ���� ", WINDOW_NORMAL);
	imshow(" Ű���� ��ư ���� ", input);

	

	while (1) {															//����Ű ���� 

		int key = waitKeyEx(0);

		if (key == 27) {												//ESC �Է� 

			cout << "���α׷��� �����մϴ�. " << endl; break;
		}

		switch (key) {													//ȭ��ǥ�� �Է¹޾� Mat�迭�� �ִ� �̹��� ������ �ε� 

		case 0x260000:													//���� ����Ű 
			if (index_num > 0) {
				index_num--;

				//cout << " ���� ȭ��ǥ Ű �Է� " << endl;
				//cout << "up index ��ȣ : " << index_num << endl << endl;
			}
		

			break;

		case 0x280000:													//�Ʒ��� ����Ű 
			
			if (index_num < 6) {
				index_num++;

				//cout << " �Ʒ��� ȭ��ǥ Ű �Է� " << endl;
				//cout << "down index ��ȣ : " << index_num << endl << endl;
			}
			else{
				index_num = 0;
			}
				
			break;
		}
		if (index_num >0 && index_num < 6) {
			
			imshow("����", save_Ori[index_num]);
			imshow("�ٴ� ����", save_Hands[index_num]);
			imshow("���", save_Result[index_num]);

		}
		
	}//while()

	waitKey();
	return 0;

}//main()





