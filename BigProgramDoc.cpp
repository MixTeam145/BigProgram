
// BigProgramDoc.cpp : implementation of the CBigProgramDoc class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "BigProgram.h"
#endif

#include "BigProgramDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "Distribution.h"
#include "PEXP.h"
#include "PIS.h"
#include "Chi2Histogram.h"

#include "GenerateDlg.h"
#include "PlevelsDlg.h"
#include "SpeedtestDlg.h"

#include <chrono>

// CBigProgramDoc

IMPLEMENT_DYNCREATE(CBigProgramDoc, CDocument)

BEGIN_MESSAGE_MAP(CBigProgramDoc, CDocument)
	ON_COMMAND(ID_GENERATE, &CBigProgramDoc::OnGenerate)
	ON_COMMAND(ID_PVALUES, &CBigProgramDoc::OnPvalues)
	ON_COMMAND(ID_SPEEDTEST, &CBigProgramDoc::OnSpeedtest)
	ON_COMMAND(ID_BUTTON_GENERATE, &CBigProgramDoc::OnButtonGenerate)
	ON_COMMAND(ID_BUTTON_PLEVELS, &CBigProgramDoc::OnButtonPlevels)
	ON_COMMAND(ID_BUTTON_SPEEDTEST, &CBigProgramDoc::OnButtonSpeedtest)
END_MESSAGE_MAP()


// CBigProgramDoc construction/destruction

CBigProgramDoc::CBigProgramDoc() noexcept
	: s(nullptr)
	, g_lambda(1)
	, g_sample_size(100)
	, g_method(0)
	, p_lambda0(1)
	, p_lambda1(1)
	, p_sample_size(100)
	, p_npvals(10000)
	, p_method(0)
	, s_sample_size(100)
	, s_step(1)
	, current_image(image::NONE)
	, nstates(0)
	, observed(nullptr)
	, expected(nullptr)
	, plevels(nullptr)
	, ecdf_plevels(new double[20])
{
	simulation_time.first = new std::chrono::microseconds[10];
	simulation_time.second = new std::chrono::microseconds[10];
}

CBigProgramDoc::~CBigProgramDoc()
{
	if (s) delete s;
	if (observed) delete[] observed;
	if (expected) delete[] expected;
	if (plevels) delete[] plevels;
	delete[] ecdf_plevels;
	delete[] simulation_time.first;
	delete[] simulation_time.second;
}

BOOL CBigProgramDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CBigProgramDoc serialization

void CBigProgramDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CBigProgramDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CBigProgramDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CBigProgramDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl* pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CBigProgramDoc diagnostics

#ifdef _DEBUG
void CBigProgramDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CBigProgramDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CBigProgramDoc commands

void CBigProgramDoc::OnGenerate()
{
	CGenerateDlg dlg;
	dlg.m_lambda = g_lambda;
	dlg.m_sample_size = g_sample_size;
	dlg.m_method = g_method;
	if (dlg.DoModal() == IDOK) {
		PoissonDistribution distr(dlg.m_lambda);
		delete s;
		switch (dlg.m_method) {
		case 0:
			s = new PIS(distr, dlg.m_sample_size);
			break;
		case 1:
			s = new PEXP(distr, dlg.m_sample_size);
			break;
		}
		//s->Simulate();
		Chi2Histogram hist(s, distr);

		nstates = hist.GetNStates();

		delete[] observed;
		observed = new int[nstates];
		memcpy(observed, hist.GetObserved(), nstates * sizeof(int));

		delete[] expected;
		expected = new double[nstates];
		memcpy(expected, hist.GetExpected(), nstates * sizeof(double));

		current_image = image::GENERATE;
		g_lambda = dlg.m_lambda;
		g_sample_size = dlg.m_sample_size;
		g_method = dlg.m_method;
		UpdateAllViews(0);
	}
}

