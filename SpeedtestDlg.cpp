// SpeedtestDlg.cpp: файл реализации
//

#include "pch.h"
#include "BigProgram.h"
#include "afxdialogex.h"
#include "SpeedtestDlg.h"


// Диалоговое окно CSpeedtestDlg

IMPLEMENT_DYNAMIC(CSpeedtestDlg, CDialogEx)

CSpeedtestDlg::CSpeedtestDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SPEEDTEST, pParent)
	, m_step(1)
	, m_sample_size(100)
{

}

CSpeedtestDlg::~CSpeedtestDlg()
{
}

void CSpeedtestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_step);
	DDX_Text(pDX, IDC_SAMPLE_SIZE3, m_sample_size);
}


BEGIN_MESSAGE_MAP(CSpeedtestDlg, CDialogEx)
END_MESSAGE_MAP()


// Обработчики сообщений CSpeedtestDlg
