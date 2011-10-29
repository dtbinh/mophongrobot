
//*OGLI* Khuôn mẫu các hàm thư viện OpenGL
#include <gl/gl.h>
#include <gl/glu.h>

//*OGLI* Các thư viện cần liên kết của OpenGL
#pragma comment(lib, "opengl32.lib") 
#pragma comment(lib, "glu32.lib") 

#pragma warning ( disable : 4566 )

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


/////////////////////////////////////////////////////////
// Bắt đầu lớp OpenGlInit
// Tác giả: Phan Mạnh Dần
// Ngày 06/10/2011
//
// Lớp khởi tạo môi trường đồ hoạ OpenGL cho MFC
// Gọi các hàm trong các hàm tương ứng của lớp View của ứng dụng
class OpenGlInit
{
public:
	// Hàm khởi tạo
	OpenGlInit();

	// Gọi trong hàm OnCreate(LPCREATESTRUCT lpCreateStruct)
	// Sửa nội dung tuỳ theo chương trình
	void OnCreate(HDC _hDC);
	
	// Gọi trong hàm OnSize(UINT nType, int cx, int cy)
	void OnSize(UINT nType, int cx, int cy);
	
	// Gọi trong hàm OnDestroy()
	void OnDestroy();

	// Gọi trong hàm OnDraw(CDC* /*pDC*/)
	// Sửa nội dung tuỳ theo chương trình
	void OnDraw();
	
	// Thêm trong hàm OnEraseBkgnd(CDC* /*pDC*/)
	// Thay thế nội dung bằng:
	// return TRUE;

	// Thêm trong hàm PreCreateWindow(CREATESTRUCT& cs)
	// Vào đầu hàm
	// cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	// Thêm trong hàm OnTimer UINT_PTR nIDEvent)
	// Vào cuối hàm
	// RedrawWindow();

protected:
	void SetupPixelFormat();

public:
	HDC     hDC;
	HGLRC   hRC;
	int timerID;		// ID của bộ đếm thời gian (timer)
	int timerElapse;	// Khoảng thời gian giữa các lần vẽ lại
};

OpenGlInit::OpenGlInit()
{
	hDC = NULL;
	hRC = NULL;
	timerID = 1; // Thay đổi nếu cần để tránh trùng với timer sẵn có
	timerElapse = 10;
}

// Set up pixel format for graphics initialization
void OpenGlInit::SetupPixelFormat()
{
    PIXELFORMATDESCRIPTOR pfd, *ppfd;
    int pixelformat;

    ppfd = &pfd;

    ppfd->nSize = sizeof(PIXELFORMATDESCRIPTOR);
    ppfd->nVersion = 1;
    ppfd->dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    ppfd->dwLayerMask = PFD_MAIN_PLANE;
    ppfd->iPixelType = PFD_TYPE_COLORINDEX;
    ppfd->cColorBits = 16;
    ppfd->cDepthBits = 16;
    ppfd->cAccumBits = 0;
    ppfd->cStencilBits = 0;

    pixelformat = ChoosePixelFormat(hDC, ppfd);
    SetPixelFormat(hDC, pixelformat, ppfd);
}

// Initialize OpenGL graphics
void OpenGlInit::OnCreate(HDC _hDC)
{
    hDC = _hDC;

    SetupPixelFormat();

    hRC = wglCreateContext(hDC);
    wglMakeCurrent(hDC, hRC);

    glClearColor(0, 0, 0, 0.5);
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);
}

// Resize graphics to fit window
void OpenGlInit::OnSize(UINT nType, int width, int height)
{
    // Get new window size
	GLfloat aspect;

    aspect = (GLfloat)width / height;

    // Adjust graphics to window size
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, aspect, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

// Draw frame
void OpenGlInit::OnDraw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set location in front of camera
    glLoadIdentity();

	static int angle = 0;

	glRotatef(float(angle++), 0.0f, 0.0f, 1.0f);
    glTranslated(0, 0, -10);

    // Draw a square
    glBegin(GL_QUADS);
		glColor3d(1, 0, 0);
		glVertex3d(-2, 2, 0);
		glVertex3d(2, 2, 0);
		glVertex3d(2, -2, 0);
		glVertex3d(-2, -2, 0);
    glEnd();

    // Show the new scene
    SwapBuffers(hDC);
}

void OpenGlInit::OnDestroy()
{
	::wglMakeCurrent(NULL,  NULL);

	if (hRC)
		::wglDeleteContext(hRC);
}

// Kết thúc lớp OpenGlInit
/////////////////////////////////////////////////////////

// Khai báo đầu tệp tin của lớp View
//*OGLI*
OpenGlInit openGiInit;
//*OGLI*
