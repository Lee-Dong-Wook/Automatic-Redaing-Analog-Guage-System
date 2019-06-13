#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

#define PI 3.1415926535

double angle; 

double ATAN2(Point2d start, Point2d end) {

	double dy = end.y - start.y;
	double dx = end.x - start.x;

	double ang = atan2(dx, dy) * (180.0 / PI);

	if (ang < 0.0){

		ang += 360.0;
	}
	
	if ( ang < 180.0) {
		ang = 180.0 - ang; 
	}

	else if (ang > 180.0 && ang < 360.0) {

		ang -= 360.0;
		
		ang = abs(ang) + 180.0;
	}
	return ang;
}
void Extract_Hour(double angle) {

	double hour;	//연산 결과가 12이 아니라 12에 거의 근사이기 때문에 int로 할경우 소수점이 잘려 11시으로 출력된다. 
	
	hour = angle / 30.0;
	
	if (hour > 11.99) {
		cout << hour << "시 " << endl;
	}
	
	else {
		cout << (int)hour << "시 " << endl;
	}
}

void Extract_Min(double angle) {

	double min;

	min = angle / 6.0;

	if (min > 59.99) {		//연산 결과가 60이 아니라 60에 거의 근사이기 때문에 int로 할경우 소수점이 잘려 59분으로 출력된다. 
							//또한 60분이란 분 또한 없기 때문에 0으로 초기화한다. 
		min = 0.0;
		cout << min << "분" << endl;
	}

	else {
		cout << (int)min << "분" << endl;
	}	
}


double ATAN(Point2d start, Point2d end) {

	double dy = end.y - start.y;
	double dx = end.x - start.x;

	double angle = atan2(dx, dy) * (180 / PI);

	if (angle < 0.0)
	{
		angle += 360.0;
	}

	return angle;
}

int main() {

	Point2d start(0,0);
	Point2d end1(1,1);
	Point2d end2(-1,1);
	Point2d end3(-1, -1);
	Point2d end4(1,-1);

	Point2d zeroPoint(140, 140);		//x,y
	Point2d departPoint1(210, 70);
	Point2d departPoint2(70, 70);
	Point2d departPoint3(70, 210);
	Point2d departPoint4(210, 210);

	Point2d twelve(140, 70);
	Point2d three(210, 140);			//3시
	Point2d six(140, 210);
	Point2d nine(70, 140);

	cout << "극 좌표계 상 atan2() 사용 " << endl << endl;
	cout << " 점 A( 1,  1) : " << ATAN(start, end1) << "도 " << endl << endl;
	cout << " 점 B(-1,  1) : " << ATAN(start, end2) << "도 " << endl << endl;
	cout << " 점 C(-1, -1) : " << ATAN(start, end3) << "도 " << endl << endl;
	cout << " 점 D( 1, -1) : " << ATAN(start, end4) << "도 " << endl << endl;

	cout << "이미지 상 atan2() 사용 " << endl << endl;
	cout << " 점 A(210, 70)  : " << ATAN2(zeroPoint, departPoint1) << "도 " << endl << endl;
	cout << " 점 B(70, 70)   : " << ATAN2(zeroPoint, departPoint2) << "도 " << endl << endl;
	cout << " 점 C(70, 210)  : " << ATAN2(zeroPoint, departPoint3) << "도 " << endl << endl;
	cout << " 점 D(210, 210) : " << ATAN2(zeroPoint, departPoint4) << "도 " << endl << endl;

	cout << "12시, 3시, 6시 9시 출력" << endl << endl;
	cout << " 12시- 점 A(140, 70)  : " << ATAN2(zeroPoint, twelve) << "도 " << endl << endl;
	cout << " 3시 - 점 B(210, 140) : " << ATAN2(zeroPoint, three) << "도 " << endl << endl;
	cout << " 6시 - 점 C(140, 210) : " << ATAN2(zeroPoint, six) << "도 " << endl << endl;
	cout << " 9시 - 점 D(70, 140)  : " << ATAN2(zeroPoint, nine) << "도 " << endl << endl;
	
	cout << endl; 

	//45도
	angle = ATAN2(zeroPoint, departPoint1);
	Extract_Hour(angle);
	Extract_Min(angle);
	cout << endl;

	//315도 
	angle = ATAN2(zeroPoint, departPoint2);
	Extract_Hour(angle);
	Extract_Min(angle);
	cout << endl;

	//225도 
	angle = ATAN2(zeroPoint, departPoint3);
	Extract_Hour(angle);
	Extract_Min(angle);
	cout << endl;

	//135도 
	angle = ATAN2(zeroPoint, departPoint4);
	Extract_Hour(angle);
	Extract_Min(angle);
	cout << endl;

	//12시 0분
	angle = ATAN2(zeroPoint, twelve);
	Extract_Hour(angle);
	Extract_Min(angle);
	cout << endl;

	//3시 15분 -> 2시 14분이 나온다. 210, 141하니 3시 15분이 나오는데 오차값이 있다. 이에 대해서 연구가 더필요하다.
	angle = ATAN2(zeroPoint, three);
	Extract_Hour(angle);
	Extract_Min(angle);
	cout << endl;

	//6시 30분 
	angle = ATAN2(zeroPoint, six);
	Extract_Hour(angle);
	Extract_Min(angle);
	cout << endl;

	//9시 45분 
	angle = ATAN2(zeroPoint, nine);
	Extract_Hour(angle);
	Extract_Min(angle);
	cout << endl;

	return 0; 
}

	


