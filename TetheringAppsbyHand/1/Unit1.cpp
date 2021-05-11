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
	TetheringManager1->AllowedAdapters = _T("Network");
	TetheringAppProfile1->Manager = TetheringManager1;
	// Random string that uniquely identifies your manager.
	Caption = Format(_T("AppTetheringByHand1 : %s"), ARRAYOFCONST((TetheringManager1->Identifier)));
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender) {

	try {
		// Unpair
		for (size_t i = 0; i < TetheringManager1->PairedManagers->Count; ++i) {
			TetheringManager1->UnPairManager(TetheringManager1->PairedManagers->Items[i]);
		}
		/*
		 * Call the DiscoverManagers method of your TTetheringManager component of your application
		 * to start discovering other applications that use app tethering.
		 */
		TetheringManager1->DiscoverManagers();
	}
	catch (ETetheringException &e) {
		Memo1->Lines->Add(e.Message);
	}

}

// ---------------------------------------------------------------------------
// When the DiscoverManagers finishes, the OnEndManagersDiscovery event of your manager occurs.
void __fastcall TForm1::TetheringManager1EndManagersDiscovery(TObject * const Sender,
	TTetheringManagerInfoList * const ARemoteManagers) {
	size_t x = SIZE_MAX;
	Memo1->Lines->Add(_T("All Remote Managers : "));
	for (size_t i = 0; i < ARemoteManagers->Count; ++i) {
		Memo1->Lines->Add(_T("ManagerIdentifier : ") + ARemoteManagers->Items[i].ManagerIdentifier);
		Memo1->Lines->Add(_T("ManagerName : ") + ARemoteManagers->Items[i].ManagerName);
		Memo1->Lines->Add(_T("ManagerText : ") + ARemoteManagers->Items[i].ManagerText);
		Memo1->Lines->Add(_T("ConnectionString : ") + ARemoteManagers->Items[i].ConnectionString);
		Memo1->Lines->Add(_T("ManagerAdapters : ") + ARemoteManagers->Items[i].ManagerAdapters);

		if (String(_T("TetheringManager2")) == ARemoteManagers->Items[i].ManagerText)
			x = i;
	}

	Memo1->Lines->Add(_T("\n------------------------------------------"));

	if (SIZE_MAX != x) {
		// Pairing remote Manager operation.
		TetheringManager1->PairManager(ARemoteManagers->Items[x]);
	}
}

// ---------------------------------------------------------------------------
// Event after your manager started a pairing operation and succeeded.
void __fastcall TForm1::TetheringManager1PairedToRemote(TObject * const Sender,
	const TTetheringManagerInfo &AManagerInfo) {
	Memo1->Lines->Add(_T("Pair operation successed : "));
	Memo1->Lines->Add(_T("Remote Manager : ") + AManagerInfo.ManagerText);
	Memo1->Lines->Add(_T("\n----------------------------------------"));
}

// ---------------------------------------------------------------------------
/*
 * After the pairing operation succeeded, your manager starts a profile discovering operation automatically.
 * If the operation succeeds, your manager gets a list of profiles published by the paired manager.
 */
void __fastcall TForm1::TetheringManager1EndProfilesDiscovery(TObject * const Sender,
	TTetheringProfileInfoList * const ARemoteProfiles) {
	Memo1->Lines->Add(_T("Profile discovering operation successed : "));
	for (size_t i = 0; i < ARemoteProfiles->Count; ++i) {
		Memo1->Lines->Add(String(i) + String(_T(" : ")) + ARemoteProfiles->Items[i].ProfileText);

		if (String(_T("TetheringAppProfile2")) == ARemoteProfiles->Items[i].ProfileText) {
			// connect to a profile published by the paired manager.
			TetheringAppProfile1->Connect(ARemoteProfiles->Items[i]);
			Memo1->Lines->Add(String(_T("connect to ")) + ARemoteProfiles->Items[i].ProfileText);
		}

	}
	Memo1->Lines->Add(_T("\n----------------------------------------"));
}

// ---------------------------------------------------------------------------
// Occurs when your manager requests to pair with a remote manager and the remote manager specifies a password.
void __fastcall TForm1::TetheringManager1RequestManagerPassword(TObject * const Sender,
	const UnicodeString ARemoteIdentifier, UnicodeString &Password) {
	for (size_t i = 0; i < TetheringManager1->RemoteManagers->Count; ++i) {
		if (String(_T("TetheringManager2")) == TetheringManager1->RemoteManagers->Items[i]
			.ManagerText) {
			Password = String(_T("whoami?"));
		}
	}
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender) {
	try {
		// SendString is faster than the SendStream. SendString is a synchronous function.
		TetheringAppProfile1->SendString(TetheringManager1->RemoteProfiles->Items[0],
			_T("HINT_transient_str_resource"), Edit1->Text);
	}
	catch (ETetheringException &e) {
		Memo1->Lines->Add(e.Message);
	}
}

// ---------------------------------------------------------------------------
/*
 * With Transient resources, we don¡¯t have a Resource defined at design-time,
 * so we use the TetheringAppProfile¡¯s generic OnResourceReceived event.
 */
void __fastcall TForm1::TetheringAppProfile1ResourceReceived(TObject * const Sender,
	TRemoteResource * const AResource) {
	if (_T("HINT_transient_stream_resource") == AResource->Hint) {
		AResource->Value.AsStream->Position = 0;
		Image1->Bitmap->LoadFromStream(AResource->Value.AsStream);
	}
}
// ---------------------------------------------------------------------------
