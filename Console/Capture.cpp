
// https://www.cnblogs.com/zhiyiYo/p/14800601.html

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

	// ��ȡ��Ļ DC
	m_data->m_screenDC = GetDC(NULL);
	m_data->m_compatibleDC = CreateCompatibleDC(m_data->m_screenDC);

	// ����λͼ
	m_data->m_hBitmap = CreateCompatibleBitmap(m_data->m_screenDC, m_width, m_height);
	SelectObject(m_data->m_compatibleDC, m_data->m_hBitmap);
	return;
}

Capture::~Capture() {
	delete m_data;
	return;
}

/* ��ȡ������Ļ�Ľ�ͼ */
Mat Capture::getScreenshot() {
	// �õ�λͼ������
	BitBlt(m_data->m_compatibleDC, 0, 0, m_width, m_height, m_data->m_screenDC, 0, 0, SRCCOPY);
	GetBitmapBits(m_data->m_hBitmap, m_width * m_height * 4, m_data->m_screenshotData);

	// ����ͼ��
	Mat Capture(m_height, m_width, CV_8UC4, m_data->m_screenshotData);
	return Capture;
}

/** @brief ��ȡָ����Χ����Ļ��ͼ
 * @param x ͼ�����Ͻǵ� X ����
 * @param y ͼ�����Ͻǵ� Y ����
 * @param width ͼ����
 * @param height ͼ��߶�
 */
Mat Capture::getScreenshot(int x, int y, int width, int height) {
	Mat Capture = getScreenshot();
	return Capture(cv::Rect(x, y, width, height));
}

/* ��ȡ��Ļ����ֵ */
double Capture::getZoom() {
	// ��ȡ���ڵ�ǰ��ʾ�ļ�����
	HWND hWnd = GetDesktopWindow();
	HMONITOR hMonitor = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);

	// ��ȡ�������߼����
	MONITORINFOEX monitorInfo;
	monitorInfo.cbSize = sizeof(monitorInfo);
	GetMonitorInfo(hMonitor, &monitorInfo);
	int cxLogical = (monitorInfo.rcMonitor.right - monitorInfo.rcMonitor.left);

	// ��ȡ������������
	DEVMODE dm;
	dm.dmSize = sizeof(dm);
	dm.dmDriverExtra = 0;
	EnumDisplaySettings(monitorInfo.szDevice, ENUM_CURRENT_SETTINGS, &dm);
	int cxPhysical = dm.dmPelsWidth;

	return cxPhysical * 1.0 / cxLogical;
}
