#pragma once

namespace CLI {
	ref class Label;
}

namespace CLI {
	ref class LabelList :
		public System::Windows::Forms::Control {
	public:
		/*�R���X�g���N�^*/
		LabelList();
		/*�f�X�g���N�^*/
		~LabelList();
		/*���X�g�ɒǉ�
		.Label�̃|�C���^*/
		void AddList(Label^ label);

	private:
		/*�K�{*/
		System::ComponentModel::Container^ component;
		/*���x�����X�g*/
		System::Collections::Generic::List<Label^>list;
	};
}
