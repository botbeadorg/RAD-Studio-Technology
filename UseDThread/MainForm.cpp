// ---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include <System.SysUtils.hpp>
#include "MainForm.h"
#include "ppl_elems.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TForm1 *Form1;

__fastcall TDemoThread::TDemoThread() {
}

__fastcall TDemoThread::TDemoThread(TMemo *memo) : TThread(false), m_count(0), m_memo(Form1->Memo1)
{
}

// -------------------------------------
__fastcall TDemoThread::~TDemoThread() {

}

// -------------------------------------
void __fastcall TDemoThread::Execute() {
	while (!Terminated) {
		Synchronize(hello);
		Sleep(100);
	}
}

// -------------------------------------
void __fastcall TDemoThread::hello() {
	String s;
	s = Sysutils::Format(_T("hello %d"), ARRAYOFCONST((m_count)));
	m_memo->Lines->Add(s);
	m_count++;
}

// ---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner) : TForm(Owner) {
}

// ---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender) {
	m_demo_thread = new TDemoThread(Memo1);
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender) {
	m_demo_thread->Terminate();
}
// ---------------------------------------------------------------------------
