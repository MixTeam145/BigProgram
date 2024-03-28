// GenerateDlg.cpp: файл реализации
//

#include "pch.h"
#include "BigProgram.h"
#include "afxdialogex.h"
#include "GenerateDlg.h"


// Диалоговое окно CGenerateDlg

IMPLEMENT_DYNAMIC(CGenerateDlg, CDialogEx)

CGenerateDlg::CGenerateDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GENERATE, pParent)
	, m_method(0)
	, m_lambda(1)
	, m_sample_size(100)
{

}

CGenerateDlg::~CGenerateDlg()
{
}

void CGenerateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, m_method);
	DDX_Text(pDX, IDC_LAMBDA, m_lambda);
	DDX_Text(pDX, IDC_SAMPLE_SIZE, m_sample_size);
}


BEGIN_MESSAGE_MAP(CGenerateDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CGenerateDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// Обработчики сообщений CGenerateDlg


void CGenerateDlg::OnBnClickedOk()
{
	UpdateData(1);
	if (m_lambda <= 0)
		AfxMessageBox(L"Введите допустимое значение параметра (>0)!");
	else if (m_sample_size <= 0)
		AfxMessageBox(L"Введите допустимый размер выборки (>0)!");
	else CDialogEx::OnOK();
}
