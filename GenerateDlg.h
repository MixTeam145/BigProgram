#pragma once
#include "afxdialogex.h"


// Диалоговое окно CGenerateDlg

class CGenerateDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGenerateDlg)

public:
	CGenerateDlg(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~CGenerateDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GENERATE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	int m_method;
	double m_lambda;
	int m_sample_size;
	afx_msg void OnBnClickedOk();
};
