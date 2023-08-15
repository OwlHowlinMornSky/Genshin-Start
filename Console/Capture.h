
// https://www.cnblogs.com/zhiyiYo/p/14800601.html

#pragma once

#include <opencv2/opencv.hpp>

struct CaptureData;

class Capture {
public:
	Capture();
	~Capture();

	double static getZoom();
	cv::Mat getScreenshot();
	cv::Mat getScreenshot(int x, int y, int width, int height);

private:
	int m_width;
	int m_height;
	CaptureData* m_data;
};
