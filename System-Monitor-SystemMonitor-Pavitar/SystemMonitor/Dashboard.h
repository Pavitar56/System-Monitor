#pragma once
#include"ClientInfoForm.h"
#include"User.h"

#define ServerApplication "MultiClientMultipleMessagesServer"
#define ServerApplicationPath "F:\\Incedo\\FinalProject1_July2022 Northstar\\MultiClientMultipleMessagesServer\\x64\\Debug\\MultiClientMultipleMessagesServer.exe"
#define ConnectionString "server=localhost;user=root;database=finaldb;port=3306;password=Pavi@_8156"

#define ColSocket "SocketNumber"
#define ColSystemName "System_Name"
#define ColTotalRam "TotalRam"
#define ColFieldName "FreeRam"
#define ColRamUsage "RamUsage"
#define ColSystem_Idle_Window "System_Idle_Window"
#define ColDate_and_Time "Date_and_Time"
#define ColCpu_Usage "Cpu_Usage"
#define ColTotalRam "TotalRam"
#define ColFreeRam "FreeRam"
#define ColTotalDsikSpace "TotalDiskSpace"
#define ColFreeDiskSpace "FreeDiskSpace"
#define ColClientName "MachineName"

#define TimeInterval 10
#define TableName "FinalTable"

namespace SystemMonitor {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Data::SqlClient;
	using namespace MySql::Data::MySqlClient;
	using namespace System::Diagnostics;
	//using namespace System::Data::MySqlClient;
	
	//using namespace MySql.Data.MySqlClient;

