#pragma once

namespace CLI {
	ref class Label :
		public System::Windows::Forms::Label {
	public:
		/*コンストラクタ*/
		Label();
		/*コンストラクタ
		.コメント
		.X座標
		.Y座標*/
		Label(System::String^ str, const System::UInt32& x, const System::UInt32& y);
		/*コンストラクタ
		.コメント
		.X座標
		.Y座標
		.横幅
		.縦幅*/
		Label(System::String^ str, const System::UInt32& x, const System::UInt32& y, 
			const System::UInt32& width, const System::UInt32& height);
		/*デストラクタ*/
		~Label();
		
	public:
		/*コメントの設定
		.コメント*/
		void SetString(System::String^ str);
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
