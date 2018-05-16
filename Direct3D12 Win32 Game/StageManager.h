#pragma once

#include "Stage.h"

class StageManager
{
public:
/*
loads all stages into memory
*/
	StageManager();
	~StageManager();

	

	void loadAllStages(RenderData* _RD);
	void loadPlatform(RenderData* _RD, Stage* _stage, std::ifstream& _opened_file);
	void loadMovingPlatform(RenderData* _RD, Stage* _stage, std::ifstream& _opened_file);
	void loadSpawnPoints(Stage* _stage, std::ifstream& _opened_file);

	
	Stage* returnSceneWithIndex(int i);


private:


	std::vector<std::unique_ptr<Stage>> m_all_stages;
};

