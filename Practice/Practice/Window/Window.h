#pragma once

ref class Window :
	public System::Windows::Forms::Form {
public:
	/*�R���X�g���N�^*/
	Window();
	/*�f�X�g���N�^*/
	~Window();

protected:
	/*����ۂ̃R�[���o�b�N�֐�
	.���N���X
	.�C�x���g���*/
	void CloseEvent(System::Object^ obj, System::ComponentModel::CancelEventArgs^ args);

private:
	/*�����o�̏�����*/
	void Initialize(void);
	/*�C�x���g�̃Z�b�g*/
	void SetEvent(void);
	/*�K�{*/
	System::ComponentModel::Container^ component;
};
