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

	double hour;	//���� ����� 12�� �ƴ϶� 12�� ���� �ٻ��̱� ������ int�� �Ұ�� �Ҽ����� �߷� 11������ ��µȴ�. 
	
	hour = angle / 30.0;
	
	if (hour > 11.99) {
		cout << hour << "�� " << endl;
	}
	
	else {
		cout << (int)hour << "�� " << endl;
	}
}

void Extract_Min(double angle) {

	double min;

	min = angle / 6.0;

	if (min > 59.99) {		//���� ����� 60�� �ƴ϶� 60�� ���� �ٻ��̱� ������ int�� �Ұ�� �Ҽ����� �߷� 59������ ��µȴ�. 
							//���� 60���̶� �� ���� ���� ������ 0���� �ʱ�ȭ�Ѵ�. 
		min = 0.0;
		cout << min << "��" << endl;
	}

	else {
		cout << (int)min << "��" << endl;
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
	Point2d three(210, 140);			//3��
	Point2d six(140, 210);
	Point2d nine(70, 140);

	cout << "�� ��ǥ�� �� atan2() ��� " << endl << endl;
	cout << " �� A( 1,  1) : " << ATAN(start, end1) << "�� " << endl << endl;
	cout << " �� B(-1,  1) : " << ATAN(start, end2) << "�� " << endl << endl;
	cout << " �� C(-1, -1) : " << ATAN(start, end3) << "�� " << endl << endl;
	cout << " �� D( 1, -1) : " << ATAN(start, end4) << "�� " << endl << endl;

	cout << "�̹��� �� atan2() ��� " << endl << endl;
	cout << " �� A(210, 70)  : " << ATAN2(zeroPoint, departPoint1) << "�� " << endl << endl;
	cout << " �� B(70, 70)   : " << ATAN2(zeroPoint, departPoint2) << "�� " << endl << endl;
	cout << " �� C(70, 210)  : " << ATAN2(zeroPoint, departPoint3) << "�� " << endl << endl;
	cout << " �� D(210, 210) : " << ATAN2(zeroPoint, departPoint4) << "�� " << endl << endl;

	cout << "12��, 3��, 6�� 9�� ���" << endl << endl;
	cout << " 12��- �� A(140, 70)  : " << ATAN2(zeroPoint, twelve) << "�� " << endl << endl;
	cout << " 3�� - �� B(210, 140) : " << ATAN2(zeroPoint, three) << "�� " << endl << endl;
	cout << " 6�� - �� C(140, 210) : " << ATAN2(zeroPoint, six) << "�� " << endl << endl;
	cout << " 9�� - �� D(70, 140)  : " << ATAN2(zeroPoint, nine) << "�� " << endl << endl;
	
	cout << endl; 

	//45��
	angle = ATAN2(zeroPoint, departPoint1);
	Extract_Hour(angle);
	Extract_Min(angle);
	cout << endl;

	//315�� 
	angle = ATAN2(zeroPoint, departPoint2);
	Extract_Hour(angle);
	Extract_Min(angle);
	cout << endl;

	//225�� 
	angle = ATAN2(zeroPoint, departPoint3);
	Extract_Hour(angle);
	Extract_Min(angle);
	cout << endl;

	//135�� 
	angle = ATAN2(zeroPoint, departPoint4);
	Extract_Hour(angle);
	Extract_Min(angle);
	cout << endl;

	//12�� 0��
	angle = ATAN2(zeroPoint, twelve);
	Extract_Hour(angle);
	Extract_Min(angle);
	cout << endl;

	//3�� 15�� -> 2�� 14���� ���´�. 210, 141�ϴ� 3�� 15���� �����µ� �������� �ִ�. �̿� ���ؼ� ������ ���ʿ��ϴ�.
	angle = ATAN2(zeroPoint, three);
	Extract_Hour(angle);
	Extract_Min(angle);
	cout << endl;

	//6�� 30�� 
	angle = ATAN2(zeroPoint, six);
	Extract_Hour(angle);
	Extract_Min(angle);
	cout << endl;

	//9�� 45�� 
	angle = ATAN2(zeroPoint, nine);
	Extract_Hour(angle);
	Extract_Min(angle);
	cout << endl;

	return 0; 
}

	


