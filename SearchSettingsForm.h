#pragma once
#include "FormHeaders.h"
#include "ImageCompare.h"

namespace CVImageSearch {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;
	using namespace System::Collections::Generic;

	/// <summary>
	/// Сводка для SearchSettingsForm
	/// </summary>
	public ref class SearchSettingsForm : public System::Windows::Forms::Form
	{
	public:
		int descriptorType;
		int comparisionType;
		int thresholdPercent;
		int distanceWindow;
		int featuresNum;

	public:
		SearchSettingsForm(int descriptorType, int comparisionType, double threshold, int distanceWindow, int featuresNum)
		{
			InitializeComponent();

			this->descriptorType = descriptorType;
			this->comparisionType = comparisionType;
			this->thresholdPercent = threshold * 100;
			this->distanceWindow = distanceWindow;
			this->featuresNum = featuresNum;


			for each (auto descriptorTypePair in ImageCompare::GetDescriptorTypeAsMap())
			{
				std::string typeName = descriptorTypePair.second;
				descriptorTypeComboBox->Items->Add(msclr::interop::marshal_as<String^>(typeName));
			}
			descriptorTypeComboBox->SelectedIndex = descriptorType;

			for each (auto comparisionTypePair in ImageCompare::GetComparisionTypeAsMap())
			{
				std::string typeName = comparisionTypePair.second;
				comparisionTypeComboBox->Items->Add(msclr::interop::marshal_as<String^>(typeName));
			}
			comparisionTypeComboBox->SelectedIndex = comparisionType;

			similarityTypeNumericUpDown->Value = thresholdPercent;
			featuresNumberNumericUpDown->Value = featuresNum;
			distanceWindowNumericUpDown->Value = distanceWindow;
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~SearchSettingsForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::ComboBox^  descriptorTypeComboBox;
	private: System::Windows::Forms::ComboBox^  comparisionTypeComboBox;

	protected:
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::NumericUpDown^  distanceWindowNumericUpDown;

	private: System::Windows::Forms::NumericUpDown^  similarityTypeNumericUpDown;
	private: System::Windows::Forms::NumericUpDown^  featuresNumberNumericUpDown;
	private: System::Windows::Forms::Button^  confirmButton;
	private: System::Windows::Forms::Button^  cancelButton;
	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->descriptorTypeComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->comparisionTypeComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->distanceWindowNumericUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->similarityTypeNumericUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->featuresNumberNumericUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->confirmButton = (gcnew System::Windows::Forms::Button());
			this->cancelButton = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->distanceWindowNumericUpDown))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->similarityTypeNumericUpDown))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->featuresNumberNumericUpDown))->BeginInit();
			this->SuspendLayout();
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(12, 8);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(94, 13);
			this->label2->TabIndex = 1;
			this->label2->Text = L"Вид дескриптора";
			// 
			// descriptorTypeComboBox
			// 
			this->descriptorTypeComboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->descriptorTypeComboBox->FormattingEnabled = true;
			this->descriptorTypeComboBox->Location = System::Drawing::Point(12, 24);
			this->descriptorTypeComboBox->Name = L"descriptorTypeComboBox";
			this->descriptorTypeComboBox->Size = System::Drawing::Size(155, 21);
			this->descriptorTypeComboBox->TabIndex = 2;
			// 
			// comparisionTypeComboBox
			// 
			this->comparisionTypeComboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comparisionTypeComboBox->FormattingEnabled = true;
			this->comparisionTypeComboBox->Location = System::Drawing::Point(12, 77);
			this->comparisionTypeComboBox->Name = L"comparisionTypeComboBox";
			this->comparisionTypeComboBox->Size = System::Drawing::Size(155, 21);
			this->comparisionTypeComboBox->TabIndex = 4;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 61);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(83, 13);
			this->label1->TabIndex = 3;
			this->label1->Text = L"Тип сравнения";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(267, 9);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(113, 13);
			this->label3->TabIndex = 7;
			this->label3->Text = L"Процент совпадений";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(12, 114);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(132, 13);
			this->label4->TabIndex = 5;
			this->label4->Text = L"Допустимое отклонение";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(264, 62);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(130, 13);
			this->label6->TabIndex = 13;
			this->label6->Text = L"Количество признаков *";
			// 
			// distanceWindowNumericUpDown
			// 
			this->distanceWindowNumericUpDown->Location = System::Drawing::Point(12, 130);
			this->distanceWindowNumericUpDown->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000, 0, 0, 0 });
			this->distanceWindowNumericUpDown->Name = L"distanceWindowNumericUpDown";
			this->distanceWindowNumericUpDown->Size = System::Drawing::Size(155, 20);
			this->distanceWindowNumericUpDown->TabIndex = 15;
			// 
			// similarityTypeNumericUpDown
			// 
			this->similarityTypeNumericUpDown->Location = System::Drawing::Point(267, 25);
			this->similarityTypeNumericUpDown->Name = L"similarityTypeNumericUpDown";
			this->similarityTypeNumericUpDown->Size = System::Drawing::Size(155, 20);
			this->similarityTypeNumericUpDown->TabIndex = 16;
			// 
			// featuresNumberNumericUpDown
			// 
			this->featuresNumberNumericUpDown->Location = System::Drawing::Point(267, 78);
			this->featuresNumberNumericUpDown->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000, 0, 0, 0 });
			this->featuresNumberNumericUpDown->Name = L"featuresNumberNumericUpDown";
			this->featuresNumberNumericUpDown->Size = System::Drawing::Size(155, 20);
			this->featuresNumberNumericUpDown->TabIndex = 17;
			// 
			// confirmButton
			// 
			this->confirmButton->Location = System::Drawing::Point(121, 170);
			this->confirmButton->Name = L"confirmButton";
			this->confirmButton->Size = System::Drawing::Size(85, 25);
			this->confirmButton->TabIndex = 18;
			this->confirmButton->Text = L"Подтвердить";
			this->confirmButton->UseVisualStyleBackColor = true;
			this->confirmButton->Click += gcnew System::EventHandler(this, &SearchSettingsForm::confirmButton_Click);
			// 
			// cancelButton
			// 
			this->cancelButton->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->cancelButton->Location = System::Drawing::Point(226, 170);
			this->cancelButton->Name = L"cancelButton";
			this->cancelButton->Size = System::Drawing::Size(85, 25);
			this->cancelButton->TabIndex = 19;
			this->cancelButton->Text = L"Отмена";
			this->cancelButton->UseVisualStyleBackColor = true;
			this->cancelButton->Click += gcnew System::EventHandler(this, &SearchSettingsForm::cancelButton_Click);
			// 
			// SearchSettingsForm
			// 
			this->AcceptButton = this->confirmButton;
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->CancelButton = this->cancelButton;
			this->ClientSize = System::Drawing::Size(434, 211);
			this->Controls->Add(this->cancelButton);
			this->Controls->Add(this->confirmButton);
			this->Controls->Add(this->featuresNumberNumericUpDown);
			this->Controls->Add(this->similarityTypeNumericUpDown);
			this->Controls->Add(this->distanceWindowNumericUpDown);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->comparisionTypeComboBox);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->descriptorTypeComboBox);
			this->Controls->Add(this->label2);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->Name = L"SearchSettingsForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"Настройки поиска";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->distanceWindowNumericUpDown))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->similarityTypeNumericUpDown))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->featuresNumberNumericUpDown))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: 
		System::Void confirmButton_Click(System::Object^  sender, System::EventArgs^  e) {

			for each (auto descriptorType in ImageCompare::GetDescriptorTypeAsMap())
			{
				std::string typeName = descriptorType.second;
				if (descriptorTypeComboBox->Text == msclr::interop::marshal_as<String^>(typeName)) {
					this->descriptorType = descriptorType.first;
				}
			}

			for each (auto ComparisionType in ImageCompare::GetComparisionTypeAsMap())
			{
				std::string typeName = ComparisionType.second;
				if (comparisionTypeComboBox->Text == msclr::interop::marshal_as<String^>(typeName)) {
					this->comparisionType = ComparisionType.first;
				}
			}

			this->thresholdPercent = (int)similarityTypeNumericUpDown->Value;
			this->featuresNum = (int)featuresNumberNumericUpDown->Value;
			this->distanceWindow = (int)distanceWindowNumericUpDown->Value;
			
			this->DialogResult = Windows::Forms::DialogResult::OK;
			this->Close();
		}

		System::Void cancelButton_Click(System::Object^  sender, System::EventArgs^  e) {

			this->DialogResult = Windows::Forms::DialogResult::Cancel;
			this->Close();
		}
	};
}
