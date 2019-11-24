
#include <opencv2/opencv.hpp>
#include "ImagePreprocessing.hpp"
#include <iostream>

using namespace std;
using namespace cv;

const int matSize = 5;															//�̹��� ����  
const int frontArr = -1;														//�迭 ���� 	 
Mat original_Image[matSize];													//���� �̹��� ��� 	
Mat gray_Image[matSize];														//�׷��̽����� ���		
Mat output_Image[matSize];														//��� �̹��� ��� 

int main() {

	cout << "========== �̹��� ��ȣ ���� ========== " << endl << endl;
	cout << "����Ű : Ű���� ����Ű ��, Ű���� ����Ű ��, ESC : ����" << endl << endl;

	for (int i = 1; i <= matSize; i++) {					    //Mat ��� �� ���� �� ��ŭ ��ȸ  

		string img_number = format("%d.png", i);				//���ϸ��� ���ڿ��� �޾ƿ�

		original_Image[i] = imread(img_number, IMREAD_COLOR);
		if (!original_Image[i].data) {
			cout << "�̹��� ����" << endl;
		}
		
		//CV_Assert(original_Image[i].data);										//�̹��� ����ó�� 
	}

	Mat input(200, 200, CV_8U, Scalar(255));

	namedWindow(" Ű���� ��ư ���� ", WINDOW_NORMAL);
	imshow(" Ű���� ��ư ���� ", input);

	int index_num = 0;

	while (1) {															//����Ű ���� 

		int key = waitKeyEx(0);

		if (key == 27) {												//ESC �Է� 

			cout << "���α׷��� �����մϴ�. " << endl; break;
		}

		switch (key) {													//ȭ��ǥ�� �Է¹޾� Mat�迭�� �ִ� �̹��� ������ �ε� 

		case 0x260000:													//���� ����Ű 
				index_num--;
			
			cout << " ���� ȭ��ǥ Ű �Է� " << endl;
			cout << "up index ��ȣ : " << index_num << endl << endl;

			//���� �̹��� 	
			imshow("original", original_Image[index_num]);
			break;

		case 0x280000:													//�Ʒ��� ����Ű 
			
				index_num++;
			
			cout << " �Ʒ��� ȭ��ǥ Ű �Է� " << endl;
			cout << "down index ��ȣ : " << index_num << endl << endl;

			imshow("original", original_Image[index_num]);
			break;
		}
	}//while()

	waitKey();
	return 0;
}//main()






