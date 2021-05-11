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
#include <FMX.Memo.hpp>
#include <FMX.ScrollBox.hpp>
#include <FMX.Edit.hpp>
#include <FMX.Objects.hpp>

// ---------------------------------------------------------------------------
class TForm1 : public TForm {
__published: // IDE-managed Components
	TTetheringAppProfile *TetheringAppProfile1;
	TTetheringManager *TetheringManager1;
	TButton *Button1;
	TMemo *Memo1;
	TButton *Button2;
	TEdit *Edit1;
	TImage *Image1;

	void __fastcall FormCreate(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall TetheringManager1EndManagersDiscovery(TObject * const Sender,
		TTetheringManagerInfoList * const ARemoteManagers);
	void __fastcall TetheringManager1PairedToRemote(TObject * const Sender,
		const TTetheringManagerInfo &AManagerInfo);
	void __fastcall TetheringManager1EndProfilesDiscovery(TObject * const Sender,
		TTetheringProfileInfoList * const ARemoteProfiles);
	void __fastcall TetheringManager1RequestManagerPassword(TObject * const Sender,
		const UnicodeString ARemoteIdentifier, UnicodeString &Password);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall TetheringAppProfile1ResourceReceived(TObject * const Sender,
		TRemoteResource * const AResource);

private: // User declarations
public: // User declarations
	__fastcall TForm1(TComponent* Owner);
};

// ---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
// ---------------------------------------------------------------------------
#endif
