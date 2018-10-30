#include <string>
#include <vector>
#include "Global.h"
#include "Player.h"
#include "Projectile.h"
#include "Alien.h"
#include "UFO.h"

using namespace std;

LRESULT CALLBACK MessageHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
void Paint(HWND hWnd, LPPAINTSTRUCT lpPS);
HWND CreateMainWindow(HINSTANCE hInstance);
void InitializeGame();
void CleanUpGame();

RECT rc;
HDC hdcMem;
HBITMAP hbmMem, hbmOld;
HBRUSH hbrBkGnd, hbrPlayer, hbrAlien, hbrUFO;
HFONT hFontMenu;
HFONT hFontGame;

UINT frames = 0;
UINT winSizeX = 500;
UINT winSizeY = 500;
UINT interval = (int)(1000/60.0f);
UINT score = 0;
int gamestate = 0; //0 = menu, 1 = game, 2 = game over

bool pressedSpace;
bool pressedLeft;
bool pressedRight;

Player* player;
Projectile* projectilePlayer;
vector<Alien*> aliens;
vector<Projectile*> projectilesAliens;
UFO* ufo;

IntVector2 playerSize;

int alienDir;
IntVector2 alienMovement;
int alienDownSpeed;
IntVector2 alienSize;
int alienShootProbability;

IntVector2 projectileSize;

int ufoDir;
IntVector2 ufoSize;
float ufoSpawnProbability;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
   LPSTR lpCmdLine, int nCmdShow)
{
   HWND hWnd = CreateMainWindow(hInstance);   

   SetTimer(hWnd, 1, interval, (TIMERPROC)NULL);

   MSG msg;

   while (GetMessage(&msg, NULL, 0, 0))
   {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
   }
   
   CleanUpGame();
   DeleteObject(hbrPlayer);
   DeleteObject(hbrAlien);
   DeleteObject(hbrUFO);
   DeleteObject(hbmMem);
   DeleteObject(hbmOld);
   DeleteObject(hFontMenu);
   DeleteObject(hFontGame);
   DeleteDC(hdcMem);
   return 0;
}

void CleanUpGame()
{
   if (player)
   {
      delete player;
      player = NULL;
   }
      
   if (projectilePlayer)
   {
      delete projectilePlayer;
      projectilePlayer = NULL;
   }
      
   for (int i = 0; i < (int)projectilesAliens.size(); i++)
   {
      delete projectilesAliens[i];
      projectilesAliens.erase(projectilesAliens.begin() + i);
      i--;
   }
   for (int i = 0; i < (int)aliens.size(); i++)
   {
      delete aliens[i];
      aliens.erase(aliens.begin() + i);
      i--;
   }
   if (ufo)
   {
      delete ufo;
      ufo = NULL;
   }
      
}

void InitializeGame()
{
   CleanUpGame();
   gamestate = 1;
   score = 0;
   pressedSpace = false;
   pressedLeft = false;
   pressedRight = false;
   alienSize = IntVector2{ 8, 8 };
   playerSize = IntVector2{ 16, 8 };
   projectileSize = IntVector2{ 3, 7 };
   ufoSize = IntVector2{ 15, 8 };
   player = new Player(IntVector2{ (int)(winSizeX * 0.5f), (int)winSizeY - playerSize.y * 2}, playerSize, winSizeX, winSizeY);
   ufo = NULL;
   UINT w = 11;
   UINT h = 5;
   int points;
   for (int x = 0; x < w; x++)
   {
      for (int y = 0; y < h; y++)
      {
         if (y == 0)
         {
            points = 40;
         }
         else if (y == 1 || y == 2)
         {
            points = 20;
         }
         else
         {
            points = 10;
         }
         aliens.push_back(new Alien(IntVector2{ x * (int)(alienSize.x * 2.0f) + alienSize.x, y * (int)(alienSize.y * 2.0f) + (int)(alienSize.y * 2.5f) }, alienSize, winSizeX, points));
      }
   }
   alienDir = 2;
   alienDownSpeed = 4;
   alienShootProbability = 5;

   ufoDir = 6;
   ufoSpawnProbability = 0.1f;
}

