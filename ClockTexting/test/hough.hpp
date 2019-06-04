#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

//hough_coord() 
//���� �� ��� ��ǥ���� �������� ���� ����
//���� ��ó�� �� ���� ���� ����
//���� �������� �������� ������ ��ǥ(x,y)�� �R ��ȯ ��ǥ��� ��ȯ�Ͽ� � ���� 

//�ܰ�
//1. ���� ��ȯ ��ǥ�迡�� ��� ���� 
//2. ���� �� ��� ȭ���� ���� ���� �˻�
//3. ���� ���� ��ǥ�� ���� ���� ��ȯ ���� ��� ����

void hough_coord(Mat image, Mat& acc_mat, double rho, double theta)
{
	int  acc_h = int((image.rows + image.cols) * 2 / rho);			//���� ��� ����
	int  acc_w = int(CV_PI / theta);								//���� ��� �ʺ� 								

	acc_mat = Mat(acc_h, acc_w, CV_32S, Scalar(0));					//���� ������� 

	for (int i = 0; i < image.rows; i++) {							//�Է�ȭ�� ��ȸ
		for (int j = 0; j < image.cols; j++)
		{
			Point pt(j, i);											//��ȸ ��ǥ	
			if (image.at<uchar>(pt) > 0) {							//���� ���� �˻�(0���� ũ�� ���� ����) 

				//�������� ������ ���� �ٽ� 0~acc_w������ �ݺ��� ����, ���� ����(��ȭ�� ��Ÿ)��ŭ ���� 
				//�� 0~180�� ���� ���� 
				//�� �������� �Էµ� ��ǥ(pt)�� x,y�� ����(��Ÿt)�� ���� ��ȯ ���Ŀ� �����ؼ� Pt�� ��� 
				//�Ÿ��� ������ ��ǥ�� ����� ���� ��������� �ش� ���Ұ��� 1���� 

				for (int t = 0; t < acc_mat.cols; t++)				//0~180�� �ݺ� 
				{
					double radian = t * theta;
					double r = pt.x * cos(radian) + pt.y * sin(radian);
					r = cvRound(r / rho + acc_mat.rows / 2.0);

					//�������� ������ �Է¿����� �� ��ǥ�鿡 ���� 0~180���� ȸ��, ���� ��ȯ ���Ŀ� ���� �Ÿ��� ������ ��ǥ ��� 
					//�� ��ǥ�� �ش��ϴ� ���� ��������� ���ҿ� ���� ���� 

					acc_mat.at<int>((int)r, t)++;					//(p,��Ÿ) ��ǥ�� ���� 
																	//�����̴� 0 + 1 �Ͽ� 1�� ��ǥ�� ���� p.556
				}
			}
		}
	}
}

void acc_mask(Mat acc_mat, Mat& acc_dst, Size size, int thresh)
{
	acc_dst = Mat(acc_mat.size(), CV_32S, Scalar(0));
	Point  h_m = size / 2;	// ����ũ ũ�� ����

	for (int r = h_m.y; r < acc_mat.rows - h_m.y; r++) {
		for (int t = h_m.x; t < acc_mat.cols - h_m.x; t++)
		{
			Point center = Point(t, r) - h_m;
			int c_value = acc_mat.at<int>(center);	// �߽�ȭ��
			if (c_value >= thresh)
			{
				double maxVal = 0;
				for (int u = 0; u < size.height; u++) {
					for (int v = 0; v < size.width; v++)
					{
						Point start = center + Point(v, u);
						if (start != center && acc_mat.at<int>(start) > maxVal)
							maxVal = acc_mat.at<int>(start);
					}
				}

				Rect rect(center, size);
				if (c_value >= maxVal)
				{
					acc_dst.at<int>(center) = c_value;
					acc_mat(rect).setTo(0);
				}
			}
		}
	}
}

void thres_lines(Mat acc_dst, Mat& lines, double _rho, double theta, int thresh)
{
	for (int r = 0; r < acc_dst.rows; r++) {
		for (int t = 0; t < acc_dst.cols; t++)
		{
			float value = (float)acc_dst.at<int>(r, t);					// ������
			if (value >= thresh)										// ���� ���� �Ӱ谪
			{
				float rho = (float)((r - acc_dst.rows / 2) * _rho);		// �����Ÿ�
				float radian = (float)(t * theta);						// ����

				Matx13f line(rho, radian, value); 						// ���� ����
				lines.push_back((Mat)line);
			}
			t++;
		}

	}
}

void sort_lines(Mat lines, vector<Vec2f>& s_lines)
{
	Mat acc = lines.col(2), idx;
	sortIdx(acc, idx, SORT_EVERY_COLUMN + SORT_DESCENDING);

	for (int i = 0; i < idx.rows; i++)
	{
		int id = idx.at<int>(i);
		float rho = lines.at<float>(id, 0);		// �����Ÿ�
		float radian = lines.at<float>(id, 1);
		s_lines.push_back(Vec2f(rho, radian));
	}
}

void houghLines(Mat src, vector<Vec2f>& s_lines, double rho, double theta, int thresh)
{
	Mat  acc_mat, acc_dst, lines;
	hough_coord(src, acc_mat, rho, theta);				// ���� ���� ��� ���� 
	acc_mask(acc_mat, acc_dst, Size(3, 7), thresh);		// ���� ���� ����� ���� �ִ밪 ���� 

	thres_lines(acc_dst, lines, rho, theta, thresh);	//�Ӱ谪 �̻��� ������(����) ���� 	
	sort_lines(lines, s_lines);							//������ ������ �������� �������� ���� 
}

void draw_houghLines(Mat image, Mat& dst, vector<Vec2f> lines, int nline)
{
	if (image.channels() == 3) {
		image.copyTo(dst);
	}
	else {
		cvtColor(image, dst, COLOR_GRAY2BGR);								//�÷� ���� ���� 
	}

	for (int i = 0; i < min((int)lines.size(), nline); i++)					//���� ���� ���� �ݺ� 
	{
		float rho = lines[i][0];											//�����Ÿ�		
		float theta = lines[i][1];											//���� 
		double a = cos(theta);
		double b = sin(theta);

		Point2d delta(1000 * -b, 1000 * a);									//�������� �� ��ǥ ��� 
		Point2d pt(a*rho, b*rho);											//�������� �̵� ��ġ 

		line(dst, pt + delta, pt - delta, Scalar(0, 255, 0), 2, LINE_AA);   //���� ���� ���� 

	}
}
