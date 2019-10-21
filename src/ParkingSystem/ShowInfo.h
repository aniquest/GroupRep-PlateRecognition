#pragma once
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/highgui/highgui_c.h>
#include<opencv2\opencv.hpp>
#include<mysql.h>
#include "afxwin.h"
#include "CPictureEx.h"
using namespace cv;

// CShowInfo �Ի���

class CShowInfo : public CDialogEx
{
	DECLARE_DYNAMIC(CShowInfo)

public:
	CShowInfo(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CShowInfo();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Show_Dio };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CPictureEx gif1;
	CPictureEx gif2;
	afx_msg void OnBnClickedUp();
	afx_msg void OnBnClickedDown();
};
