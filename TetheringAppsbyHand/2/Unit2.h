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
#include <FMX.Memo.hpp>
#include <FMX.ScrollBox.hpp>
#include <FMX.Objects.hpp>

// ---------------------------------------------------------------------------
class TForm2 : public TForm {
__published: // IDE-managed Components
	TTetheringAppProfile *TetheringAppProfile2;
	TTetheringManager *TetheringManager2;
	TMemo *Memo1;
	TButton *Button1;
	TImage *Image1;

	void __fastcall FormCreate(TObject *Sender);
	void __fastcall TetheringManager2PairedFromLocal(TObject * const Sender,
		const TTetheringManagerInfo &AManagerInfo);
	void __fastcall TetheringAppProfile2AfterConnectProfile(TObject * const Sender,
		const TTetheringProfileInfo &AProfileInfo);
	void __fastcall TetheringAppProfile2ResourceReceived(TObject * const Sender,
		TRemoteResource * const AResource);
	void __fastcall Button1Click(TObject *Sender);

private: // User declarations
public: // User declarations
	__fastcall TForm2(TComponent* Owner);
};

// ---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
// ---------------------------------------------------------------------------
#endif
