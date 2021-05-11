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
	TetheringManager2->AllowedAdapters = _T("Network");
	TetheringManager2->Password = _T("whoami?");
	TetheringAppProfile2->Manager = TetheringManager2;
	// Random string that uniquely identifies your manager.
	Caption = Format(_T("AppTetheringByHand2 : %s"), ARRAYOFCONST((TetheringManager2->Identifier)));

	Image1->Bitmap->LoadFromFile(ExtractFilePath(ParamStr(0)) + _T("cpp.png"));
}

// ---------------------------------------------------------------------------
// Event after a remote manager has paired with your manager successfully
void __fastcall TForm2::TetheringManager2PairedFromLocal(TObject * const Sender,
	const TTetheringManagerInfo &AManagerInfo)

{
	Memo1->Lines->Add(_T("Pair operation successed : "));
	Memo1->Lines->Add(_T("Remote Manager : ") + AManagerInfo.ManagerText);
	Memo1->Lines->Add(_T("\n----------------------------------------"));
}

// ---------------------------------------------------------------------------
// Occurs after a remote profile successfully connects to your profile
// AProfileInfo provides information about the remote profile.
void __fastcall TForm2::TetheringAppProfile2AfterConnectProfile(TObject * const Sender,
	const TTetheringProfileInfo &AProfileInfo) {
	Memo1->Lines->Add(_T("Remote profile connect operation successed : "));
	Memo1->Lines->Add(_T("Remote profile : ") + AProfileInfo.ProfileText);
	Memo1->Lines->Add(_T("\n----------------------------------------"));
}

// ---------------------------------------------------------------------------
/*
 * With Transient resources, we don¡¯t have a Resource defined at design-time,
 * so we use the TetheringAppProfile¡¯s generic OnResourceReceived event.
 */
void __fastcall TForm2::TetheringAppProfile2ResourceReceived(TObject * const Sender,
	TRemoteResource * const AResource) {
	Memo1->Lines->Add(_T("Resource incoming : "));
	// enum class DECLSPEC_DENUM TRemoteResourceType : unsigned char { Data, Stream };
	Memo1->Lines->Add(AResource->ResType);
	/*
	 * A remote resource provides a Name that uniquely identifies the resource within the Profile
	 * that shares the resource, and a Hint that describes the resource.
	 */
	Memo1->Lines->Add(AResource->Name);
	Memo1->Lines->Add(AResource->Hint);
	/*
	 * By default, remote resources are public (IsPublic is True) and persistent (IsTemp is False).
	 *
	 * Application profiles use protected (IsPublic is False), temporary (IsTemp is True) remote resources
	 * for one-time exchanges of data, such as sending strings or receiving streams.
	 */
	Memo1->Lines->Add(BoolToStr(AResource->IsPublic, true));
	Memo1->Lines->Add(BoolToStr(AResource->IsTemp, true));

	/*
	 *Kind determines whether the value of the remote resource is defined on the profile that shares the resource (default).
	 */
	// enum class DECLSPEC_DENUM TTetheringRemoteKind : unsigned char { Shared, Mirror };
	Memo1->Lines->Add(AResource->Kind);

	if (_T("HINT_transient_str_resource") == AResource->Hint) {
		Memo1->Lines->Add(AResource->Value.AsString);
	}
}

// ---------------------------------------------------------------------------
void __fastcall TForm2::Button1Click(TObject *Sender) {
	/*
	 * Note we created the stream but did not free it.
	 * The App Tethering framework will take care of that for us.
	 */
	TMemoryStream* LStream = new TMemoryStream;
	Image1->Bitmap->SaveToStream(LStream);
	LStream->Position = 0;
	TetheringAppProfile2->SendStream(TetheringManager2->RemoteProfiles->First(),
		_T("HINT_transient_stream_resource"), LStream);
}
// ---------------------------------------------------------------------------
