//-----------------------------------------------------------------------------
//@File:	main.cpp
//@Brief:	Main rendering loop is defined here. We create a window subsystem
//			a renderer and setup screen size.
//@Author:	Hector Morales Piloni
//@Date:	April 11, 2015
//-----------------------------------------------------------------------------
#define GLES_VERSION 2

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <EGL/egl.h>
#include <string>

#include "Scene.h"
#include "Timer.h"
#include "Platform.h"
#include "EGLRuntime.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

using namespace std;
using namespace MaliSDK;

int main(void)
{
	//Initialize platform subsystem and EGL
	Platform* platform = Platform::getInstance();
	platform->createWindow(WINDOW_WIDTH, WINDOW_HEIGHT);
	EGLRuntime::initializeEGL(EGLRuntime::OPENGLES2);
	eglMakeCurrent(EGLRuntime::display, EGLRuntime::surface, EGLRuntime::surface, EGLRuntime::context);

	Scene *scene = new Scene(WINDOW_WIDTH, WINDOW_HEIGHT);
	scene->Initialize();

	//Timer variable to calculate FPS
	Timer fpsTimer;
	fpsTimer.reset();
	DWORD wait = 0;

	bool end = false;
	while (!end)
	{		
		//End when something happens to the window
		if (platform->checkWindow() != Platform::WINDOW_IDLE)
			end = true;

		//This prints FPS every second
		float fFPS = fpsTimer.getFPS();		
		if (fpsTimer.isTimePassed(1.0f)){
			LOGI("FPS:\t%.1f\n", fFPS);			
		}

		scene->Draw();
		eglSwapBuffers(EGLRuntime::display, EGLRuntime::surface);
		
		//Calculate how much we have to wait to achieve 30FPS, 
		//getInterval() tells us how much time have passed 
		//since the last call (seems to be in centi-seconds)
		float interval = fpsTimer.getInterval() * 100;
		wait = (DWORD)(1000 / (interval * 30));
		Sleep(wait);
	}

	//Shutdown everything
	EGLRuntime::terminateEGL();
	platform->destroyWindow();
	delete platform;
	delete scene;

	return 0;
}