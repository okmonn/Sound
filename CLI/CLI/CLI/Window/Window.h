#pragma once
#include "../Page/Page.h"

namespace CLI {
	ref class Window :
		public System::Windows::Forms::Form {
	public:
		/*�R���X�g���N�^*/
		Window();
		/*�f�X�g���N�^*/
		~Window();

	private:
		/*�����o�̏�����*/
		void Initialize(void);

	private:
		/*�K�{*/
		System::ComponentModel::Container^ component;
		/*�^�X�N�^�u�R���g���[���[*/
		System::Windows::Forms::TabControl^ tabCtl;
		Page^ page;
	};
}