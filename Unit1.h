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
#include "CSPIN.h"
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
        TLabel *Label8;
        TButton *Button5;
        TPanel *Panel3;
        TLabel *Label9;
        TLabel *Label10;
        TLabel *Label12;
        TShape *Shape1;
        TLabel *Label11;
        TButton *Button6;
        TLabel *Label13;
        TLabel *Label14;
        TImage *Przeszkoda1;
        TImage *Przeszkoda2;
        TImage *Przeszkoda3;
        TLabel *Label15;
        TLabel *Label16;
        TLabel *Label17;
        TLabel *Label18;
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
        void __fastcall Label8Click(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall Button5Click(TObject *Sender);
        void __fastcall Button4Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button6Click(TObject *Sender);
        void __fastcall Label14Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
