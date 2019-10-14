#pragma once
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/highgui/highgui_c.h>
#include<opencv2\opencv.hpp>
#include<mysql.h>
using namespace cv;

// CShowInfo 对话框

class CShowInfo : public CDialogEx
{
	DECLARE_DYNAMIC(CShowInfo)

public:
	CShowInfo(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CShowInfo();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Show_Dio };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
