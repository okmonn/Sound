#pragma once

namespace CLI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Window の概要
	/// </summary>
	public ref class Window : public System::Windows::Forms::Form
	{
	public:
		void OnKeyDown(KeyEventArgs^ info) override {
			this->Close();
			Form::OnKeyDown(info);
		}
		Window(void)
		{
			InitializeComponent();
			this->KeyPreview = true;

			//
			//TODO: ここにコンストラクター コードを追加します
			//
		}

	protected:
		/// <summary>
		/// 使用中のリソースをすべてクリーンアップします。
		/// </summary>
		~Window()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		/// <summary>
		/// 必要なデザイナー変数です。
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// デザイナー サポートに必要なメソッドです。このメソッドの内容を
		/// コード エディターで変更しないでください。
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = gcnew System::ComponentModel::Container();
			this->Size = System::Drawing::Size(900, 480);
			this->Text = L"おかもん";
			this->Padding = System::Windows::Forms::Padding(0);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Icon = gcnew System::Drawing::Icon("MyLogo.ico");
			this->BackColor = System::Drawing::Color::White;
			this->StartPosition = System::Windows::Forms::FormStartPosition::Manual;
			this->Location = System::Drawing::Point(0, 0);
		}
#pragma endregion
	};
}
