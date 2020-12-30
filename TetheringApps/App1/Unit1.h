// ---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
// ---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <IPPeerClient.hpp>
#include <IPPeerServer.hpp>
#include <System.Tether.AppProfile.hpp>
#include <System.Tether.Manager.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <FMX.Edit.hpp>
#include <FMX.Dialogs.hpp>
#include <FMX.ActnList.hpp>
#include <System.Actions.hpp>

// ---------------------------------------------------------------------------
class TForm1 : public TForm {
__published: // IDE-managed Components
	TTetheringManager *TetheringManager1;
	TTetheringAppProfile *TetheringAppProfile1;
	TButton *Button1;
	TStatusBar *StatusBar1;
	TLabel *Label100;
	TLabel *Label1;
	TEdit *Edit1;
	TEditButton *EditButton1;
	TButton *Button2;
	TImageControl *ImageControl1;
	TOpenDialog *OpenDialog1;
	TLabel *Label2;
	TImageControl *ImageControl2;
	TActionList *ActionList1;
	TAction *actReset;
	TButton *Button3;

	void __fastcall FormCreate(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall TetheringManager1PairedToRemote(TObject * const Sender, const TTetheringManagerInfo &AManagerInfo);
	void __fastcall TetheringManager1RequestManagerPassword(TObject * const Sender,
		const UnicodeString ARemoteIdentifier, UnicodeString &Password);
	void __fastcall EditButton1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall TetheringAppProfile1ResourceReceived(TObject * const Sender, TRemoteResource * const AResource);
	void __fastcall actResetExecute(TObject *Sender);
	void __fastcall actResetUpdate(TObject *Sender);

private: // User declarations
public: // User declarations
	__fastcall TForm1(TComponent* Owner);
};

// ---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
// ---------------------------------------------------------------------------
#endif
