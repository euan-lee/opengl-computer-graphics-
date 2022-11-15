#include <GL/glut.h>
#include <GL/glui.h>
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;
GLUI_Checkbox   *checkbox;
int   wireframe = 0;
int flag_checkbox = 0;

int Opencv_project1() {
	Mat image = Mat(400, 600, CV_8UC3, Scalar(0, 0, 0));
	rectangle(image, Point(100, 100), Point(500, 300), Scalar(0, 255, 0), 5);
	circle(image, Point(300, 200), 100, Scalar(255, 0, 0), 3);
	imshow("Image", image);
	waitKey(1);
	printf("Opencv_project1");
	return(0);
}
int Opencv_project2() {
	Mat img = imread("lenna.jpg");
	if (img.empty()) {
		printf("영상 입력 오류\n");
		return -1;
	}
			imshow("img", img);

		cout << "행의 수 = " << img.rows << endl;
		cout << "열의 수 = " << img.cols << endl;
		cout << "행렬의 크기 = " << img.size() << endl;
		cout << "전체 화소 개수 = " << img.total() << endl;
		cout << "한 화소 크기 = " << img.elemSize() << endl;
		cout << "타입 = " << img.type() << endl;
		cout << "채널 = " << img.channels() << endl;
		waitKey(0);
		return 0;
}

void control_cb(int control)
{
	if (control == 1) {
		printf("callback: %d\n", control);
		if (flag_checkbox == 1)flag_checkbox = 0;
		else if (flag_checkbox == 0)flag_checkbox = 1;
		printf("             checkbox: %d\n", checkbox->get_int_val());
		printf("             checkbox flag: %d\n", flag_checkbox);
		Opencv_project2();
	}
	if (control == 0) {
		printf("callback: %d\n", control);
		if (flag_checkbox == 1)flag_checkbox = 0;
		else if (flag_checkbox == 0)flag_checkbox = 1;
		printf("             checkbox2: %d\n", checkbox->get_int_val());
		printf("             checkbox flag: %d\n", flag_checkbox);
		Opencv_project1();
	}
}

int main()
{
	GLUI *glui = GLUI_Master.create_glui("GLUI", 0, 400, 50);
	GLUI_Master.set_glutIdleFunc(NULL);
	int main_window = glui->get_glut_window_id();
	new GLUI_StaticText(glui, "컴비전 과제");
	new GLUI_Separator(glui);
	checkbox = new GLUI_Checkbox(glui, "case1", &wireframe, 0, control_cb);
	checkbox = new GLUI_Checkbox(glui, "case2", &wireframe, 1, control_cb);
	glutMainLoop();
	return 0;
}
