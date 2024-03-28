
// BigProgramView.cpp : implementation of the CBigProgramView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "BigProgram.h"
#endif

#include "BigProgramDoc.h"
#include "BigProgramView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CBigProgramView

IMPLEMENT_DYNCREATE(CBigProgramView, CView)

BEGIN_MESSAGE_MAP(CBigProgramView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CBigProgramView construction/destruction

CBigProgramView::CBigProgramView() noexcept
{
	// TODO: add construction code here

}

void CBigProgramView::DrawGenerate()
{
	CClientDC* pDC = new CClientDC(this);
	CBigProgramDoc* pDoc = GetDocument();

	pDoc->SetTitle(L"Histograms");

	CRect rect;
	GetClientRect(&rect);
	int width = rect.Width(),
		height = rect.Height();

	CPen pen;
	pen.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	CPen* pOldPen = (CPen*)pDC->SelectObject(&pen);
	pDC->MoveTo(width / 10 - 5, 2 * height / 15 + 5);
	pDC->LineTo(width / 10, 2 * height / 15);
	pDC->MoveTo(width / 10 + 5, 2 * height / 15 + 5);
	pDC->LineTo(width / 10, 2 * height / 15);

	pDC->LineTo(width / 10, 9. * height / 10);
	pDC->LineTo(14 * width / 15, 9 * height / 10);
	pDC->LineTo(14 * width / 15 - 5, 9 * height / 10 + 5);
	pDC->MoveTo(14 * width / 15, 9 * height / 10);
	pDC->LineTo(14 * width / 15 - 5, 9 * height / 10 - 5);
	pDC->SelectObject(pOldPen);
	pen.DeleteObject();

	pDC->SetViewportOrg(width / 10, 9 * height / 10);

	const int* freq_empiric = pDoc->GetObserved();
	const double* freq_theor = pDoc->GetExpected();
	int n = pDoc->GetNStates();
	int max = 0, min = pDoc->GetSampleSize();
	for (int i = 0; i < n; ++i) {
		if (freq_empiric[i] > max) max = freq_empiric[i];
		if (freq_empiric[i] < min) min = freq_empiric[i];
	}

	CFont font;
	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));
	lf.lfHeight = 25;
	lf.lfWeight = 800;
	font.CreateFontIndirect(&lf);
	CFont* def_font = pDC->SelectObject(&font);

	CString str;
	str.Format(L"%d", max);
	pDC->TextOut(-20 - str.GetLength() * 10, -2 * height / 3 - 12, str);
	pDC->MoveTo(-5, -2 * height / 3);
	pDC->LineTo(5, -2 * height / 3);
	str.Format(L"%d", min);
	pDC->TextOut(-20 - str.GetLength() * 10, -2 * height / 3. * static_cast<double>(min) / max - 12, str);
	pDC->MoveTo(-5, -2 * height / 3. * static_cast<double>(min) / max);
	pDC->LineTo(5, -2 * height / 3. * static_cast<double>(min) / max);

	CBrush brush1, brush2;
	brush1.CreateSolidBrush(RGB(0, 0, 255));
	brush2.CreateSolidBrush(RGB(255, 0, 255));
	CBrush* pOldBrush = pDC->SelectObject(&brush1);
	for (int i = 0; i < n; ++i) {
		str.Format(L"%d", i);
		pDC->SelectObject(&brush2);
		pDC->Rectangle(12. * width * i / (15 * n) + width / (10. * n), -2 * height / 3. * static_cast<double>(freq_theor[i]) / max, 12 * width * (i + 1.) / (15 * n), 0);
		pDC->SelectObject(&brush1);
		pDC->Rectangle(12. * width * i / (15 * n) + width / (5. * n), -2 * height / 3. * static_cast<double>(freq_empiric[i]) / max, 12 * width * (i + 1.) / (15 * n) - width / (10. * n), 0);
		pDC->TextOut((12 * width * (2 * i + 1.) / (15 * n) + width / (10. * n)) / 2 - 6 * str.GetLength(), 10, str);
	}

	pDC->SelectObject(&brush2);
	pDC->Rectangle(6 * width / 10, -2 * height / 3, 6 * width / 10 + 35, -2 * height / 3 + 35);
	pDC->TextOut(6 * width / 10 + 35, -2 * height / 3, L" - theoretical");
	pDC->SelectObject(&brush1);
	pDC->Rectangle(6 * width / 10, -2 * height / 3 + 45, 6 * width / 10 + 35, -2 * height / 3 + 75);
	pDC->TextOut(6 * width / 10 + 35, -2 * height / 3 + 45, L" - empiric");

	pDC->SelectObject(pOldBrush);
	pDC->SelectObject(def_font);

	delete pDC;
}

