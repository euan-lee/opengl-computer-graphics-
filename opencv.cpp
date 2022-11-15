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
int Opencv_project1() {
	Mat Frame_image = imread("Frame1.jpg");
	Mat lenna_image = imread("lenna.jpg");
	double alpha, beta;
	alpha = 0.4;
	beta = (1.0 - alpha);
	resize(Frame_image, Frame_image, Size(300, 300));
	resize(lenna_image, lenna_image, Size(300, 300));
	Mat Fusion;
	addWeighted(Frame_image, alpha, lenna_image, beta, 0.0, Fusion);
	//Fusion = Frame_image + lenna_image;
	imshow("w", Fusion);
	Point2f srcTri[3], dstTri[3];
	Mat warp_mat(2, 3, CV_32FC1);
	Mat dst;
	srcTri[0] = Point2f(0, 0);
	srcTri[1] = Point2f(lenna_image.cols - 1.0f, 0);
	srcTri[2] = Point2f(0, lenna_image.rows - 1.0f);
	dstTri[0] = Point2f(lenna_image.cols*0.0f, lenna_image.rows*0.33f);
	dstTri[1] = Point2f(lenna_image.cols*0.85f, lenna_image.rows*0.25f);
	dstTri[2] = Point2f(lenna_image.cols*0.15f, lenna_image.rows*0.7f);
	warp_mat = getAffineTransform(srcTri, dstTri);
	warpAffine(lenna_image, dst, warp_mat, lenna_image.size());
	imshow("image", lenna_image);
	imshow("dst", dst);
	return 0;
}
void Opencv_project2() {
	Mat Frame_img = imread("Frame1.jpg");
	if (Frame_img.empty()) {
		printf("영상 입력 오류\n");

	}
	imshow("img", Frame_img);
	waitKey(0);

}

void control_cb(int control)
{
	if (control == 1) {
		printf("callback: %d\n", control);
		if (flag_checkbox == 1)flag_checkbox = 0;
		else if (flag_checkbox == 0)flag_checkbox = 1;
		printf("             checkbox: %d\n", checkbox->get_int_val());
		printf("             checkbox flag: %d\n", flag_checkbox);
		ang = 1;
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
	while (1) {
		if (ang == 1)break;
	}
	printf("end of system!!");
	return 0;
}
