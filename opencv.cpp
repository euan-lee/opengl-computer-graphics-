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
int x_Arr[4] = { 0,0,0, 0 };
int y_Arr[4] = { 0, 0, 0,0 };
Mat Frame_image;
Mat lenna_image;
Mat Fusion;
Mat Book;
Mat Undistorted;
void Affine() {
	Mat src = imread("lenna.jpg", IMREAD_COLOR);
	resize(src, src, Size(Frame_image.cols, Frame_image.rows));
	Mat dst;
	Point2f srcTri[3], dstTri[3];
	Mat warp_mat(2, 3, CV_32FC1);
	srcTri[0] = Point2f(0, 0);
	srcTri[1] = Point2f(src.cols - 1.0f, 0);
	srcTri[2] = Point2f(0, src.rows - 1.0f);
	dstTri[0] = Point2f(x_Arr[0], y_Arr[0]);
	dstTri[1] = Point2f(x_Arr[1], y_Arr[1]);
	dstTri[2] = Point2f(x_Arr[2], y_Arr[2]);
	warp_mat = getAffineTransform(srcTri, dstTri);
	warpAffine(src, dst, warp_mat, src.size());
	double alpha, beta;
	Fusion;
	alpha=0.4;
	beta = (1.0 - alpha);
	addWeighted(Frame_image, alpha, dst, beta, 0.0, Fusion);
	imshow("선형 합성", Fusion);
	printf("affine");
}
void Distort() {
	
	Point2f inputp[4], outputp[4];
	inputp[0] = Point2f(x_Arr[0], y_Arr[0]);    inputp[1] = Point2f(x_Arr[2], y_Arr[2]);
	inputp[2] = Point2f(x_Arr[1], y_Arr[1]);  inputp[3] = Point2f(x_Arr[3], y_Arr[3]);
	outputp[0] = Point2f(0, 0);  
	outputp[1] = Point2f(0, Book.rows);
	outputp[2] = Point2f(Book.cols, 0);
	outputp[3] = Point2f(Book.cols, Book.rows);
	Mat h = getPerspectiveTransform(inputp, outputp);
	warpPerspective(Book, Undistorted, h, Book.size());
	imshow("Warped Image", Undistorted);
}
int flag = 0;

void onMouse(int event, int x, int y, int flags, void* param) // 마우스 콜백 함수
{	
	if (event == EVENT_LBUTTONDOWN) {
		if (click_cnt < 3) {
			x_Arr[click_cnt] = x;
			y_Arr[click_cnt] = y;
		}
		printf("x:%d,y:%d", x_Arr[click_cnt], y_Arr[click_cnt]);
		if (click_cnt == 3&&flag==0) {
			Affine();
			click_cnt = -1;
		}
		
		click_cnt++;
	}
}

void onMouse2(int event, int x, int y, int flags, void* param) // 마우스 콜백 함수
{
	if (event == EVENT_LBUTTONDOWN) {
		if (click_cnt < 4) {
			x_Arr[click_cnt] = x;
			y_Arr[click_cnt] = y;
			printf("x:%d,y:%d", x_Arr[click_cnt], y_Arr[click_cnt]);
		}
		if (click_cnt == 4 ) {
			Distort();
		}
		click_cnt++;
	}
}

int Opencv_project1() {
	 x_Arr[4] = { 0,};
	 y_Arr[4] = { 0, };
	flag = 0;
	lenna_image = imread("lenna.jpg");
	Frame_image = imread("Frame1.jpg");
	imshow("image", Frame_image);
	setMouseCallback("image", onMouse);
	return 0;
}

int Opencv_project2() {
	x_Arr[4] = { 0, };
	y_Arr[4] = { 0, };
	flag = 1;
	 Book = imread("NoteBook.jpg");
	imshow("image", Book);
	setMouseCallback("image", onMouse2);
	if (img.empty())return -1;
}
void OpencvSave() {
	imwrite("C:\fusion_result1.jpg", Fusion);
	imwrite("C:\ undistorted_result1.jpg", Undistorted);
	printf("save");
}


void Exit() {
	exit(0);
	printf("exit");
}
void control_cb(int control)
{
	if (control == 0) {
		Opencv_project1();
	}
	if (control == 1) {
		Opencv_project2();
	}
	if (control == 2) {
		OpencvSave();
	}
	if (control == 3) {
		Exit();
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
	checkbox = new GLUI_Checkbox(glui, "assignment1", &wireframe, 0, control_cb);
	checkbox = new GLUI_Checkbox(glui, "assignment2", &wireframe, 1, control_cb);
	checkbox = new GLUI_Checkbox(glui, "save", &wireframe, 2, control_cb);
	checkbox = new GLUI_Checkbox(glui, "exit", &wireframe, 3, control_cb);
	glutMainLoop();
	return 0;
}
