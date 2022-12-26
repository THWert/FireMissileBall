#pragma once
#define BMAX 10

struct Bullet
{
	ObLine missile;
	bool isVisible;

	Bullet()
	{
		missile.SetLocalPos(Vector2(2000.0f, 2000.0f));
		missile.scale.x = 0.0f;
		missile.rotation = 0.0f;
		missile.isVisible = false;
	}
};

struct Ball
{
	ObCircle ball;
	bool isVisible;

	Ball()
	{
		ball.SetLocalPos(Vector2(2000.0f, 2000.0f));
		ball.scale.x = 0.0f;
		ball.rotation = 0.0f;
		ball.isVisible = false;
	}
};

class Main : public Scene
{
private:
	ObRect player;
	ObCircle pet;

	Bullet bullet[BMAX];
	Ball missileball[BMAX];

public:
	virtual void Init() override;
	virtual void Release() override; //해제
	virtual void Update() override;
	virtual void LateUpdate() override;//갱신
	virtual void Render() override;
	virtual void ResizeScreen() override;
};
