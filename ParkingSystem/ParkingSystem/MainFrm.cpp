
// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "ParkingSystem.h"

#include "MainFrm.h"

using namespace pdflib;
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND(ID_32771, &CMainFrame::OnOutputToPDF)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	// TODO: 在此添加成员初始化代码
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("未能创建工具栏\n");
		return -1;      // 未能创建
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: 如果不需要可停靠工具栏，则删除这三行
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);


	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return TRUE;
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序



void CMainFrame::OnOutputToPDF()
{
	try {
		/*  This is where the data files are. Adjust as necessary. */
		const wstring searchpath = L"../data";

		PDFlib p;
		const wstring imagefile = L"nesrin.jpg";
		int image;

		wostringstream optlist;

		//  This means we must check return values of load_font() etc.
		p.set_option(L"errorpolicy=return");

		// Set the search path for fonts and PDF files
		optlist.str(L"");
		optlist << L"searchpath={{" << searchpath << L"}}";
		p.set_option(optlist.str());

		if (p.begin_document(L"starter_basic.pdf", L"") == -1) 
		{
			wcerr << L"Error: " << p.get_errmsg() << endl;
			return;
		}

		p.set_info(L"Creator", L"PDFlib starter sample");
		p.set_info(L"Title", L"starter_basic");

		/* We load the image before the first page, and use it
		* on all pages
		*/
		image = p.load_image(L"auto", imagefile, L"");

		if (image == -1) 
		{
			wcerr << L"Error: " << p.get_errmsg() << endl;
			return;
		}

		/*  Page 1 */
		p.begin_page_ext(0, 0, L"width=a4.width height=a4.height");
		/* use NotoSerif-Regular font and unicode encoding for placing the text
		* and demonstrate various options how to pass the unicode text to PDFlib
		*/
		optlist.str(L"");
		optlist.str(L"fontname={NotoSerif-Regular} encoding=unicode embedding fontsize=24");

		/* using plain 7 bit ASCII text */
		p.fit_textline(L"en: Hello!", 50, 700, optlist.str());
		/* using unicode escapes */
		p.fit_textline(L"gr: \u0393\u03B5\u03B9\u03AC!", 50, 650, optlist.str());
		p.fit_textline(L"ru: \u041F\u0440\u0438\u0432\u0435\u0442!", 50, 600, optlist.str());
		/* using PDFlib's character references */
		optlist << optlist.str() << L" charref=true";
		p.fit_textline(L"es: &#xA1;Hola!", 50, 550, optlist.str());


		p.fit_image(image, 0.0, 0.0, L"scale=0.25");

		p.end_page_ext(L"");

		/*  Page 2 */
		p.begin_page_ext(0, 0, L"width=a4.width height=a4.height");

		/*  red rectangle */
		p.setcolor(L"fill", L"rgb", 1.0, 0.0, 0.0, 0.0);
		p.rect(200, 200, 250, 150);
		p.fill();

		/*  blue circle */
		p.setcolor(L"fill", L"rgb", 0.0, 0.0, 1.0, 0.0);
		p.arc(400, 600, 100, 0, 360);
		p.fill();

		/*  thick gray line */
		p.setcolor(L"stroke", L"gray", 0.5, 0.0, 0.0, 0.0);
		p.setlinewidth(10);
		p.moveto(100, 500);
		p.lineto(300, 700);
		p.stroke();

		/*  Using the same image handle means the data will be copied
		to the PDF only once, which saves space.
		*/
		p.fit_image(image, 150.0, 25.0, L"scale=0.25");
		p.end_page_ext(L"");

		/*  Page 3 */
		p.begin_page_ext(0, 0, L"width=a4.width height=a4.height");

		/*  Fit the image to a box of predefined size (without distortion) */
		optlist.str(L"boxsize={400 400} position={center} fitmethod=meet");

		p.fit_image(image, 100, 200, optlist.str());

		p.end_page_ext(L"");

		p.close_image(image);
		p.end_document(L"");
	}

	catch (PDFlib::Exception &ex)
	{
		//wcerr << L"PDFlib exception occurred:" << endl
		//	<< L"[" << ex.get_errnum() << L"] " << ex.get_apiname()
		//	<< L": " << ex.get_errmsg() << endl;
		return;
	}
	catch (exception &e) 
	{
		//cerr << "C++ exception occurred: " << e.what() << endl;
		return;
	}
	catch (...) 
	{
		//cerr << "Generic C++ exception occurred!" << endl;
		return;
	}

}
