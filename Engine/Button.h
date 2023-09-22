#pragma once
#include "GameObject.h"

class Button : public GameObject {
public:
	Button(GameObject* parent);
	~Button();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	bool Finished(); // ButtonÇ™èIÇÌÇ¡ÇΩÇÁtrue
	void SetImage(std::string normal, std::string pushed);
	void SetPosition(int x, int y);
	void Push(bool pushed);
	bool MouseInArea(XMFLOAT3 mousePos);
private:
	int hImage_;
	int hPush_;
	bool pushed_;
	XMFLOAT3 center_;
	XMFLOAT3 size_;
};