void DecideAlienMovement()
{
   int closestToWall = winSizeX * 0.5f;
   if (alienDir > 0) {
      for (vector<Alien*>::iterator i = aliens.begin(); i != aliens.end(); ++i)
      {
         if ((*i)->GetPos().x > closestToWall)
            closestToWall = (*i)->GetPos().x;
      }
      if (closestToWall >= winSizeX - alienSize.x * 0.5f)
      {
         alienDir = alienDir * -1;
         alienMovement = IntVector2{ 0, alienDownSpeed };
      }
      else
      {
         alienMovement = IntVector2{ alienDir, 0 };
      }
   }
   else if(alienDir < 0)
   {
      for (vector<Alien*>::iterator i = aliens.begin(); i != aliens.end(); ++i)
      {
         if ((*i)->GetPos().x < closestToWall)
            closestToWall = (*i)->GetPos().x;
      }
      if (closestToWall <= 0 + alienSize.x * 0.5f)
      {
         alienDir = alienDir * -1;
         alienMovement = IntVector2{ 0, alienDownSpeed };
      }
      else
      {
         alienMovement = IntVector2{ alienDir, 0 };
      }
   }

   for (vector<Alien*>::iterator i = aliens.begin(); i != aliens.end(); ++i)
   {
      if ((*i)->GetPos().x > closestToWall)
         closestToWall = (*i)->GetPos().x;
   }
}

bool RectCollision(RECT* rect1, RECT* rect2)
{
   if (
      rect1->top < rect2->bottom &&
      rect1->bottom > rect2->top &&
      rect1->left < rect2->right &&
      rect1->right > rect2->left)
      return true;
   return false;
}

void TestCollisionPlayerProjectile()
{
   if (projectilePlayer)
   {
      if (ufo && RectCollision(projectilePlayer->GetRect(), ufo->GetRect()))
      {
         delete projectilePlayer;
         projectilePlayer = NULL;
         score += ufo->GetPoints();
         delete ufo;
         ufo = NULL;
         return;
      }
      for (int i = 0; i < (int)aliens.size(); i++)
      {
         if (RectCollision(projectilePlayer->GetRect(), aliens[i]->GetRect()))
         {
            delete projectilePlayer;
            projectilePlayer = NULL;
            score += aliens[i]->GetPoints();
            delete aliens[i];
            aliens.erase(aliens.begin() + i);
            
            return;
         }
      }
   }
}

void TestCollisionAlienProjectiles()
{
   for (int i = 0; i < (int)projectilesAliens.size(); i++)
   {
      if (player && RectCollision(player->GetRect(), projectilesAliens[i]->GetRect()))
      {
         delete player;
         player = NULL;
         gamestate = 2;
         delete projectilesAliens[i];
         projectilesAliens.erase(projectilesAliens.begin() + i);
         i--;
         return;
      }
      if (projectilesAliens[i]->GetRect()->bottom > winSizeY)
      {
         delete projectilesAliens[i];
         projectilesAliens.erase(projectilesAliens.begin() + i);
         i--;
      }
   }
}

void TestCollisionProjectiles()
{
   if (projectilePlayer)
   {
      for (int i = 0; i < (int)projectilesAliens.size(); i++)
      {
         if (RectCollision(projectilePlayer->GetRect(), projectilesAliens[i]->GetRect()))
         {
            delete projectilePlayer;
            projectilePlayer = NULL;
            delete projectilesAliens[i];
            projectilesAliens.erase(projectilesAliens.begin() + i);
            return;
         }
      }
   }
}

