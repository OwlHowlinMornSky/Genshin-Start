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
*   之一Yo https://www.cnblogs.com/zhiyiYo/p/14800601.html
*   Tyler Parret True <mysteryworldgod@outlook.com><https://github.com/OwlHowlinMornSky>
*/
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
