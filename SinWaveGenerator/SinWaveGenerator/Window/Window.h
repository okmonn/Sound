#pragma once
#include "../Label/Label.h"
#include "../Button/Button.h"

namespace CLI {
	ref class Window :
		public System::Windows::Forms::Form {
	public:
		/*�R���X�g���N�^*/
		Window();
		/*�R���X�g���N�^
		.����
		.�c��*/
		Window(const System::UInt32& width, const System::UInt32& height);
		/*�f�X�g���N�^*/
		~Window();
		/*���x���̒ǉ�
		.���x��*/
		void AddLabel(Label^ label);
		/*�{�^���̒ǉ�
		.�{�^��*/
		void AddButton(Button^ button);

	public :
		/*���W�̐ݒ�
		.X���W
		.Y���W*/
		void SetPos(const System::UInt32& x, const System::UInt32& y);
		/*�T�C�Y�̐ݒ�
		.����
		.�c��*/
		void SetSize(const System::UInt32& width, const System::UInt32& height);

	private:
		/*�����o�̏�����*/
		void Initialize(void);

	private:
		/*�K�{*/
		System::ComponentModel::Container^ component;
	};
}
