#pragma once
#include "afxdialogex.h"


// Диалоговое окно CPlevelsDlg

class CPlevelsDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPlevelsDlg)

public:
	CPlevelsDlg(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~CPlevelsDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PLEVELS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	int m_method;
	double m_lambda0;
	double m_lambda1;
	int m_sample_size;
	int m_npvals;
	afx_msg void OnBnClickedOk();
};
