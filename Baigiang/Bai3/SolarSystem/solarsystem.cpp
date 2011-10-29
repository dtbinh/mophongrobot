//-----------------------------------------------------------------------------
//           Name: ogl_transforms.cpp
//         Author: Kevin Harris
//  Last Modified: 02/01/05
//    Description: Demonstrates how to use translation, rotation, and scaling 
//                 matrices to create a simulated solar system.
//
//   Control Keys: F1    - Speed up rotations
//                 F2    - Slow down rotations
//                 Space - Toggle orbiting on/off
//-----------------------------------------------------------------------------

#define STRICT
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <mmsystem.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "geometry.h"
#include "resource.h"
#include "matrix4x4f.h"
#include "vector3f.h"

//-----------------------------------------------------------------------------
// GLOBALS
//-----------------------------------------------------------------------------
HWND  g_hWnd = NULL;
HDC   g_hDC  = NULL;
HGLRC g_hRC  = NULL;

float  g_fElpasedTime;
double g_dCurrentTime;
double g_dLastTime;

float g_fSpeedmodifier = 1.0f;
bool  g_bOrbitOn = true;

//-----------------------------------------------------------------------------
// Name: InitGraphics()
// Desc: 
//-----------------------------------------------------------------------------
void InitGraphics( void )
{
	GLuint PixelFormat;

	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.nSize      = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion   = 1;
	pfd.dwFlags    = PFD_DRAW_TO_WINDOW |PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 16;
	pfd.cDepthBits = 16;

	g_hDC = GetDC( g_hWnd );
	PixelFormat = ChoosePixelFormat( g_hDC, &pfd );
	SetPixelFormat( g_hDC, PixelFormat, &pfd);
	g_hRC = wglCreateContext( g_hDC );
	wglMakeCurrent( g_hDC, g_hRC );

	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	glEnable(GL_DEPTH_TEST);

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective( 45.0f, 640.0f / 480.0f, 0.1f, 100.0f);
}

//-----------------------------------------------------------------------------
// Name: ResizeGraphics()
// Desc: Resize graphics to fit window
//-----------------------------------------------------------------------------
void ResizeGraphics()
{
	// Get new window size
	RECT rect;
	GetClientRect(g_hWnd, &rect);

	int nWidth  = rect.right; 
	int nHeight = rect.bottom;
	glViewport(0, 0, nWidth, nHeight);

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective( 45.0, (GLdouble)nWidth / (GLdouble)nHeight, 0.1, 100.0);
}

//-----------------------------------------------------------------------------
// Name: ShutDownGraphics()
// Desc: 
//-----------------------------------------------------------------------------
void ShutDownGraphics( void )   
{
	if( g_hRC != NULL )
	{
		wglMakeCurrent( NULL, NULL );
		wglDeleteContext( g_hRC );
		g_hRC = NULL;
	}

	if( g_hDC != NULL )
	{
		ReleaseDC( g_hWnd, g_hDC );
		g_hDC = NULL;
	}
}


