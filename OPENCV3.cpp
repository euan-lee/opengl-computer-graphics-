#include <GL/glut.h>
#include <GL/glui.h>
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;
GLUI_Checkbox   *checkbox;
GLUI_RadioGroup *radio;
GLUI_Button *btn12;
GLUI_Button *btn1;
int   wireframe = 0;
int flag_checkbox = 0;
int ang = 0;
int click_cnt= 0;
int Threshold_val;
int width = 20;
int height = 20;
int   obj = 0;
int vid_camera_flag = 0;
int ToGrayScale_flag = 0;
int GaussianLow_flag = 0;
int Histogram_flag = 0;
int Canny_flag = 0;
int Threshold_flag = 0;
int save_flag = 0;
double fps = 30.0;
int fourcc = VideoWriter::fourcc('W', 'M', 'V', '1'); // 동영상 사용시 저장할 코덱을 지정
VideoWriter outputVideo; // Videowirter  객체 생성
Mat img;
Mat img_cloned;

void Camera(int x) {
	width = 200;
	height = 200;
	vid_camera_flag=1;
	btn1->set_name("camera running");
	printf(" Camera\n");
	VideoCapture cap(0);
	VideoWriter  save;

	if (!cap.isOpened())
	{
		printf("Can't open the camera");
		return ;
	}



	if (save_flag == 1) {
		outputVideo.open("output2.WMV", fourcc, fps, Size( height, width), true);
	}
	while (1)
	{
		cap >> img;
		img_cloned = img.clone();
		if (vid_camera_flag == 0) {
			cap.release();
			outputVideo.release();
			break;
		}
		if (ToGrayScale_flag == 1) {//img_cloned을 회색으로
			cvtColor(img_cloned, img_cloned, COLOR_BGR2GRAY);
		}
		if (Histogram_flag == 1 && GaussianLow_flag == 1) {
			printf("Histogram ,GaussianLow 둘중 하나만 골라주세요!\n");
			return;
		}

		if (GaussianLow_flag == 1 && Histogram_flag == 0) {
			GaussianBlur(img_cloned, img_cloned, Size(7, 7), 0);
		}

		if (Histogram_flag == 1&& GaussianLow_flag == 0) {
			equalizeHist(img_cloned, img_cloned);
		}

		if (Canny_flag == 1 && Threshold_flag == 1) {
			printf("Canny_flag ,Threshold_flag둘중 하나만 골라주세요!\n");
			return;
		}
		
		if (Canny_flag == 1&& Threshold_flag == 0) {//Canny
			Canny(img_cloned, img_cloned, 100, 150);
		}
		if (Threshold_flag == 1&& Canny_flag == 0) {//Threshold
			threshold(img_cloned,img_cloned, Threshold_val, 255, THRESH_BINARY);
		}
		img_cloned.resize(height, width);
		imshow("camera img", img);
		imshow("camera img2", img_cloned);
		if (save_flag == 1) {
			outputVideo.write(img_cloned);
		}
		if (waitKey(10) == 27)
			break;
	}
	return;
};

void video(int x) {

	printf("video\n");
	
	};

void WidthCrt(int x) {
	
	printf("video width:%d\n", width);
};

void FileOpen(int x) {

	printf("FileOpen:\n");
}
void Stop(int x) {
	btn1->set_name("FileOpen");
	printf("stop:\n");
	vid_camera_flag = 0;
}

void HeightCrt(int x) {
	printf("video height:%d\n", height);

};

void Save(int x) {
	if (save_flag == 0) {

		save_flag = 1;
	}
	else {
		save_flag = 0;
	}
	btn1->set_name("FileOpen");
	//imwrite("fusion_result1.jpg", Fusion);
	printf("save");
}

