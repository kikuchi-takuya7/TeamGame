#include "Input.h"
#include "Global.h"

#include "Imgui/imgui.h"
#include "Imgui/imgui_internal.h"

namespace Input
{
	//�E�B���h�E�n���h��
	HWND	hWnd_;

	//DirectInput�I�u�W�F�N�g
	LPDIRECTINPUT8			pDInput_;

	//�L�[�{�[�h
	LPDIRECTINPUTDEVICE8	pKeyDevice_;	//�f�o�C�X�I�u�W�F�N�g
	BYTE keyState_[256];					//���݂̊e�L�[�̏��
	BYTE prevKeyState_[256];				//�O�t���[���ł̊e�L�[�̏��

	//�}�E�X
	LPDIRECTINPUTDEVICE8	pMouseDevice_;	//�f�o�C�X�I�u�W�F�N�g
	DIMOUSESTATE mouseState_;				//�}�E�X�̏��
	DIMOUSESTATE prevMouseState_;			//�O�t���[���̃}�E�X�̏��
	POINT mousePos_;							//�}�E�X�J�[�\���̈ʒu

	//�R���g���[���[
	const int MAX_PAD_NUM = 4;
	XINPUT_STATE controllerState_[MAX_PAD_NUM];
	XINPUT_STATE prevControllerState_[MAX_PAD_NUM];




	//������
	void Initialize(HWND hWnd)
	{
		//�E�B���h�E�n���h��
		hWnd_ = hWnd;

		//DirectInput�{��
		DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION,
			IID_IDirectInput8, (VOID**)&pDInput_, nullptr);

		//�L�[�{�[�h
		pDInput_->CreateDevice(GUID_SysKeyboard, &pKeyDevice_, nullptr);
		pKeyDevice_->SetDataFormat(&c_dfDIKeyboard);
		pKeyDevice_->SetCooperativeLevel(NULL, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);

		//�}�E�X
		pDInput_->CreateDevice(GUID_SysMouse, &pMouseDevice_, nullptr);
		pMouseDevice_->SetDataFormat(&c_dfDIMouse);
		pMouseDevice_->SetCooperativeLevel(hWnd_, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	}


	//�X�V
	void Update()
	{
		//�L�[�{�[�h
		pKeyDevice_->Acquire();
		memcpy(prevKeyState_, keyState_, sizeof(keyState_));
		pKeyDevice_->GetDeviceState(sizeof(keyState_), &keyState_);

		//�}�E�X
		bool flag = true;
		//imgui�̃E�B���h�E��ŃQ�[����ʂɃ}�E�X���͂������Ȃ��悤�ɂ���
		ImGuiContext& g = *GImGui;
		for (int i = 1; i != g.Windows.Size; i++) {//0�ɂ�imgui�̏����E�B���h�E�H�݂����Ȃ̂������Ă邽��1����
			ImGuiWindow* window = g.Windows[i];
			ImVec2 windowPos = window->Pos;
			ImVec2 windowSize = window->Size;
			ImVec2 mousePos = ImGui::GetMousePos();
			if (mousePos.x > windowPos.x && mousePos.y > windowPos.y && mousePos.x < windowPos.x + windowSize.x && mousePos.y < windowPos.y + windowSize.y) {
				flag = false;
			}
		}
		if (flag == true) {
			pMouseDevice_->Acquire();
			memcpy(&prevMouseState_, &mouseState_, sizeof(mouseState_));
			pMouseDevice_->GetDeviceState(sizeof(mouseState_), &mouseState_);
		}

		//�R���g���[���[
		for (int i = 0; i < MAX_PAD_NUM; i++)
		{
			memcpy(&prevControllerState_[i], &controllerState_[i], sizeof(controllerState_[i]));
			XInputGetState(i, &controllerState_[i]);
		}

	}



	//�J��
	void Release()
	{
		SAFE_RELEASE(pMouseDevice_);
		SAFE_RELEASE(pKeyDevice_);
		SAFE_RELEASE(pDInput_);
	}



	/////////////////////////////�@�L�[�{�[�h���擾�@//////////////////////////////////

	//�L�[��������Ă��邩���ׂ�
	bool IsKey(int keyCode)
	{
		//�����Ă�
		if (keyState_[keyCode] & 0x80)
		{
			return true;
		}
		return false;
	}


	//�L�[���������������ׂ�i�������ςȂ��͖����j
	bool IsKeyDown(int keyCode)
	{
		//���͉����ĂāA�O��͉����ĂȂ�
		if (IsKey(keyCode) && !(prevKeyState_[keyCode] & 0x80))
		{
			return true;
		}
		return false;
	}


	//�L�[���������������ׂ�
	bool IsKeyUp(int keyCode)
	{
		//�������ĂȂ��āA�O��͉����Ă�
		if (!IsKey(keyCode) && prevKeyState_[keyCode] & 0x80)
		{
			return true;
		}
		return false;
	}


	/////////////////////////////�@�}�E�X���擾�@//////////////////////////////////

