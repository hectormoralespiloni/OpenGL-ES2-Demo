# OpenGL ES2.0 Demo (April 2015)
----------------------------
_OpenGL ES 2.0 Demo for MaliSDK_

This demo uses MaliSDK to setup OGL ES, it uses basic Gouraud & Phong shaders and the geometry is procedurally built, like the sphere which is programmatically generated using the Icosphere method, i.e.: it starts with an Icosahedron and refines triangles until some user-defined recursion level (see picture below with 3 levels of refinement). 

Shadow Mapping was work in progress but I leave it unfinished since I made a porting to Android which has already the shadow mapping part implemented.

![](https://github.com/hectormoralespiloni/OpenGL-ES2-Demo/blob/master/openglES2Demo.png)

Requirements:
* Visual Studio 2012+
* Mali SDK (http://malideveloper.arm.com/develop-for-mali/sdks/opengl-es-sdk-for-linux). When you click the download link, you will se Windows versions available as well.
* In order to run the EXE you need to copy the .dlls to the executable folder and _"MALI_EMULATOR_COMPILER_MANAGER_PATH"_ environment variable (set when Mali SDK is installed).