	/// <summary>
	/// Summary for Dashboard
	/// </summary>
	public ref class Dashboard : public System::Windows::Forms::Form
	{
	public:
		Dashboard(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Dashboard()
		{
			if (components)
			{
				delete components;
			}
		}





	private: System::Data::DataSet^ dataSet1;

	private: System::Windows::Forms::ContextMenuStrip^ contextMenuStrip1;

	private: System::Windows::Forms::Button^ LatestInfoBtn;
	private: System::Windows::Forms::ComboBox^ SelectClientBox;



	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::StatusStrip^ statusStrip1;
	private: System::Windows::Forms::ToolStripStatusLabel^ toolStripStatusLabel1;
	private: System::Windows::Forms::Button^ Detail_InfoBtn;
	private: System::Windows::Forms::Label^ Welcome;

	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::Label^ label8;
	private: System::Windows::Forms::Label^ label9;
	private: System::Windows::Forms::ComboBox^ EntriesBox;
	private: System::Windows::Forms::ComboBox^ QueryBox;
	private: System::Windows::Forms::Button^ ExecuteBtn;
	private: System::Windows::Forms::Button^ Refreshbtn;
	private: System::Windows::Forms::Label^ label10;
	private: System::Windows::Forms::Label^ label11;
	private: System::Windows::Forms::Button^ Loggerbtn;
	private: System::Windows::Forms::Button^ StopBtn;
	private: System::Windows::Forms::Label^ QueryLabel;



















	private: System::ComponentModel::IContainer^ components;
	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)                     //inialize all the necessary components with correct properties needed to load dashboard
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->dataSet1 = (gcnew System::Data::DataSet());
			this->contextMenuStrip1 = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->LatestInfoBtn = (gcnew System::Windows::Forms::Button());
			this->SelectClientBox = (gcnew System::Windows::Forms::ComboBox());
			this->statusStrip1 = (gcnew System::Windows::Forms::StatusStrip());
			this->toolStripStatusLabel1 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->Detail_InfoBtn = (gcnew System::Windows::Forms::Button());
			this->Welcome = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->EntriesBox = (gcnew System::Windows::Forms::ComboBox());
			this->QueryBox = (gcnew System::Windows::Forms::ComboBox());
			this->ExecuteBtn = (gcnew System::Windows::Forms::Button());
			this->Refreshbtn = (gcnew System::Windows::Forms::Button());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->Loggerbtn = (gcnew System::Windows::Forms::Button());
			this->StopBtn = (gcnew System::Windows::Forms::Button());
			this->QueryLabel = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataSet1))->BeginInit();
			this->statusStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// dataSet1
			// 
			this->dataSet1->DataSetName = L"NewDataSet";
			// 
			// contextMenuStrip1
			// 
			this->contextMenuStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			this->contextMenuStrip1->Name = L"contextMenuStrip1";
			this->contextMenuStrip1->Size = System::Drawing::Size(61, 4);
			// 
			// LatestInfoBtn
			// 
			this->LatestInfoBtn->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom));
			this->LatestInfoBtn->AutoSize = true;
			this->LatestInfoBtn->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->LatestInfoBtn->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->LatestInfoBtn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->LatestInfoBtn->Location = System::Drawing::Point(32, 155);
			this->LatestInfoBtn->Margin = System::Windows::Forms::Padding(2);
			this->LatestInfoBtn->Name = L"LatestInfoBtn";
			this->LatestInfoBtn->Size = System::Drawing::Size(134, 36);
			this->LatestInfoBtn->TabIndex = 8;
			this->LatestInfoBtn->Text = L"Latest Info";
			this->LatestInfoBtn->UseVisualStyleBackColor = true;
			this->LatestInfoBtn->Click += gcnew System::EventHandler(this, &Dashboard::LatestInfoBtn_Click);
			// 
			// SelectClientBox
			// 
			this->SelectClientBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom));
			this->SelectClientBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->SelectClientBox->FormattingEnabled = true;
			this->SelectClientBox->ItemHeight = 26;
			this->SelectClientBox->Location = System::Drawing::Point(19, 99);
			this->SelectClientBox->Margin = System::Windows::Forms::Padding(2);
			this->SelectClientBox->MaxDropDownItems = 5;
			this->SelectClientBox->Name = L"SelectClientBox";
			this->SelectClientBox->Size = System::Drawing::Size(273, 34);
			this->SelectClientBox->TabIndex = 7;
			this->SelectClientBox->Text = L"Select Client Name";
			// 
			// statusStrip1
			// 
			this->statusStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			this->statusStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->toolStripStatusLabel1 });
			this->statusStrip1->Location = System::Drawing::Point(0, 539);
			this->statusStrip1->Name = L"statusStrip1";
			this->statusStrip1->Padding = System::Windows::Forms::Padding(1, 0, 10, 0);
			this->statusStrip1->Size = System::Drawing::Size(784, 22);
			this->statusStrip1->TabIndex = 5;
			this->statusStrip1->Text = L"statusStrip1";
			// 
			// toolStripStatusLabel1
			// 
			this->toolStripStatusLabel1->Name = L"toolStripStatusLabel1";
			this->toolStripStatusLabel1->Size = System::Drawing::Size(118, 17);
			this->toolStripStatusLabel1->Text = L"toolStripStatusLabel1";
			// 
			// Detail_InfoBtn
			// 
			this->Detail_InfoBtn->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom));
			this->Detail_InfoBtn->AutoSize = true;
			this->Detail_InfoBtn->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->Detail_InfoBtn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Detail_InfoBtn->Location = System::Drawing::Point(310, 158);
			this->Detail_InfoBtn->Margin = System::Windows::Forms::Padding(2);
			this->Detail_InfoBtn->Name = L"Detail_InfoBtn";
			this->Detail_InfoBtn->Size = System::Drawing::Size(131, 36);
			this->Detail_InfoBtn->TabIndex = 10;
			this->Detail_InfoBtn->Text = L"Detail Info";
			this->Detail_InfoBtn->UseVisualStyleBackColor = true;
			this->Detail_InfoBtn->Click += gcnew System::EventHandler(this, &Dashboard::Detail_InfoBtn_Click);
			// 
			// Welcome
			// 
			this->Welcome->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom));
			this->Welcome->AutoSize = true;
			this->Welcome->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 21.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Welcome->Location = System::Drawing::Point(234, 26);
			this->Welcome->Name = L"Welcome";
			this->Welcome->Size = System::Drawing::Size(339, 33);
			this->Welcome->TabIndex = 11;
			this->Welcome->Text = L"Welcome to Dashboard";
			this->Welcome->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// label3
			// 
			this->label3->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom));
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->Location = System::Drawing::Point(35, 224);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(95, 20);
			this->label3->TabIndex = 12;
			this->label3->Text = L"Client Name";
			this->label3->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label4
			// 
			this->label4->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom));
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label4->Location = System::Drawing::Point(35, 259);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(119, 20);
			this->label4->TabIndex = 13;
			this->label4->Text = L"Socket Number";
			this->label4->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label5
			// 
			this->label5->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom));
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label5->Location = System::Drawing::Point(35, 293);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(108, 20);
			this->label5->TabIndex = 14;
			this->label5->Text = L"System Name";
			this->label5->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label6
			// 
			this->label6->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom));
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label6->Location = System::Drawing::Point(35, 331);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(43, 20);
			this->label6->TabIndex = 15;
			this->label6->Text = L"Ram";
			this->label6->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label7
			// 
			this->label7->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom));
			this->label7->AutoSize = true;
			this->label7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label7->Location = System::Drawing::Point(36, 385);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(152, 20);
			this->label7->TabIndex = 16;
			this->label7->Text = L"System Idle Window";
			this->label7->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label8
			// 
			this->label8->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom));
			this->label8->AutoSize = true;
			this->label8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label8->Location = System::Drawing::Point(41, 415);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(94, 20);
			this->label8->TabIndex = 17;
			this->label8->Text = L"Cpu_Usage";
			this->label8->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label9
			// 
			this->label9->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom));
			this->label9->AutoSize = true;
			this->label9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label9->Location = System::Drawing::Point(41, 449);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(113, 20);
			this->label9->TabIndex = 18;
			this->label9->Text = L"Date and Time";
			this->label9->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// EntriesBox
			// 
			this->EntriesBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom));
			this->EntriesBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->EntriesBox->FormattingEnabled = true;
			this->EntriesBox->Items->AddRange(gcnew cli::array< System::Object^  >(20) {
				L"1", L"2", L"3", L"4", L"5", L"6", L"7", L"8",
					L"9", L"10", L"11", L"12", L"13", L"14", L"15", L"16", L"17", L"18", L"19", L"20"
			});
			this->EntriesBox->Location = System::Drawing::Point(335, 99);
			this->EntriesBox->Name = L"EntriesBox";
			this->EntriesBox->Size = System::Drawing::Size(71, 33);
			this->EntriesBox->TabIndex = 19;
			// 
			// QueryBox
			// 
			this->QueryBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom));
			this->QueryBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->QueryBox->FormattingEnabled = true;
			this->QueryBox->Items->AddRange(gcnew cli::array< System::Object^  >(6) {
				L"Max Ram Usage in Last n Entries", L"Min Ram Usage in Last n Entries",
					L"Max Cpu Usage in Last n Entries", L"Min Cpu Usage in Last n Entries", L"Max FreeDiskSpace in Last n Entries", L"Min FreeDiskSpace in Last n Entries"
			});
			this->QueryBox->Location = System::Drawing::Point(432, 102);
			this->QueryBox->Name = L"QueryBox";
			this->QueryBox->Size = System::Drawing::Size(340, 33);
			this->QueryBox->TabIndex = 20;
			this->QueryBox->Text = L"Query Box";
			// 
			// ExecuteBtn
			// 
			this->ExecuteBtn->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom));
			this->ExecuteBtn->AutoSize = true;
			this->ExecuteBtn->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->ExecuteBtn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 17.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->ExecuteBtn->Location = System::Drawing::Point(556, 155);
			this->ExecuteBtn->Name = L"ExecuteBtn";
			this->ExecuteBtn->Size = System::Drawing::Size(116, 39);
			this->ExecuteBtn->TabIndex = 21;
			this->ExecuteBtn->Text = L"Execute";
			this->ExecuteBtn->UseVisualStyleBackColor = true;
			this->ExecuteBtn->Click += gcnew System::EventHandler(this, &Dashboard::ExecuteBtn_Click);
			// 
			// Refreshbtn
			// 
			this->Refreshbtn->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Right));
			this->Refreshbtn->AutoSize = true;
			this->Refreshbtn->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->Refreshbtn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Refreshbtn->Location = System::Drawing::Point(652, 20);
			this->Refreshbtn->Name = L"Refreshbtn";
			this->Refreshbtn->Size = System::Drawing::Size(92, 34);
			this->Refreshbtn->TabIndex = 22;
			this->Refreshbtn->Text = L"Refresh";
			this->Refreshbtn->UseVisualStyleBackColor = true;
			this->Refreshbtn->Click += gcnew System::EventHandler(this, &Dashboard::Refreshbtn_Click);
			// 
			// label10
			// 
			this->label10->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom));
			this->label10->AutoSize = true;
			this->label10->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label10->Location = System::Drawing::Point(38, 480);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(129, 20);
			this->label10->TabIndex = 23;
			this->label10->Text = L"Total Disk Space";
			this->label10->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label11
			// 
			this->label11->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom));
			this->label11->AutoSize = true;
			this->label11->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label11->Location = System::Drawing::Point(36, 510);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(131, 20);
			this->label11->TabIndex = 24;
			this->label11->Text = L"Total Free Space";
			this->label11->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// Loggerbtn
			// 
			this->Loggerbtn->AutoSize = true;
			this->Loggerbtn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Loggerbtn->Location = System::Drawing::Point(19, 25);
			this->Loggerbtn->Name = L"Loggerbtn";
			this->Loggerbtn->Size = System::Drawing::Size(133, 34);
			this->Loggerbtn->TabIndex = 25;
			this->Loggerbtn->Text = L"Start Server";
			this->Loggerbtn->UseVisualStyleBackColor = true;
			this->Loggerbtn->Click += gcnew System::EventHandler(this, &Dashboard::Loggerbtn_Click);
			// 
			// StopBtn
			// 
			this->StopBtn->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->StopBtn->AutoSize = true;
			this->StopBtn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->StopBtn->Location = System::Drawing::Point(654, 502);
			this->StopBtn->Name = L"StopBtn";
			this->StopBtn->Size = System::Drawing::Size(118, 34);
			this->StopBtn->TabIndex = 26;
			this->StopBtn->Text = L"Stop Server";
			this->StopBtn->UseVisualStyleBackColor = true;
			this->StopBtn->Click += gcnew System::EventHandler(this, &Dashboard::StopBtn_Click);
			// 
			// QueryLabel
			// 
			this->QueryLabel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom));
			this->QueryLabel->AutoSize = true;
			this->QueryLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->QueryLabel->Location = System::Drawing::Point(445, 234);
			this->QueryLabel->Name = L"QueryLabel";
			this->QueryLabel->Size = System::Drawing::Size(51, 20);
			this->QueryLabel->TabIndex = 27;
			this->QueryLabel->Text = L"label2";
			this->QueryLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->QueryLabel->Visible = false;
			// 
			// Dashboard
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoSize = true;
			this->ClientSize = System::Drawing::Size(784, 561);
			this->Controls->Add(this->QueryLabel);
			this->Controls->Add(this->StopBtn);
			this->Controls->Add(this->Loggerbtn);
			this->Controls->Add(this->label11);
			this->Controls->Add(this->label10);
			this->Controls->Add(this->Refreshbtn);
			this->Controls->Add(this->ExecuteBtn);
			this->Controls->Add(this->QueryBox);
			this->Controls->Add(this->EntriesBox);
			this->Controls->Add(this->label9);
			this->Controls->Add(this->label8);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->Welcome);
			this->Controls->Add(this->Detail_InfoBtn);
			this->Controls->Add(this->LatestInfoBtn);
			this->Controls->Add(this->SelectClientBox);
			this->Controls->Add(this->statusStrip1);
			this->Margin = System::Windows::Forms::Padding(2);
			this->Name = L"Dashboard";
			this->Text = L"Dashboard";
			this->Load += gcnew System::EventHandler(this, &Dashboard::Dashboard_Load);
			this->Leave += gcnew System::EventHandler(this, &Dashboard::Dashboard_Leave);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataSet1))->EndInit();
			this->statusStrip1->ResumeLayout(false);
			this->statusStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	

	private:System::Void Labels_Back_To_Original_State()         //function to revert labels back to original state to display new client information
	{

		try
		{
			for (int i = 0; i < this->Controls->Count; i++)
			{
				if (Controls[i]->Name->Contains("label"))
				{
					//Controls[i]->Visible = false;
					Controls[i]->Text = Controls[i]->Text->Split(':')[0];
				}
			}
		}
		catch (Exception^ e)
		{
			MessageBox::Show("Exception occured!could not reinitialize labels!",
				"Exception found", MessageBoxButtons::OK);
		}
		
	}


	private:System::Void ClientNamesRefresh()                 //function to refersh client names from database in combo box 
	{
		String^ connection = ConnectionString;
		MySqlConnection^ conDB = gcnew MySqlConnection(connection);

		try
		{
			conDB->Open();     //connecting to database

			String^ query = "SELECT distinct " + ColClientName + " FROM " + TableName + " where " + ColClientName + " IS NOT NULL;";
			MySqlCommand^ cmdDatabase = gcnew MySqlCommand(query, conDB);

			MySqlDataReader^ myReader = cmdDatabase->ExecuteReader();  //executing query to find all distinct client names available

			while (myReader->Read())
			{
				String^ ClientName = myReader->GetString(0);
				int index = SelectClientBox->FindString(ClientName);
				if (index < 0)                                              //aapending only new clients in combox
				{
					SelectClientBox->Items->Add(ClientName);
				}

			}
			myReader->Close();
		}
		catch (Exception^ e)
		{
			MessageBox::Show("Failed to connect to database(database connection string is wrong)",
				"Exception found", MessageBoxButtons::OK);
		}
		finally
		{
			
			conDB->Close();               //clsoing connecting,deallocating resources
		}
		
	}
	
	

	

	private: System::Void Dashboard_Load(System::Object^ sender, System::EventArgs^ e) //event that occurs at loading form to refereh client names
	{
		ClientNamesRefresh();
		toolStripStatusLabel1->Text = "Active";	

	}

	private: System::Void Dashboard_Leave(System::Object^ sender, System::EventArgs^ e) 
	{
	
		toolStripStatusLabel1->Text = "Not Active";
	}


	public:User^ SelectedClient = nullptr;               //contains information of selected client name and number of entries  combobox

	private: System::Void Detail_InfoBtn_Click(System::Object^ sender, System::EventArgs^ e) //detail info btn event click
	{
		//User^ SelectedClient = nullptr;


		try
		{
			SelectedClient = gcnew User;
			SelectedClient->name = this->SelectClientBox->Text;
			SelectedClient->Entries = int::Parse(this->EntriesBox->Text);             //initializes client info from combobox to class varaible user

			SystemMonitor::ClientInfoForm^ SystemInfoForm = gcnew SystemMonitor::ClientInfoForm(SelectedClient);  //creates clientinfo form with selected combobox names and entries

			SystemInfoForm->Show();   //opens clientinfo form for selected client

		}
		catch (...)
		{
			MessageBox::Show("Exception occured.Please select number of Entries to search for!",
				"Exception", MessageBoxButtons::OK);

		}
		
	
	
	}
		private: System::Void LatestInfoBtn_Click(System::Object^ sender, System::EventArgs^ e)   //latest info button click handler to display latest
		{
																									//client information of selected client

			Labels_Back_To_Original_State();                                               //reverting labels back to original state 
			
			String^ connection = ConnectionString;
			MySqlConnection^ conDB = gcnew MySqlConnection(connection);
			
			try 
			{
				
				conDB->Open();                       //connected to database
				String^ query = "SELECT * FROM " + TableName + " where MachineName IS NOT NULL and MachineName = @SelectedClient order by id desc LIMIT 1;";
				MySqlCommand^ cmdDatabase = gcnew MySqlCommand(query, conDB);
				cmdDatabase->Parameters->AddWithValue("@SelectedClient", this->SelectClientBox->Text);  //dynamically adding selected client name from combobox to query
				MySqlDataReader^ myReader = cmdDatabase->ExecuteReader();              //executing query for slected client name
				
				while (myReader->Read())               //reading rows to display info
				{
					this->label3->Text = this->label3->Text + ":    " + myReader[ColClientName];
					this->label4->Text = this->label4->Text + ":    " + myReader[ColSocket];
					this->label5->Text = this->label5->Text + ":    " + myReader[ColSystemName];
					
					this->label6->Text = this->label6->Text + ":    " + "Total Ram = " + Math::Round((myReader->GetUInt64(ColTotalRam) / (1024.0 * 1024)),2) + "GB   Free Ram = " 
						                 + Math::Round((myReader->GetUInt64(ColFreeRam) / (1024*1024)),2) + "GB \r\n"	
										+	"			RamUsage = " + myReader[ColRamUsage] +" % ";
					
					this->label7->Text = this->label7->Text + ":    " + myReader[ColSystem_Idle_Window] + " seconds";
					this->label8->Text = this->label8->Text + ":    " + myReader[ColCpu_Usage] + " %";
					this->label9->Text = this->label9->Text + ":    " + myReader[ColDate_and_Time];
					this->label10->Text = this->label10->Text + ":    " + Math::Round((myReader->GetUInt64(ColTotalDsikSpace) / (1024)), 2) + " GB";
					this->label11->Text = this->label11->Text + ":    " + Math::Round((myReader->GetUInt64(ColFreeDiskSpace) / (1024)), 2) + " GB";
					
				}
				myReader->Close();  //deallocating data reader
			}
			catch (Exception^ e) {
				
				MessageBox::Show("Exception occured",
					"Exception", MessageBoxButtons::OK);
			}
			finally
			{
				conDB->Close();     //closing connection,deallocating resources
			}
			


			/*for (int i = 0; i < this->Controls->Count; i++)
			{
				if(Controls[i]->Name ->Contains("label"))
				{
					Controls[i]->Visible = true;
				}
			}*/
		
		}


		private: System::Void Refreshbtn_Click(System::Object^ sender, System::EventArgs^ e)  //refersh button click handler to refersh 
		{																						//clinet name combobox with updated client names
				
			ClientNamesRefresh();
		
		}


		private: System::Void Loggerbtn_Click(System::Object^ sender, System::EventArgs^ e) //button to start server
		{

			array<Process^>^ Server = Process::GetProcessesByName(ServerApplication);  //checking if server already exists or not

			if (Server->Length == 0)                        //if doesnot exist start the server
			{
				try
				{
					ProcessStartInfo^ startInfo = gcnew ProcessStartInfo();
					startInfo->FileName = ServerApplicationPath;          //server exe path
					Process::Start(startInfo);

					MessageBox::Show("Server Is now Running!",
						"Server Is  Running", MessageBoxButtons::OK);
				}
				catch(Exception ^e)
				{
					MessageBox::Show("Path provided to server application is wrong!",
						"Exception", MessageBoxButtons::OK);
				}
			}
			else                                                    //if it exists do not start new server
			{

				MessageBox::Show("Server Is Already Running.You are trying to start a new server!",
					"Server Is  Running", MessageBoxButtons::OK);
			}

		}


		private: System::Void StopBtn_Click(System::Object^ sender, System::EventArgs^ e)  //button to stop server
		{

			array<Process^>^ Server = Process::GetProcessesByName(ServerApplication); //checking if server already exists or not

			if (Server->Length == 0)                                   //if server is not running req user to start server before closing
			{
				MessageBox::Show("Server Is already not Running.Please start server before killing it!",
					"Server Is not Running", MessageBoxButtons::OK);
			}
			else                                                 //if server is running then close it
			{
				Server[0]->Kill();
				MessageBox::Show("Server Is now closed!",
					"Server Is not Running", MessageBoxButtons::OK);
			}
		
		}
		


		private:System::Void ExecuteQuery(String^ MinMax, String^ Column, int^ Entries)     //helper function to execute queries selected in combobox
		{																				

			String^ connection = ConnectionString;
			MySqlConnection^ conDB = gcnew MySqlConnection(connection);

			try 
			{

				conDB->Open();    //connecting to database
				String^ query = "Select * from(select * from " + TableName + " where MachineName is not null order by id desc limit " + Entries + ")sub where "
								+ Column + " = (Select " + MinMax + "(" + Column + ") from(select * from " + TableName +
							" where MachineName is not null order by id desc limit " + Entries + ")sub2) group by MachineName;";

				MySqlCommand^ cmdDatabase = gcnew MySqlCommand(query, conDB);
				MySqlDataReader^ myReader = cmdDatabase->ExecuteReader();  //executing query to find min and max usage according to arguments passed

				this->QueryLabel->Text = "";
				int rows = 0;    //counting number of clients with same usage

				while (myReader->Read())
				{
					rows = rows + 1;
					this->QueryLabel->Text = this->QueryLabel->Text + "Client Name " + (rows).ToString() + " : " + myReader["MachineName"] + "\r\n" +
												Column + " : " + Math::Round(myReader->GetDouble(Column),2);   //initalizing the info read

					if ("FreeDiskSpace" == Column)     //only freedisk query needs gb otherwise all other values are in %
					{
						this->QueryLabel->Text = this->QueryLabel->Text + " MB \r\n";
					}
					else
					{
						this->QueryLabel->Text = this->QueryLabel->Text + " % \r\n";
					}
					
				}
				this->QueryLabel->Text = this->QueryLabel->Text + "There are total of " + rows.ToString() + " Clients with " + MinMax + " " + Column + "\r\n";

				myReader->Close();  //closing the reader
			}
			catch (Exception^ e)             //exception catcher 
			{ 
				MessageBox::Show("Exception occured",
					"Exception", MessageBoxButtons::OK);
			}
			finally          //freein g resourcing and setting visiblity of label to be true to display info
			{
				this->QueryLabel->Visible = true;

				conDB->Close();            //deallocating resources
			}


		}

		private: System::Void ExecuteBtn_Click(System::Object^ sender, System::EventArgs^ e)     //execute button click handler 
		{


			try 
			{
				String^ QueryAsked = this->QueryBox->Text;                    //reading selected query
				int Entries = int::Parse(this->EntriesBox->Text);             //reading selected number of last entries to execute query on
				int QueryAskedIndex = this->QueryBox->SelectedIndex;            //reading selected query index from combobox   

				//System::Diagnostics::Debug::WriteLine(QueryAskedIndex);
				 
				/*
				
				giving appropiate arguments to helper function of execute button according to query selected
				
				*/

				if ( 0 == QueryAskedIndex)                                           
				{
					ExecuteQuery("MAX", "RamUsage" , Entries);
				}
				else if (1 == QueryAskedIndex)
				{
					ExecuteQuery("MIN", "RamUsage", Entries);
				}
				else if (2 == QueryAskedIndex)
				{
					ExecuteQuery("MAX", "Cpu_Usage", Entries);
				}
				else if (3 == QueryAskedIndex)
				{
					ExecuteQuery("MIN", "Cpu_Usage", Entries);
				}
				else if (4 == QueryAskedIndex)
				{
					ExecuteQuery("MAX", "FreeDiskSpace", Entries);
				}
				else if (5 == QueryAskedIndex)
				{
					ExecuteQuery("MIN", "FreeDiskSpace", Entries);
				}
				else                                             //if queryselected is not available in given options inside combox then disaply message
				{
					MessageBox::Show("Please select Correct Query",
						"Exception", MessageBoxButtons::OK);
				}
	
			}
			catch (Exception^ e)           //exception occures when either query box or number of entries box is not selected by user 
			{

				MessageBox::Show("Please select both Entries and Query before executing it!",
					"Exception", MessageBoxButtons::OK);
			}

		}
};
}
