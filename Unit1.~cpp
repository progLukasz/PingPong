//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "mmsystem.h"

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CSPIN"
#pragma resource "*.dfm"
TForm1 *Form1;
int x = -1, y = -1;
int player1points = 0, player2points = 0;
int difficultyLevel = 1;
bool sound = true;
bool gameWithCPU = 0;
int pointsToWin = 5;
bool gameStarted = false;
bool obstaclesActive = false;
bool player1MoveUp = false;
bool player1MoveDown = false;
bool player2MoveUp = false;
bool player2MoveDown = false;

void switchPlayer1OnOff (bool onOff)
{
        if (onOff)
        {
        Form1->Player1Down->Enabled = true;
        Form1->Player1Up->Enabled = true;
        Form1->Player1Racket->Visible = true;
        }
        else
        {
        Form1->Player1Down->Enabled = false;
        Form1->Player1Up->Enabled = false;
        Form1->Player1Racket->Visible = false;
        }
}
void switchPlayer2OnOff (bool onOff)
{
        if (onOff)
        {
        Form1->Player2Down->Enabled = true;
        Form1->Player2Up->Enabled = true;
        Form1->Player2Racket->Visible = true;
        }
        else
        {
        Form1->Player2Down->Enabled = false;
        Form1->Player2Up->Enabled = false;
        Form1->Player2Racket->Visible = false;
        }
}
void switchBallOnOff(bool onOff)
{
        if (onOff)
        {
        Form1->TimerBall->Enabled = true;
        Form1->Ball->Visible = true;
        }
        else
        {
        Form1->TimerBall->Enabled = false;
        Form1->Ball->Visible = false;
        }
}
void switchObstaclesOnOff(bool onOff)
{
        if (onOff)
        {
                Form1->Obstacle1->Visible = true;
                Form1->Obstacle2->Visible = true;
                Form1->Obstacle3->Visible = true;
        }
        else
        {
                Form1->Obstacle1->Visible = false;
                Form1->Obstacle2->Visible = false;
                Form1->Obstacle3->Visible = false;
        }
}
void adjustDifficultyLevel(int diffLevel)
{
        switch(diffLevel)
        {
                case 1:
                {
                        Form1->Player1Racket->Height = 135;
                        Form1->Player2Racket->Height = 135;
                        Form1->TimerBall->Interval = 15;
                        Form1->Obstacle1->Height = 40;
                        Form1->Obstacle1->Top = 134;
                        Form1->Obstacle2->Height = 40;
                        Form1->Obstacle2->Top = 280;
                        Form1->Obstacle3->Height = 40;
                        Form1->Obstacle3->Top = 426;
                        break;
                }
                case 2:
                {
                        Form1->Player1Racket->Height = 110;
                        Form1->Player2Racket->Height = 110;
                        Form1->TimerBall->Interval = 10;
                        Form1->Obstacle1->Height = 60;
                        Form1->Obstacle1->Top = 124;
                        Form1->Obstacle2->Height = 60;
                        Form1->Obstacle2->Top = 270;
                        Form1->Obstacle3->Height = 60;
                        Form1->Obstacle3->Top = 416;
                        break;
                }
                case 3:
                {
                        Form1->Player1Racket->Height = 85;
                        Form1->Player2Racket->Height = 85;
                        Form1->TimerBall->Interval = 5;
                        Form1->Obstacle1->Height = 80;
                        Form1->Obstacle1->Top = 114;
                        Form1->Obstacle2->Height = 80;
                        Form1->Obstacle2->Top = 260;
                        Form1->Obstacle3->Height = 80;
                        Form1->Obstacle3->Top = 406;
                }

        }
}

void playWithCPU (TImage * racket, TImage * ball, int difficulty)
{
                if (ball->Left < Form1->Table->Width/3)
                {
                        player2MoveUp = false;
                        player2MoveDown = false;
                        {
                                if (racket->Top > ball->Top)
                                {
                                        racket->Top -= 5 * difficulty;
                                        player2MoveUp = true;
                                }
                                else if ((racket->Top + racket->Height) < (ball->Top + ball->Height))
                                {
                                        racket->Top += 5 * difficulty;
                                        player2MoveDown = true;
                                }
                        }
                }
}

