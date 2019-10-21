// ShowInfo.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ParkingSystem.h"
#include "ShowInfo.h"
#include "afxdialogex.h"
#include <string>

// CShowInfo �Ի���

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


// CShowInfo ��Ϣ�������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//��ʼ�����ݿ�   
	MYSQL local_mysql;
	//��ʼ�����ݿ����  
	mysql_init(&local_mysql);

	//�������ݿ�����ʽ   

	mysql_options(&local_mysql, MYSQL_SET_CHARSET_NAME, "gbk");

	//�������ݿ�

	if (!mysql_real_connect(&local_mysql, "localhost", "root", "19970928.lin", "parking_system", 3306, NULL, 0))
	{
		AfxMessageBox(_T("connect to database failed!"));
		mysql_error(&local_mysql);
	}
	// �����ַ����飬�洢Ҫִ�е�SQL���

	char sql_select[100];

	//��Ҫִ�е�SQL������������
	int id=1;
	sprintf_s(sql_select, "SELECT *FROM car_info WHERE CarID='%d';", id);
	std::string p1,p2,t1,t2,m,n;
	//ִ�����
	if (mysql_query(&local_mysql, sql_select) == 0)//ִ�в�ѯ���ɹ���
	{
		MYSQL_RES* result = mysql_store_result(&local_mysql);
		MYSQL_ROW row;
		while (row = mysql_fetch_row(result))
		{
			//�������н��   
			p1 = row[5];
			p2 = row[6];
			t1 = row[2];
			t2 = row[3];
			m  = row[4];
			n = row[7];
		}
	}
	std::wstring stemp;
	//ͼƬһ
	CImage  image;
	int cx, cy;
	CRect   rect;
	//����·������ͼƬ 
	stemp = StoWs(p1);
	LPCTSTR str = stemp.c_str();
	image.Load(str);
	//��ȡͼƬ�Ŀ� ��
	cx = image.GetWidth();
	cy = image.GetHeight();

	CWnd *pWnd = NULL;
	pWnd = GetDlgItem(IDC_INPICTURE);//��ȡ�ؼ����
									  //��ȡPicture Control�ؼ��Ŀͻ���
	pWnd->GetClientRect(&rect);

	CDC *pDc = NULL;
	pDc = pWnd->GetDC();//��ȡpicture control��DC  
						//����ָ���豸�����е�λͼ����ģʽ
	int ModeOld = SetStretchBltMode(pDc->m_hDC, STRETCH_HALFTONE);
	//��Դ�����и���һ��λͼ��Ŀ����Σ���Ŀ���豸���õ�ģʽ����ͼ��������ѹ��
	image.StretchBlt(pDc->m_hDC, rect, SRCCOPY);
	SetStretchBltMode(pDc->m_hDC, ModeOld);
	ReleaseDC(pDc);

	//ͼƬ��
	CImage  image1;
	int cx1, cy1;
	CRect   rect1;
	//����·������ͼƬ  
	stemp = StoWs(p2);
	LPCTSTR str1 = stemp.c_str();
	image1.Load(str1);
	//��ȡͼƬ�Ŀ� ��
	cx1 = image1.GetWidth();
	cy1 = image1.GetHeight();

	CWnd *pWnd1 = NULL;
	pWnd1 = GetDlgItem(IDC_OUTPICTURE);//��ȡ�ؼ����
										//��ȡPicture Control�ؼ��Ŀͻ���
	pWnd1->GetClientRect(&rect1);

	CDC *pDc1 = NULL;
	pDc1 = pWnd1->GetDC();//��ȡpicture control��DC  
						  //����ָ���豸�����е�λͼ����ģʽ
	int ModeOld1 = SetStretchBltMode(pDc1->m_hDC, STRETCH_HALFTONE);
	//��Դ�����и���һ��λͼ��Ŀ����Σ���Ŀ���豸���õ�ģʽ����ͼ��������ѹ��
	image1.StretchBlt(pDc1->m_hDC, rect1, SRCCOPY);
	SetStretchBltMode(pDc1->m_hDC, ModeOld1);
	ReleaseDC(pDc1);

	//�����ı�
	stemp = StoWs(t1);
	str = stemp.c_str();
	GetDlgItem(IDC_INTIME)->SetWindowText(str);
	stemp = StoWs(t2);
	str = stemp.c_str();
	GetDlgItem(IDC_OUTTIME)->SetWindowText(str);
	stemp = StoWs(m);
	str = stemp.c_str();
	GetDlgItem(IDC_TOTAL)->SetWindowText(str);
	stemp = StoWs(n);
	str = stemp.c_str();
	GetDlgItem(IDC_TYPE)->SetWindowText(str);
	mysql_close(&local_mysql);
}
