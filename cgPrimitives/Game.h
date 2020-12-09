#pragma once
#include "Base/GameState.h"
#include "Base/GameStateManager.h"
#include "Graphic/Mesh.h"
#include "Graphic/Shader.h"
#include "Base/ShaderManager.h"
#include "Base/ResourceManager.h"
#include "Graphic/Model.h"
#include "Graphic/Skybox.h"
#include "Player.h"
#include "Graphic/GUI.h"
#include "Graphic/GUILine.h"
#include<vector>

class Game : public GameState
{
private:
	Platform* platform = nullptr;
	GameStateManager* manager = nullptr;
	ResourceManager* resourceManager = nullptr;
	ShaderManager* shaderManager = nullptr; 
	Player *player = nullptr;
	Graphic::GUI* gui = nullptr;
	Graphic::GUILine* m_image = nullptr;
	int opcion;
	enum primitiva
	{
		linea,
		curva,
		circulo,
	};
	struct Vector 
	{
		int x, y;
	};
	std::stack<Vector> clicks;
public:
	Game();
	~Game();
	void Init() override;
	void Draw() override;
	bool Input(std::map<int, bool> keys) override;
	bool MouseInput(int x, int y, bool leftbutton);
	void Update(unsigned int delta) override;
	void Close() override;
	void LoadShaders();
	void LoadModels(const std::map<std::string, std::string>& models);
	void recta(float x, float y, float x2, float y2);
	void rectasindiv(float x, float y, float x2, float y2);
	void bresenham(float x, float y, float x2, float y2);
	void bresenhamcurva(float x, float y, float x2, float y2, float x3, float y3, float x4, float y4);
	void CirculoBresenham(float x1, float y1, int r);
	void Problema3(float x1, float y1, float x2, float y2);
	void estrella();
};