//-----------------------------------------------------------------------------
// Name: DrawGraphics()
// Desc: Render a solar system using a matrix utility class and glMultMatrixf.
//
// Note:
//
// Each call to a transformation command (i.e. glScalef, glRotatef, 
// glTranslatef, glMultMatrixf etc...) multiplies a new 4×4 matrix M by the 
// current model-view matrix C to yield CM. When done issuing transformation 
// commands, vertices v are then multiplied by the current model-view matrix 
// CM to yield CMv. This process means that the last transformation command 
// called in your program is actually the first one applied to your model 
// vertices - therefore we have to specify the matrices in the reverse order 
// of how we would normally see them applied in math books.
//
//-----------------------------------------------------------------------------
void DrawGraphics( void )
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	//
	// Have the view matrix move the view move us to a good vantage point so 
	// we can see the Sun sitting at the origin while the Earth orbits it.
	//

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	gluLookAt( 0.0, 2.0, 25.0,  // Camera position
		0.0, 0.0, 0.0,   // Look-at point
		0.0, 1.0, 0.0 ); // Up vector

	//
	// Cache rotational positions between frames...
	//

	static float fSunSpin    = 0.0f;  // Góc quay của mặt trời, ban đầu bằng 0  
	static float fEarthSpin  = 0.0f;  // Góc tự quay của trái đất
	static float fEarthOrbit = 0.0f; // Góc quay quanh mặt trời của trái đất
	static float fMoonSpin   = 0.0f; // Góc tự quay của mặt trăng
	static float fMoonOrbit  = 0.0f; // Góc quay của mặt trăng quanh TĐ

	if( g_bOrbitOn == true )
	{
		fSunSpin -= g_fSpeedmodifier * (g_fElpasedTime * 10.0f);

		fEarthSpin  -= g_fSpeedmodifier * (g_fElpasedTime * 100.0f);
		fEarthOrbit -= g_fSpeedmodifier * (g_fElpasedTime * 20.0f);

		fMoonSpin  -= g_fSpeedmodifier * (g_fElpasedTime * 50.0f);
		fMoonOrbit -= g_fSpeedmodifier * (g_fElpasedTime * 200.0f);
	}

	//
	// The Sun is easy because the mesh for it is initially created centered  
	// at origin. All we have to do is spin it by rotating it about the Y axis
	// and scale it by 5.0f.
	//

	matrix4x4f mSunMatrix;

	mSunMatrix.rotate_y( fSunSpin );  // 1. Spin it on its axis.

	glPushMatrix();
	{
		glMultMatrixf( mSunMatrix.m );

		glColor4f( 1.0f, 1.0f, 0.0f, 1.0f );
		renderWireSphere( 1.0f, 20, 20 );
	}
	glPopMatrix();

	//
	// The Earth is a little more complicated since it needs to spin as well 
	// as orbit the Sun. This can be done by combining three transformations 
	// together.
	//

	matrix4x4f mEarthTranslationToOrbit;
	matrix4x4f mEarthSpinRotation;
	matrix4x4f mEarthOrbitRotation;
	matrix4x4f mEarthMatrix;

	mEarthSpinRotation.rotate_y( fEarthSpin );
	mEarthTranslationToOrbit.translate( vector3f(0.0f, 0.0f, -12.0f) );
	mEarthOrbitRotation.rotate_y( fEarthOrbit );

	// Now, concatenate them together...

	mEarthMatrix = mEarthOrbitRotation *      // 3. and rotate it again to make it orbit the origin (or the Sun).
		mEarthTranslationToOrbit * // 2. Then translate it away from the origin (where the Sun's at)
		mEarthSpinRotation;        // 1. Spin the Earth on its own axis.

	glPushMatrix();
	{
		glMultMatrixf( mEarthMatrix.m );

		glColor4f( 0.0f, 0.0f, 1.0f, 1.0f );
		renderWireSphere( 1.0f, 10, 10 );
	}
	glPopMatrix();

	//
	// The Moon is the hardest to understand since it needs to not only spin on
	// its own axis and orbit the Earth, but needs to follow the Earth, 
	// which is orbiting the Sun.
	//
	// This can be done by combining five transformations together with the last
	// two being borrowed from the Earth's transformation.
	//

	matrix4x4f mMoonTranslationToOrbit;
	matrix4x4f mMoonSpinRotation;
	matrix4x4f mMoonOrbitRotation;
	matrix4x4f mMoonMatrix;

	mMoonSpinRotation.rotate_y( fMoonSpin );
	mMoonOrbitRotation.rotate_y( fMoonOrbit );
	mMoonTranslationToOrbit.translate( vector3f(0.0f, 0.0f, -2.0f) );

	//
	// The key to understanding the first three transforms is to pretend that 
	// the Earth is located at the origin. We know it's not, but if we pretend 
	// that it is, we can set up the Moon just like the we did the Earth since 
	// the Moon orbits the Earth just like the Earth orbits the Sun.
	//
	// Once the Moon's transforms are set up we simply reuse the Earth's 
	// translation and rotation matrix, which placed it in orbit, to offset  
	// the Moon out to where it should be... following the Earth.
	// 

	// Now, concatenate them together...

	mMoonMatrix = mEarthOrbitRotation *      // 5. and move with it by matching its orbit of the Earth.
		mEarthTranslationToOrbit * // 4. Now, translate out to where the Earth is really at

		mMoonOrbitRotation *       // 3. and rotate it again to make it orbit the origin (or the pretend Earth).
		mMoonTranslationToOrbit *  // 2. Then translate it away from the origin (pretending that the Earth is there)
		mMoonSpinRotation;         // 1. Spin the Moon on its own axis.

	glPushMatrix();
	{
		glMultMatrixf( mMoonMatrix.m );

		glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
		renderWireSphere( 0.5f, 8, 8 );
	}
	glPopMatrix();

	SwapBuffers( g_hDC );
}
//


