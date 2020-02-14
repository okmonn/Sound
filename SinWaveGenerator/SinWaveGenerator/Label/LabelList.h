#pragma once

namespace CLI {
	ref class Label;
}

namespace CLI {
	ref class LabelList :
		public System::Windows::Forms::Control {
	public:
		/*コンストラクタ*/
		LabelList();
		/*デストラクタ*/
		~LabelList();
		/*リストに追加
		.Labelのポインタ*/
		void AddList(Label^ label);

	private:
		/*必須*/
		System::ComponentModel::Container^ component;
		/*ラベルリスト*/
		System::Collections::Generic::List<Label^>list;
	};
}