	//�}�E�X�̃{�^����������Ă��邩���ׂ�
	bool IsMouseButton(int buttonCode)
	{
		//�����Ă�
		if (mouseState_.rgbButtons[buttonCode] & 0x80)
		{
			return true;
		}
		return false;
	}

	//�}�E�X�̃{�^�����������������ׂ�i�������ςȂ��͖����j
	bool IsMouseButtonDown(int buttonCode)
	{
		//���͉����ĂāA�O��͉����ĂȂ�
		if (IsMouseButton(buttonCode) && !(prevMouseState_.rgbButtons[buttonCode] & 0x80))
		{
			return true;
		}
		return false;
	}

	//�}�E�X�̃{�^�����������������ׂ�
	bool IsMouseButtonUp(int buttonCode)
	{
		//�������ĂȂ��āA�O��͉����Ă�
		if (!IsMouseButton(buttonCode) && prevMouseState_.rgbButtons[buttonCode] & 0x80)
		{
			return true;
		}
		return false;
	}

	//�}�E�X�J�[�\���̈ʒu���擾
	XMFLOAT3 GetMousePosition()
	{
		XMFLOAT3 result = XMFLOAT3((float)mousePos_.x, (float)mousePos_.y, 0);
		return result;
	}

	//�}�E�X�J�[�\���̈ʒu���Z�b�g
	void SetMousePosition(int x, int y)
	{
		mousePos_.x = x;
		mousePos_.y = y;
	}


	//���̃t���[���ł̃}�E�X�̈ړ��ʂ��擾
	XMFLOAT3 GetMouseMove()
	{
		XMFLOAT3 result = XMFLOAT3((float)mouseState_.lX, (float)mouseState_.lY, (float)mouseState_.lZ);
		return result;
	}


	/////////////////////////////�@�R���g���[���[���擾�@//////////////////////////////////

	//�R���g���[���[�̃{�^����������Ă��邩���ׂ�
	bool IsPadButton(int buttonCode, int padID)
	{
		if (controllerState_[padID].Gamepad.wButtons & buttonCode)
		{
			return true; //�����Ă�
		}
		return false; //�����ĂȂ�
	}

	//�R���g���[���[�̃{�^�����������������ׂ�i�������ςȂ��͖����j
	bool IsPadButtonDown(int buttonCode, int padID)
	{
		//���͉����ĂāA�O��͉����ĂȂ�
		if (IsPadButton(buttonCode, padID) && !(prevControllerState_[padID].Gamepad.wButtons & buttonCode))
		{
			return true;
		}
		return false;
	}

	//�R���g���[���[�̃{�^�����������������ׂ�
	bool IsPadButtonUp(int buttonCode, int padID)
	{
		//�������ĂȂ��āA�O��͉����Ă�
		if (!IsPadButton(buttonCode, padID) && prevControllerState_[padID].Gamepad.wButtons & buttonCode)
		{
			return true;
		}
		return false;
	}


	float GetAnalogValue(int raw, int max, int deadZone)
	{
		float result = (float)raw;

		if (result > 0)
		{
			//�f�b�h�]�[��
			if (result < deadZone)
			{
				result = 0;
			}
			else
			{
				result = (result - deadZone) / (max - deadZone);
			}
		}

		else
		{
			//�f�b�h�]�[��
			if (result > -deadZone)
			{
				result = 0;
			}
			else
			{
				result = (result + deadZone) / (max - deadZone);
			}
		}

		return result;
	}


	//���X�e�B�b�N�̌X�����擾
	XMFLOAT3 GetPadStickL(int padID)
	{
		float x = GetAnalogValue(controllerState_[padID].Gamepad.sThumbLX, 32767, XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
		float y = GetAnalogValue(controllerState_[padID].Gamepad.sThumbLY, 32767, XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
		return XMFLOAT3(x, y, 0);
	}

	//�E�X�e�B�b�N�̌X�����擾
	XMFLOAT3 GetPadStickR(int padID)
	{
		float x = GetAnalogValue(controllerState_[padID].Gamepad.sThumbRX, 32767, XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE);
		float y = GetAnalogValue(controllerState_[padID].Gamepad.sThumbRY, 32767, XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE);
		return XMFLOAT3(x, y, 0);
	}

	//���g���K�[�̉������݋���擾
	float GetPadTrrigerL(int padID)
	{
		return GetAnalogValue(controllerState_[padID].Gamepad.bLeftTrigger, 255, XINPUT_GAMEPAD_TRIGGER_THRESHOLD);
	}

	//�E�g���K�[�̉������݋���擾
	float GetPadTrrigerR(int padID)
	{
		return GetAnalogValue(controllerState_[padID].Gamepad.bRightTrigger, 255, XINPUT_GAMEPAD_TRIGGER_THRESHOLD);
	}

	//�U��������
	void SetPadVibration(int l, int r, int padID)
	{
		XINPUT_VIBRATION vibration;
		ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
		vibration.wLeftMotorSpeed = l; // �����[�^�[�̋���
		vibration.wRightMotorSpeed = r;// �E���[�^�[�̋���
		XInputSetState(padID, &vibration);
	}

}