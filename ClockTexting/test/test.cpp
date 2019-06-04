#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
//void draw_houghLines(Mat src, Mat& dst, vector<Vec2f> lines, int nline);

int main() {

	Mat dst, cdst, cdstP; 

	string filename = "2.jpg";

	Mat src = imread(filename, IMREAD_COLOR);
	CV_Assert(src.data);

	imshow("ori", src);

	Size imgSize(280, 280);
	resize(src, src, imgSize);

	GaussianBlur(src, src, Size(5, 5), 2, 2);
	imshow("gau", src);

	int thresh = 50;
	Canny(src, dst, thresh, thresh * 2, 3);

	imshow("canny", dst);
	//---------------------------------------------------------------
	cvtColor(dst,cdst,COLOR_GRAY2BGR);
	cdstP = cdst.clone();


	// Probabilistic Line Transform
	vector<Vec4i> linesP; // will hold the results of the detection
	HoughLinesP(dst, linesP, 1, CV_PI / 180, 50, 50, 10); // runs the actual detection				//dst�� ���� �׷��̽������� ȣ�������Ҷ��� �׷��� �������� ������� 
	
	int nline = 3;			//��ħ�� 2�� ��ħ�� 1�� 
// Draw the lines
	for (size_t i = 0; i < min((int)linesP.size(), nline); i++)
	{
		Vec4i l = linesP[i];
		line(cdstP, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 255, 0), 3, LINE_AA);
	}

	imshow("Source", src);
	imshow("HoughLinesP", cdstP);

	waitKey();
	return 0; 
}

	


