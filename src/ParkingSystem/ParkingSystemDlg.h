
// ParkingSystemDlg.h : 头文件
//

#pragma once
#include "afxdtctl.h"
#include"DataBase.h"
#include "afxwin.h"

// CParkingSystemDlg 对话框
class CParkingSystemDlg : public CDialogEx
{
// 构造
public:
	CParkingSystemDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PARKINGSYSTEM_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOutputToPdfBtn();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButtonCarnum();
	afx_msg void OnBnClickedButtonCarmoney();
	CDateTimeCtrl m_Data_Start;
	CDateTimeCtrl m_Data_End;
	
};
