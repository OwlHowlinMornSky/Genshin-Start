/*
*  Source Document
* 
*   Copyright 2021-2023  之一Yo
* 
*   CC BY-NC-SA 4.0 https://creativecommons.org/licenses/by-nc-sa/4.0/
* 
*  Genshin, Start!
* 
*   Copyright 2023 Tyler Parret True
* 
*   Licensed under the Apache License, Version 2.0 (the "License");
*   you may not use this file except in compliance with the License.
*   You may obtain a copy of the License at
* 
*       http://www.apache.org/licenses/LICENSE-2.0
* 
*   Unless required by applicable law or agreed to in writing, software
*   distributed under the License is distributed on an "AS IS" BASIS,
*   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*   See the License for the specific language governing permissions and
*   limitations under the License.
* 
* @Authors
*    之一Yo https://www.cnblogs.com/zhiyiYo/p/14800601.html
*    Tyler Parret True <mysteryworldgod@outlook.com><https://github.com/OwlHowlinMornSky>
*/
#include "Capture.h"

#define WIN32_LEAN_AND_MEAN TRUE
#include <Windows.h>

struct CaptureData {
	HDC m_screenDC;
	HDC m_compatibleDC;
	HBITMAP m_hBitmap;
	LPVOID m_screenshotData = nullptr;
};


using namespace cv;

Capture::Capture() {
	m_data = new CaptureData;

	double zoom = getZoom();
	m_width = static_cast<int>(round(GetSystemMetrics(SM_CXSCREEN) * zoom) + 0.5);
	m_height = static_cast<int>(GetSystemMetrics(SM_CYSCREEN) * zoom);
	m_data->m_screenshotData = new char[m_width * m_height * 4];
	memset(m_data->m_screenshotData, 0, m_width);

	// 获取屏幕 DC
	m_data->m_screenDC = GetDC(NULL);
	m_data->m_compatibleDC = CreateCompatibleDC(m_data->m_screenDC);

	// 创建位图
	m_data->m_hBitmap = CreateCompatibleBitmap(m_data->m_screenDC, m_width, m_height);
	SelectObject(m_data->m_compatibleDC, m_data->m_hBitmap);
	return;
}

Capture::~Capture() {
	delete m_data;
	return;
}

/* 获取整个屏幕的截图 */
Mat Capture::getScreenshot() {
	// 得到位图的数据
	BitBlt(m_data->m_compatibleDC, 0, 0, m_width, m_height, m_data->m_screenDC, 0, 0, SRCCOPY);
	GetBitmapBits(m_data->m_hBitmap, m_width * m_height * 4, m_data->m_screenshotData);

	// 创建图像
	Mat Capture(m_height, m_width, CV_8UC4, m_data->m_screenshotData);
	return Capture;
}

/** @brief 获取指定范围的屏幕截图
 * @param x 图像左上角的 X 坐标
 * @param y 图像左上角的 Y 坐标
 * @param width 图像宽度
 * @param height 图像高度
 */
Mat Capture::getScreenshot(int x, int y, int width, int height) {
	Mat Capture = getScreenshot();
	return Capture(cv::Rect(x, y, width, height));
}

/* 获取屏幕缩放值 */
double Capture::getZoom() {
	// 获取窗口当前显示的监视器
	HWND hWnd = GetDesktopWindow();
	HMONITOR hMonitor = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);

	// 获取监视器逻辑宽度
	MONITORINFOEX monitorInfo;
	monitorInfo.cbSize = sizeof(monitorInfo);
	GetMonitorInfo(hMonitor, &monitorInfo);
	int cxLogical = (monitorInfo.rcMonitor.right - monitorInfo.rcMonitor.left);

	// 获取监视器物理宽度
	DEVMODE dm;
	dm.dmSize = sizeof(dm);
	dm.dmDriverExtra = 0;
	EnumDisplaySettings(monitorInfo.szDevice, ENUM_CURRENT_SETTINGS, &dm);
	int cxPhysical = dm.dmPelsWidth;

	return cxPhysical * 1.0 / cxLogical;
}
