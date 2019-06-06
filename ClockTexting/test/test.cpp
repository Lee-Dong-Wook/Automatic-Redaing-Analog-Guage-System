#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

#define PI 3.1415926535

double getDegree(double y, double x) {
	return atan2(y, x) * 180 / PI;
}
int main() {

	cout << getDegree(1, 1) << endl;
	
	return 0; 
}

	


