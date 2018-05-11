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
	Rectangle getSpriteBox() { return m_spritebox; };
	void setFramerate(float _framerate);
	float getFramerate() { return m_framerate;};
	void setMaxFrames(int _maxFrames);
	int getMaxFrames() { return m_maxFrames; };
	void setSpriteBoxStartPos(Vector2 _start);
	Vector2 getSpriteboxStartPos() { return m_spriteBoxStartPos; };
	void setFurthestLeftPos(float _left);
	float getFurthestLeftPos() { return m_furthestLeftPos; };
	void setIncrements(Vector2 _increments);
	Vector2 getIncrements() { return m_spriteBoxIncrements; };

	void setloop(bool _loop);
	void setPlay(bool _play);
	bool getPlay();

	const Vector2 getSpriteScale();


private:
	float m_framerate = 30;
	float m_elapsedTime = 0;
	int m_frames = 0;
	int m_maxFrames = 30;
	bool loop = true;
	bool play = true;
	int m_resourcenum = 0;

	Vector2 m_spriteBoxIncrements;
	Vector2 m_spriteBoxStartPos;
	float m_furthestLeftPos;
	Rectangle m_spritebox;
	Microsoft::WRL::ComPtr<ID3D12Resource> m_texture = nullptr;
};

