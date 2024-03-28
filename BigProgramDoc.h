
// BigProgramDoc.h : interface of the CBigProgramDoc class
//


#pragma once
#include "PoissonSampleGenerator.h"

class CBigProgramDoc : public CDocument
{
protected: // create from serialization only
	CBigProgramDoc() noexcept;
	DECLARE_DYNCREATE(CBigProgramDoc)

// Attributes
public:
	enum class image
	{
		NONE,
		GENERATE,
		PLEVELS,
		SPEEDTEST,
	} current_image;
// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CBigProgramDoc();
	int GetNStates() const { return nstates; }
	const int* GetObserved() const { return observed; }
	const double* GetExpected() const { return expected; }
	int GetSampleSize() const { return g_sample_size; }
	double GetLambda0() const { return p_lambda0; }
	double GetLambda1() const { return p_lambda1; }
	double* GetECDF() const { return ecdf_plevels; }
	const std::pair<const std::chrono::microseconds*, const std::chrono::microseconds*> GetTime() const { return simulation_time; }
	double GetStep() const { return s_step; }
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS

private:
	PoissonSampleGenerator* s;
	
	double g_lambda;
	int g_sample_size;
	int g_method;

	double p_lambda0;
	double p_lambda1;
	int p_sample_size;
	int p_method;
	int p_npvals;

	double s_step;
	int s_sample_size;

	int nstates;
	int* observed;
	double* expected;
	double* plevels;
	double* ecdf_plevels;
	std::pair<std::chrono::microseconds*, std::chrono::microseconds*> simulation_time;
public:
	afx_msg void OnGenerate();
	afx_msg void OnPvalues();
	afx_msg void OnSpeedtest();
	afx_msg void OnButtonGenerate();
	afx_msg void OnButtonPlevels();
	afx_msg void OnButtonSpeedtest();
};