HWND CreateMainWindow(HINSTANCE hInstance)
{
   WNDCLASSEX wndClass = {
      sizeof(WNDCLASSEX),
      CS_DBLCLKS | CS_OWNDC |
      CS_HREDRAW | CS_VREDRAW,
      MessageHandler,
      0,
      0,
      hInstance,
      LoadIcon(NULL, IDI_WINLOGO),
      LoadCursor(NULL, IDC_ARROW),
      (HBRUSH)GetStockObject(WHITE_BRUSH),
      NULL,
      "Main",
      LoadIcon(NULL, IDI_WINLOGO)
   };

   RegisterClassEx(&wndClass);

   RECT desktop;
   const HWND hDesktop = GetDesktopWindow();
   GetWindowRect(hDesktop, &desktop);

   return CreateWindowEx(
      NULL,
      "Main",
      "Space Invaders",
      WS_OVERLAPPEDWINDOW | WS_VISIBLE,
      (int)(desktop.right * 0.5f - (winSizeX + 16) * 0.5f), (int)(desktop.bottom * 0.5f - (winSizeY + 39) * 0.5f),
      winSizeX + 16, winSizeY + 39,
      NULL,
      NULL,
      hInstance,
      NULL);
}

LRESULT CALLBACK MessageHandler(
   HWND hWnd,
   UINT msg,
   WPARAM wParam,
   LPARAM lParam)
{
   switch (msg)
   {
   case WM_CLOSE:
      PostQuitMessage(0);
      return 0;
      break;
   case WM_KEYDOWN:
      if (player)
      {
         switch (wParam)
         {
         case VK_LEFT:
            //player->Move(-1);
            pressedLeft = true;
            break;
         case VK_RIGHT:
            //player->Move(1);
            pressedRight = true;
            break;
         case VK_SPACE:
            pressedSpace = true;
            break;
         }
      }
      break;
   case WM_KEYUP:
      if (gamestate == 0 && wParam == VK_RETURN)
         InitializeGame();
      else if (gamestate == 2 && wParam == VK_RETURN)
         gamestate = 0;
      switch (wParam)
      {
      case VK_LEFT:
         //player->Move(0);
         pressedLeft = false;
         break;
      case VK_RIGHT:
         //player->Move(0);
         pressedRight = false;
         break;
      case VK_SPACE:
         pressedSpace = false;
         break;
      case VK_ESCAPE:
         PostQuitMessage(0);
         break;
      case VK_F5:
         InitializeGame();
         break;
      }
      break;
   case WM_ERASEBKGND:
      return (LRESULT)1;
      break;
   case WM_TIMER:
      //Hier Updaten
      switch (gamestate)
      {
      case 0:
         break;
      case 2:
         break;
      case 1:
         if (player)
         {
            player->Update();
            if (pressedSpace && !projectilePlayer)
               projectilePlayer = player->Shoot();
            if (pressedLeft)
               player->Move(-1);
            else if (pressedRight)
               player->Move(1);
            else
               player->Move(0);
         }

         if (projectilePlayer)
         {
            projectilePlayer->Update();
            if (projectilePlayer->deleteThis) {
               delete projectilePlayer;
               projectilePlayer = NULL;
            }
         }
         if (ufo)
         {
            if (ufo->GetPos().x < ufoSize.x * 0.5f * -1)
            {
               ufoDir = abs(ufoDir);
            }
            else if (ufo->GetPos().x > winSizeX + ufoSize.x * 0.5f)
            {
               ufoDir = abs(ufoDir) * -1;
            }
            ufo->Update(ufoDir);
         }

         DecideAlienMovement();

         for (vector<Alien*>::iterator i = aliens.begin(); i != aliens.end(); ++i)
            (*i)->Update(alienMovement);
         for (vector<Projectile*>::iterator i = projectilesAliens.begin(); i != projectilesAliens.end(); ++i)
            (*i)->Update();
         if (aliens.size() > 0 && rand() % 100 < alienShootProbability)
            projectilesAliens.push_back(new Projectile(aliens.at(rand() % aliens.size())->GetPos(), projectileSize, 2, winSizeX));
         else if (aliens.size() == 0)
         {
            int points = score;
            InitializeGame();
            score = points;
            alienDownSpeed += alienDownSpeed * score * 0.001;
         }
         if (!ufo && rand() % 1000 <= (int)ufoSpawnProbability * 10)
         {
            ufo = new UFO(IntVector2{ (int)(ufoSize.y * -1), ufoSize.y }, ufoSize);
         }

         TestCollisionPlayerProjectile();
         TestCollisionAlienProjectiles();
         TestCollisionProjectiles();
         break;
      }
      RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_INTERNALPAINT);
      frames++;
      return 0;
      break;
   case WM_PAINT:
      PAINTSTRUCT ps;
      HDC hdc = GetDC(hWnd);
      BeginPaint(hWnd, &ps);
      //hier zeichnen
      Paint(hWnd, &ps);

      SetPixel(hdc, 10, 10, RGB(0, 0, 0));
      EndPaint(hWnd, &ps);
      return 0;
      break;
   }
   return DefWindowProc(hWnd, msg, wParam, lParam);
}

