//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CSPIN"
#pragma resource "*.dfm"
TForm1 *Form1;
int x = -1, y = -1;
int gracz1pkt = 0, gracz2pkt = 0;
int poziomTrudnosci = 1;
bool dzwiek = true;
bool graZKomputerem;
int pktDoZdobycia = 1;
bool rozgrywkaRozpoczeta = false;
bool przeszkodyAktywne = false;
bool gracz1ruchWGore = false;
bool gracz1ruchWDol = false;
bool gracz2ruchWGore = false;
bool gracz2ruchWDol = false;

void wlaczWylaczGracza1 (bool onOff)
{
        if (onOff)
        {
        Form1->Gracz1WDol->Enabled = true;
        Form1->Gracz1WGore->Enabled = true;
        Form1->Gracz1Paletka->Visible = true;
        }
        else
        {
        Form1->Gracz1WDol->Enabled = false;
        Form1->Gracz1WGore->Enabled = false;
        Form1->Gracz1Paletka->Visible = false;
        }
}
void wlaczWylaczGracza2 (bool onOff)
{
        if (onOff)
        {
        Form1->Gracz2WDol->Enabled = true;
        Form1->Gracz2WGore->Enabled = true;
        Form1->Gracz2Paletka->Visible = true;
        }
        else
        {
        Form1->Gracz2WDol->Enabled = false;
        Form1->Gracz2WGore->Enabled = false;
        Form1->Gracz2Paletka->Visible = false;
        }
}
void wlaczWylaczPilke(bool onOff)
{
        if (onOff)
        {
        Form1->TimerPileczka->Enabled = true;
        Form1->Pileczka->Visible = true;
        }
        else
        {
        Form1->TimerPileczka->Enabled = false;
        Form1->Pileczka->Visible = false;
        }
}
void wlaczWylaczPrzeszkody(bool onOff)
{
        if (onOff)
        {
                Form1->Przeszkoda1->Visible = true;
                Form1->Przeszkoda2->Visible = true;
                Form1->Przeszkoda3->Visible = true;
        }
        else
        {
                Form1->Przeszkoda1->Visible = false;
                Form1->Przeszkoda2->Visible = false;
                Form1->Przeszkoda3->Visible = false;
        }
}
void dostosujPoziomTrudnosci(int poziomTrud)
{
        switch(poziomTrud)
        {
                case 1:
                {
                        Form1->Gracz1Paletka->Height = 135;
                        Form1->Gracz2Paletka->Height = 135;
                        Form1->TimerPileczka->Interval = 3;
                        break;
                }
                case 2:
                {
                        Form1->Gracz1Paletka->Height = 110;
                        Form1->Gracz2Paletka->Height = 110;
                        Form1->TimerPileczka->Interval = 2;
                }
                case 3:
                {
                        Form1->Gracz1Paletka->Height = 85;
                        Form1->Gracz2Paletka->Height = 85;
                        Form1->TimerPileczka->Interval = 1;
                }

        }
}
void grajJakoKomputer (TImage * paletka, TImage * pilka, int trudnosc)
{
                if (pilka->Left < Form1->Stol->Width/3*trudnosc)
                {
                        gracz2ruchWGore = false;
                        gracz2ruchWDol = false;
                        if (paletka->Top > pilka->Top)
                        {
                                paletka->Top -= 10;
                                gracz2ruchWGore = true;
                        }
                        else if ((paletka->Top + paletka->Height) < (pilka->Top + pilka->Height))
                        {
                                paletka->Top +=10;
                                gracz2ruchWDol = true;
                        }
                }
}
void rozpocznijNowySet(TImage * pilka, TTimer * timerPilki, TShape * stol)
{
        Form1->Panel1->Visible = false;
        Form1->Panel2->Visible = false;
        Form1->Panel3->Visible = true;
        Form1->Gracz1Paletka->Visible = true;
        if (!graZKomputerem)    Form1->Gracz2Paletka->Visible = true;
        wlaczWylaczPrzeszkody(przeszkodyAktywne);
        Application->ProcessMessages(); Sleep(2000);
        Form1->Gracz1Paletka->Top = 216;
        Form1->Gracz2Paletka->Top = 216;
        Form1->Panel3->Visible = false;
        dostosujPoziomTrudnosci(poziomTrudnosci);
        Form1->TimerPileczka->Enabled = true;
        pilka->Left = stol->Width / 2;
        pilka->Top = stol->Height / 2;
        x  = -2; y = -2;
        wlaczWylaczPilke(true);

}
void rozpocznijNowaPartie(TImage * pilka, TTimer * timerPilki, TShape * stol)
{
        gracz1pkt = 0;
        gracz2pkt = 0;
        Form1->Label9->Caption = 0;
        Form1->Label10->Caption = 0;
        rozpocznijNowySet(pilka, timerPilki, stol);
}
void odbijOdPrzeszkody(TImage * pilka, TImage * przeszkoda)
{
        int pilkaLewaKrawedz = pilka->Left;
        int pilkaPrawaKrawedz = pilka->Left + pilka->Width;
        int pilkaGornaKrawedz = pilka->Top;
        int pilkaDolnaKrawedz = pilka->Top + pilka->Height;
        int pilkaSrodekPionowo = pilka->Top + pilka->Height/2;
        int pilkaSrodekPoziomo = pilka->Left + pilka->Width/2;
        int przeszkodaLewaKrawedz = przeszkoda->Left;
        int przeszkodaPrawaKrawedz = przeszkoda->Left + przeszkoda->Width;
        int przeszkodaGornaKrawedz = przeszkoda->Top;
        int przeszkodaDolnaKrawedz = przeszkoda->Top + przeszkoda->Height;

        if ((pilkaSrodekPionowo >= przeszkodaGornaKrawedz
                && pilkaSrodekPionowo <= przeszkodaDolnaKrawedz)
                && ((x > 0 && pilkaPrawaKrawedz >= przeszkodaLewaKrawedz
                &&  pilkaPrawaKrawedz <= (przeszkodaLewaKrawedz + 9))
                || (x < 0 && pilkaLewaKrawedz <= przeszkodaPrawaKrawedz
                && pilkaLewaKrawedz >= (przeszkodaPrawaKrawedz - 9))))
        {
                x = -x;
        }
          if ((pilkaSrodekPoziomo >= przeszkodaLewaKrawedz
                && pilkaSrodekPoziomo <= przeszkodaPrawaKrawedz)
                && ((y > 0 && pilkaDolnaKrawedz >= przeszkodaGornaKrawedz
                && pilkaDolnaKrawedz <= (przeszkodaGornaKrawedz + 9))
                || (y < 0 && pilkaGornaKrawedz <= przeszkodaDolnaKrawedz
                && pilkaGornaKrawedz >= (przeszkodaDolnaKrawedz - 9))))
                {
                y = -y;
                }
}
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
     if ((Gracz1Paletka->Top) < Stol->Height -  Gracz1Paletka->Height/2) Gracz1Paletka->Top += 10;
}

