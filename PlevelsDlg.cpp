// PlevelsDlg.cpp: файл реализации
//

#include "pch.h"
#include "BigProgram.h"
#include "afxdialogex.h"
#include "PlevelsDlg.h"


// Диалоговое окно CPlevelsDlg

IMPLEMENT_DYNAMIC(CPlevelsDlg, CDialogEx)

CPlevelsDlg::CPlevelsDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PLEVELS, pParent)
	, m_method(0)
	, m_lambda0(1)
	, m_lambda1(1)
	, m_sample_size(100)
	, m_npvals(10000)
{

}

CPlevelsDlg::~CPlevelsDlg()
{
}

void CPlevelsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, m_method);
	DDX_Text(pDX, IDC_H0, m_lambda0);
	DDX_Text(pDX, IDC_H1, m_lambda1);
	DDX_Text(pDX, IDC_SAMPLE_SIZE2, m_sample_size);
	DDX_Text(pDX, IDC_NPVALS, m_npvals);
}


BEGIN_MESSAGE_MAP(CPlevelsDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CPlevelsDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// Обработчики сообщений CPlevelsDlg


void CPlevelsDlg::OnBnClickedOk()
{
	UpdateData(1);
	if (m_lambda0 <= 0 || m_lambda1 <= 0)
		AfxMessageBox(L"Введите допустимое значение параметра (>0)!");
	else if (m_sample_size < 50)
		AfxMessageBox(L"Введите допустимый размер выборки (>=50)!");
	else if (m_npvals <= 0)
		AfxMessageBox(L"Введите допустимый размер массива pvalue (>0)!");
	else CDialogEx::OnOK();
}
