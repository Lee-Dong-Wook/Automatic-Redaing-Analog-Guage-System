#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

//hough_coord() 
//영상 내 모든 좌표에서 직선인지 여부 점검
//영상 전처리 후 직선 성분 검출
//영상 공간에서 직선으로 인지된 좌표(x,y)를 헢 변환 좌표계로 변환하여 곡선 구성 

//단계
//1. 허프 변환 좌표계에서 행렬 구성 
//2. 영상 내 모든 화소의 직선 여부 검사
//3. 직선 인지 좌표에 대한 허프 변환 누정 행렬 구성

void hough_coord(Mat image, Mat& acc_mat, double rho, double theta)
{
	int  acc_h = int((image.rows + image.cols) * 2 / rho);			//누적 행렬 높이
	int  acc_w = int(CV_PI / theta);								//누적 행렬 너비 								

	acc_mat = Mat(acc_h, acc_w, CV_32S, Scalar(0));					//허프 누적행렬 

	for (int i = 0; i < image.rows; i++) {							//입력화소 조회
		for (int j = 0; j < image.cols; j++)
		{
			Point pt(j, i);											//조회 좌표	
			if (image.at<uchar>(pt) > 0) {							//직선 여부 검사(0보다 크면 직선 간주) 

				//직선으로 인지한 점은 다시 0~acc_w까지의 반복문 구성, 각도 간격(변화량 세타)만큼 증가 
				//즉 0~180도 까지 증가 
				//이 과정에서 입력된 좌표(pt)의 x,y와 각도(세타t)를 허프 변환 수식에 대입해서 Pt를 계산 
				//거리와 각도를 좌표로 사용해 허프 누적행렬의 해당 원소값을 1증가 

				for (int t = 0; t < acc_mat.cols; t++)				//0~180도 반복 
				{
					double radian = t * theta;
					double r = pt.x * cos(radian) + pt.y * sin(radian);
					r = cvRound(r / rho + acc_mat.rows / 2.0);

					//직선으로 인지된 입력영상의 각 좌표들에 대해 0~180도로 회전, 허프 변환 수식에 따라 거리와 각도로 좌표 계산 
					//이 좌표에 해당하는 허프 누적행렬의 원소에 값을 누적 

					acc_mat.at<int>((int)r, t)++;					//(p,세타) 좌표에 누적 
																	//직선이니 0 + 1 하여 1로 좌표에 누적 p.556
				}
			}
		}
	}
}

void acc_mask(Mat acc_mat, Mat& acc_dst, Size size, int thresh)
{
	acc_dst = Mat(acc_mat.size(), CV_32S, Scalar(0));
	Point  h_m = size / 2;	// 마스크 크기 절반

	for (int r = h_m.y; r < acc_mat.rows - h_m.y; r++) {
		for (int t = h_m.x; t < acc_mat.cols - h_m.x; t++)
		{
			Point center = Point(t, r) - h_m;
			int c_value = acc_mat.at<int>(center);	// 중심화소
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
			float value = (float)acc_dst.at<int>(r, t);					// 누적값
			if (value >= thresh)										// 직선 길이 임계값
			{
				float rho = (float)((r - acc_dst.rows / 2) * _rho);		// 수직거리
				float radian = (float)(t * theta);						// 각도

				Matx13f line(rho, radian, value); 						// 단일 직선
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
		float rho = lines.at<float>(id, 0);		// 수직거리
		float radian = lines.at<float>(id, 1);
		s_lines.push_back(Vec2f(rho, radian));
	}
}

void houghLines(Mat src, vector<Vec2f>& s_lines, double rho, double theta, int thresh)
{
	Mat  acc_mat, acc_dst, lines;
	hough_coord(src, acc_mat, rho, theta);				// 허프 누적 행렬 구성 
	acc_mask(acc_mat, acc_dst, Size(3, 7), thresh);		// 허프 누적 행렬의 지역 최대값 선정 

	thres_lines(acc_dst, lines, rho, theta, thresh);	//임계값 이상인 누적값(직선) 선별 	
	sort_lines(lines, s_lines);							//직선을 누적값 기준으로 내림차순 정렬 
}

void draw_houghLines(Mat image, Mat& dst, vector<Vec2f> lines, int nline)
{
	if (image.channels() == 3) {
		image.copyTo(dst);
	}
	else {
		cvtColor(image, dst, COLOR_GRAY2BGR);								//컬러 영상 변한 
	}

	for (int i = 0; i < min((int)lines.size(), nline); i++)					//검출 직선 개수 반복 
	{
		float rho = lines[i][0];											//수직거리		
		float theta = lines[i][1];											//각도 
		double a = cos(theta);
		double b = sin(theta);

		Point2d delta(1000 * -b, 1000 * a);									//직선상의 한 좌표 계산 
		Point2d pt(a*rho, b*rho);											//직선상의 이동 위치 

		line(dst, pt + delta, pt - delta, Scalar(0, 255, 0), 2, LINE_AA);   //직선 색상 지정 

	}
}
