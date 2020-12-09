#include "Game.h"
#include<iostream>
#include <glm.hpp>
#include <time.h>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
#include <math.h>
#include <chrono>
#include <thread>
#define _USE_MATH_DEFINES

float angle = 0;
float medio = 2;
float c = 0;
float m = 0;
float a = 20;
float b = 20;
Game::Game()
{

}

Game::~Game()
{
}

void Game::Init()
{
	std::cout << " Menu Init" << std::endl;
	this->platform = Platform::GetPtr();
	this->manager = GameStateManager::GetPtr();
	resourceManager = ResourceManager::GetPtr();
	
	auto resourceManger = ResourceManager::GetPtr();
	resourceManger->Add(ResourceType::GUILine, "Line");

	resourceManger->Wait();
	player = new Player();

	LoadShaders();

	resourceManger->Load();
	m_image = (Graphic::GUILine*) resourceManager->GetElement("Line");
	srand(time(NULL));
	gui = new Graphic::GUI(m_image, player->GetCamera(), shaderManager);
	for (int i = 0; i < 1024; i++) 
	{
		m_image->PutPixel(i, 500, 50, 50,  255, 255);
		m_image->PutPixel(500, i, 50, 50, 255, 255);

	}
	//recta(110, 100, 410, 200);
	//bresenham(100, 100, 400, 200);
	//bresenhamcurva(200,200,200,300,300,300,300,200);
	//bresenhamcurva(300, 200, 300, 100, 400, 100, 400, 200);
	//CirculoBresenham(500, 450, 200);
	//recta(100,100,300,200);
	//recta(300, 200, 400, 200);
	//recta(100, 100, 400, 200);
	 //Problema3(100, 100, 300, 200);
	 //Problema3(300, 200, 400, 200);
	 //Problema3(100, 100, 400, 200);
	estrella();

	
	m_image->Load();
}

void Game::LoadShaders()
{
	shaderManager = ShaderManager::getPtr();
	shaderManager->initShader(player->GetCamera());
	shaderManager->LoadShaders("gui", "Assets/Shaders/gui.vert", "Assets/Shaders/gui.frag");
}

void Game::Draw()
{
	shaderManager->draw();
}

void Game::rectasindiv(float x, float y, float x2, float y2) 
{
	float dy = y2 - y;
	float dx = x2 - x;
	float deno;
	if (abs(dy) < abs(dx)) 
	{
		deno = abs(dx);
	}
	else if (abs(dy) >= abs(dx)) 
	{
		deno = abs(dy);
	}
	float xinc = dx / deno;
	float yinc = dy / deno;
	m_image->PutPixel(x, y, 0, 0, 0, 255);
	for (int i = 0; i <= abs(deno); i++) 
	{
		x = x + xinc;
		y = y + yinc;
		m_image->PutPixel(x, y, 0, 0, 0, 255);
	}
	m_image->Load();
}

void Game::CirculoBresenham(float x1, float y1, int r) {
	int R[8] = {100,150,200,0,0,0,0,0};
	int G[8] = {0,150,100,50,100,250,0,0};
	int B[8] = { 0,0,0,50,100,150,200,250 };
	float x = 0;
	float y = r;
	float p = 1 - r;
	while (x <= y) {
		m_image->PutPixel(x + x1, y + y1, R[0], G[0], B[0], 255);
		m_image->PutPixel(-x + x1, y + y1, R[1], G[1], B[1], 255);
		m_image->PutPixel(-x + x1, -y + y1, R[2], G[2], B[2], 255);
		m_image->PutPixel(x + x1, -y + y1, R[3], G[3], B[3], 255);
		m_image->PutPixel(-y + x1, x + y1, R[4], G[4], B[4], 255);
		m_image->PutPixel(-y + x1, -x + y1, R[5], G[5], B[5], 255);
		m_image->PutPixel(y + x1, -x + y1, R[6], G[6], B[6], 255);
		m_image->PutPixel(y + x1, x + y1, R[7], G[7], B[7], 255);
		m_image->Load();
		



		if (p <= 0) {
			x++;
			y = y;
			p = p + (2 * x) + 3;

		}
		else {
			x++;
			y--;
			p = p + (2 * x) - (2 * y) + 5;

		}

	}

}

