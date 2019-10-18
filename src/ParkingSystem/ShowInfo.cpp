// ShowInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "ParkingSystem.h"
#include "ShowInfo.h"
#include "afxdialogex.h"
#include <string>

// CShowInfo 对话框

IMPLEMENT_DYNAMIC(CShowInfo, CDialogEx)

CShowInfo::CShowInfo(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_Show_Dio, pParent)
{

}

CShowInfo::~CShowInfo()
{
}

void CShowInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CShowInfo, CDialogEx)
	ON_BN_CLICKED(IDOK, &CShowInfo::OnBnClickedOk)
END_MESSAGE_MAP()


// CShowInfo 消息处理程序
std::wstring StoWs(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}

void CShowInfo::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//初始化数据库   
	MYSQL local_mysql;
	//初始化数据库对象  
	mysql_init(&local_mysql);

	//设置数据库编码格式   

	mysql_options(&local_mysql, MYSQL_SET_CHARSET_NAME, "gbk");

	//连接数据库

	if (!mysql_real_connect(&local_mysql, "localhost", "root", "19970928.lin", "parking_system", 3306, NULL, 0))
	{
		AfxMessageBox(_T("connect to database failed!"));
		mysql_error(&local_mysql);
	}
	// 定义字符数组，存储要执行的SQL语句

	char sql_select[100];

	//将要执行的SQL语句放入数组中
	int id=1;
	sprintf_s(sql_select, "SELECT *FROM car_info WHERE CarID='%d';", id);
	std::string p1,p2,t1,t2,m;
	//执行语句
	if (mysql_query(&local_mysql, sql_select) == 0)//执行查询语句成功！
	{
		MYSQL_RES* result = mysql_store_result(&local_mysql);
		MYSQL_ROW row;
		while (row = mysql_fetch_row(result))
		{
			//处理逐行结果   
			p1 = row[6];
			p2 = row[7];
			t1 = row[2];
			t2 = row[3];
			m  = row[5];
		}
	}
	std::wstring stemp;
	//图片一
	CImage  image;
	int cx, cy;
	CRect   rect;
	//根据路径载入图片 
	stemp = StoWs(p1);
	LPCTSTR str = stemp.c_str();
	image.Load(str);
	//获取图片的宽 高
	cx = image.GetWidth();
	cy = image.GetHeight();

	CWnd *pWnd = NULL;
	pWnd = GetDlgItem(IDC_INPICTURE);//获取控件句柄
									  //获取Picture Control控件的客户区
	pWnd->GetClientRect(&rect);

	CDC *pDc = NULL;
	pDc = pWnd->GetDC();//获取picture control的DC  
						//设置指定设备环境中的位图拉伸模式
	int ModeOld = SetStretchBltMode(pDc->m_hDC, STRETCH_HALFTONE);
	//从源矩形中复制一个位图到目标矩形，按目标设备设置的模式进行图像的拉伸或压缩
	image.StretchBlt(pDc->m_hDC, rect, SRCCOPY);
	SetStretchBltMode(pDc->m_hDC, ModeOld);
	ReleaseDC(pDc);

	//图片二
	CImage  image1;
	int cx1, cy1;
	CRect   rect1;
	//根据路径载入图片  
	stemp = StoWs(p2);
	LPCTSTR str1 = stemp.c_str();
	image1.Load(str1);
	//获取图片的宽 高
	cx1 = image1.GetWidth();
	cy1 = image1.GetHeight();

	CWnd *pWnd1 = NULL;
	pWnd1 = GetDlgItem(IDC_OUTPICTURE);//获取控件句柄
										//获取Picture Control控件的客户区
	pWnd1->GetClientRect(&rect1);

	CDC *pDc1 = NULL;
	pDc1 = pWnd1->GetDC();//获取picture control的DC  
						  //设置指定设备环境中的位图拉伸模式
	int ModeOld1 = SetStretchBltMode(pDc1->m_hDC, STRETCH_HALFTONE);
	//从源矩形中复制一个位图到目标矩形，按目标设备设置的模式进行图像的拉伸或压缩
	image1.StretchBlt(pDc1->m_hDC, rect1, SRCCOPY);
	SetStretchBltMode(pDc1->m_hDC, ModeOld1);
	ReleaseDC(pDc1);

	//设置文本
	stemp = StoWs(t1);
	str = stemp.c_str();
	GetDlgItem(IDC_INTIME)->SetWindowText(str);
	stemp = StoWs(t2);
	str = stemp.c_str();
	GetDlgItem(IDC_OUTTIME)->SetWindowText(str);
	stemp = StoWs(m);
	str = stemp.c_str();
	GetDlgItem(IDC_TOTAL)->SetWindowText(str);
	mysql_close(&local_mysql);
}
