#pragma once
#include <SimpleMath.h>

#define BACKGROUND_COLOR	(DirectX::Colors::DarkGray)		//	�w�i�F

class Screen
{
public:
	const static int WIDTH = 1280;		//	��ʂ̉���
	const static int HEIGHT = 720;		//	��ʂ̏c��

	//	��ʃT�C�Y��Vector2�ŕԂ�
	static DirectX::SimpleMath::Vector2 SCREEN_SIZE()
	{
		return { WIDTH, HEIGHT };
	}
	//	��ʂ̒��S���W��Ԃ�
	static DirectX::SimpleMath::Vector2 SCREEN_CENTER()
	{
		return { (float)WIDTH_HALF(), (float)HEIGHT_HALF() };
	}

	//	�����̔�����Ԃ�
	static int WIDTH_HALF()
	{
		return (int)(WIDTH / 2);
	}

	//	�c���̔�����Ԃ�
	static int HEIGHT_HALF()
	{
		return (int)(HEIGHT / 2);
	}

	//	��ʂ̔����̃T�C�Y��Ԃ��iSCREEN_CENTER�Ǔ����j
	static DirectX::SimpleMath::Vector2 SCREEN_HALF()
	{
		return SCREEN_CENTER();
	}
};