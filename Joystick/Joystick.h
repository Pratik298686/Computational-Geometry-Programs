#ifndef JOYSTICK_H
#define JOYSTICK_H
//#include <glad/glad.h>
#include <GLFW/glfw3.h>

//analog input button values
#define GLFW_JOYSTICK_BTN_LEFT 0
#define GLFW_JOYSTICK_BTN_DOWN 1
#define GLFW_JOYSTICK_BTN_RIGHT 2
#define GLFW_JOYSTICK_BTN_UP 3
#define GLFW_JOYSTICK_SHOULDER_LEFT 4
#define GLFW_JOYSTICK_SHOULDER_RIGHT 5
#define GLFW_JOYSTICK_TRIGGER_LEFT 6
#define GLFW_JOYSTICK_TRIGGER_RIGHT 7
#define GLFW_JOYSTICK_SELECT 8
#define GLFW_JOYSTICK_START 9
#define GLFW_JOYSTICK_LEFT_STICK 10
#define GLFW_JOYSTICK_RIGHT_STICK 11
#define GLFW_JOYSTICK_HOME 12
#define GLFW_JOYSTICK_CLICK 13
#define GLFW_JOYSTICK_DPAD_UP 14
#define GLFW_JOYSTICK_DPAD_RIGHT 15
#define GLFW_JOYSTICK_DPAD_DOWN 16
#define GLFW_JOYSTICK_DPAD_LEFT 17

//axes
#define GLFW_JOYSTICK_AXES_LEFT_STICK_X 0
#define GLFW_JOYSTICK_AXES_LEFT_STICK_Y 1
#define GLFW_JOYSTICK_AXES_RIGHT_STICK_X 2
#define GLFW_JOYSTICK_AXES_LEFT_TRIGGER 3
#define GLFW_JOYSTICK_AXES_RIGHT_TRIGGER 4
#define GLFW_JOYSTICK_AXES_RIGHT_STICK_X 5


class Joystick
{
public:
	Joystick(int i);
	void update();
	float axesState(int axis);
	unsigned char buttonState(int button);

	int getAxesCount();
	int getButtonCount();

	bool isPresent();
	const char* getName();

	static int getId(int i);

private:
	int present;
	int id;
	const char* name;
	
	int axesCount;
	const float* axes;

	int buttonCount;
	const unsigned char* buttons;
};

#endif // !