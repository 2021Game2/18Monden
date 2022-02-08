#ifndef CINPUT_H
#define CINPUT_H

#include "GLFW/glfw3.h"
/*
���̓N���X
CInput
*/

class CInput {
	//�E�B���h�E�|�C���^
	static GLFWwindow* mpWindow;
	static int sm_wheel;

public:

	/*
	������
	Init(�E�B���h�E�|�C���^)
	*/
	static void Init(GLFWwindow* w);
	/*
	�}�E�X�J�[�\���̍��W���擾����
	GetMousePos(X���W�|�C���^,Y���W�|�C���^)
	�f�B�X�v���C�̍��オ���_(0,0)
	*/
	static void GetMousePos(int* px, int* py);
	/*
	�}�E�X�{�^���̏��
	GetMouseButton(�{�^��)
	�{�^��1
	GLFW_MOUSE_BUTTON_LEFT(���{�^��)
	GLFW_MOUSE_BUTTON_RIGHT(�E�{�^��)
	return;
	true:������Ă���
	false:������Ă��Ȃ�
	*/
	static bool GetMouseButton(int button);
	/*
	�}�E�X�J�[�\���̍��W��ݒ肷��
	SetCursorPos(X���W,Y���W)
	�f�B�X�v���C�̍��オ���_(0,0)
	*/
	static void SetMousePos(int x, int y);

	/*
	�}�E�X�J�[�\���̍��W���擾����
	GetMousePosW(X���W�|�C���^,Y���W�|�C���^)
	�E�B���h�E�̍��オ���_(0,0)
	*/
	static void GetMousePosW(int* px, int* py);

	static void MouseScrollCB(GLFWwindow* window, double x, double y);

	//�}�E�X�z�C�[���̈ړ��ʂ�Ԃ�
	static int GetWheelValue();

	//�R�[���o�b�N�n�̐��l��ؾ��
	static void InputReset();
};

#endif