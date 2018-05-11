#include "pch.h"
#include "StageManager.h"
#include <fstream>

std::string getFileData(std::ifstream & _file);


StageManager::StageManager()
{
}

StageManager::~StageManager()
{
}

void StageManager::loadAllStages(RenderData * _RD)
{
	std::ifstream all_stages_file;
	all_stages_file.open("..\\GameAssets\\Stages\\All_Stages.txt");

	int i = 0;
	assert(all_stages_file);
	while (!all_stages_file.eof())
	{
		std::string stage_name = getFileData(all_stages_file);
		std::string file_string = "..\\GameAssets\\Stages\\" + stage_name + ".txt";
		std::ifstream stage_file;
		stage_file.open(file_string);

		m_all_stages.push_back(std::make_unique<Stage>());

		Stage* current_stage = m_all_stages[i].get();
		current_stage->setName(getFileData(stage_file));

		while (!stage_file.eof())
		{
			std::string object_to_load = (getFileData(stage_file));
			if (object_to_load == "platform")
			{
				loadPlatform(_RD, current_stage, stage_file);
			}
			else if (object_to_load == "moving_platform")
			{
				loadMovingPlatform(_RD, current_stage, stage_file);
			}
			else if (object_to_load == "spawn_points")
			{
				loadSpawnPoints(current_stage, stage_file);
			}
			else if (object_to_load == "whatever_object_you_want")
			{

			}
		}

		stage_file.close();
		i++;
	}

	all_stages_file.close();
}

void StageManager::loadPlatform(RenderData * _RD, Stage* _stage, std::ifstream & _opened_file)
{

	Platform* platform = new Platform(_RD,"platform");
	
	float spawnX = std::stof(getFileData(_opened_file));
	float spawnY = std::stof(getFileData(_opened_file));
	platform->SetSpawn(Vector2(spawnX,spawnY));

	float x_scale = std::stof(getFileData(_opened_file));
	float y_scale = std::stof(getFileData(_opened_file));
	platform->SetScale(Vector2(x_scale, y_scale));
	Rectangle rect = Rectangle
	(platform->GetPos().x,platform->GetPos().y,
		platform->TextureSize().x * x_scale,
		platform->TextureSize().y * y_scale);
	
	platform->GetPhysics()->SetCollider(rect);

	_stage->addPlatform(platform);
}

void StageManager::loadMovingPlatform(RenderData * _RD, Stage* _stage, std::ifstream & _opened_file)
{
	float VecX = std::stof(getFileData(_opened_file));
	float VecY = std::stof(getFileData(_opened_file));
	Vector2 start(VecX, VecY);

	VecX = std::stof(getFileData(_opened_file));
	VecY = std::stof(getFileData(_opened_file));
	Vector2 end(VecX, VecY);

	float travel = std::stof(getFileData(_opened_file));
	float stay = std::stof(getFileData(_opened_file));

	MovingPlatform* platform = new MovingPlatform(_RD,start,end,travel,stay, "platform");
	float spawnX = std::stof(getFileData(_opened_file));
	float spawnY = std::stof(getFileData(_opened_file));
	platform->SetSpawn(Vector2(spawnX, spawnY));

	float x_scale = std::stof(getFileData(_opened_file));
	float y_scale = std::stof(getFileData(_opened_file));
	platform->SetScale(Vector2(x_scale, y_scale));

	Rectangle rect = Rectangle
	(platform->GetPos().x, platform->GetPos().y,
		platform->TextureSize().x * x_scale,
		platform->TextureSize().y * y_scale);

	platform->GetPhysics()->SetCollider(rect);

	_stage->addPlatform(platform);

}

void StageManager::loadSpawnPoints(Stage* _stage, std::ifstream & _opened_file)
{
	for (int i = 0; i < 4; i++)
	{
		float VecX = std::stof(getFileData(_opened_file));
		float VecY = std::stof(getFileData(_opened_file));
		_stage->setSpawnPointAtIndex(i, Vector2(VecX, VecY));
	}
}

Stage * StageManager::returnSceneWithIndex(int i)
{
	return m_all_stages[i].get();
}
