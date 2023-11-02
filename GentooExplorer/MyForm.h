#pragma once

#pragma comment(lib, "ws2_32.lib")
#include <iostream>
#include <vector>
#include <string>
#include <winsock.h>
#include <Windows.h>

typedef unsigned char uchar;
static const std::string b = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";//=
static std::string base64_encode(const std::string& in) {
	std::string out;

	int val = 0, valb = -6;
	for (uchar c : in) {
		val = (val << 8) + c;
		valb += 8;
		while (valb >= 0) {
			out.push_back(b[(val >> valb) & 0x3F]);
			valb -= 6;
		}
	}
	if (valb > -6) out.push_back(b[((val << 8) >> (valb + 8)) & 0x3F]);
	while (out.size() % 4) out.push_back('=');
	return out;
}


static std::string base64_decode(const std::string& in) {

	std::string out;

	std::vector<int> T(256, -1);
	for (int i = 0; i < 64; i++) T[b[i]] = i;

	int val = 0, valb = -8;
	for (uchar c : in) {
		if (T[c] == -1) break;
		val = (val << 6) + T[c];
		valb += 6;
		if (valb >= 0) {
			out.push_back(char((val >> valb) & 0xFF));
			valb -= 8;
		}
	}
	return out;
}

std::string getSerial() {
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0) {
		std::cout << "error" << std::endl;
		exit(1);
	}
	char szPath[128] = "";
	gethostname(szPath, sizeof(szPath));
	unsigned long long physicalMemory = 0;
	GetPhysicallyInstalledSystemMemory(&physicalMemory);
	physicalMemory *= 1024;
	std::string a(szPath);
	std::string watermark = "#PONSUKECOMMUNICATIONS#";
	std::string serial_unencrypted = a + "#PONSUKECOMMUNICATIONS#" + std::to_string(physicalMemory);
	return base64_encode(serial_unencrypted);
}

namespace GentooExplorer {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		String^ url_back;
		String^ url_fd;
		int registered = 0;
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ label1;
	protected:
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::WebBrowser^ webBrowser1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ button3;

	protected:

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
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->webBrowser1 = (gcnew System::Windows::Forms::WebBrowser());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(256, 11);
			this->label1->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(50, 16);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Адрес:";
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(319, 7);
			this->textBox1->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(595, 22);
			this->textBox1->TabIndex = 1;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(923, 5);
			this->button1->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(100, 28);
			this->button1->TabIndex = 2;
			this->button1->Text = L"Перейти";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// webBrowser1
			// 
			this->webBrowser1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->webBrowser1->Location = System::Drawing::Point(16, 39);
			this->webBrowser1->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->webBrowser1->MinimumSize = System::Drawing::Size(27, 25);
			this->webBrowser1->Name = L"webBrowser1";
			this->webBrowser1->Size = System::Drawing::Size(1008, 489);
			this->webBrowser1->TabIndex = 3;
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(124, 5);
			this->button2->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(100, 28);
			this->button2->TabIndex = 4;
			this->button2->Text = L">>";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(13, 5);
			this->button3->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(100, 28);
			this->button3->TabIndex = 5;
			this->button3->Text = L"<<";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1039, 543);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->webBrowser1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label1);
			this->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->Name = L"MyForm";
			this->Text = L"GentooExplorer";
			this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		if (Convert::ToString(this->textBox1->Text)->StartsWith("serial:")) {
			String^ tmp = Convert::ToString(this->textBox1->Text);
			tmp = tmp->Remove(0, 7);
			String^ str2 = gcnew String(getSerial().c_str());
			if (tmp == str2) {
				MessageBox::Show("Спасибо за покупку GentooExplorer!", "Спасибо!", MessageBoxButtons::OK, MessageBoxIcon::Information);
				this->registered = 1;
			}
			else {
				MessageBox::Show("Невалидный серийный код!", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
		else {
			std::string h = "gentoo.org";
			String^ gentoo = gcnew String(h.c_str());
			// dbg needs
			//String^ test = Convert::ToString(this->webBrowser1->Url);
			if ((this->registered == 1) || (Convert::ToString(this->textBox1->Text) == gentoo)) {
				this->url_back = Convert::ToString(this->webBrowser1->Url);
				this->webBrowser1->Navigate(this->textBox1->Text);
				this->Text = "GentooExplorer - " + this->textBox1->Text;
			}
			else {
				MessageBox::Show("Вы используете нелицензионную версию GentooExplorer!", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
				//myForm->Show();
			}
		}
	}
	private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
		this->url_fd = Convert::ToString(this->webBrowser1->Url);
		this->webBrowser1->Navigate(this->url_back);
	}
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
	this->url_back = Convert::ToString(this->webBrowser1->Url);
	this->webBrowser1->Navigate(this->url_fd);
	}
};
}