//-----------------------------------------------------------------------------
// Name: WindowProc()
// Desc: The window's message handler
//-----------------------------------------------------------------------------
LRESULT CALLBACK WindowProc( HWND   hWnd, 
							UINT   msg, 
							WPARAM wParam, 
							LPARAM lParam )
{
	switch( msg )
	{
	case WM_KEYDOWN:
		{
			switch( wParam )
			{
			case VK_ESCAPE:
				PostQuitMessage(0);
				break;

			case VK_SPACE:
				g_bOrbitOn = !g_bOrbitOn;
				break;

			case VK_F1:
				++g_fSpeedmodifier;
				break;

			case VK_F2:
				--g_fSpeedmodifier;
				break;
			}
		}
		break;

	case WM_SIZE:
		ResizeGraphics();
		break;

	case WM_CLOSE:
		{
			PostQuitMessage(0); 
		}

	case WM_DESTROY:
		{
			PostQuitMessage(0);
		}
		break;

	default:
		{
			return DefWindowProc( hWnd, msg, wParam, lParam );
		}
		break;
	}

	return 0;
}

//-----------------------------------------------------------------------------
// Name: WinMain()
// Desc: The application's entry point
//-----------------------------------------------------------------------------
int WINAPI WinMain( HINSTANCE hInstance,
				   HINSTANCE hPrevInstance,
				   LPSTR     lpCmdLine,
				   int       nCmdShow )
{
	WNDCLASSEX winClass; 
	MSG        uMsg;

	memset(&uMsg,0,sizeof(uMsg));

	winClass.lpszClassName = "MY_WINDOWS_CLASS";
	winClass.cbSize        = sizeof(WNDCLASSEX);
	winClass.style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	winClass.lpfnWndProc   = WindowProc;
	winClass.hInstance     = hInstance;
	winClass.hIcon         = LoadIcon(hInstance, (LPCTSTR)IDI_OPENGL_ICON);
	winClass.hIconSm       = LoadIcon(hInstance, (LPCTSTR)IDI_OPENGL_ICON);
	winClass.hCursor       = LoadCursor(NULL, IDC_ARROW);
	winClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	winClass.lpszMenuName  = NULL;
	winClass.cbClsExtra    = 0;
	winClass.cbWndExtra    = 0;

	if( !RegisterClassEx(&winClass) )
		return E_FAIL;

	g_hWnd = CreateWindowEx( NULL, "MY_WINDOWS_CLASS", 
		"OpenGL - Transforms",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		0, 0, 640, 480, NULL, NULL, hInstance, NULL );

	if( g_hWnd == NULL )
		return E_FAIL;

	ShowWindow( g_hWnd, nCmdShow );
	UpdateWindow( g_hWnd );

	InitGraphics();

	while( uMsg.message != WM_QUIT )
	{
		if( PeekMessage( &uMsg, NULL, 0, 0, PM_REMOVE ) )
		{
			TranslateMessage( &uMsg );
			DispatchMessage( &uMsg );
		}
		else
		{
			g_dCurrentTime = timeGetTime();
			g_fElpasedTime = (float)((g_dCurrentTime - g_dLastTime) * 0.001);
			g_dLastTime    = g_dCurrentTime;

			DrawGraphics();
		}
	}

	ShutDownGraphics();

	UnregisterClass( "MY_WINDOWS_CLASS", winClass.hInstance );

	return uMsg.wParam;
}

