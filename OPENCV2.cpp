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
int width,height,Threshold_val;
void Camera(int x) {
	printf("x:%d\n",x);
};

void video(int x) {
	printf("video:%d\n", x);
};

void WidthCrt(int x) {
	
	printf("video width:%d\n", width);
};

void FileOpen(int x) {
	printf("FileOpen:\n");
}
void Stop(int x) {
	printf("stop:\n");
}

void HeightCrt(int x) {
	printf("video height:%d\n", height);

};
void Save(int x) {
	//imwrite("fusion_result1.jpg", Fusion);
	printf("save");
}

void ToGrayScale(int x) {
	printf("ToGrayScale");
}
void GaussianLow(int x) {
	printf("Gaussian Low!\n");
}
void HistogramEquation(int x) {
	printf("Gaussian Low!\n");
}
void None(int x) {
	printf("None!\n");
}
void Canny(int x) {
	printf("None!\n");
}
void Threshold(int x) {
	printf("Threshold_val:%d!\n", Threshold_val);
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
	GLUI_Button *btn12 = glui->add_button("video", 1, video);
	//btn12->set_name("Camera");
	//btn12->set_w(20);
	//btn12->set_h(20);
	GLUI_Button *btn1 = glui->add_button("FileOpen", 1, FileOpen);
	GLUI_Button *btn2 = glui->add_button("STOP", 1, Stop);
	GLUI_Panel *btn3 = glui->add_panel("",GLUI_PANEL_RAISED);
	spin_w = glui->add_spinner_to_panel(btn3, "W", GLUI_SPINNER_INT,&width,0,WidthCrt);
	spin_w->set_int_limits(10, 800, GLUI_LIMIT_CLAMP);
	spin_w->set_speed(0.0001);
	spin_h = glui->add_spinner_to_panel(btn3, "H", GLUI_SPINNER_INT, &height,0, HeightCrt);
	spin_h->set_int_limits(10, 800, GLUI_LIMIT_CLAMP);
	spin_h->set_speed(0.0001);
	GLUI_Checkbox *btn13 = glui->add_checkbox("save", &wireframe, 0, Save);

	GLUI_Checkbox *btn14 = glui->add_checkbox("ToGrayScale", &wireframe, 0, ToGrayScale);
	new GLUI_Separator(glui);
	GLUI_Checkbox *btn15 = glui->add_checkbox("Gaussian Low", &wireframe, 1, GaussianLow);
	GLUI_Checkbox *btn16 = glui->add_checkbox("Histogram Equation", &wireframe, 1, HistogramEquation);
	new GLUI_Separator(glui);
	GLUI_Checkbox *btn17 = glui->add_checkbox("Canny", &wireframe, 1, Canny);
	//GLUI_Checkbox *btn18 = glui->add_checkbox("Threshold", &wireframe, 1, Threshold);
	GLUI_Scrollbar  *btn18;
	btn18 = new GLUI_Scrollbar(glui, "Threshold : ", GLUI_SCROLL_HORIZONTAL, &Threshold_val, 0,Threshold);
	btn18->set_int_limits(0, 255);
	GLUI_Checkbox *btn19 = glui->add_checkbox("None", &wireframe, 1, None);
	GLUI_Checkbox *btn20 = glui->add_checkbox("Exit", &wireframe, 1, Exit);
	glutMainLoop();
	return 0;
}
