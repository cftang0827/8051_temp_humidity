#pragma once
#include <windows.h>




namespace serialPort {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO::Ports;

	/// <summary>
	/// Form1 的摘要
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public: delegate void displayHum(String^ hum);
	public: delegate void displayTemp(String^ temp);
	public: displayHum^ dH;
			displayTemp^ dT;
	public:
		
		SerialPort^ sp;
		Form1(void)
		{
			InitializeComponent();
			array<String^>^ serialPortList = nullptr;
			//array<String^>^ BaudComboBox = nullptr;
			try
			{
				// Get a list of serial port names.
				serialPortList = SerialPort::GetPortNames();
			}
			catch (Win32Exception^ ex)
			{
				//Console::WriteLine(ex->Message);
			}

			Array::Sort(serialPortList);

			for(int i = 0; i < serialPortList->Length; i++)
			{
				SerialPortBox->Items->Add(serialPortList[i]);
			}

			BaudComboBox -> Items -> Add(9600);
			BaudComboBox -> Items -> Add(115200);

			requestBtn -> Enabled = false;
			setDelegate_H();
			setDelegate_T();
		}

	protected:
		/// <summary>
		/// 清除任何使用中的資源。
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::ComboBox^  SerialPortBox;
	protected: 


	protected: 
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Label^  status;

	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::ComboBox^  BaudComboBox;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  temp;
	private: System::Windows::Forms::TextBox^  humBox;
	private: System::Windows::Forms::TextBox^  tempBox;


	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Button^  requestBtn;


