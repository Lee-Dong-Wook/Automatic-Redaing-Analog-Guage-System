#pragma once
// ������Ʈ ��       : ClockTexting
// ������Ʈ ����     : openCV�� �̿��Ͽ� �Ƴ��α� �ð��� �̹����� ó���Ͽ� �ð������� ����
// ��ũ��Ʈ ���     : ��ó�� �� �̹������� �ð�ٴ� ���� �� ������ ����Ͽ� �ð� ����  
// ��ũ��Ʈ ��       : ExtractTime.hpp	
//					  1. ExtractHands    : ��ħ�� ��ħ�� ����, �ٴ� �׸��� �Լ� ȣ�� 
//					  2. draw_Lines	     : ���� �� ������ ��ħ�� ��ħ���� �����Ͽ� �׸�
//					  3. Calc_AnglePoint : ������ ����ϱ� ���� �ٴ��� ������ ���� 
//					  4. Calc_Angle      : ����� ������ ������ ����Ͽ� ���� ����
//					  5. Extract_Hour    : �� ���� 
//					  6. Extract_Min     : �� ���� 				
// openCV ����      : 4.0.1 
// �ۼ� ���� �Ͻ�    : 2019. 06. 02.
// ������ ���� �Ͻ�  : 2019. 06. 14.
// �ۼ��� �� ������  : �̵��� 
// e-mail			: dongwookRaynor@gmail.com 
// github ��ũ		: https://github.com/Lee-Dong-Wook/ClockTexting

#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

#define PI 3.1415926535

//���� ����
void	draw_Lines(Mat& bgr, vector<Vec4i> lines, const int& nline, double& ang);
void	Calc_AnglePoint(Point pt_start, Point pt_end, Point pt_center, Point& pt_angle);
double  Calc_Angle(Point2d start, Point2d end);
//int		Extract_Hour(double angle);
//int		Extract_Min(double angle);

void Extract_Hands(Mat gray, Mat &bgr, const int& nline, double& ang) {

	double rho = 1;																		//�����Ÿ� 	
	double theta = CV_PI / 180;	

	cvtColor(gray, bgr, COLOR_GRAY2BGR);												//gray�� ��ó���� �� ���̳ʸ� �̹��� ä�� 1��
																						//bgr�� //gray�� ä���� gray -> BGR
	//**** ȣ����ȯ ���� ���� ****
	vector<Vec4i> lines;																// ����� �� 
	HoughLinesP(gray, lines, rho, theta, 50, 50, 10);									//Ȯ���� ȣ�� ��ȯ 
	
	draw_Lines(bgr, lines, nline, ang);										//���� �� ���� �׸��� 
																						//����° ���ڴ� �׸� �� ���� 	
}//Extract_Hands


void draw_Lines(Mat& bgr, vector<Vec4i> lines, const int& nline, double& ang) {	//lines�� ����� ���� ������(x, y), ����(x, y)�� ����
																							//int�� vector ������ 4���� ���Ҹ� ����ֱ�	
	Vec4i li;																				//���� ��ǥ�� ��� �ִ� ���� 4�� ¥�� int�� vector ���� 									
	int	  x = (bgr.cols) / 2;																
	int   y = (bgr.rows) / 2; 
	Point pt_center(x, y);																	//�̹����� �߽� 	
	//int	  HOURS;
	//int   MINUTES;

	for (size_t i = 0; i < min((int)lines.size(), nline); i++)								//������ ũ��� nline�� ���ؼ� ���� ���� ���� for�� �ݺ� 
	{
		li = lines[i];																		//li�� i��° line�� ���ؼ� ������(x,y), ������(x,y)�� �� �ε����� ���� 

		Point pt_start(li[0], li[1]);														//li�� �ε����� ����� ������, ����� ���� ���� �� 
		Point pt_end(li[2], li[3]);															//li�� �ε����� ����� ������, ����� ���� ���� �� 
		Point pt_angle;																		//������ ��� ���� �� 	
		double angle;																		//�ٴð� y�� ���� ���� 
		
		//**** ����� ���� ���� ��,�� ����  ****
		if(i == 0){
			
			line(bgr, pt_start, pt_end, Scalar(0, 255, 0), 1, LINE_AA);						//��ħ ���� 

			cout << endl;
			cout << " ���� �ٴ� : ����� | �ٴ� ���� : �ʷ� = ���� �ٴ� " << endl<<endl;

			cout << "����Ʈ pt_start : ������ " << pt_start << endl;
			cout << "����Ʈ pt_end : ������ " << pt_end << endl<<endl;

			Calc_AnglePoint(pt_start, pt_end, pt_center, pt_angle);
			cout <<"pt_angle : " << pt_angle << endl<<endl;

			angle = Calc_Angle(pt_center, pt_angle);
			cout << "angle :" << angle << endl<<endl;
			cout << "==========================================================" << endl;
			ang = angle;
			//MINUTES = Extract_Min(angle);
		}	

		else if (i == 2) {			//i > lines.size()/2

			line(bgr, pt_start, pt_end, Scalar(0, 0, 255), 1, LINE_AA);						//��ħ ���� 

			cout << endl;
			cout << " ���� �ٴ� : ����� | �ٴ� ���� : ���� = ���� �ٴ� " << endl<<endl;

			cout << "����Ʈ pt_start : ������ " << pt_start << endl;
			cout << "����Ʈ pt_end : ������ " << pt_end << endl<<endl;

			Calc_AnglePoint(pt_start, pt_end, pt_center, pt_angle);
			cout << "pt_angle :" << pt_angle << endl<<endl;

			angle = Calc_Angle(pt_center, pt_angle);
			cout << "angle :" << angle << endl<<endl;
			ang = angle;
			//HOURS= Extract_Hour(angle);
		}
	}//for()

	//hour = HOURS;
	//minute = MINUTES;

	//cout << endl << "�̹����� �ð� : ";
	//cout << HOURS << "��  "<< MINUTES <<" �� " << endl;
	//imshow("�ٴ� ���� ǥ�� ", bgr);
}//draw_Lines()


