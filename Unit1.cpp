//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
int x = -8, y = -8;
int gracz1pkt = 0, gracz2pkt = 0;
int poziomTrudnosci = 1;
bool dzwiek = true;
int pktDoZdobycia = 10;
bool skucha (TImage * pilka, TImage * gracz1paletka, TImage * gracz2paletka);

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Gracz1WGoreTimer(TObject *Sender)
{
        if (Gracz1Paletka->Top > 0) Gracz1Paletka->Top -=10;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Gracz1WDolTimer(TObject *Sender)
{
     if ((Gracz1Paletka->Top) < Stol->Height -  Gracz1Paletka->Height) Gracz1Paletka->Top += 10;
}

void __fastcall TForm1::Gracz2WGoreTimer(TObject *Sender)
{
         if (Gracz2Paletka->Top > 0) Gracz2Paletka->Top -=10;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Gracz2WDolTimer(TObject *Sender)
{
         if ((Gracz2Paletka->Top) < Stol->Height -  Gracz2Paletka->Height) Gracz2Paletka->Top += 10;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        if (Key == VK_UP)
        {
                Gracz1WGore->Enabled = true;
        }

        if (Key == VK_DOWN)
        {
                Gracz1WDol->Enabled = true;
        }
        if (Key == 0x51)
        {
                Gracz2WGore->Enabled = true;
        }

        if (Key == 0x41)
        {
                Gracz2WDol->Enabled = true;
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
     if (Key == VK_UP)          Gracz1WGore->Enabled = false;
     if (Key == VK_DOWN)        Gracz1WDol->Enabled = false;
     if (Key == 0x51)           Gracz2WGore->Enabled = false;
     if (Key == 0x41)           Gracz2WDol->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
        Gracz1WGore->Enabled = false;
        Gracz1WDol->Enabled = false;
        Gracz2WGore->Enabled = false;
        Gracz2WDol->Enabled = false;
        TimerPileczka->Enabled = false;
        Pileczka->Visible =false;
        Panel1->Visible = true;
        Panel2->Visible = false;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::TimerPileczkaTimer(TObject *Sender)
{
        Pileczka->Left += x;
        Pileczka->Top += y;

        if (Pileczka->Top >= Stol->Top) y = -y;
        if ((Pileczka->Top + Pileczka->Height) <=  (Stol->Top + Stol->Height)) y = -y;
        // skucha
        if ((Pileczka->Left < (Gracz2Paletka->Left +  Gracz2Paletka->Width - 15))
               || ((Pileczka->Left + Pileczka->Width) > (Gracz1Paletka->Left + 15)))
        {
                 TimerPileczka->Enabled = false;
                 Pileczka->Visible = false;
        }
        if ((Pileczka->Top > Gracz1Paletka->Top - Pileczka->Height/2
                && Pileczka->Top < Gracz1Paletka->Top + Gracz1Paletka->Height
                && Pileczka->Left + Pileczka->Width > Gracz1Paletka->Left)
                ||
                (Pileczka->Top > Gracz2Paletka->Top - Pileczka->Height/2
                && Pileczka->Top < Gracz2Paletka->Top + Gracz2Paletka->Height
                && Pileczka->Left < Gracz2Paletka->Left + Gracz2Paletka->Width)
                )
        {
                x = -x;
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Label4Click(TObject *Sender)
{
        if (poziomTrudnosci == 1) poziomTrudnosci = 2;
        else if (poziomTrudnosci == 2) poziomTrudnosci = 3;
        else if (poziomTrudnosci == 3) poziomTrudnosci = 1;

        switch(poziomTrudnosci)
        {
        case 1: Label4->Caption = "Latwy";  break;
        case 2: Label4->Caption = "Sredni"; break;
        case 3: Label4->Caption = "Trudny"; break;
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Label6Click(TObject *Sender)
{
        if (dzwiek == true)
        {
                dzwiek = false;
                Label6->Caption = "Wylaczone";
        }
        else
        {
                dzwiek = true;
                Label6->Caption = "Wlaczone";
        }

}
//---------------------------------------------------------------------------