void ToGrayScale(int x) {
	if (ToGrayScale_flag ==0) {

		ToGrayScale_flag = 1;
	}
	else {
		ToGrayScale_flag = 0;
	}
	printf("ToGrayScale");
}
void GaussianLow(int x) {
	if (GaussianLow_flag == 0) {

		GaussianLow_flag = 1;
	}
	else {
		GaussianLow_flag = 0;
	}
	printf("Gaussian Low!\n");
}
void HistogramEquation(int x) {
	if (Histogram_flag == 0) {

		Histogram_flag = 1;
	}
	else {
		Histogram_flag = 0;
	}
	printf("Histogram_flag!\n");
}
void None(int x) {
	ToGrayScale_flag = 0;
	GaussianLow_flag = 0;
	Histogram_flag = 0;
	Canny_flag = 0;
	Threshold_flag = 0;
	printf("None!\n");
}
void Canny(int x) {
	if (Canny_flag == 0) {

		Canny_flag = 1;
	}
	else {
		Canny_flag = 0;
	}
	printf("Canny_flag!\n");
}
void Threshold(int x) {
	if (Threshold_flag == 0) {

		Threshold_flag = 1;
	}
	else {
		Threshold_flag = 0;
	}
}

void Threshold_view(int x) {
	printf("Threshold_val:%d\n",Threshold_val);
}

void Exit(int x) {
	printf("exit!\n");
	exit(0);
}

int main()
{
	GLUI_Spinner* spin_w;
	GLUI_Spinner* spin_h;
	GLUI *glui = GLUI_Master.create_glui("GLUI", 0, 400, 200);
	GLUI_Master.set_glutIdleFunc(NULL);
	int main_window = glui->get_glut_window_id();
	new GLUI_StaticText(glui, "컴비전 과제");
	new GLUI_Separator(glui);
	GLUI_Button *btn11 = glui->add_button("Camera", 1, Camera);
	btn12 = glui->add_button("video", 1, video);
	btn1 = glui->add_button("FileOpen", 1, FileOpen);
	GLUI_Button *btn2 = glui->add_button("STOP", 1, Stop);
	GLUI_Panel *btn3 = glui->add_panel("",GLUI_PANEL_RAISED);
	spin_w = glui->add_spinner_to_panel(btn3, "W", GLUI_SPINNER_INT,&width, NULL,WidthCrt);
	spin_w->set_int_limits(10, 800, GLUI_LIMIT_CLAMP);
	spin_w->set_speed(0.0001);
	spin_h = glui->add_spinner_to_panel(btn3, "H", GLUI_SPINNER_INT, &height, NULL, HeightCrt);
	spin_h->set_int_limits(10, 600, GLUI_LIMIT_CLAMP);
	spin_h->set_speed(0.01);
	GLUI_Checkbox *btn13 = glui->add_checkbox("save", &wireframe, 0, Save);
	btn13->set_alignment(GLUI_ALIGN_RIGHT);
	GLUI_Checkbox *btn14 = glui->add_checkbox("ToGrayScale", &wireframe, 0, ToGrayScale);
	new GLUI_Separator(glui);
	GLUI_Checkbox *btn15 = glui->add_checkbox("Gaussian Low", &wireframe, 1, GaussianLow);
	GLUI_Checkbox *btn16 = glui->add_checkbox("Histogram Equation", &wireframe, 1, HistogramEquation);
	new GLUI_Separator(glui);
	GLUI_Checkbox *btn17 = glui->add_checkbox("Canny", &wireframe, 1, Canny);
	GLUI_Scrollbar  *btn18;
	GLUI_Checkbox *btn21 = glui->add_checkbox("Threshold", &wireframe, 1, Threshold);
	btn18 = new GLUI_Scrollbar(glui, "Threshold\n ", GLUI_SCROLL_HORIZONTAL, &Threshold_val, 0,Threshold_view);
	btn18->set_int_limits(0, 255);
	GLUI_Checkbox *btn19 = glui->add_checkbox("None", &wireframe, 1, None);
	GLUI_Button *btn20 = glui->add_button("Exit", 1, Exit);
	glutMainLoop();
	return 0;
}