	private:
		/// <summary>
		/// 設計工具所需的變數。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器
		/// 修改這個方法的內容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->SerialPortBox = (gcnew System::Windows::Forms::ComboBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->status = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->BaudComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->temp = (gcnew System::Windows::Forms::Label());
			this->humBox = (gcnew System::Windows::Forms::TextBox());
			this->tempBox = (gcnew System::Windows::Forms::TextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->requestBtn = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// SerialPortBox
			// 
			this->SerialPortBox->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->SerialPortBox->FormattingEnabled = true;
			this->SerialPortBox->Location = System::Drawing::Point(127, 31);
			this->SerialPortBox->Name = L"SerialPortBox";
			this->SerialPortBox->Size = System::Drawing::Size(121, 28);
			this->SerialPortBox->TabIndex = 0;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->label1->Location = System::Drawing::Point(24, 34);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(84, 20);
			this->label1->TabIndex = 1;
			this->label1->Text = L"COM port";
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->button1->Location = System::Drawing::Point(264, 28);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(101, 82);
			this->button1->TabIndex = 2;
			this->button1->Text = L"Connect";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// status
			// 
			this->status->AutoSize = true;
			this->status->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->status->Location = System::Drawing::Point(24, 142);
			this->status->Name = L"status";
			this->status->Size = System::Drawing::Size(117, 20);
			this->status->TabIndex = 3;
			this->status->Text = L"Disconnection";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->label2->Location = System::Drawing::Point(24, 85);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(86, 20);
			this->label2->TabIndex = 4;
			this->label2->Text = L"Baud Rate";
			// 
			// BaudComboBox
			// 
			this->BaudComboBox->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->BaudComboBox->FormattingEnabled = true;
			this->BaudComboBox->Location = System::Drawing::Point(127, 82);
			this->BaudComboBox->Name = L"BaudComboBox";
			this->BaudComboBox->Size = System::Drawing::Size(121, 28);
			this->BaudComboBox->TabIndex = 5;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->label3->Location = System::Drawing::Point(24, 206);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(78, 20);
			this->label3->TabIndex = 6;
			this->label3->Text = L"Humidity";
			// 
			// temp
			// 
			this->temp->AutoSize = true;
			this->temp->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->temp->Location = System::Drawing::Point(24, 259);
			this->temp->Name = L"temp";
			this->temp->Size = System::Drawing::Size(107, 20);
			this->temp->TabIndex = 7;
			this->temp->Text = L"Temperature";
			// 
			// humBox
			// 
			this->humBox->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->humBox->Location = System::Drawing::Point(175, 203);
			this->humBox->Name = L"humBox";
			this->humBox->Size = System::Drawing::Size(100, 29);
			this->humBox->TabIndex = 8;
			// 
			// tempBox
			// 
			this->tempBox->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->tempBox->Location = System::Drawing::Point(175, 256);
			this->tempBox->Name = L"tempBox";
			this->tempBox->Size = System::Drawing::Size(100, 29);
			this->tempBox->TabIndex = 9;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->label4->Location = System::Drawing::Point(282, 206);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(23, 20);
			this->label4->TabIndex = 10;
			this->label4->Text = L"%";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->label5->Location = System::Drawing::Point(282, 259);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(25, 20);
			this->label5->TabIndex = 10;
			this->label5->Text = L"℃";
			// 
			// requestBtn
			// 
			this->requestBtn->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->requestBtn->Location = System::Drawing::Point(264, 134);
			this->requestBtn->Name = L"requestBtn";
			this->requestBtn->Size = System::Drawing::Size(101, 39);
			this->requestBtn->TabIndex = 11;
			this->requestBtn->Text = L"Request";
			this->requestBtn->UseVisualStyleBackColor = true;
			this->requestBtn->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(398, 320);
			this->Controls->Add(this->requestBtn);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->tempBox);
			this->Controls->Add(this->humBox);
			this->Controls->Add(this->temp);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->BaudComboBox);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->status);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->SerialPortBox);
			this->Name = L"Form1";
			this->Text = L"Room temperature and humidity";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
			 }
	private: void displayTextHum(String^ hum)
			 {
				 humBox -> Text = hum;
				 
			 }
	private: void displayTextTemp(String^ temp)
			 {
				 tempBox -> Text = temp;
			 }
	private: void setDelegate_H(void)
			 {
				 dH = gcnew displayHum(this,&serialPort::Form1::displayTextHum);
			 }
	private: void setDelegate_T(void)
			 {
				 dT = gcnew displayTemp(this,&serialPort::Form1::displayTextTemp);
			 }

	private: void DataReceivedHandler(
                        Object^ sender,
                        SerialDataReceivedEventArgs^ e)
    {
		Form1^ a = gcnew Form1;
        SerialPort^ sp1 = (SerialPort^)sender;
		String^ hum = sp1 -> ReadLine();
		String^ temp = sp1 -> ReadLine();
		
		if( hum[0] == 'T' && temp[0] == 'H')
		{
			String^ tt = hum;
			hum = temp->Substring(1,temp->Length-1);
			temp = tt->Substring(1,tt->Length-1);
		}else
		{
			hum = hum->Substring(1,hum->Length-1);
			temp = temp->Substring(1,temp->Length-1);
		}
		

		humBox-> Invoke(this->dH,hum);
		tempBox -> Invoke(this->dT,temp);
    }

	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {


				 sp = gcnew SerialPort();
				 sp->PortName = SerialPortBox->SelectedItem->ToString();
				 sp->BaudRate = System::Convert::ToInt32( BaudComboBox->SelectedItem->ToString() );
				 sp->DataReceived += gcnew SerialDataReceivedEventHandler(this,&serialPort::Form1::DataReceivedHandler);
				 try
				 {
					sp->Open();

				 }catch(IO::IOException^ e)
				 {
					 this->status->Text = "Error";
				 }

				 if(sp->IsOpen)
				 {
					 this->status->Text = "Connection Success!";
					 requestBtn -> Enabled = true;
					 
				 }else
				 {
					 this->status->Text = "Connection Fail";
				 }
			 }
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
				 sp -> WriteLine("a");
				 

				//String^ hum = sp -> ReadLine();
				//String^ temp = sp -> ReadLine();

				//humBox -> Text = hum;
				//tempBox -> Text = temp;


			 }
};
}