void Paint(HWND hWnd, LPPAINTSTRUCT lpPS)
{
   if (!hbmMem)
   {
      hbrPlayer = CreateSolidBrush(RGB(0, 255, 0));
      hbrAlien = CreateSolidBrush(RGB(255, 255, 255));
      hbrUFO = CreateSolidBrush(RGB(255, 0, 0));
      GetClientRect(hWnd, &rc);
      hdcMem = CreateCompatibleDC(lpPS->hdc);

      hbmMem = CreateCompatibleBitmap(
         lpPS->hdc,
         rc.right - rc.left,
         rc.bottom - rc.top);

      hFontMenu = CreateFont(48, 0, 0, 0, FW_BOLD, false, false, false, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("OCR A Extended"));
      hFontGame = CreateFont(20, 0, 0, 0, FW_BOLD, false, false, false, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("OCR A Extended"));
   }
   hbmOld = (HBITMAP)SelectObject(hdcMem, hbmMem);

   hbrBkGnd = CreateSolidBrush(RGB(0, 0, 0));
   FillRect(hdcMem, &rc, hbrBkGnd);
   DeleteObject(hbrBkGnd);

   SetBkMode(hdcMem, TRANSPARENT);

   //SetWindowText(hWnd, ("F: " + std::to_string(frames)).c_str());
   
   SYSTEMTIME swinSizeYstime;
   GetSystemTime(&swinSizeYstime);

   //Hier zeichnen
   switch (gamestate)
   {
   case 0:
      SelectObject(hdcMem, hFontMenu);
      SetTextColor(hdcMem, RGB(255, 255, 255));
      TextOut(hdcMem, winSizeX * 0.1f + 3, winSizeY * 0.2f + 2, "SPACE INVADERS", 14);
      
      SetTextColor(hdcMem, RGB(204, 204, 0));
      TextOut(hdcMem, winSizeX * 0.1f, winSizeY * 0.2f, "SPACE INVADERS", 14);

      SetTextColor(hdcMem, RGB(255, 255, 255));
      TextOut(hdcMem, winSizeX * 0.2f, winSizeY * 0.5f, "Press ENTER",11);
      TextOut(hdcMem, winSizeX * 0.2f, winSizeY * 0.6f, "to start", 8);
      break;
   case 2:
      SelectObject(hdcMem, hFontMenu);
      SetTextColor(hdcMem, RGB(255, 0, 0));
      TextOut(hdcMem, winSizeX * 0.25f, winSizeY * 0.45f, "GAME OVER", 9);
      break;
   case 1:
      SelectObject(hdcMem, hFontGame);
      SetTextColor(hdcMem, RGB(255, 255, 255));
      string scoreText = "Score: " + std::to_string(score);
      TextOut(hdcMem,5, 0, scoreText.c_str(), scoreText.length());

      if (player)
         player->Draw(hdcMem, hbrPlayer);
      if (projectilePlayer)
         projectilePlayer->Draw(hdcMem, hbrPlayer);

      for (vector<Alien*>::iterator i = aliens.begin(); i != aliens.end(); ++i)
         (*i)->Draw(hdcMem, hbrAlien);
      for (vector<Projectile*>::iterator i = projectilesAliens.begin(); i != projectilesAliens.end(); ++i)
         (*i)->Draw(hdcMem, hbrAlien);

      if (ufo)
         ufo->Draw(hdcMem, hbrUFO);
      break;
   }

   BitBlt(lpPS->hdc,
      rc.left, rc.top,
      rc.right - rc.left, rc.bottom - rc.top,
      hdcMem,
      0, 0,
      SRCCOPY);
}