#pragma once

namespace CLI {
	ref class Page :
		public System::Windows::Forms::TabPage {
	public:
		/*コンストラクタ*/
		Page();
		/*デストラクタ*/
		~Page();

	private:
		/*メンバの初期化*/
		void Initialize(void);

	private:
		/*必須*/
		System::ComponentModel::Container^ component;
		/*ラベル*/
		System::Windows::Forms::Label^ label;
	};
}
