#include "pch.h" 
#include "MovingPlatform.h"
#include "ImageGO2D.h"
#include "GameStateData.h"
#include "RenderData.h"

/*
platform will be constantly moving between start and end positions
"stay" param indicates how long will the platform stay idling after the goal was reached
*/
MovingPlatform::MovingPlatform(RenderData * _RD, Vector2 _start, Vector2 _end, float _travel_time, float _stay, string _filename) 
{
	m_physics = new Physics2D(_RD, _filename);
	m_physics->SetOwner(this);
	m_physics->SetGrav(0);

	start_pos = _start;
	end_pos = _end;

	travel_time = _travel_time;
	stay_time = _stay;

	tag = GameObjectTag::PLATFORM;


	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	string fullpath = "../DDS/" + _filename + ".dds";
	std::wstring wFilename = converter.from_bytes(fullpath.c_str());

	ResourceUploadBatch resourceUpload(_RD->m_d3dDevice.Get());

	resourceUpload.Begin();

	DX::ThrowIfFailed(
		CreateDDSTextureFromFile(_RD->m_d3dDevice.Get(), resourceUpload, wFilename.c_str(),
			m_texture.ReleaseAndGetAddressOf()));


	CreateShaderResourceView(_RD->m_d3dDevice.Get(), m_texture.Get(),
		_RD->m_resourceDescriptors->GetCpuHandle(m_resourceNum = _RD->m_resourceCount++));

	auto uploadResourcesFinished = resourceUpload.End(_RD->m_commandQueue.Get());

	uploadResourcesFinished.wait();
}

MovingPlatform::MovingPlatform()
{
}



MovingPlatform::~MovingPlatform()
{
}

void MovingPlatform::Tick(GameStateData * _GSD)
{
	float dt = _GSD->m_dt;

	elapsed_time += dt;

	if (!stay)
	{
		Vector2 newpos = Vector2(0, 0);
		float lerp_value = elapsed_time / travel_time;

		if (direction)
		{
			newpos = Vector2::Lerp(start_pos, end_pos, lerp_value);
		}
		else
		{
			newpos = Vector2::Lerp(end_pos, start_pos, lerp_value);
		}

		if (elapsed_time > travel_time)
		{
			elapsed_time = 0;
			stay = true;
			direction = !direction;
		}

		
		m_pos = newpos;
	}
	else
	{
		if (elapsed_time > stay_time)
		{
			elapsed_time = 0;
			stay = false;
		}
	}
}
