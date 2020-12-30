// ---------------------------------------------------------------------------

#ifndef Unit2H
#define Unit2H
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
class TForm2 : public TForm {
__published: // IDE-managed Components
	TTetheringManager *TetheringManager1;
	TTetheringAppProfile *TetheringAppProfile1;
	TLabel *Label1;
	TLabel *Label2;
	TImageControl *ImageControl1;
	TEdit *Edit1;
	TEditButton *EditButton1;
	TButton *Button1;
	TOpenDialog *OpenDialog1;
	TImageControl *ImageControl2;
	TButton *Button2;
	TButton *Button3;
	TActionList *ActionList1;
	TAction *actReset;

	void __fastcall FormCreate(TObject *Sender);
	void __fastcall TetheringManager1PairedFromLocal(TObject * const Sender, const TTetheringManagerInfo &AManagerInfo);
	void __fastcall TetheringAppProfile1Resources0ResourceReceived(TObject * const Sender,
		TRemoteResource * const AResource);
	void __fastcall TetheringAppProfile1Resources1ResourceReceived(TObject * const Sender,
		TRemoteResource * const AResource);
	void __fastcall EditButton1Click(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);

private: // User declarations
public: // User declarations
	__fastcall TForm2(TComponent* Owner);
};

// ---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
// ---------------------------------------------------------------------------
#endif