void Game::bresenhamcurva(float x, float y, float x2, float y2, float x3, float y3, float x4, float y4) 
{
	float u = 0;
	float inc = 0.001f;
	float x1 = 0;
	float y1 = 0;
	while (u <= 1) 
	{
		x1 = x4 * pow(u, 3) + 3*x3 * pow(u, 2)*(1 - u) + 3*x2 * u*pow((1 - u), 2) + x * pow((1 - u), 3);
		y1 = y4 * pow(u, 3) + 3*y3 * pow(u, 2)*(1 - u) + 3*y2 * u*pow((1 - u), 2) + y * pow((1 - u), 3);
		m_image->PutPixel(x1, y1, 0, 0, 0, 255);
		u += inc;
	}
	m_image->Load();

}

void Game::estrella() 
{
	CirculoBresenham(500, 450, 200);
	recta(500, 300, 600, 400);
	recta(400, 400, 500, 300);
	recta(300, 400, 400, 400);
	recta(300, 400, 400, 450);
	recta(350, 550, 400, 450);
	recta(350, 550, 500, 500);
	recta(600, 400, 700, 400);
	recta(600, 450, 700, 400);
	recta(600, 450, 650, 550);
	recta(500, 500, 650, 550);
}

void Game::bresenham(float x, float y, float x2, float y2) 
{
	float dx = x2 - x;
	float dy = y2 - y;
	float p = 2 * dy - dx;
	m_image->PutPixel(x, y, 0, 0, 0, 255);
	for (int i = 0; i <= dx; i++) 
	{
		if (p > 0) 
		{
			x = x + 1;
			y = y;
			p = p + 2 * dy;
			m_image->PutPixel(x, y, 0, 0, 0, 255);
		}
		else 
		{
			x = x + 1;
			y = y + 1;
			p = p + 2 * dy + -2 * dx;
			m_image->PutPixel(x, y, 0, 0, 0, 255);
		}
		m_image->Load();
	}
}

void Game::Problema3(float x1, float y1, float x2, float y2) 
{
	float newX1=x1*cos(M_PI/4)-y1*sin(M_PI/4);
	float newY1=x1*sin(M_PI/4)+y1*cos(M_PI/4);
	float newX2 = x2 * cos(M_PI/4) - y2 * sin(M_PI/4);
	float newY2 = x2 * sin(M_PI/4) + y2 * cos(M_PI/4);
	recta(2 * newX1, 2 * newY1, 2 * newX2, 2 * newY2);
	
}

void Game::recta(float x, float y, float x2, float y2) 
{
	
	m = (y2 - y) / (x2 - x);
	c = y - (m * x);
	int ofset = 512;
	if (m > 1) 
	{
		while (y < y2)
		{
			x = (y - c )/ m;
			m_image->PutPixel(x, y, 0, 0, 0, 255);
			y++;
		}
	}
	m_image->Load();
	if(m<=1)
	{
		while (x < x2)
		{
			y = m * x + c;
			m_image->PutPixel(x, y, 0, 0, 0, 255);
			x++;
		}
	}
	m_image->Load();

}
void Game::Update(unsigned int delta)
{
	
	//x = 200/medio;
	//y = 200/medio;
	//x = (a + b * angle)*cos(angle);
	//y = (a+b*angle)* sin(angle);
	//angle+=.01;

	
		/*while (y < y2)
		{
			y = m * x + c;
			m_image->PutPixel(x, y, 0, 0, 0, 255);
			y++;
			m_image->Load();
		}*/
	
	
	

	
	//m_image->PutPixel(x, y, 0, 0, 0, 255);
	//medio += 2;
	
	opcion = primitiva::linea;
	switch(opcion)
	{
		case primitiva::linea:
			if (clicks.size() >= 2) 
			{
				Vector click1 = clicks.top();
				clicks.pop();
				Vector click2 = clicks.top();
				clicks.pop();
				recta(click1.x, click1.y, click2.x, click2.y);
			}
			break;
	}
	m_image->Load();
}

bool Game::MouseInput(int x, int y, bool leftbutton)
{
	if (leftbutton) 
	{
		Vector click;
		click.x = x;
		click.y = y;
		clicks.push(click);
	}
	return false;
}

bool Game::Input(std::map<int, bool> keys)
{
	
	return false;
}

void Game::Close()
{
	std::cout << " Close Init" << std::endl;
}
