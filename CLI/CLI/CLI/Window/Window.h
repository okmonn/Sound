#pragma once

namespace CLI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Window �̊T�v
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
			//TODO: �����ɃR���X�g���N�^�[ �R�[�h��ǉ����܂�
			//
		}

	protected:
		/// <summary>
		/// �g�p���̃��\�[�X�����ׂăN���[���A�b�v���܂��B
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
		/// �K�v�ȃf�U�C�i�[�ϐ��ł��B
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// �f�U�C�i�[ �T�|�[�g�ɕK�v�ȃ��\�b�h�ł��B���̃��\�b�h�̓��e��
		/// �R�[�h �G�f�B�^�[�ŕύX���Ȃ��ł��������B
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = gcnew System::ComponentModel::Container();
			this->Size = System::Drawing::Size(900, 480);
			this->Text = L"��������";
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