void CBigProgramView::DrawPlevels()
{
	CClientDC* pDC = new CClientDC(this);
	CBigProgramDoc* pDoc = GetDocument();


	if (fabs(pDoc->GetLambda0() - pDoc->GetLambda1()) < 1e-14)
		pDoc->SetTitle(L"Type I error");
	else
		pDoc->SetTitle(L"Power");


	CRect rect;
	GetClientRect(&rect);
	int width = rect.Width(),
		height = rect.Height();

	CPen pen;
	pen.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	CPen* pOldPen = (CPen*)pDC->SelectObject(&pen);
	pDC->MoveTo(width / 10 - 5, 2 * height / 15 + 5);
	pDC->LineTo(width / 10, 2 * height / 15);
	pDC->MoveTo(width / 10 + 5, 2 * height / 15 + 5);
	pDC->LineTo(width / 10, 2 * height / 15);

	pDC->LineTo(width / 10, 9. * height / 10);
	pDC->LineTo(14 * width / 15, 9 * height / 10);
	pDC->LineTo(14 * width / 15 - 5, 9 * height / 10 + 5);
	pDC->MoveTo(14 * width / 15, 9 * height / 10);
	pDC->LineTo(14 * width / 15 - 5, 9 * height / 10 - 5);
	pDC->SelectObject(pOldPen);
	pen.DeleteObject();

	pDC->SetViewportOrg(width / 10, 9 * height / 10);

	CFont font;
	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));
	lf.lfHeight = 25;
	lf.lfWeight = 800;
	font.CreateFontIndirect(&lf);
	CFont* def_font = pDC->SelectObject(&font);

	pDC->TextOut(-10, 5, L"0");
	CString str;
	for (int i = 2; i <= 20; i += 2) {
		str.Format(L"%.1f", i / 20.);
		pDC->TextOut(width * i / 25 - 15, 10, str);
		pDC->MoveTo(width * i / 25, 5);
		pDC->LineTo(width * i / 25, -5);
	}
	for (int i = 4; i <= 20; i += 4) {
		str.Format(L"%.2f", i / 20.);
		pDC->TextOut(-60, -height * i / 28 - 12, str);
		pDC->MoveTo(-5, -height * i / 28);
		pDC->LineTo(5, -height * i / 28);
	}

	pen.CreatePen(PS_SOLID, 2, RGB(220, 220, 220));
	pOldPen = (CPen*)pDC->SelectObject(&pen);
	pDC->MoveTo(0, 0);
	for (int i = 1; i <= 20; ++i) {
		pDC->LineTo(width * i / 25, -height * i / 28);
	}
	pDC->SelectObject(pOldPen);
	pen.DeleteObject();

	pen.CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	pOldPen = (CPen*)pDC->SelectObject(&pen);
	pDC->MoveTo(0, 0);
	const double* ecdf = pDoc->GetECDF();
	for (int i = 0; i < 20; ++i) {
		pDC->LineTo(width * (i + 1) / 25., -5. * height * (ecdf[i]) / 7);
	}

	pDC->SelectObject(pOldPen);

	delete pDC;
}


