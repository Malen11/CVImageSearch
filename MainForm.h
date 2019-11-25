#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <msclr\marshal_cppstd.h>

namespace CVImageSearch {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;

	/// <summary>
	/// Сводка для MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	private:
		Button^  selectImageButton;
		Button^  selectDirectoryButton;
		GroupBox^  groupBox1;
	private: System::Windows::Forms::PictureBox^  searchedPictureBox;


		System::ComponentModel::Container ^components; 

		CvCapture * capture;
		IplImage* frame;
		String^ searchFolderName;
		String^ searchFileName;

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
			this->searchedPictureBox = (gcnew System::Windows::Forms::PictureBox());
			this->selectDirectoryButton = (gcnew System::Windows::Forms::Button());
			this->groupBox1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->searchedPictureBox))->BeginInit();
			this->SuspendLayout();
			// 
			// selectImageButton
			// 
			this->selectImageButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->selectImageButton->Location = System::Drawing::Point(410, 339);
			this->selectImageButton->Name = L"selectImageButton";
			this->selectImageButton->Size = System::Drawing::Size(100, 50);
			this->selectImageButton->TabIndex = 0;
			this->selectImageButton->Text = L"Выбрать изображение";
			this->selectImageButton->UseVisualStyleBackColor = true;
			this->selectImageButton->Click += gcnew System::EventHandler(this, &MainForm::selectImageButton_Click);
			// 
			// groupBox1
			// 
			this->groupBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left));
			this->groupBox1->Controls->Add(this->selectImageButton);
			this->groupBox1->Controls->Add(this->searchedPictureBox);
			this->groupBox1->Location = System::Drawing::Point(12, 12);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(516, 395);
			this->groupBox1->TabIndex = 1;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Искомое изображение";
			// 
			// searchedPictureBox
			// 
			this->searchedPictureBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->searchedPictureBox->Location = System::Drawing::Point(6, 19);
			this->searchedPictureBox->Name = L"searchedPictureBox";
			this->searchedPictureBox->Size = System::Drawing::Size(504, 314);
			this->searchedPictureBox->TabIndex = 2;
			this->searchedPictureBox->TabStop = false;
			// 
			// selectDirectoryButton
			// 
			this->selectDirectoryButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->selectDirectoryButton->Location = System::Drawing::Point(1152, 619);
			this->selectDirectoryButton->Name = L"selectDirectoryButton";
			this->selectDirectoryButton->Size = System::Drawing::Size(100, 50);
			this->selectDirectoryButton->TabIndex = 2;
			this->selectDirectoryButton->Text = L"Выбрать директорию";
			this->selectDirectoryButton->UseVisualStyleBackColor = true;
			this->selectDirectoryButton->Click += gcnew System::EventHandler(this, &MainForm::selectDirectoryButton_Click);
			// 
			// MainForm
			// 
			this->ClientSize = System::Drawing::Size(1264, 681);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->selectDirectoryButton);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Name = L"MainForm";
			this->Text = L"Система поиска похожих изображений";
			this->groupBox1->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->searchedPictureBox))->EndInit();
			this->ResumeLayout(false);

		}

	private:

		System::Void selectImageButton_Click(System::Object^  sender, System::EventArgs^  e) {
			
			OpenFileDialog^ openFileDialog = gcnew OpenFileDialog;

			//openFileDialog->InitialDirectory = "c:\\";
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
				/*cv::resize(img, imgResised, cv::Size(img.cols * (1.0 / imageScale), img.rows * (1.0 / imageScale)));*/

				cv::cvtColor(img, img, CV_RGB2RGBA);
				HBITMAP hBit = CreateBitmap(img.cols, img.rows, 1, 32, img.data);
				
				searchedPictureBox->Image = nullptr;
				searchedPictureBox->Refresh();
				Graphics^ graphics = searchedPictureBox->CreateGraphics();
				Bitmap^ bmp = Bitmap::FromHbitmap((IntPtr)hBit);
				RectangleF rect(0, 0, img.cols * (1.0 / imageScale), img.rows * (1.0 / imageScale));
				graphics->DrawImage(bmp, rect);

				if (imageScale < 1.0) {

					searchedPictureBox->SizeMode = PictureBoxSizeMode::CenterImage;
				}
			}
		}
	
		System::Void selectDirectoryButton_Click(System::Object^  sender, System::EventArgs^  e) {

			IO::Stream^ myStream;
			FolderBrowserDialog^ folderBrowserDialog = gcnew FolderBrowserDialog;
			folderBrowserDialog->ShowNewFolderButton = false;

			if (folderBrowserDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
			{
				searchFolderName = folderBrowserDialog->SelectedPath;
			}
		}
	};
}
