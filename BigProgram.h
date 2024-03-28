
// BigProgram.h : main header file for the BigProgram application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols

#include <chrono>
#include <random>

extern unsigned seed;
extern std::mt19937 engine;
extern std::uniform_real_distribution<double> runif;

// CBigProgramApp:
// See BigProgram.cpp for the implementation of this class
//

class CBigProgramApp : public CWinAppEx
{
public:
	CBigProgramApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CBigProgramApp theApp;
