// ---------------------------------------------------------------------------

#ifndef MainFormH
#define MainFormH
// ---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <FMX.Memo.hpp>
#include <FMX.ScrollBox.hpp>

class TDemoThread : public TThread {
protected:
	void __fastcall Execute();

public:
	__fastcall TDemoThread(TMemo *memo);
	__fastcall TDemoThread();
	__fastcall ~TDemoThread();

private:
	void __fastcall hello();

	int m_count;
	TMemo *m_memo;
};

// ---------------------------------------------------------------------------
class TForm1 : public TForm {
__published: // IDE-managed Components
	TButton *Button1;
	TMemo *Memo1;
	TButton *Button2;

	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);

private: // User declarations
public: // User declarations
	__fastcall TForm1(TComponent* Owner);

	TDemoThread *m_demo_thread;
};

// ---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
// ---------------------------------------------------------------------------
#endif
