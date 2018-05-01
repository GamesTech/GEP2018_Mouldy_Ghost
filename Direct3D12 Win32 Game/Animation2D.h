#pragma once
class Animation2D
{
public:
	Animation2D(RenderData * _RD, string _filename, int _resourceNum);
	~Animation2D();
	void Render(RenderData * _RD, Vector2 _cam_pos, float _zoom, Vector2 _scale,
		Vector2 _pos, int _resourceNum, Color _colour, float _orientation, Vector2 _origin, bool _flipped);
	void update(GameStateData* _GSD);

	void reset();
	void setSpriteBox(Rectangle _box);
	void setFramerate(float _framerate);
	void setMaxFrames(int _maxFrames);
	void setSpriteBoxStartPos(Vector2 _start);
	void setIncrements(Vector2 _increments);

private:
	float m_framerate = 30;
	float m_elapsedTime = 0;
	int m_frames = 0;
	int m_maxFrames = 30;

	Vector2 m_spriteBoxIncrements;
	Vector2 m_spriteBoxStartPos;
	Rectangle m_spritebox;
	Microsoft::WRL::ComPtr<ID3D12Resource> m_texture = nullptr;
};

