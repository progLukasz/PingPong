//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TShape *Stol;
        TImage *Gracz1Paletka;
        TImage *Gracz2Paletka;
        TTimer *Gracz1WGore;
        TTimer *Gracz1WDol;
        TTimer *Gracz2WGore;
        TTimer *Gracz2WDol;
        TImage *Pileczka;
        TTimer *TimerPileczka;
        TPanel *Panel1;
        TLabel *Label1;
        TButton *Button1;
        TButton *Button2;
        TButton *Button3;
        TButton *Button4;
        TPanel *Panel2;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TLabel *Label5;
        TLabel *Label6;
        TLabel *Label7;
        void __fastcall Gracz1WGoreTimer(TObject *Sender);
        void __fastcall Gracz1WDolTimer(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall FormKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall Gracz2WGoreTimer(TObject *Sender);
        void __fastcall Gracz2WDolTimer(TObject *Sender);
        void __fastcall TimerPileczkaTimer(TObject *Sender);
        void __fastcall Label4Click(TObject *Sender);
        void __fastcall Label6Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
