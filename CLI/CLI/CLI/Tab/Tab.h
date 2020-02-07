#pragma once

namespace CLI {
	ref class Tab :
		public System::Windows::Forms::TabControl {
	public:
		/*コンストラクタ*/
		Tab();
		/*デストラクタ*/
		~Tab();
		/*タブの追加
		.見出しコメント*/
		void AddTab(const char* comment);

	private:
		/*必須*/
		System::ComponentModel::Container^ component;
		/*ラベル*/
		System::Collections::Generic::List<System::Windows::Forms::Label^>^ label;
		/*タブページ*/
		System::Collections::Generic::List<System::Windows::Forms::TabPage^>^ page;
	};
}