int drawMinusOrPlusValue ()
{
        int x = rand() % 100;
        if ( x > 50)    return 1;
        else            return -1;
}
void startNewSet(TImage * ball, TTimer * timerBall, TShape * table)
{
        int signX= rand() % 100;
        int signY = rand() % 100;
        Form1->Panel1->Visible = false;
        Form1->Panel2->Visible = false;
        Form1->Panel3->Visible = true;
        Form1->Player1Racket->Visible = true;
        if (!gameWithCPU)    Form1->Player2Racket->Visible = true;
        switchObstaclesOnOff(obstaclesActive);
        Application->ProcessMessages(); Sleep(2000);
        Form1->Player1Racket->Top = 216;
        Form1->Player2Racket->Top = 216;
        Form1->Panel3->Visible = false;
        adjustDifficultyLevel(difficultyLevel);
        Form1->TimerBall->Enabled = true;
        ball->Left = table->Width / 2;
        ball->Top = table->Height / 2;

        x = drawMinusOrPlusValue() * (rand() % 7 + 3);
        y = drawMinusOrPlusValue() * (rand() % 7 + 3);
        switchBallOnOff(true);

}
void startNewGame(TImage * ball, TTimer * timerBall, TShape * table)
{
        player1points = 0;
        player2points = 0;
        Form1->Label9->Caption = 0;
        Form1->Label10->Caption = 0;
        startNewSet(ball, timerBall, table);
}
void bounceFromObstacle(TImage * ball, TImage * obstacle)
{
        int ballLeftEdge= ball->Left;
        int ballRightEdge = ball->Left + ball->Width;
        int ballTopEdge = ball->Top;
        int ballBottomEdge = ball->Top + ball->Height;
        int obstacleLeftEdge = obstacle->Left;
        int obstacleRightEdge = obstacle->Left + obstacle->Width;
        int obstacleTopEdge = obstacle->Top;
        int obstacleBottomEdge = obstacle->Top + obstacle->Height;

        if ((ballBottomEdge >= obstacleTopEdge
                && ballBottomEdge <= obstacleBottomEdge)
                && ((x > 0 && ballRightEdge >= obstacleLeftEdge
                &&  ballRightEdge <= (obstacleLeftEdge + 9))
                || (x < 0 && ballLeftEdge<= obstacleRightEdge
                && ballLeftEdge>= (obstacleRightEdge - 9))))
        {
                if (sound)     sndPlaySound("Dzwiek/PopPrzeszk.wav", SND_ASYNC);
                x = -x;
        }
          if ((ballRightEdge >= obstacleLeftEdge
                && ballLeftEdge<= obstacleRightEdge)
                && ((y > 0 && ballBottomEdge >= obstacleTopEdge
                && ballBottomEdge <= (obstacleTopEdge + 9))
                || (y < 0 && ballTopEdge <= obstacleBottomEdge
                && ballTopEdge >= (obstacleBottomEdge - 9))))
          {
                if (sound)     sndPlaySound("Dzwiek/PopPrzeszk.wav", SND_ASYNC);
                y = -y;
          }
}
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}

