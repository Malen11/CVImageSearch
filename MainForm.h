#pragma once
#include "FormHeaders.h"
#include "ImageCompare.h"
#include "SearchSettingsForm.h"

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
	/// Сводка для MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	private:
		int descriptorType = DescriptorType::ORB;
		int comparisionType = ComparisionType::HAMMING;
		double threshold = 0.70;
		int distanceWindow = 75;
		int featuresNum = 100;

		String^ searchFolderName;
		String^ searchFileName;

		System::ComponentModel::Container ^components;

	private: System::Windows::Forms::Button ^ selectImageButton;
	private: System::Windows::Forms::Button^  selectDirectoryButton;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::PictureBox^  searchedPictureBox;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::GroupBox^  groupBox3;
	private: System::Windows::Forms::GroupBox^  groupBox4;
	private: System::Windows::Forms::PictureBox^  foundPictureBox;
	private: System::Windows::Forms::Button^  searchImagesButton;
	private: System::Windows::Forms::ListView^  findImagesListView;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  searchDirectoryTextBox;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::TextBox^  searchedImageNameTextBox;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::TextBox^  foundImageNameTextBox;
	private: System::Windows::Forms::Button^  searchSettingsButton;

	public:
		MainForm(void)
		{
			InitializeComponent();
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}

		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->selectImageButton = (gcnew System::Windows::Forms::Button());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->searchedPictureBox = (gcnew System::Windows::Forms::PictureBox());
			this->searchedImageNameTextBox = (gcnew System::Windows::Forms::TextBox());
			this->selectDirectoryButton = (gcnew System::Windows::Forms::Button());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->searchDirectoryTextBox = (gcnew System::Windows::Forms::TextBox());
			this->findImagesListView = (gcnew System::Windows::Forms::ListView());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->searchSettingsButton = (gcnew System::Windows::Forms::Button());
			this->searchImagesButton = (gcnew System::Windows::Forms::Button());
			this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->foundPictureBox = (gcnew System::Windows::Forms::PictureBox());
			this->foundImageNameTextBox = (gcnew System::Windows::Forms::TextBox());
			this->groupBox1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->searchedPictureBox))->BeginInit();
			this->groupBox2->SuspendLayout();
			this->groupBox3->SuspendLayout();
			this->groupBox4->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->foundPictureBox))->BeginInit();
			this->SuspendLayout();
			// 
			// selectImageButton
			// 
			this->selectImageButton->Location = System::Drawing::Point(6, 19);
			this->selectImageButton->Name = L"selectImageButton";
			this->selectImageButton->Size = System::Drawing::Size(100, 50);
			this->selectImageButton->TabIndex = 0;
			this->selectImageButton->Text = L"Выбрать изображение";
			this->selectImageButton->UseVisualStyleBackColor = true;
			this->selectImageButton->Click += gcnew System::EventHandler(this, &MainForm::selectImageButton_Click);
			// 
			// groupBox1
			// 
			this->groupBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->groupBox1->Controls->Add(this->label3);
			this->groupBox1->Controls->Add(this->searchedPictureBox);
			this->groupBox1->Controls->Add(this->searchedImageNameTextBox);
			this->groupBox1->Location = System::Drawing::Point(130, 12);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(516, 325);
			this->groupBox1->TabIndex = 1;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Искомое изображение";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(6, 295);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(85, 13);
			this->label3->TabIndex = 7;
			this->label3->Text = L"Расположение:";
			// 
			// searchedPictureBox
			// 
			this->searchedPictureBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->searchedPictureBox->Location = System::Drawing::Point(6, 16);
			this->searchedPictureBox->Name = L"searchedPictureBox";
			this->searchedPictureBox->Size = System::Drawing::Size(504, 273);
			this->searchedPictureBox->SizeMode = System::Windows::Forms::PictureBoxSizeMode::CenterImage;
			this->searchedPictureBox->TabIndex = 2;
			this->searchedPictureBox->TabStop = false;
			// 
			// searchedImageNameTextBox
			// 
			this->searchedImageNameTextBox->BackColor = System::Drawing::SystemColors::Control;
			this->searchedImageNameTextBox->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->searchedImageNameTextBox->Location = System::Drawing::Point(97, 295);
			this->searchedImageNameTextBox->Name = L"searchedImageNameTextBox";
			this->searchedImageNameTextBox->ReadOnly = true;
			this->searchedImageNameTextBox->Size = System::Drawing::Size(413, 13);
			this->searchedImageNameTextBox->TabIndex = 6;
			this->searchedImageNameTextBox->TabStop = false;
			// 
			// selectDirectoryButton
			// 
			this->selectDirectoryButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->selectDirectoryButton->Location = System::Drawing::Point(6, 75);
			this->selectDirectoryButton->Name = L"selectDirectoryButton";
			this->selectDirectoryButton->Size = System::Drawing::Size(100, 50);
			this->selectDirectoryButton->TabIndex = 2;
			this->selectDirectoryButton->Text = L"Выбрать директорию";
			this->selectDirectoryButton->UseVisualStyleBackColor = true;
			this->selectDirectoryButton->Click += gcnew System::EventHandler(this, &MainForm::selectDirectoryButton_Click);
			// 
			// groupBox2
			// 
			this->groupBox2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->groupBox2->Controls->Add(this->label2);
			this->groupBox2->Controls->Add(this->label1);
			this->groupBox2->Controls->Add(this->searchDirectoryTextBox);
			this->groupBox2->Controls->Add(this->findImagesListView);
			this->groupBox2->Location = System::Drawing::Point(652, 12);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(600, 657);
			this->groupBox2->TabIndex = 3;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Найденные файлы";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(15, 59);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(92, 13);
			this->label2->TabIndex = 6;
			this->label2->Text = L"Похожие файлы:";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(15, 19);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(111, 13);
			this->label1->TabIndex = 5;
			this->label1->Text = L"Директория поиска:";
			// 
			// searchDirectoryTextBox
			// 
			this->searchDirectoryTextBox->BackColor = System::Drawing::SystemColors::Window;
			this->searchDirectoryTextBox->Location = System::Drawing::Point(132, 16);
			this->searchDirectoryTextBox->Name = L"searchDirectoryTextBox";
			this->searchDirectoryTextBox->ReadOnly = true;
			this->searchDirectoryTextBox->Size = System::Drawing::Size(462, 20);
			this->searchDirectoryTextBox->TabIndex = 4;
			this->searchDirectoryTextBox->DoubleClick += gcnew System::EventHandler(this, &MainForm::selectDirectoryButton_Click);
			// 
			// findImagesListView
			// 
			this->findImagesListView->Activation = System::Windows::Forms::ItemActivation::TwoClick;
			this->findImagesListView->Location = System::Drawing::Point(6, 75);
			this->findImagesListView->Name = L"findImagesListView";
			this->findImagesListView->Size = System::Drawing::Size(588, 576);
			this->findImagesListView->TabIndex = 3;
			this->findImagesListView->UseCompatibleStateImageBehavior = false;
			this->findImagesListView->View = System::Windows::Forms::View::List;
			this->findImagesListView->ItemActivate += gcnew System::EventHandler(this, &MainForm::findImagesListView_ItemActivate);
			// 
			// groupBox3
			// 
			this->groupBox3->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left));
			this->groupBox3->Controls->Add(this->searchSettingsButton);
			this->groupBox3->Controls->Add(this->searchImagesButton);
			this->groupBox3->Controls->Add(this->selectImageButton);
			this->groupBox3->Controls->Add(this->selectDirectoryButton);
			this->groupBox3->Location = System::Drawing::Point(12, 12);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(112, 657);
			this->groupBox3->TabIndex = 4;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"Меню";
			// 
			// searchSettingsButton
			// 
			this->searchSettingsButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->searchSettingsButton->Location = System::Drawing::Point(6, 187);
			this->searchSettingsButton->Name = L"searchSettingsButton";
			this->searchSettingsButton->Size = System::Drawing::Size(100, 50);
			this->searchSettingsButton->TabIndex = 4;
			this->searchSettingsButton->Text = L"Настройки поиска";
			this->searchSettingsButton->UseVisualStyleBackColor = true;
			this->searchSettingsButton->Click += gcnew System::EventHandler(this, &MainForm::searchSettingsButton_Click);
			// 
			// searchImagesButton
			// 
			this->searchImagesButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->searchImagesButton->Location = System::Drawing::Point(6, 131);
			this->searchImagesButton->Name = L"searchImagesButton";
			this->searchImagesButton->Size = System::Drawing::Size(100, 50);
			this->searchImagesButton->TabIndex = 3;
			this->searchImagesButton->Text = L"Найти изображения";
			this->searchImagesButton->UseVisualStyleBackColor = true;
			this->searchImagesButton->Click += gcnew System::EventHandler(this, &MainForm::searchImagesButton_Click);
			// 
			// groupBox4
			// 
			this->groupBox4->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->groupBox4->Controls->Add(this->label4);
			this->groupBox4->Controls->Add(this->foundPictureBox);
			this->groupBox4->Controls->Add(this->foundImageNameTextBox);
			this->groupBox4->Location = System::Drawing::Point(130, 344);
			this->groupBox4->Name = L"groupBox4";
			this->groupBox4->Size = System::Drawing::Size(516, 325);
			this->groupBox4->TabIndex = 3;
			this->groupBox4->TabStop = false;
			this->groupBox4->Text = L"Просмотр изображения";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(6, 299);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(85, 13);
			this->label4->TabIndex = 9;
			this->label4->Text = L"Расположение:";
			// 
			// foundPictureBox
			// 
			this->foundPictureBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->foundPictureBox->Location = System::Drawing::Point(6, 19);
			this->foundPictureBox->Name = L"foundPictureBox";
			this->foundPictureBox->Size = System::Drawing::Size(504, 274);
			this->foundPictureBox->SizeMode = System::Windows::Forms::PictureBoxSizeMode::CenterImage;
			this->foundPictureBox->TabIndex = 2;
			this->foundPictureBox->TabStop = false;
			// 
			// foundImageNameTextBox
			// 
			this->foundImageNameTextBox->BackColor = System::Drawing::SystemColors::Control;
			this->foundImageNameTextBox->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->foundImageNameTextBox->Location = System::Drawing::Point(97, 299);
			this->foundImageNameTextBox->Name = L"foundImageNameTextBox";
			this->foundImageNameTextBox->ReadOnly = true;
			this->foundImageNameTextBox->Size = System::Drawing::Size(413, 13);
			this->foundImageNameTextBox->TabIndex = 8;
			this->foundImageNameTextBox->TabStop = false;
			// 
			// MainForm
			// 
			this->ClientSize = System::Drawing::Size(1261, 681);
			this->Controls->Add(this->groupBox4);
			this->Controls->Add(this->groupBox3);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->Name = L"MainForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Система поиска похожих изображений";
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->searchedPictureBox))->EndInit();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->groupBox3->ResumeLayout(false);
			this->groupBox4->ResumeLayout(false);
			this->groupBox4->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->foundPictureBox))->EndInit();
			this->ResumeLayout(false);

		}

	private:

		System::Void selectImageButton_Click(System::Object^  sender, System::EventArgs^  e) {

			OpenFileDialog^ openFileDialog = gcnew OpenFileDialog;

			openFileDialog->Filter = "jpg (*.jpg)|*.jpg|png (*.png)|*.png|All files (*.*)|*.*";
			openFileDialog->FilterIndex = 1;
			openFileDialog->RestoreDirectory = true;

			if (openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
			{
				searchFileName = openFileDialog->FileName;
				String^ tmp = searchFileName;
				cv::Mat img;
				cv::Mat imgResised;
				double scaleWidth, scaleHeight, imageScale;

				img = cv::imread(msclr::interop::marshal_as<std::string>(tmp), CV_LOAD_IMAGE_COLOR);

				scaleWidth = (double)img.cols / (searchedPictureBox->Width - 10);
				scaleHeight = (double)img.rows / (searchedPictureBox->Height - 10);

				imageScale = scaleWidth > scaleHeight ? scaleWidth : scaleHeight;
				cv::resize(img, imgResised, cv::Size(img.cols * (1.0 / imageScale), img.rows * (1.0 / imageScale)));

				cv::cvtColor(imgResised, imgResised, CV_RGB2RGBA);
				HBITMAP hBit = CreateBitmap(imgResised.cols, imgResised.rows, 1, 32, imgResised.data);
				Bitmap^ bmp = Bitmap::FromHbitmap((IntPtr)hBit);

				searchedPictureBox->Image = bmp;
				searchedImageNameTextBox->Text = searchFileName;
			}
		}

		System::Void selectDirectoryButton_Click(System::Object^  sender, System::EventArgs^  e) {

			IO::Stream^ myStream;
			FolderBrowserDialog^ folderBrowserDialog = gcnew FolderBrowserDialog;
			folderBrowserDialog->ShowNewFolderButton = false;
			if (searchFolderName != nullptr) {
				folderBrowserDialog->SelectedPath = searchFolderName;
			}

			if (folderBrowserDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
			{
				searchFolderName = folderBrowserDialog->SelectedPath;
				searchDirectoryTextBox->Text = searchFolderName;
				foundImageNameTextBox->Text = nullptr;
			}
		}

		System::Void searchImagesButton_Click(System::Object^  sender, System::EventArgs^  e) {

			try {

				if (searchFolderName == nullptr) {

					throw gcnew  Exception("Не указана директория поиска");
				}

				if (searchFileName == nullptr) {

					throw gcnew  Exception("Не указан файл для поиска");
				}

				//получаем имя искомого файла
				String^ tmpFileName = searchFileName;
				std::string searchedImageName = msclr::interop::marshal_as<std::string>(tmpFileName);

				array<String^>^ files = Directory::GetFiles(searchFolderName);
				std::vector<std::string> checkedImageNames;

				//преобразуем массив String с названиями файлов к массиву std::string с названиями изображений
				for (int i = 0; i < files->Length; i++) {

					String^ file = files[i];
					if (file->LastIndexOf('.') == -1) {
						continue;
					}

					String^ fileType = file->Substring(file->LastIndexOf('.') + 1);
					if (fileType != "jpg") {
						continue;
					}

					checkedImageNames.push_back(msclr::interop::marshal_as<std::string>(file));
				}

				//получаем список похожих изображений
				std::vector<std::string> foundImageNames = ImageCompare::GetSimilarityImages(searchedImageName, checkedImageNames, threshold, descriptorType, comparisionType, distanceWindow, featuresNum);

				//выводим
				findImagesListView->Clear();
				for each (std::string imageName in foundImageNames) {
					findImagesListView->Items->Add(msclr::interop::marshal_as<String^>(imageName));
				}
			}
			catch (Exception^ ex) {
				MessageBox::Show(this, ex->Message, "Ошибка", MessageBoxButtons::OK);
			}
		}

		System::Void findImagesListView_ItemActivate(System::Object^  sender, System::EventArgs^  e) {

			int i = findImagesListView->SelectedIndices[0];
			String^ foundFileName = findImagesListView->Items[i]->Text;

			cv::Mat img;
			cv::Mat imgResised;
			double scaleWidth, scaleHeight, imageScale;

			img = cv::imread(msclr::interop::marshal_as<std::string>(foundFileName), CV_LOAD_IMAGE_COLOR);

			scaleWidth = (double)img.cols / (foundPictureBox->Width - 10);
			scaleHeight = (double)img.rows / (foundPictureBox->Height - 10);

			imageScale = scaleWidth > scaleHeight ? scaleWidth : scaleHeight;
			cv::resize(img, imgResised, cv::Size(img.cols * (1.0 / imageScale), img.rows * (1.0 / imageScale)));

			cv::cvtColor(imgResised, imgResised, CV_RGB2RGBA);
			HBITMAP hBit = CreateBitmap(imgResised.cols, imgResised.rows, 1, 32, imgResised.data);
			Bitmap^ bmp = Bitmap::FromHbitmap((IntPtr)hBit);

			foundPictureBox->Image = bmp;
			foundImageNameTextBox->Text = foundFileName;
		}

		System::Void searchSettingsButton_Click(System::Object^  sender, System::EventArgs^  e) {

			SearchSettingsForm^ form = gcnew SearchSettingsForm(descriptorType, comparisionType, threshold, distanceWindow, featuresNum);

			if (form->ShowDialog() == Windows::Forms::DialogResult::OK) {
				
				this->descriptorType = form->descriptorType;
				this->comparisionType = form->comparisionType;
				this->featuresNum = form->featuresNum;
				this->threshold = form->thresholdPercent / 100.0;
				this->distanceWindow = form->distanceWindow;
			}
		}
	};
}
