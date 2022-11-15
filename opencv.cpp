#include <GL/glut.h>
#include <GL/glui.h>
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;
GLUI_Checkbox   *checkbox;
int   wireframe = 0;
int flag_checkbox = 0;
int ang = 0;
int click_cnt= 0;
Mat img, roi;
int x_Arr[3] = { 0,0,0 };
int y_Arr[3] = { 0, 0, 0 };
Mat Frame_image;
Mat lenna_image;

void Affine() {
	Mat src = imread("lenna.jpg", IMREAD_COLOR);
	Mat dst;
	Point2f srcTri[3], dstTri[3];
	Mat warp_mat(2, 3, CV_32FC1);
	srcTri[0] = Point2f(0, 0);
	srcTri[1] = Point2f(src.cols - 1.0f, 0);
	srcTri[2] = Point2f(0, src.rows - 1.0f);
	dstTri[0] = Point2f(src.cols*0.0f, src.rows*0.33f);
	dstTri[1] = Point2f(src.cols*0.85f, src.rows*0.25f);
	dstTri[2] = Point2f(src.cols*0.15f, src.rows*0.7f);
	warp_mat = getAffineTransform(srcTri, dstTri);
	warpAffine(src, dst, warp_mat, src.size());
	imshow("src", src);   imshow("dst", dst);
	waitKey(0);
	printf("affine");
}


void onMouse(int event, int x, int y, int flags, void* param) // 마우스 콜백 함수
{
	if (event == EVENT_LBUTTONDOWN) {
		if (click_cnt < 3) {
			x_Arr[click_cnt] = x;
			y_Arr[click_cnt] = y;
			printf("lenna_image.col:%d",lenna_image.cols);
			printf("%d,(%d,%d)\n",click_cnt, x_Arr[click_cnt], y_Arr[click_cnt]);
		}
		if (click_cnt == 3) {
			Affine();
		}
		click_cnt++;
	}
}

int Opencv_project1() {
	lenna_image = imread("lenna.jpg");
	Frame_image = imread("Frame1.jpg");
	imshow("image", lenna_image);
	imshow("image_frame", Frame_image);
	setMouseCallback("image", onMouse);
	return 0;
}

void Opencv_project2() {
}

void control_cb(int control)
{
	if (control == 0) {
		Opencv_project1();
	}
	if (control == 1) {
		Opencv_project2();
	}
}

int main()
{
	lenna_image = imread("lenna.jpg");
	Frame_image = imread("Frame1.jpg");
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