void CBigProgramView::DrawSpeedTest()
{
	CClientDC* pDC = new CClientDC(this);
	CBigProgramDoc* pDoc = GetDocument();

	pDoc->SetTitle(L"Speedtest");

	CRect rect;
	GetClientRect(&rect);
	int width = rect.Width(),
		height = rect.Height();

	CPen pen;
	pen.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	CPen* pOldPen = (CPen*)pDC->SelectObject(&pen);
	pDC->MoveTo(width / 10 - 5, 2 * height / 15 + 5);
	pDC->LineTo(width / 10, 2 * height / 15);
	pDC->MoveTo(width / 10 + 5, 2 * height / 15 + 5);
	pDC->LineTo(width / 10, 2 * height / 15);

	pDC->LineTo(width / 10, 9. * height / 10);
	pDC->LineTo(14 * width / 15, 9 * height / 10);
	pDC->LineTo(14 * width / 15 - 5, 9 * height / 10 + 5);
	pDC->MoveTo(14 * width / 15, 9 * height / 10);
	pDC->LineTo(14 * width / 15 - 5, 9 * height / 10 - 5);
	pDC->SelectObject(pOldPen);
	pen.DeleteObject();

	pDC->SetViewportOrg(width / 10, 9 * height / 10);

	CFont font;
	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));
	lf.lfHeight = 25;
	lf.lfWeight = 800;
	font.CreateFontIndirect(&lf);
	CFont* def_font = pDC->SelectObject(&font);

	pDC->TextOut(-30, -12 * height / 15 - 10, L"time, s");
	pDC->TextOut(8 * width / 10 + 20, -40, L"lambda");

	const std::pair<const std::chrono::microseconds*, const std::chrono::microseconds*> st = pDoc->GetTime();
	long long maxt{};
	for (int i = 0; i < 10; ++i) {
		if (st.second[i].count() > maxt) maxt = st.second[i].count();
	}

	long long m = 1;
	while (true) {
		if (m > maxt) break;
		m *= 10;
	}

	CString str;
	for (int i = 1; i <= 5; ++i) {
		str.Format(L"%g", static_cast<double>(m) / 5e+6 * i);
		pDC->TextOut(-20 - str.GetLength() * 10, -2 * height * i / 15 - 12, str);
		pDC->MoveTo(-5, -2 * height * i / 15);
		pDC->LineTo(5, -2 * height * i / 15);
	}

	for (int i = 1; i <= 10; ++i) {
		str.Format(L"%g", i * pDoc->GetStep());
		pDC->MoveTo(2 * width * i / 25, 5);
		pDC->LineTo(2 * width * i / 25, -5);
		pDC->TextOut(2 * width * i / 25 - 5, 10, str);
	}

	pen.CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	pOldPen = (CPen*)pDC->SelectObject(&pen);
	pDC->MoveTo(6 * width / 10, -2 * height / 3);
	pDC->LineTo(6 * width / 10 + 35, -2 * height / 3);
	pDC->TextOut(6 * width / 10 + 35, -2 * height / 3 - 15, L" - Poisson Inverse Sequential");
	pDC->MoveTo(2 * width / 25, -2 * height * st.first[0].count() / (m * 3));
	for (int i = 1; i < 10; ++i) {
		pDC->LineTo(2 * width * (i + 1) / 25, -2 * height * st.first[i].count() / (m * 3));
	}
	pDC->SelectObject(pOldPen);
	pen.DeleteObject();

	pen.CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
	pOldPen = (CPen*)pDC->SelectObject(&pen);
	pDC->MoveTo(6 * width / 10, -2 * height / 3 + 45);
	pDC->LineTo(6 * width / 10 + 35, -2 * height / 3 + 45);
	pDC->TextOut(6 * width / 10 + 35, -2 * height / 3 + 30, L" - Poisson Exponential");
	pDC->MoveTo(2 * width / 25, -2 * height * st.second[0].count() / (m * 3));
	for (int i = 1; i < 10; ++i) {
		pDC->LineTo(2 * width * (i + 1) / 25, -2 * height * st.second[i].count() / (m * 3));
	}
	pDC->SelectObject(pOldPen);

	delete pDC;
}


CBigProgramView::~CBigProgramView()
{
}

BOOL CBigProgramView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CBigProgramView drawing

void CBigProgramView::OnDraw(CDC* pDC)
{
	CBigProgramDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->SetTitle(L"BigProgram");

	switch (pDoc->current_image)
	{
	case CBigProgramDoc::image::GENERATE:
		DrawGenerate();
		break;
	case CBigProgramDoc::image::PLEVELS:
		DrawPlevels();
		break;
	case CBigProgramDoc::image::SPEEDTEST:
		DrawSpeedTest();
		break;
	}
}

void CBigProgramView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CBigProgramView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CBigProgramView diagnostics

#ifdef _DEBUG
void CBigProgramView::AssertValid() const
{
	CView::AssertValid();
}

void CBigProgramView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBigProgramDoc* CBigProgramView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBigProgramDoc)));
	return (CBigProgramDoc*)m_pDocument;
}
#endif //_DEBUG


// CBigProgramView message handlers
