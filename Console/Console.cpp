
#include <iostream>

#include "GetInstallPath.h"
#include "GetGamePath.h"
#include "GenshinStart.h"
#include "MyWhiteWindow.h"

#include "Capture.h"

namespace fs = std::filesystem;
using namespace std;


double getAvg(const cv::Mat& img) {
	cv::Mat gray;
	cv::cvtColor(img, gray, cv::COLOR_RGBA2GRAY);
	cv::Scalar scalar = cv::mean(gray);
	return scalar.val[0];
}


void func() {
	if (!ohms::genshinStart::MyRegisterClass()) {
		std::cout << "Error when initialization." << std::endl;
		return;
	}

	fs::path installPath;
	if (!ohms::genshinStart::GetInstallPath_Registry(installPath)) {
		std::cout << "Error when read the registry value." << std::endl;
		return;
	}
	cout << "Install path: " << installPath << endl;

	fs::path gamePath;
	fs::path gameName;
	if (!ohms::genshinStart::GetGamePath_Config(installPath, gamePath, gameName)) {
		std::cout << "Error when read the config of the launcher." << std::endl;
		return;
	}
	cout << "Game path: " << gamePath << endl;
	cout << "Game name: " << gameName << endl;

	Capture cap;
	while (true) {
		cv::Mat capture = cap.getScreenshot();
		if (getAvg(capture) >= 230.0) {
			break;
		}
		Sleep(20);
	}

	cout << "原神，启动！" << endl;

	if (ohms::genshinStart::YuanShen_QiDong(gamePath, gameName)) {
		cout << "Success" << endl;
	}
	else {
		cout << "Failed: 被绳之以法" << endl;
	}

	return;
}


int main(int argc, char* argv[]) {
	try {
		func();
	}
	catch (exception& ex) {
		cout << "Exception: " << ex.what() << endl;
	}
	catch (...) {
		cout << "Exception: Unknown exception." << endl;
	}
	system("pause");
	return 0;
}
