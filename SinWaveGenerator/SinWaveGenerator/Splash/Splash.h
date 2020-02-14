#pragma once

namespace CLI {
	ref class Splash :
		public System::Windows::Forms::Form {
	public:
		/*コンストラクタ*/
		Splash();
		/*コンストラクタ
		.横幅
		.縦幅*/
		Splash(const System::UInt32& width, const System::UInt32& height);
		/*デストラクタ*/
		~Splash();
		/*処理の完了通知*/
		void Complete(void);

	public:
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
		/*非同期処理*/
		void Stream(void);

	private:
		/*必須*/
		System::ComponentModel::Container^ component;
		/*待機イベント*/
		System::Threading::ManualResetEvent^ wait;
		/*タスク*/
		System::Threading::Tasks::Task^ th;
	};
}
