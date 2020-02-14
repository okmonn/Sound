#pragma once
#include "../Label/Label.h"
#include "../Button/Button.h"

namespace CLI {
	ref class Window :
		public System::Windows::Forms::Form {
	public:
		/*コンストラクタ*/
		Window();
		/*コンストラクタ
		.横幅
		.縦幅*/
		Window(const System::UInt32& width, const System::UInt32& height);
		/*デストラクタ*/
		~Window();
		/*ラベルの追加
		.ラベル*/
		void AddLabel(Label^ label);
		/*ボタンの追加
		.ボタン*/
		void AddButton(Button^ button);

	public :
		/*座標の設定
		.X座標
		.Y座標*/
		void SetPos(const System::UInt32& x, const System::UInt32& y);
		/*サイズの設定
		.横幅
		.縦幅*/
		void SetSize(const System::UInt32& width, const System::UInt32& height);

	private:
		/*メンバの初期化*/
		void Initialize(void);

	private:
		/*必須*/
		System::ComponentModel::Container^ component;
	};
}
