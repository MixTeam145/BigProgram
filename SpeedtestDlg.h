#pragma once
#include "afxdialogex.h"


// Диалоговое окно CSpeedtestDlg

class CSpeedtestDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSpeedtestDlg)

public:
	CSpeedtestDlg(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~CSpeedtestDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SPEEDTEST };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	double m_step;
	int m_sample_size;
};