//---------------------------------------------------------------------------
void __fastcall TForm1::Player1UpTimer(TObject *Sender)
{
        if (Player1Racket->Top > Table->Top)     Player1Racket->Top -=10;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Player1DownTimer(TObject *Sender)
{
     if (Player1Racket->Top + Player1Racket->Height < (Table->Top + Table->Height - 10)) Player1Racket->Top += 10;
}

void __fastcall TForm1::Player2UpTimer(TObject *Sender)
{
        if (Player2Racket->Top > Table->Top)
        {
                if (gameWithCPU== false)
                {
                        Player2Racket->Top -=10;
                }
                else
                {
                        playWithCPU (Player2Racket, Ball, difficultyLevel);
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Player2DownTimer(TObject *Sender)
{
        if (Player2Racket->Top + Player2Racket->Height < (Table->Top + Table->Height - 10))
        {
                if (gameWithCPU== false)
                {
                        Player2Racket->Top += 10;
                }
                else
                {
                        playWithCPU (Player2Racket, Ball, difficultyLevel);
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        if (Key == VK_ESCAPE)
        {
                switchBallOnOff(false);
                switchPlayer1OnOff(false);
                switchPlayer2OnOff(false);
                Form1->Panel1->Visible = true;
                Form1->Button6->Visible = true;
                if (gameStarted == true) Form1->Button6->Visible = true;
                else  Form1->Button6->Visible = false;
        }
        if (Key == VK_UP)
        {
                Player1Up->Enabled = true;
                player1MoveUp= true;
                player1MoveDown = false;
        }
        if (Key == VK_DOWN)
        {
                Player1Down->Enabled = true;
                player1MoveUp= false;
                player1MoveDown = true;
        }
        if (gameWithCPU== false)
        {
                if (Key == 0x51)
                {
                        Player2Up->Enabled = true;
                        player2MoveUp = true;
                        player2MoveDown = false;
                }
                if (Key == 0x41)
                {
                        Player2Down->Enabled = true;
                        player2MoveUp = false;
                        player2MoveDown = true;
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        if (Key == VK_UP)
        {
                Player1Up->Enabled = false;
                player1MoveUp= false;
        }

        if (Key == VK_DOWN)
        {
                Player1Down->Enabled = false;
                player1MoveDown = false;
        }

        if (gameWithCPU== false)
        {
                if (Key == 0x51)
                {
                        Player2Up->Enabled = false;
                        player2MoveUp = false;
                }

                if (Key == 0x41)
                {
                        Player2Down->Enabled = false;
                        player2MoveDown = false;
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
        switchPlayer1OnOff (false);
        switchPlayer2OnOff (false);

}
//---------------------------------------------------------------------------

void __fastcall TForm1::TimerBallTimer(TObject *Sender)
{
        Ball->Left += x;
        Ball->Top += y;
        if (Ball->Top >= Table->Top) y = -y;
        if ((Ball->Top + Ball->Height) <=  (Table->Top + Table->Height)) y = -y;

        // skucha  gracza 1
        if (((Ball->Left + Ball->Width) > Player1Racket->Left + 5)
                && (Ball->Top > Player1Racket->Top + Player1Racket->Height
                || Ball->Top + Ball->Height < Player1Racket->Top))
        {
                switchBallOnOff(false);
                switchPlayer1OnOff(false);
                if (!gameWithCPU)    switchPlayer2OnOff(false);
                Form1->Label9->Caption = ++player2points;
                if (player2points < pointsToWin)
                {
                if (sound)     sndPlaySound("Dzwiek/Headshot.wav", SND_ASYNC);
                if( Application->MessageBox(
			"Punkt dla gracza 2. Kliknij OK aby zaserwowac pilke ponownie.","" ,
			MB_OK | MB_ICONQUESTION) == IDOK )
	                startNewSet(Ball, TimerBall, Table);
                }
        }
        // skucha gracza 2
        if (Ball->Left < (Player2Racket->Left +  Player2Racket->Width - 5))
        {
                switchBallOnOff(false);
                switchPlayer1OnOff(false);
                if (!gameWithCPU)    switchPlayer2OnOff(false);
                Form1->Label10->Caption = ++player1points;
                if (player1points < pointsToWin)
                {
                if (sound)     sndPlaySound("Dzwiek/Headshot.wav", SND_ASYNC);
                if( Application->MessageBox(
			"Punkt dla gracza 1. Kliknij OK aby zaserwowac pilke ponownie.","" ,
			MB_OK | MB_ICONQUESTION) == IDOK )
	                startNewSet(Ball, TimerBall, Table);
                }
        }

        // odbicie od paletek
        if ((x < 0 &&Ball->Top + Ball->Height/2 > Player2Racket->Top
                && Ball->Top + Ball->Height/2 < Player2Racket->Top + Player2Racket->Height
                && Ball->Left <= Player2Racket->Left + Player2Racket->Width)
                || (x > 0 && Ball->Top + Ball->Height/2  > Player1Racket->Top
                && Ball->Top + Ball->Height/2 < Player1Racket->Top + Player1Racket->Height
                && Ball->Left + Ball->Width >= Player1Racket->Left))
        {
                x = -x;

                        if ((player1MoveUp&& (Ball->Left > Table->Width/2)) || (player2MoveUp && (Ball->Left < Table->Width/2)))
                        {
                                        y = (y - 1);

                        }
                        else if ((player1MoveDown && (Ball->Left > Table->Width/2)) || (player2MoveDown && (Ball->Left < Table->Width/2)))
                        {
                                        y = (y + 1);
                        }
                       // else
                       //         y = y;


                if (Form1->TimerBall->Interval > 5)  Form1->TimerBall->Interval -= 1;
                if (sound)     sndPlaySound("Dzwiek/pong.wav", SND_ASYNC);
        }
        // odbicie od przeszkod
        if (obstaclesActive)
        {
                bounceFromObstacle(Ball, Obstacle1);
                bounceFromObstacle(Ball, Obstacle2);
                bounceFromObstacle(Ball, Obstacle3);
        }

        if (player1points >= pointsToWin)
        {
                switchPlayer1OnOff(false);
                switchPlayer2OnOff(false);
                switchBallOnOff(false);
                if (sound)     sndPlaySound("Dzwiek/Clapping.wav", SND_ASYNC);
                ShowMessage("Koniec rozgrywki. Wygrywa gracz 1");
                Form1->Panel1->Visible = true;
        }

        if (player2points >= pointsToWin)
        {
                switchPlayer1OnOff(false);
                switchPlayer2OnOff(false);
                switchBallOnOff(false);
                if (sound)     sndPlaySound("Dzwiek/Clapping.wav", SND_ASYNC);
                ShowMessage("Koniec rozgrywki. Wygrywa gracz 2");
                Form1->Panel1->Visible = true;
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Label4Click(TObject *Sender)
{
        if (difficultyLevel == 1) difficultyLevel = 2;
        else if (difficultyLevel == 2) difficultyLevel = 3;
        else if (difficultyLevel == 3) difficultyLevel = 1;

        switch(difficultyLevel)
        {
        case 1: Label4->Caption = "Latwy";  break;
        case 2: Label4->Caption = "Sredni"; break;
        case 3: Label4->Caption = "Trudny"; break;
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Label6Click(TObject *Sender)
{
        if (sound)
        {
                sound = false;
                Label6->Caption = "Wylaczone";
        }
        else
        {
                sound = true;
                Label6->Caption = "Wlaczone";
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Label8Click(TObject *Sender)
{
        Label8->Caption = ++pointsToWin;
        if (pointsToWin >= 20) pointsToWin = 0;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
        switch(difficultyLevel)
        {
        case 1: Label4->Caption = "Latwy";  break;
        case 2: Label4->Caption = "Sredni"; break;
        case 3: Label4->Caption = "Trudny"; break;
        }

        if (sound == true) Label6->Caption = "Wlaczone";
        else Label6->Caption = "Wylaczone";

        if (gameWithCPU== true) Label18->Caption = "Gracz vs Komputer";
        else Label18->Caption = "Gracz vs Gracz";

        Label8->Caption = pointsToWin;
        Panel2->Visible = true;
        Panel1->Visible = false;
        Form1->Button6->Visible = false;
        gameStarted = false;


}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button5Click(TObject *Sender)
{
        Panel2->Visible = false;
        Panel5->Visible = false;
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

void __fastcall TForm1::Button1Click(TObject *Sender)
{
        switchPlayer2OnOff(gameWithCPU);
        startNewGame(Ball, TimerBall, Table);
        gameStarted = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button6Click(TObject *Sender)
{
                switchBallOnOff(true);
                switchPlayer2OnOff(gameWithCPU);
                Form1->Player1Racket->Visible = true;
                Form1->Panel1->Visible = false;
}
//---------------------------------------------------------------------------



void __fastcall TForm1::Label14Click(TObject *Sender)
{
        if (obstaclesActive)
        {
                obstaclesActive = false;
                Label14->Caption = "Wylaczone";
        }
        else
        {
                obstaclesActive = true;
                Label14->Caption = "Wlaczone";
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Label18Click(TObject *Sender)
{
       if (gameWithCPU)
        {
                gameWithCPU= false;
                Label18->Caption = "Gracz vs Gracz";
        }
        else
        {
                gameWithCPU= true;
                Label18->Caption = "Gracz vs Komputer";
        }
}
//---------------------------------------------------------------------------



void __fastcall TForm1::Button2Click(TObject *Sender)
{
        Form1->Panel1->Visible = false;
        Form1->Panel4->Visible = true;        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button7Click(TObject *Sender)
{
        Form1->Panel1->Visible = true;
        Form1->Panel4->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button8Click(TObject *Sender)
{
        if (Form1->Panel5->Visible)
        {
                Form1->Panel5->Visible = false;
                Form1->Button8->Caption = "<-- Pomoc";
        }
        else
        {
                Form1->Panel5->Visible = true;
                Form1->Button8->Caption = "--> Pomoc";
        }
}
//---------------------------------------------------------------------------