void Calc_AnglePoint(Point pt_start, Point pt_end, Point pt_center, Point& pt_angle) {		//�߽����� ��������� �ָ� ������ ���� �����Ͽ� ������ ����� ��ǥ�� ����

	//**** �߽����� ����� ���� ��ǥ ���� ****
	Point start;
	Point end; 

	start	= pt_start - pt_center;															//�������� �߽������� �Ÿ�  
	end		= pt_end - pt_center;															//�������� �߽������� �Ÿ� 

	start.x = abs(start.x);																	//����	
	start.y = abs(start.y);
	int start_sum = start.x + start.y;														//����ġ ���� 

	end.x = abs(end.x);
	end.y = abs(end.y);
	int end_sum = end.x + end.y;

	int angle_x = (start_sum > end_sum) ? pt_start.x : pt_end.x;							//�������� ������ ����ġ�� ����� ��ǥ�� ���� 
	int angle_y = (start_sum > end_sum) ? pt_start.y : pt_end.y;

	pt_angle = Point(angle_x, angle_y);

}//Calc_AnglePoint()


double Calc_Angle(Point2d center, Point2d angle_point) {									//start�� �̹��� �߽���, end�� �ٴ��� ����

	//**** y�� ���� ���� ��� ****
	double dy = angle_point.y - center.y;													//��ǥ y�� ��ȭ�� (������ x�� �߽������� �Ÿ�)
	double dx = angle_point.x - center.x;													//��ǥ x�� ��ȭ�� (������ y�� �߽������� �Ÿ�) 	

	double ang = atan2(dx, dy) * (180.0 / PI);												//���� ���� 	

	if (ang < 0.0) { ang += 360.0; }														//������ ��µǴ� ������ ���� ����� ��ȯ 

	if (ang < 180.0) { ang = 180.0 - ang; }													//�̹����� ����ǥ��� ���� ��Ī����		
																							
	
	else if (ang > 180.0 && ang < 360.0) {													//�̹����� ����ǥ��� ���� ��Ī����											
																							
		ang -= 360.0;
		ang = abs(ang) + 180.0;
	}
	return ang;
}


//**** ��, �� ���� ****
//int Extract_Hour(double angle) {					
//
//	double hour;										
//
//	hour = angle / 30.0;																	//12�ð��� 360���� 1�ð��� 30���� ǥ�� 
//
//	if (hour > 11.99) {																		//�ð��� ���������� double ĳ���ÿ����� �ϸ� �Ҽ����� �߷� ġ������ ���� �߻� 				
//		cout << " ��� : "  << hour << "�� " << endl;										//�׷��� ���� ������ ����� �ٻ簪�� �׳� ��� 					
//	}
//
//	else {
//		cout << " ��� : " << (int)hour << "�� " << endl;									//�׷��� ������ ���������� ĳ���� ���� �� ��� 
//	}
//
//	return (int)hour;
//}


//int Extract_Min(double angle) {
//
//	double min;
//
//	min = angle / 6.0;
//
//	if (min > 59.99) {		
//							 
//		min = 0.0;																		   // 60���̶� �� ���� ���� ������ 0���� �ʱ�ȭ				
//		cout << " ��� : " << min << "��" << endl;
//	}
//
//	else {
//		cout << " ��� : " << (int)min << "��" << endl;
//	}
//
//	return (int)min;
//}

