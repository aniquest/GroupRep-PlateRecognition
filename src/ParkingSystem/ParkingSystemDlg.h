
// ParkingSystemDlg.h : ͷ�ļ�
//

#pragma once
#include "afxdtctl.h"
#include"DataBase.h"
#include "afxwin.h"

// CParkingSystemDlg �Ի���
class CParkingSystemDlg : public CDialogEx
{
// ����
public:
	CParkingSystemDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PARKINGSYSTEM_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton2();
	//CDateTimeCtrl m_Data_Start;
	//CDateTimeCtrl m_Data_End;	
public:
	int id = 1;
};
