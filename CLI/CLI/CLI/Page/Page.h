#pragma once

namespace CLI {
	ref class Page :
		public System::Windows::Forms::TabPage {
	public:
		/*�R���X�g���N�^*/
		Page();
		/*�f�X�g���N�^*/
		~Page();

	private:
		/*�����o�̏�����*/
		void Initialize(void);

	private:
		/*�K�{*/
		System::ComponentModel::Container^ component;
		/*���x��*/
		System::Windows::Forms::Label^ label;
	};
}
