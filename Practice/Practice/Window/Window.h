#pragma once

ref class Window :
	public System::Windows::Forms::Form {
public:
	/*コンストラクタ*/
	Window();
	/*デストラクタ*/
	~Window();

protected:
	/*閉じる際のコールバック関数
	.基底クラス
	.イベント情報*/
	void CloseEvent(System::Object^ obj, System::ComponentModel::CancelEventArgs^ args);

private:
	/*メンバの初期化*/
	void Initialize(void);
	/*イベントのセット*/
	void SetEvent(void);
	/*必須*/
	System::ComponentModel::Container^ component;
};
