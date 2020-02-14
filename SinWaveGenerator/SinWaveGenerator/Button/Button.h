#pragma once

namespace CLI {
	ref class Button : 
		public System::Windows::Forms::Button {
	public:
		/*�R���X�g���N�^*/
		Button();
		/*�R���X�g���N�^
		.�R�����g
		.X���W
		.Y���W*/
		Button(System::String^ str, const System::UInt32& x, const System::UInt32& y);
		/*�R���X�g���N�^
		.�R�����g
		.X���W
		.Y���W
		.����
		.�c��*/
		Button(System::String^ str, const System::UInt32& x, const System::UInt32& y, 
			const System::UInt32& width, const System::UInt32& height);

		/*�f�X�g���N�^*/
		~Button();

	public:
		/*�R�����g�̐ݒ�
		.�R�����g*/
		void SetString(System::String^ str);
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
