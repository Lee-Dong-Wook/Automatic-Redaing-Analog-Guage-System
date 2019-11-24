#pragma once
// 프로젝트 명       : ClockTexting
// 프로젝트 목적     : openCV를 이용하여 아날로그 시계의 이미지를 처리하여 시간정보를 추출
// 스크립트 기능     : 전처리 된 이미지에서 시계바늘 검출 후 각도를 계산하여 시간 추출  
// 스크립트 명       : ExtractTime.hpp	
//					  1. ExtractHands    : 시침과 분침을 추출, 바늘 그리기 함수 호츨 
//					  2. draw_Lines	     : 검출 된 라인을 시침과 분침으로 구분하여 그림
//					  3. Calc_AnglePoint : 각도를 계산하기 편한 바늘의 끝점을 추출 
//					  4. Calc_Angle      : 추출된 끝점과 원점을 계산하여 각도 추출
//					  5. Extract_Hour    : 시 추출 
//					  6. Extract_Min     : 분 추출 				
// openCV 버전      : 4.0.1 
// 작성 시작 일시    : 2019. 06. 02.
// 마지막 수정 일시  : 2019. 06. 14.
// 작성자 및 수정자  : 이동욱 
// e-mail			: dongwookRaynor@gmail.com 
// github 링크		: https://github.com/Lee-Dong-Wook/ClockTexting

#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

#define PI 3.1415926535

//전방 선언
void	draw_Lines(Mat& bgr, vector<Vec4i> lines, const int& nline, double& ang);
void	Calc_AnglePoint(Point pt_start, Point pt_end, Point pt_center, Point& pt_angle);
double  Calc_Angle(Point2d start, Point2d end);
//int		Extract_Hour(double angle);
//int		Extract_Min(double angle);

void Extract_Hands(Mat gray, Mat &bgr, const int& nline, double& ang) {

	double rho = 1;																		//수직거리 	
	double theta = CV_PI / 180;	

	cvtColor(gray, bgr, COLOR_GRAY2BGR);												//gray는 전처리가 된 바이너리 이미지 채널 1개
																						//bgr는 //gray의 채널을 gray -> BGR
	//**** 호프변환 직선 검출 ****
	vector<Vec4i> lines;																// 검출된 선 
	HoughLinesP(gray, lines, rho, theta, 50, 50, 10);									//확률적 호프 변환 
	
	draw_Lines(bgr, lines, nline, ang);										//검출 된 선을 그리기 
																						//세번째 인자는 그릴 선 개수 	
}//Extract_Hands


