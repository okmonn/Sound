#pragma once

namespace CLI {
	ref class Tab :
		public System::Windows::Forms::TabControl {
	public:
		/*�R���X�g���N�^*/
		Tab();
		/*�f�X�g���N�^*/
		~Tab();
		/*�^�u�̒ǉ�
		.���o���R�����g*/
		void AddTab(const char* comment);

	private:
		/*�K�{*/
		System::ComponentModel::Container^ component;
		/*���x��*/
		System::Collections::Generic::List<System::Windows::Forms::Label^>^ label;
		/*�^�u�y�[�W*/
		System::Collections::Generic::List<System::Windows::Forms::TabPage^>^ page;
	};
}
