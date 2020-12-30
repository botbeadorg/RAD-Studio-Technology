// ---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "Unit1.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TForm1 *Form1;

// ---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner) : TForm(Owner) {
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender) {
	TetheringManager1->AllowedAdapters = L"Network";
	TetheringAppProfile1->Manager = TetheringManager1;
	TetheringAppProfile1->Group = L"ExperimentEithAppTethering-Auto";
	TetheringAppProfile1->Resources->Items[0]->IsPublic = true;
	TetheringAppProfile1->Resources->Items[0]->Kind = TTetheringRemoteKind::Shared;
	TetheringAppProfile1->Resources->Items[0]->Name = L"SomeText";
	TetheringAppProfile1->Resources->Items[0]->ResType = TRemoteResourceType::Data;
	TetheringAppProfile1->Resources->Items[1]->IsPublic = true;
	TetheringAppProfile1->Resources->Items[1]->Kind = TTetheringRemoteKind::Shared;
	TetheringAppProfile1->Resources->Items[1]->Name = L"SomeImage";
	TetheringAppProfile1->Resources->Items[1]->ResType = TRemoteResourceType::Stream;
	TetheringAppProfile1->Actions->Items[0]->Action = actReset;
	TetheringAppProfile1->Actions->Items[0]->IsPublic = true;
	TetheringAppProfile1->Actions->Items[0]->Name = L"CrossApp_actReset";
	TetheringAppProfile1->Actions->Items[0]->Kind = TTetheringRemoteKind::Shared;
	TetheringAppProfile1->Actions->Items[0]->NotifyUpdates = true;
	Caption = Format("App1 : %s", ARRAYOFCONST((TetheringManager1->Identifier)));
	Button3->Action = actReset;
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender) {
	TetheringManager1->AutoConnect();
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::TetheringManager1PairedToRemote(TObject * const Sender,
	const TTetheringManagerInfo &AManagerInfo) {
	Label1->Text = Format("Connected : %s %s", ARRAYOFCONST((AManagerInfo.ManagerIdentifier,
		AManagerInfo.ManagerName)));
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::TetheringManager1RequestManagerPassword(TObject * const Sender,
	const UnicodeString ARemoteIdentifier, UnicodeString &Password) {
	Password = L"INeedAPassword!";
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::EditButton1Click(TObject *Sender) {
	TetheringAppProfile1->Resources->FindByName("SomeText")->Value = TResourceValue::_op_Implicit(Edit1->Text);
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender) {
	if (OpenDialog1->Execute()) {
		ImageControl1->LoadFromFile(OpenDialog1->FileName);
		TMemoryStream *LStream = new TMemoryStream;
		ImageControl1->Bitmap->SaveToStream(LStream);
		LStream->Position = 0;
		TetheringAppProfile1->Resources->FindByName("SomeImage")->Value = TResourceValue::_op_Implicit(LStream);
	}
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::TetheringAppProfile1ResourceReceived(TObject * const Sender, TRemoteResource * const AResource)
{
	if (AResource->Hint == L"TransientString")
		Label2->Text = AResource->Value.AsString;
	else if (AResource->Hint == L"TransientStream") {
		AResource->Value.AsStream->Position = 0;
		ImageControl2->Bitmap->LoadFromStream(AResource->Value.AsStream);
	}
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::actResetExecute(TObject *Sender) {
	Edit1->Text = L"";
	Label2->Text = L"";
}

// ---------------------------------------------------------------------------

void __fastcall TForm1::actResetUpdate(TObject *Sender) {
	actReset->Enabled = (Edit1->Text != L"") || (Label2->Text != L"");
}
// ---------------------------------------------------------------------------