void draw_Lines(Mat& bgr, vector<Vec4i> lines, const int& nline, double& ang) {	//lines는 검출된 선의 시작점(x, y), 끝점(x, y)를 가짐
																							//int형 vector 변수에 4개의 원소를 집어넣기	
	Vec4i li;																				//선의 좌표를 담고 있는 원소 4개 짜리 int형 vector 변수 									
	int	  x = (bgr.cols) / 2;																
	int   y = (bgr.rows) / 2; 
	Point pt_center(x, y);																	//이미지의 중심 	
	//int	  HOURS;
	//int   MINUTES;

	for (size_t i = 0; i < min((int)lines.size(), nline); i++)								//라인의 크기와 nline을 비교해서 적은 수를 정해 for문 반복 
	{
		li = lines[i];																		//li는 i번째 line에 대해서 시작점(x,y), 종료점(x,y)를 각 인덱스에 저장 

		Point pt_start(li[0], li[1]);														//li의 인덱스에 저장된 시작점, 검출된 선의 시작 점 
		Point pt_end(li[2], li[3]);															//li의 인덱스에 저장된 종료점, 검출된 선의 종료 점 
		Point pt_angle;																		//각도를 재기 위한 점 	
		double angle;																		//바늘과 y축 과의 각도 
		
		//**** 검출된 선에 대해 시,분 구분  ****
		if(i == 0){
			
			line(bgr, pt_start, pt_end, Scalar(0, 255, 0), 1, LINE_AA);						//분침 추출 

			cout << endl;
			cout << " 검출 바늘 : 계기판 | 바늘 색상 : 초록 = 메인 바늘 " << endl<<endl;

			cout << "포인트 pt_start : 시작점 " << pt_start << endl;
			cout << "포인트 pt_end : 종료점 " << pt_end << endl<<endl;

			Calc_AnglePoint(pt_start, pt_end, pt_center, pt_angle);
			cout <<"pt_angle : " << pt_angle << endl<<endl;

			angle = Calc_Angle(pt_center, pt_angle);
			cout << "angle :" << angle << endl<<endl;
			cout << "==========================================================" << endl;
			ang = angle;
			//MINUTES = Extract_Min(angle);
		}	

		else if (i == 2) {			//i > lines.size()/2

			line(bgr, pt_start, pt_end, Scalar(0, 0, 255), 1, LINE_AA);						//시침 추출 

			cout << endl;
			cout << " 검출 바늘 : 계기판 | 바늘 색상 : 빨강 = 서브 바늘 " << endl<<endl;

			cout << "포인트 pt_start : 시작점 " << pt_start << endl;
			cout << "포인트 pt_end : 종료점 " << pt_end << endl<<endl;

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

	//cout << endl << "이미지의 시간 : ";
	//cout << HOURS << "시  "<< MINUTES <<" 분 " << endl;
	//imshow("바늘 검출 표시 ", bgr);
}//draw_Lines()


void Calc_AnglePoint(Point pt_start, Point pt_end, Point pt_center, Point& pt_angle) {		//중심점과 상대적으로 멀리 떨어진 점을 선택하여 각도를 계산할 좌표로 선정

	//**** 중심점과 계산을 위한 좌표 추출 ****
	Point start;
	Point end; 

	start	= pt_start - pt_center;															//시작점과 중심점과의 거리  
	end		= pt_end - pt_center;															//종료점과 중심점과의 거리 

	start.x = abs(start.x);																	//절댓값	
	start.y = abs(start.y);
	int start_sum = start.x + start.y;														//가중치 생성 

	end.x = abs(end.x);
	end.y = abs(end.y);
	int end_sum = end.x + end.y;

	int angle_x = (start_sum > end_sum) ? pt_start.x : pt_end.x;							//시작점과 끝점의 가중치를 계산해 좌표로 지정 
	int angle_y = (start_sum > end_sum) ? pt_start.y : pt_end.y;

	pt_angle = Point(angle_x, angle_y);

}//Calc_AnglePoint()


double Calc_Angle(Point2d center, Point2d angle_point) {									//start는 이미지 중심점, end는 바늘의 끝점

	//**** y축 기준 각도 계산 ****
	double dy = angle_point.y - center.y;													//좌표 y의 변화량 (끝점의 x와 중심점과의 거리)
	double dx = angle_point.x - center.x;													//좌표 x의 변화량 (끝점의 y와 중심점과의 거리) 	

	double ang = atan2(dx, dy) * (180.0 / PI);												//계산된 각도 	

	if (ang < 0.0) { ang += 360.0; }														//음수로 출력되는 각도에 대해 양수로 변환 

	if (ang < 180.0) { ang = 180.0 - ang; }													//이미지와 극좌표계는 상하 대칭관계		
																							
	
	else if (ang > 180.0 && ang < 360.0) {													//이미지와 극좌표계는 상하 대칭관계											
																							
		ang -= 360.0;
		ang = abs(ang) + 180.0;
	}
	return ang;
}


//**** 시, 분 추출 ****
//int Extract_Hour(double angle) {					
//
//	double hour;										
//
//	hour = angle / 30.0;																	//12시간을 360도로 1시간을 30도로 표현 
//
//	if (hour > 11.99) {																		//시간의 데이터형이 double 캐스팅연산을 하면 소수점이 잘려 치명적인 오류 발생 				
//		cout << " 결과 : "  << hour << "시 " << endl;										//그래서 거의 정수와 가까운 근사값은 그냥 출력 					
//	}
//
//	else {
//		cout << " 결과 : " << (int)hour << "시 " << endl;									//그렇지 않으면 정수형으로 캐스팅 연산 후 출력 
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
//		min = 0.0;																		   // 60분이란 분 또한 없기 때문에 0으로 초기화				
//		cout << " 결과 : " << min << "분" << endl;
//	}
//
//	else {
//		cout << " 결과 : " << (int)min << "분" << endl;
//	}
//
//	return (int)min;
//}

