#pragma once
#include "../Page/Page.h"

namespace CLI {
	ref class Window :
		public System::Windows::Forms::Form {
	public:
		/*コンストラクタ*/
		Window();
		/*デストラクタ*/
		~Window();

	private:
		/*メンバの初期化*/
		void Initialize(void);

	private:
		/*必須*/
		System::ComponentModel::Container^ component;
		/*タスクタブコントローラー*/
		System::Windows::Forms::TabControl^ tabCtl;
		Page^ page;
	};
}
