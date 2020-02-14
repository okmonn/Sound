#pragma once

namespace CLI {
	ref class Splash :
		public System::Windows::Forms::Form {
	public:
		/*�R���X�g���N�^*/
		Splash();
		/*�R���X�g���N�^
		.����
		.�c��*/
		Splash(const System::UInt32& width, const System::UInt32& height);
		/*�f�X�g���N�^*/
		~Splash();
		/*�����̊����ʒm*/
		void Complete(void);

	public:
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
		/*�񓯊�����*/
		void Stream(void);

	private:
		/*�K�{*/
		System::ComponentModel::Container^ component;
		/*�ҋ@�C�x���g*/
		System::Threading::ManualResetEvent^ wait;
		/*�^�X�N*/
		System::Threading::Tasks::Task^ th;
	};
}
