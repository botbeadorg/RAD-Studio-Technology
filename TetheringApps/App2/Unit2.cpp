// ---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "Unit2.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TForm2 *Form2;

// ---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner) : TForm(Owner) {
}

// ---------------------------------------------------------------------------
void __fastcall TForm2::FormCreate(TObject *Sender) {
	TetheringManager1->AllowedAdapters = L"Network";
	TetheringManager1->Password = L"INeedAPassword!";
	TetheringAppProfile1->Manager = TetheringManager1;
	TetheringAppProfile1->Group = L"ExperimentEithAppTethering-Auto";
	TetheringAppProfile1->Resources->Items[0]->IsPublic = true;
	TetheringAppProfile1->Resources->Items[0]->Kind = TTetheringRemoteKind::Mirror;
	TetheringAppProfile1->Resources->Items[0]->Name = L"SomeText";
	TetheringAppProfile1->Resources->Items[0]->ResType = TRemoteResourceType::Data;
	TetheringAppProfile1->Resources->Items[1]->IsPublic = true;
	TetheringAppProfile1->Resources->Items[1]->Kind = TTetheringRemoteKind::Mirror;
	TetheringAppProfile1->Resources->Items[1]->Name = L"SomeImage";
	TetheringAppProfile1->Resources->Items[1]->ResType = TRemoteResourceType::Stream;
	TetheringAppProfile1->Actions->Items[0]->Action = actReset;
	TetheringAppProfile1->Actions->Items[0]->IsPublic = true;
	TetheringAppProfile1->Actions->Items[0]->Name = L"CrossApp_actReset";
	TetheringAppProfile1->Actions->Items[0]->Kind = TTetheringRemoteKind::Mirror;
	Caption = Format("App2 : %s", ARRAYOFCONST((TetheringManager1->Identifier)));
	Button3->Action = actReset;
}

// ---------------------------------------------------------------------------
void __fastcall TForm2::TetheringManager1PairedFromLocal(TObject * const Sender,
	const TTetheringManagerInfo &AManagerInfo)

{
	Label1->Text = Format("Connected : %s %s", ARRAYOFCONST((AManagerInfo.ManagerIdentifier,
		AManagerInfo.ManagerName)));
}

// ---------------------------------------------------------------------------
void __fastcall TForm2::TetheringAppProfile1Resources0ResourceReceived(TObject * const Sender,
	TRemoteResource * const AResource)

{
	Label2->Text = AResource->Value.AsString;
}

// ---------------------------------------------------------------------------
void __fastcall TForm2::TetheringAppProfile1Resources1ResourceReceived(TObject * const Sender,
	TRemoteResource * const AResource)

{
	AResource->Value.AsStream->Position = 0;
	ImageControl1->Bitmap->LoadFromStream(AResource->Value.AsStream);
}

// ---------------------------------------------------------------------------
void __fastcall TForm2::EditButton1Click(TObject *Sender) {
	TetheringAppProfile1->SendString(TetheringManager1->RemoteProfiles->First(), L"TransientString", Edit1->Text);
}

// ---------------------------------------------------------------------------
void __fastcall TForm2::Button1Click(TObject *Sender) {
	if (OpenDialog1->Execute()) {
		ImageControl2->LoadFromFile(OpenDialog1->FileName);

		TMemoryStream* LStream = new TMemoryStream;
		ImageControl2->Bitmap->SaveToStream(LStream);

		LStream->Position = 0;
		TetheringAppProfile1->SendStream(TetheringManager1->RemoteProfiles->First(), "TransientStream", LStream);
	}
}

// ---------------------------------------------------------------------------
void __fastcall TForm2::Button2Click(TObject *Sender) {
	TetheringAppProfile1->RunRemoteAction(TetheringManager1->RemoteProfiles->First(), "CrossApp_actReset");
}
// ---------------------------------------------------------------------------
