#pragma once
#include "Engine/GameObject.h"



//���������Ǘ�����N���X
class SaveManager : public GameObject
{

public:
    //�R���X�g���N�^
    SaveManager(GameObject* parent);

    //�f�X�g���N�^
    ~SaveManager();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

