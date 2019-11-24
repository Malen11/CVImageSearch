#include "MainForm.h"

//capture = cvCaptureFromCAM(0);

using namespace System;
using namespace System::Windows::Forms;

[STAThread]
int main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	CVImageSearch::MainForm form;
	Application::Run(%form);
	return 0;
}