/*
//-----------------------------------------------------------------------------
// Name: DrawGraphics()
// Desc: Render a solar system using glScalef, glRotatef, and glTranslatef.
//
// Note:
//
// Each call to a transformation command (i.e. glScalef, glRotatef, 
// glTranslatef, glMultMatrixf etc...) multiplies a new 4×4 matrix M by the 
// current model-view matrix C to yield CM. When done issuing transformation 
// commands, vertices v are then multiplied by the current model-view matrix 
// CM to yield CMv. This process means that the last transformation command 
// called in your program is actually the first one applied to your model 
// vertices - therefore we have to specify the matrices in the reverse order 
// of how we would normally see them applied in math books.
//
//-----------------------------------------------------------------------------
void DrawGraphics( void )
{
glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

//
// Have the view matrix move the view move us to a good vantage point so 
// we can see the Sun sitting at the origin while the Earth orbits it.
//

glMatrixMode( GL_MODELVIEW );
glLoadIdentity();

gluLookAt( 0.0, 2.0, 25.0,  // Camera position
0.0, 0.0, 0.0,   // Look-at point
0.0, 1.0, 0.0 ); // Up vector

//
// Cache rotational positions between frames...
//

static float fSunSpin    = 0.0f;    
static float fEarthSpin  = 0.0f;    
static float fEarthOrbit = 0.0f;
static float fMoonSpin   = 0.0f;
static float fMoonOrbit  = 0.0f;

if( g_bOrbitOn == true )
{
fSunSpin -= g_fSpeedmodifier * (g_fElpasedTime * 10.0f);

fEarthSpin  -= g_fSpeedmodifier * (g_fElpasedTime * 100.0f);
fEarthOrbit -= g_fSpeedmodifier * (g_fElpasedTime * 20.0f);

fMoonSpin  -= g_fSpeedmodifier * (g_fElpasedTime * 50.0f);
fMoonOrbit -= g_fSpeedmodifier * (g_fElpasedTime * 200.0f);
}

//
// The Sun is easy because the mesh for it is initially created centered  
// at origin. All we have to do is spin it by rotating it about the Y axis
// and scale it by 5.0f.
//

glPushMatrix();
{
glRotatef( fSunSpin, 0.0f, 1.0f, 0.0f ); // 2. and then spin it on its axis.
glScalef( 5.0f, 5.0f, 5.0f );            // 1. Uniformly scale the Sun up in size

glColor4f( 1.0f, 1.0f, 0.0f, 1.0f );
renderSolidSphere( 1.0f, 20, 20 );
}
glPopMatrix();

//
// The Earth is a little more complicated since it needs to spin as well 
// as orbit the Sun. This can be done by combining three transformations 
// together.
//

glPushMatrix();
{
glRotatef( fEarthOrbit, 0.0f, 1.0f, 0.0f ); // 3. and rotate it again to make it orbit the origin (or the Sun).
glTranslatef( 0.0f, 0.0f, -12.0f );         // 2. Then translate it away from the origin (where the Sun's at)
glRotatef( fEarthSpin, 0.0f, 1.0f, 0.0f );  // 1. Spin the Earth on its own axis.

glColor4f( 0.0f, 0.0f, 1.0f, 1.0f );
renderSolidSphere( 1.0f, 10, 10 );
}
glPopMatrix();

//
// The Moon is the hardest to understand since it needs to not only spin on
// its own axis and orbit the Earth, but needs to follow the Earth, 
// which is orbiting the Sun.
//
// This can be done by combining five transformations together with the last
// two being borrowed from the Earth's transformation.
//

glPushMatrix();
{
glRotatef( fEarthOrbit, 0.0f, 1.0f, 0.0f ); // 5. and move with it by matching its orbit of the Earth.
glTranslatef( 0.0f, 0.0f, -12.0f );         // 4. Now, translate out to where the Earth is really at

glRotatef( fMoonOrbit, 0.0f, 1.0f, 0.0f );  // 3. and rotate it again to make it orbit the origin (or the pretend Earth).
glTranslatef( 0.0f, 0.0f, -2.0f );          // 2. Then translate it away from the origin (pretending that the Earth is there)
glRotatef( fMoonSpin, 0.0f, 1.0f, 0.0f );   // 1. Spin the Moon on its own axis.

glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
renderSolidSphere( 0.5f, 8, 8 );
}
glPopMatrix();

SwapBuffers( g_hDC );
}
*/