void CBigProgramDoc::OnPvalues()
{
	CPlevelsDlg dlg;
	dlg.m_lambda0 = p_lambda0;
	dlg.m_lambda1 = p_lambda1;
	dlg.m_sample_size = p_sample_size;
	dlg.m_npvals = p_npvals;
	dlg.m_method = p_method;
	if (dlg.DoModal() == IDOK) {
		PoissonDistribution d0(dlg.m_lambda0), d1(dlg.m_lambda1);
		delete s;
		switch (dlg.m_method) {
		case 0:
			s = new PIS(d1, dlg.m_sample_size);
			break;
		case 1:
			s = new PEXP(d1, dlg.m_sample_size);
			break;
		}
		Chi2Histogram hist(s, d0);
		delete[] plevels;
		plevels = new double[dlg.m_npvals];
		for (int i = 0; i < dlg.m_npvals; ++i) {
			s->Simulate();
			hist.SetData(s, d0);
			hist.Chi2();
			plevels[i] = hist.plevel;
		}
		memset(ecdf_plevels, 0, 20 * sizeof(double));
		for (int i = 0; i < dlg.m_npvals; ++i) {
			++ecdf_plevels[static_cast<int>(floor(plevels[i] * 20))];
		}
		ecdf_plevels[0] /= dlg.m_npvals;
		for (int i = 1; i < 20; ++i) {
			ecdf_plevels[i] = ecdf_plevels[i] / dlg.m_npvals + ecdf_plevels[i - 1];
		}
		current_image = image::PLEVELS;
		p_lambda0 = dlg.m_lambda0;
		p_lambda1 = dlg.m_lambda1;
		p_sample_size = dlg.m_sample_size;
		p_npvals = dlg.m_npvals;
		p_method = dlg.m_method;
		UpdateAllViews(0);
	}
}


void CBigProgramDoc::OnSpeedtest()
{
	CSpeedtestDlg dlg;
	dlg.m_step = s_step;
	dlg.m_sample_size = s_sample_size;
	if (dlg.DoModal() == IDOK) {
		PoissonDistribution distr(dlg.m_step);
		PIS s1(distr, dlg.m_sample_size);
		PEXP s2(distr, dlg.m_sample_size);
		double param{};
		for (int i = 0; i < 10; ++i) {
			param += dlg.m_step;
			s1.SetDistributionParameter(param);
			s2.SetDistributionParameter(param);
			auto begin = std::chrono::steady_clock::now();
			s1.Simulate();
			auto end = std::chrono::steady_clock::now();
			simulation_time.first[i] = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
			begin = std::chrono::steady_clock::now();
			s2.Simulate();
			end = std::chrono::steady_clock::now();
			simulation_time.second[i] = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
		}
		current_image = image::SPEEDTEST;
		s_step = dlg.m_step;
		s_sample_size = dlg.m_sample_size;
		UpdateAllViews(0);
	}
}


void CBigProgramDoc::OnButtonGenerate()
{
	PoissonDistribution distr(g_lambda);
	delete s;
	switch (g_method) {
	case 0:
		s = new PIS(distr, g_sample_size);
		break;
	case 1:
		s = new PEXP(distr, g_sample_size);
		break;
	}
	nstates = distr.GetNStates();
	//s->Simulate();
	Chi2Histogram hist(s, distr);

	delete[] observed;
	observed = new int[nstates];
	memcpy(observed, hist.GetObserved(), nstates * sizeof(int));

	delete[] expected;
	expected = new double[nstates];
	memcpy(expected, hist.GetExpected(), nstates * sizeof(double));

	current_image = image::GENERATE;
	UpdateAllViews(0);
}


void CBigProgramDoc::OnButtonPlevels()
{
	PoissonDistribution d0(p_lambda0), d1(p_lambda1);
	delete s;
	switch (p_method) {
	case 0:
		s = new PIS(d1, p_sample_size);
		break;
	case 1:
		s = new PEXP(d1, p_sample_size);
		break;
	}
	Chi2Histogram hist(s, d0);
	delete[] plevels;
	plevels = new double[p_npvals];
	for (int i = 0; i < p_npvals; ++i) {
		s->Simulate();
		hist.SetData(s, d0);
		hist.Chi2();
		plevels[i] = hist.plevel;
	}
	memset(ecdf_plevels, 0, 20 * sizeof(double));
	for (int i = 0; i < p_npvals; ++i) {
		++ecdf_plevels[static_cast<int>(floor(plevels[i] * 20))];
	}
	ecdf_plevels[0] /= p_npvals;
	for (int i = 1; i < 20; ++i) {
		ecdf_plevels[i] = ecdf_plevels[i] / p_npvals + ecdf_plevels[i - 1];
	}
	current_image = image::PLEVELS;
	UpdateAllViews(0);
}


void CBigProgramDoc::OnButtonSpeedtest()
{
	PoissonDistribution distr(s_step);
	PIS s1(distr, s_sample_size);
	PEXP s2(distr, s_sample_size);
	double param{};
	for (int i = 0; i < 10; ++i) {
		param += s_step;
		s1.SetDistributionParameter(param);
		s2.SetDistributionParameter(param);
		auto begin = std::chrono::steady_clock::now();
		s1.Simulate();
		auto end = std::chrono::steady_clock::now();
		simulation_time.first[i] = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
		begin = std::chrono::steady_clock::now();
		s2.Simulate();
		end = std::chrono::steady_clock::now();
		simulation_time.second[i] = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
	}
	current_image = image::SPEEDTEST;
	UpdateAllViews(0);
}
