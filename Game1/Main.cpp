#include "stdafx.h"
#include "Main.h"

void Main::Init()
{
    player.SetWorldPos(Vector2(0.0f, 0.0f));
    player.scale = Vector2(80.0f, 80.0f);
    player.rotation = 0.0f;
    player.isAxis = true;
    player.isFilled = false;
    player.isVisible = true;
    player.color = Color(4.0f / 255.0f, 176.0f / 255.0f, 153.0f / 255.0f, 1.0f);

    pet.SetParentRT(player);
    pet.SetLocalPos(Vector2(100.0f, 100.0f));
    pet.scale = Vector2(30.0f, 30.0f);
    pet.rotation = 0.0f;
    pet.isAxis = true;

    for (int i = 0; i < BMAX; i++)
    {
        missileball[i].ball.SetParentRT(bullet[i].missile);
        missileball[i].ball.SetLocalPos(Vector2(30.0f, 30.0f));
        missileball[i].ball.scale = Vector2(10.0f, 10.0f);
        missileball[i].ball.rotation = 0.0f;
        missileball[i].ball.isAxis = false;
        missileball[i].ball.isFilled = true;
        missileball[i].ball.isVisible = true;
        missileball[i].ball.color = Color(0.5f, 0.5f, 0.5f, 1.0f);
    }

}

void Main::Release()
{
}

void Main::Update()
{
    if (INPUT->KeyPress(VK_UP))
    {
        player.MoveWorldPos(player.GetUp() * 200.0f * DELTA);
    }
    if (INPUT->KeyPress(VK_DOWN))
    {
        player.MoveWorldPos(-player.GetUp() * 200.0f * DELTA);
    }
    if (INPUT->KeyPress(VK_LEFT))
    {
        player.rotation -= 120.0f * ToRadian * DELTA;
    }
    if (INPUT->KeyPress(VK_RIGHT))
    {
        player.rotation += 120.0f * ToRadian * DELTA;
    }

    if (INPUT->KeyDown('R'))
    {
        for (int i = 0; i < BMAX; i++)
        {
            bullet[i].isVisible = false;
            missileball[i].isVisible = false;

            if (!bullet[i].isVisible)
            {
                BMAX - 10;
            }
        }
    }

    //발사해라
    if (INPUT->KeyDown(VK_SPACE))
    {
        for (int i = 0; i < BMAX; i++)
        {
            if (!bullet[i].isVisible)
            {
                missileball[i].isVisible = true;
                bullet[i].isVisible = true;
                bullet[i].missile.rotation = Utility::DirToRadian(player.GetRight());
                bullet[i].missile.SetWorldPos(player.GetWorldPos());
                break;
            }
        }       
    }

    for (int i = 0; i < BMAX; i++)
    {
        if (bullet[i].isVisible)
        {
            bullet[i].missile.MoveWorldPos(bullet[i].missile.GetRight() * 200.0f * DELTA);
        }
    }

    pet.revolution += 30.0f * ToRadian * DELTA;

    for (int i = 0; i < BMAX; i++)
    {
        missileball[i].ball.revolution += 500.0f * ToRadian * DELTA;
    }

    player.Update();
    pet.Update();

    for (int i = 0; i < BMAX; i++)
    {
        if (!bullet[i].isVisible) continue;
        bullet[i].missile.Update();
        missileball[i].ball.Update();
    }
}

void Main::LateUpdate()
{
}

void Main::Render()
{
    player.Render();
    pet.Render();

    for (int i = 0; i < BMAX; i++)
    {
        if (!bullet[i].isVisible) continue;
        bullet[i].missile.Render();
        missileball[i].ball.Render();
    }
}

void Main::ResizeScreen()
{
}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
    app.SetAppName(L"Game1");
    app.SetInstance(instance);
	app.InitWidthHeight(1400,800.0f);
	WIN->Create();
	Main* main = new Main();
	int wParam = (int)WIN->Run(main);
	SafeDelete(main);
	WIN->Destroy();
	WIN->DeleteSingleton();
	
	return wParam;
}