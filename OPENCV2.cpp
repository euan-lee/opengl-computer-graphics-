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

void onMouse(int event, int x, int y, int flags, void* param) // 마우스 콜백 함수
{	
	if (event == EVENT_LBUTTONDOWN) {
		if (click_cnt < 3) {
			//x_Arr[click_cnt] = x;
			//y_Arr[click_cnt] = y;
		}

		if (click_cnt == 3) {
			//Affine();
			click_cnt = -1;
		}
		
		click_cnt++;
	}
}


void OpencvSave() {
	printf("save");
}

void Exit() {
	exit(0);
}
void control_cb(int control)
{
	if (control == 0) {
		//Opencv_project1();
	}
	if (control == 1) {
	//	Opencv_project2();
	}
	if (control == 2) {
		OpencvSave();
	}
	if (control == 3) {
		Exit();
	}
	if (control == 4) {
		//OpencvSave2();
	}
}

int main()
{
	GLUI *glui = GLUI_Master.create_glui("GLUI", 0, 400, 200);
	GLUI_Master.set_glutIdleFunc(NULL);
	int main_window = glui->get_glut_window_id();
	new GLUI_StaticText(glui, "컴비전 과제");
	new GLUI_Separator(glui);

	GLUI_Panel* drawPanel = glui->add_panel("");
	glui->add_checkbox_to_panel(drawPanel, "Video File", &wireframe, 3, control_cb);
	glui->add_checkbox_to_panel(drawPanel, "Camera", &wireframe, 3, control_cb);
	glui->add_button("FileOpen", 0, (GLUI_Update_CB)exit);
	glui->add_button("Stop", 0, (GLUI_Update_CB)exit);
	GLUI_Panel* drawPanel2 = glui->add_panel("");
	glui->add_checkbox_to_panel(drawPanel2, "width", &wireframe);
	new GLUI_Separator(glui);
	glui->add_rollout_to_panel(drawPanel2, "width1", 1)
	glui->add_spinner_to_panel("height",GLUI_Spinner_INT,3,control_cb);
	//spinner->set_int_limits(3, 60);
	//spinner->set_alignment(GLUI_ALIGN_RIGHT);
	checkbox = new GLUI_Checkbox(glui, "save", &wireframe, 3, control_cb);
	checkbox = new GLUI_Checkbox(glui, "ToGrayScale", &wireframe, 3, control_cb);
	new GLUI_Separator(glui);
	checkbox = new GLUI_Checkbox(glui, "Gaussian Low", &wireframe, 3, control_cb);
	checkbox = new GLUI_Checkbox(glui, "Histogram Equation", &wireframe, 3, control_cb);
	new GLUI_Separator(glui);
	checkbox = new GLUI_Checkbox(glui, "Canny", &wireframe, 3, control_cb);
	checkbox = new GLUI_Checkbox(glui, "Threshold", &wireframe, 3, control_cb);
	checkbox = new GLUI_Checkbox(glui, "None", &wireframe, 3, control_cb);
	//스크롤 바 추가
	glui->add_button("Quit", 0, (GLUI_Update_CB)exit);
	glutMainLoop();
	return 0;
}
