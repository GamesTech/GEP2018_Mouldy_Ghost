#pragma once
#include "GameObject2D.h"
#include <string>

using std::string;
struct RenderData;

//GEP:: Builds on the Base Game Object 2D class to allow images to be displayed to screen.
// These need to made into dds format objects which can be done using the Images project in the Asset Pipeline solution folder.
// Based on this part of the DirectXTK12 wiki documentation
//https://github.com/Microsoft/DirectXTK12/wiki/Sprites-and-textures 

class ImageGO2D
	: public GameObject2D
{
public:
	ImageGO2D(RenderData* _RD, string _filename, Vector2 _spritesize = Vector2(0,0), int _in_row = 0);
	ImageGO2D() = default;
	virtual ~ImageGO2D();

	virtual void Render(RenderData* _RD, int _sprite = 0,
		Vector2 _cam_pos = Vector2::Zero);

	void scaleFromPoint(Vector2 point, Vector2 scale);

	void CentreOrigin();
	Vector2 TextureSize();

protected:
	void FlipX();
	bool flipped = false;

	Microsoft::WRL::ComPtr<ID3D12Resource> m_texture;
	int m_resourceNum = -1;
	Vector2 m_spriteSize;
};