void __fastcall TForm1::Gracz2WGoreTimer(TObject *Sender)
{
        if (graZKomputerem == false)
        {
                if (Gracz2Paletka->Top > 0) Gracz2Paletka->Top -=10;
        }
        else
        {
                grajJakoKomputer (Gracz2Paletka, Pileczka, poziomTrudnosci);
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Gracz2WDolTimer(TObject *Sender)
{
        if (graZKomputerem == false)
        {
                if ((Gracz2Paletka->Top) < Stol->Height -  Gracz2Paletka->Height/2) Gracz2Paletka->Top += 10;
        }
        else
        {
                grajJakoKomputer (Gracz2Paletka, Pileczka, poziomTrudnosci);
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        if (Key == VK_ESCAPE)
        {
                wlaczWylaczPilke(false);
                wlaczWylaczGracza1(false);
                wlaczWylaczGracza2(false);
                Form1->Panel1->Visible = true;
                Form1->Button6->Visible = true;
                if (rozgrywkaRozpoczeta == true) Form1->Button6->Visible = true;
                else  Form1->Button6->Visible = false;
        }
        if (Key == VK_UP)
        {
                Gracz1WGore->Enabled = true;
                gracz1ruchWGore = true;
                gracz1ruchWDol = false;
        }
        if (Key == VK_DOWN)
        {
                Gracz1WDol->Enabled = true;
                gracz1ruchWGore = false;
                gracz1ruchWDol = true;
        }
        if (graZKomputerem == false)
        {
                if (Key == 0x51)
                {
                        Gracz2WGore->Enabled = true;
                        gracz2ruchWGore = true;
                        gracz2ruchWDol = false;
                }
                if (Key == 0x41)
                {
                        Gracz2WDol->Enabled = true;
                        gracz2ruchWGore = false;
                        gracz2ruchWDol = true;
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
     if (Key == VK_UP)          Gracz1WGore->Enabled = false;
     if (Key == VK_DOWN)        Gracz1WDol->Enabled = false;
     if (graZKomputerem == false)
     {
        if (Key == 0x51)           Gracz2WGore->Enabled = false;
        if (Key == 0x41)           Gracz2WDol->Enabled = false;
     }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
        wlaczWylaczGracza1 (false);
        wlaczWylaczGracza2 (false);

}
//---------------------------------------------------------------------------

void __fastcall TForm1::TimerPileczkaTimer(TObject *Sender)
{
        Pileczka->Left += x;
        Pileczka->Top += y;
        if (Pileczka->Top >= Stol->Top) y = -y;
        if ((Pileczka->Top + Pileczka->Height) <=  (Stol->Top + Stol->Height)) y = -y;
        // skucha  gracza 1
        if ((Pileczka->Left + Pileczka->Width) > (Gracz1Paletka->Left + 15))
        {
                wlaczWylaczPilke(false);
                wlaczWylaczGracza1(false);
                if (!graZKomputerem)    wlaczWylaczGracza2(false);
                Form1->Label9->Caption = ++gracz2pkt;
                if (gracz2pkt < pktDoZdobycia)
                {
                if( Application->MessageBox(
			"Punkt dla gracza 2. Kliknij OK aby zaserwowac pilke ponownie.","" ,
			MB_OK | MB_ICONQUESTION) == IDOK )
	                rozpocznijNowySet(Pileczka, TimerPileczka, Stol);
                }
        }
        // skucha gracza 2
        if (Pileczka->Left < (Gracz2Paletka->Left +  Gracz2Paletka->Width - 15))
        {
                wlaczWylaczPilke(false);
                wlaczWylaczGracza1(false);
                if (!graZKomputerem)    wlaczWylaczGracza2(false);
                Form1->Label10->Caption = ++gracz1pkt;
                if (gracz1pkt < pktDoZdobycia)
                {
                if( Application->MessageBox(
			"Punkt dla gracza 1. Kliknij OK aby zaserwowac pilke ponownie.","" ,
			MB_OK | MB_ICONQUESTION) == IDOK )
	                rozpocznijNowySet(Pileczka, TimerPileczka, Stol);
                }
        }
        // odbicie od paletek
        if ((Pileczka->Top + Pileczka->Height/2 > Gracz2Paletka->Top
                && Pileczka->Top + Pileczka->Height/2 < Gracz2Paletka->Top + Gracz2Paletka->Height
                && Pileczka->Left <= Gracz2Paletka->Left + Gracz2Paletka->Width)
                || (Pileczka->Top + Pileczka->Height/2  > Gracz1Paletka->Top
                && Pileczka->Top + Pileczka->Height/2 < Gracz1Paletka->Top + Gracz1Paletka->Height
                && Pileczka->Left + Pileczka->Width >= Gracz1Paletka->Left))
        {
                if (!(x > -4 && x < 4))
                {
                        if (gracz1ruchWGore || gracz2ruchWGore)
                        {
                                if (y > 0)
                                        x = -1.2 * x;
                                else
                                        x = -0.8 * x;
                        }
                        else if (gracz1ruchWDol || gracz2ruchWDol)
                        {
                                if (y > 0)
                                        x = -0.8 * x;
                                else
                                        x = -1.2 * x;
                        }
                        else
                                x = -x;
                }
                if (Form1->TimerPileczka->Interval > 5)  Form1->TimerPileczka->Interval -= 1;
        }
        // odbicie od przeszkod
        if (przeszkodyAktywne)
        {
                odbijOdPrzeszkody(Pileczka, Przeszkoda1);
                odbijOdPrzeszkody(Pileczka, Przeszkoda2);
                odbijOdPrzeszkody(Pileczka, Przeszkoda3);
        }

        if (gracz1pkt >= pktDoZdobycia)
        {
                wlaczWylaczGracza1(false);
                wlaczWylaczGracza2(false);
                wlaczWylaczPilke(false);
                ShowMessage("Koniec rozgrywki. Wygrywa gracz 1");
                Form1->Panel1->Visible = true;
        }

        if (gracz2pkt >= pktDoZdobycia)
        {
                wlaczWylaczGracza1(false);
                wlaczWylaczGracza2(false);
                wlaczWylaczPilke(false);
                ShowMessage("Koniec rozgrywki. Wygrywa gracz 2");
                Form1->Panel1->Visible = true;
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
        if (dzwiek)
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

void __fastcall TForm1::Label8Click(TObject *Sender)
{
        Label8->Caption = ++pktDoZdobycia;
        if (pktDoZdobycia >= 20) pktDoZdobycia = 0;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
        switch(poziomTrudnosci)
        {
        case 1: Label4->Caption = "Latwy";  break;
        case 2: Label4->Caption = "Sredni"; break;
        case 3: Label4->Caption = "Trudny"; break;
        }

        if (dzwiek == true) Label6->Caption = "Wylaczone";
        else Label6->Caption = "Wlaczone";

        Label8->Caption = pktDoZdobycia;
        Panel2->Visible = true;
        Panel1->Visible = false;
        Form1->Button6->Visible = false;
        rozgrywkaRozpoczeta = false;


}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button5Click(TObject *Sender)
{
        Panel2->Visible = false;
        Panel1->Visible = true;        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender)
{
        
        if( Application->MessageBox(
			"Czy na pewno chcesz opuscic gre?","Zakoncz gre" ,
			MB_YESNO | MB_ICONQUESTION) == IDYES )
		Application->Terminate();

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
        graZKomputerem = false;
        Form1->Gracz2Paletka->Visible = true;
        rozpocznijNowaPartie(Pileczka, TimerPileczka, Stol);
        rozgrywkaRozpoczeta = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
        graZKomputerem = true;
        wlaczWylaczGracza2 (true);
        rozpocznijNowaPartie(Pileczka, TimerPileczka, Stol);
        rozgrywkaRozpoczeta = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button6Click(TObject *Sender)
{
                Form1->TimerPileczka->Enabled = true;
                if (graZKomputerem)     wlaczWylaczGracza2(true);
                Form1->Gracz1Paletka->Visible = true;
                wlaczWylaczPilke(true);
                Form1->Panel1->Visible = false;
}
//---------------------------------------------------------------------------



void __fastcall TForm1::Label14Click(TObject *Sender)
{
        if (przeszkodyAktywne)
        {
                przeszkodyAktywne = false;
                Label14->Caption = "Wylaczone";
        }
        else
        {
                przeszkodyAktywne = true;
                Label14->Caption = "Wlaczone";
        }
}
//---------------------------------------------------------------------------

