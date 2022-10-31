#pragma once
#include"User.h"
//#define ConnectionString "server = localhost; user id = root; persistsecurityinfo = True; database = testdb"
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
	using namespace MySql::Data::MySqlClient;
	/// <summary>
	/// Summary for ClientInfoForm
	/// </summary>
	public ref class ClientInfoForm : public System::Windows::Forms::Form
	{

	public:User^ ClientInfo=nullptr;
	public:
		ClientInfoForm(User^ user)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			ClientInfo = gcnew User;
			ClientInfo->name = user->name;
			this->ClientName->Text = ClientInfo->name;
			ClientInfo->Entries = user->Entries;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~ClientInfoForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::DataVisualization::Charting::Chart^ CpuRamUsageChart;
	protected:

	protected:

	private: System::Windows::Forms::Label^ ClientName;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^ RamChart;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^ DiskUsageChart;
	private: System::Windows::Forms::DataGridView^ dataGridView1;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^ IdleWindowChart;

	protected:

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)        //initializing all the necesssary components with correct properties needed to load form
		{
			System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^ legend1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^ series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^ series2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Title^ title1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Title());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea2 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^ legend2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^ series3 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^ series4 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Title^ title2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Title());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea3 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^ legend3 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^ series5 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Title^ title3 = (gcnew System::Windows::Forms::DataVisualization::Charting::Title());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea4 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^ legend4 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^ series6 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Title^ title4 = (gcnew System::Windows::Forms::DataVisualization::Charting::Title());
			this->CpuRamUsageChart = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->ClientName = (gcnew System::Windows::Forms::Label());
			this->RamChart = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->DiskUsageChart = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->IdleWindowChart = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->CpuRamUsageChart))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->RamChart))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DiskUsageChart))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->IdleWindowChart))->BeginInit();
			this->SuspendLayout();
			// 
			// CpuRamUsageChart
			// 
			this->CpuRamUsageChart->BackImageAlignment = System::Windows::Forms::DataVisualization::Charting::ChartImageAlignmentStyle::Center;
			chartArea1->AxisX->Title = L"Timestamp";
			chartArea1->AxisY->Title = L"Usage in %";
			chartArea1->Name = L"ChartArea1";
			this->CpuRamUsageChart->ChartAreas->Add(chartArea1);
			legend1->DockedToChartArea = L"ChartArea1";
			legend1->Name = L"Legend1";
			this->CpuRamUsageChart->Legends->Add(legend1);
			this->CpuRamUsageChart->Location = System::Drawing::Point(16, 88);
			this->CpuRamUsageChart->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->CpuRamUsageChart->Name = L"CpuRamUsageChart";
			series1->ChartArea = L"ChartArea1";
			series1->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series1->IsValueShownAsLabel = true;
			series1->LabelForeColor = System::Drawing::Color::Crimson;
			series1->Legend = L"Legend1";
			series1->LegendText = L"Cpu_Usage(%)";
			series1->MarkerBorderColor = System::Drawing::Color::Black;
			series1->MarkerStyle = System::Windows::Forms::DataVisualization::Charting::MarkerStyle::Triangle;
			series1->Name = L"Cpu";
			series2->ChartArea = L"ChartArea1";
			series2->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series2->IsValueShownAsLabel = true;
			series2->LabelForeColor = System::Drawing::Color::DeepSkyBlue;
			series2->Legend = L"Legend1";
			series2->LegendText = L"Ram_Usage(%)";
			series2->MarkerColor = System::Drawing::Color::Black;
			series2->MarkerStyle = System::Windows::Forms::DataVisualization::Charting::MarkerStyle::Circle;
			series2->Name = L"Ram";
			this->CpuRamUsageChart->Series->Add(series1);
			this->CpuRamUsageChart->Series->Add(series2);
			this->CpuRamUsageChart->Size = System::Drawing::Size(461, 317);
			this->CpuRamUsageChart->TabIndex = 0;
			this->CpuRamUsageChart->Text = L"CpuUsage";
			title1->Name = L"Ram and CPU usage";
			title1->Text = L"Ram and CPU Usage in %";
			this->CpuRamUsageChart->Titles->Add(title1);
			// 
			// ClientName
			// 
			this->ClientName->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom));
			this->ClientName->AutoSize = true;
			this->ClientName->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 21.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->ClientName->Location = System::Drawing::Point(627, 29);
			this->ClientName->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->ClientName->Name = L"ClientName";
			this->ClientName->Size = System::Drawing::Size(99, 33);
			this->ClientName->TabIndex = 1;
			this->ClientName->Text = L"label1";
			// 
			// RamChart
			// 
			this->RamChart->Anchor = System::Windows::Forms::AnchorStyles::Top;
			chartArea2->AxisX->Title = L"TimeStamp";
			chartArea2->AxisY->Title = L"Ram in GB";
			chartArea2->Name = L"ChartArea1";
			this->RamChart->ChartAreas->Add(chartArea2);
			legend2->Name = L"Legend1";
			this->RamChart->Legends->Add(legend2);
			this->RamChart->Location = System::Drawing::Point(503, 88);
			this->RamChart->Name = L"RamChart";
			series3->ChartArea = L"ChartArea1";
			series3->IsValueShownAsLabel = true;
			series3->Legend = L"Legend1";
			series3->Name = L"TotalRam";
			series4->ChartArea = L"ChartArea1";
			series4->IsValueShownAsLabel = true;
			series4->Legend = L"Legend1";
			series4->Name = L"FreeRam";
			series4->SmartLabelStyle->AllowOutsidePlotArea = System::Windows::Forms::DataVisualization::Charting::LabelOutsidePlotAreaStyle::No;
			this->RamChart->Series->Add(series3);
			this->RamChart->Series->Add(series4);
			this->RamChart->Size = System::Drawing::Size(458, 317);
			this->RamChart->TabIndex = 2;
			this->RamChart->Text = L"chart1";
			title2->Name = L"Title1";
			title2->Text = L"Total Ram and Available Ram";
			this->RamChart->Titles->Add(title2);
			// 
			// DiskUsageChart
			// 
			this->DiskUsageChart->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			chartArea3->Area3DStyle->Enable3D = true;
			chartArea3->Name = L"ChartArea1";
			this->DiskUsageChart->ChartAreas->Add(chartArea3);
			legend3->Name = L"Legend1";
			this->DiskUsageChart->Legends->Add(legend3);
			this->DiskUsageChart->Location = System::Drawing::Point(27, 463);
			this->DiskUsageChart->Name = L"DiskUsageChart";
			series5->ChartArea = L"ChartArea1";
			series5->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Pie;
			series5->IsValueShownAsLabel = true;
			series5->Legend = L"Legend1";
			series5->Name = L"DiskUsage";
			this->DiskUsageChart->Series->Add(series5);
			this->DiskUsageChart->Size = System::Drawing::Size(404, 362);
			this->DiskUsageChart->TabIndex = 3;
			this->DiskUsageChart->Text = L"chart1";
			title3->Name = L"Title1";
			title3->Text = L"Disk Usage in GB";
			this->DiskUsageChart->Titles->Add(title3);
			// 
			// dataGridView1
			// 
			this->dataGridView1->AllowUserToAddRows = false;
			this->dataGridView1->AllowUserToDeleteRows = false;
			this->dataGridView1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->Location = System::Drawing::Point(512, 463);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->RowHeadersWidth = 51;
			this->dataGridView1->Size = System::Drawing::Size(877, 340);
			this->dataGridView1->TabIndex = 4;
			// 
			// IdleWindowChart
			// 
			this->IdleWindowChart->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			chartArea4->AxisX->Title = L"TimeStamp";
			chartArea4->AxisY->Title = L"Idle Window in seconds";
			chartArea4->Name = L"ChartArea1";
			this->IdleWindowChart->ChartAreas->Add(chartArea4);
			legend4->Name = L"Legend1";
			this->IdleWindowChart->Legends->Add(legend4);
			this->IdleWindowChart->Location = System::Drawing::Point(986, 100);
			this->IdleWindowChart->Name = L"IdleWindowChart";
			series6->ChartArea = L"ChartArea1";
			series6->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::StepLine;
			series6->IsValueShownAsLabel = true;
			series6->Legend = L"Legend1";
			series6->Name = L"Idle Time(sec)";
			this->IdleWindowChart->Series->Add(series6);
			this->IdleWindowChart->Size = System::Drawing::Size(427, 295);
			this->IdleWindowChart->TabIndex = 5;
			this->IdleWindowChart->Text = L"chart1";
			title4->Name = L"Title1";
			title4->Text = L"IdleWindow of client in seconds";
			this->IdleWindowChart->Titles->Add(title4);
			// 
			// ClientInfoForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1443, 857);
			this->Controls->Add(this->IdleWindowChart);
			this->Controls->Add(this->dataGridView1);
			this->Controls->Add(this->DiskUsageChart);
			this->Controls->Add(this->RamChart);
			this->Controls->Add(this->ClientName);
			this->Controls->Add(this->CpuRamUsageChart);
			this->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->Name = L"ClientInfoForm";
			this->Text = L"ClientInfoForm";
			this->Load += gcnew System::EventHandler(this, &ClientInfoForm::ClientInfoForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->CpuRamUsageChart))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->RamChart))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DiskUsageChart))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->IdleWindowChart))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	
	private:System::Void Initialize_CpuRamUsage_Chart()    //plots ram and cpu usage line chart with values of selected client
	{
		String^ connection = ConnectionString;
		MySqlConnection^ conDB = gcnew MySqlConnection(connection);

		try {

			conDB->Open(); //connected to database
			String^ query = "SELECT Cpu_Usage,RamUsage,Date_and_Time FROM(SELECT * FROM " + TableName + " where MachineName is not Null and MachineName = @Name order by id DESC LIMIT @Entries)SUB ORDER BY id ASC; ";

			MySqlCommand^ cmdDatabase = gcnew MySqlCommand(query, conDB);
			cmdDatabase->Parameters->AddWithValue("@Name", ClientInfo->name);      //dynamicaly adding selected clientname from dashboard to query
			cmdDatabase->Parameters->AddWithValue("@Entries", ClientInfo->Entries); //dynamicaly adding number of last entries from dashboard to query 

			MySqlDataReader^ myReader = cmdDatabase->ExecuteReader();  //executing the query

			while (myReader->Read())
			{
				String^ time = myReader->GetString(ColDate_and_Time);             // xaxis is timestamp cloumn
				this->CpuRamUsageChart->Series["Cpu"]->Points->AddXY(time->Split(' ')[3], Math::Round(myReader->GetDouble(ColCpu_Usage),2)); //cpu usage series
				this->CpuRamUsageChart->Series["Ram"]->Points->AddY(myReader->GetInt64(ColRamUsage)); //ram usage series

				//System::Diagnostics::Debug::WriteLine(myReader[ColCpu_Usage]);
				
			}
			myReader->Close();
		}
		catch (Exception^ e) 
		{
			MessageBox::Show("Failed ",
				"Exception Occured", MessageBoxButtons::OK);
		}
		finally
		{
			conDB->Close();   //closing the conection
		}
		
	}

	private:System::Void Initialize_RamChart()        //initalises ram bar chart with total ram and available ram at tiemstamps
	{

		String^ connection = ConnectionString;
		MySqlConnection^ conDB = gcnew MySqlConnection(connection);

		try {

			conDB->Open();  //connected to database
			String^ query = "SELECT TotalRam,FreeRam,Date_and_Time FROM(SELECT * FROM " + TableName + " where MachineName is not NULL and MachineName=@Name order by id DESC LIMIT @Entries)SUB ORDER by id ASC;";
		
			MySqlCommand^ cmdDatabase = gcnew MySqlCommand(query, conDB);
			cmdDatabase->Parameters->AddWithValue("@Name", ClientInfo->name);
			cmdDatabase->Parameters->AddWithValue("@Entries", ClientInfo->Entries);

			MySqlDataReader^ myReader = cmdDatabase->ExecuteReader();
			while (myReader->Read())
			{
				String^ time = myReader->GetString(ColDate_and_Time);         //xaxis is time stamp when data was added in database
				int total = Math::Round((myReader->GetUInt64(ColTotalRam) / (1024.0 * 1024)), 2);   //converting KB to GB
				int Free = Math::Round((myReader->GetInt64(ColFreeRam) / (1024.0 * 1024)), 2);      // ^

				this->RamChart->Series["TotalRam"]->Points->AddXY(time->Split(' ')[3], total);   //extracting only time in xaxis 
				this->RamChart->Series["FreeRam"]->Points->AddY(Free);

				System::Diagnostics::Debug::WriteLine(myReader[ColFreeRam]);
			}
			myReader->Close();
		}
		catch (Exception^ e) {

			MessageBox::Show("Failed ",
				"Exception Occured", MessageBoxButtons::OK);
		}
		finally
		{
			conDB->Close();   //closing the connection
		}
		

	}
	
	private:System::Void Initialize_DiskPieChart()          //initalizes the pie chart of disk space with slected client info
	{
		String^ connection = ConnectionString;
		MySqlConnection^ conDB = gcnew MySqlConnection(connection);

		try {

			conDB->Open();   //connecting to database
			String^ query = "SELECT AVG(TotalDiskSpace),AVG(FreeDiskSpace) from " + TableName + " where MachineName is not null and MachineName = @Name order by id desc limit @Entries;";
			MySqlCommand^ cmdDatabase = gcnew MySqlCommand(query, conDB);
			cmdDatabase->Parameters->AddWithValue("@Name", ClientInfo->name);
			cmdDatabase->Parameters->AddWithValue("@Entries", ClientInfo->Entries);

			MySqlDataReader^ myReader = cmdDatabase->ExecuteReader();
			
			myReader->Read();
			int total = Math::Round((myReader->GetUInt64(0) / (1024)), 2);         //converting MB to GB
			int Free = Math::Round((myReader->GetUInt64(1) / (1024)), 2);
			int used = total - Free;

			this->DiskUsageChart->Series["DiskUsage"]->Points->AddXY("Used Space(GB)", used);   //adding to pie chart
			this->DiskUsageChart->Series["DiskUsage"]->Points->AddXY("Free Space(GB)",Free);

				
			myReader->Close();
		}
		catch (Exception^ e) 
		{

			MessageBox::Show("Failed ",
				"Exception Occured", MessageBoxButtons::OK);
		}
		finally
		{
			conDB->Close();   //closing the connection
		}


	}



	private:System::Void Initialize_DataGrid()          //Initialize datagrid to dispaly last n entries of selected client in table format
	{
		String^ connection = ConnectionString;
		MySqlConnection^ conDB = gcnew MySqlConnection(connection);

		try {

			conDB->Open();          //connecting to database
			String^ query = "Select * FROM(Select * FROM " + TableName + " Where MachineName is not NULL and MachineName= @Name order by id desc LIMIT @Entries)sub order by id ASC;";
			MySqlCommand^ cmdDatabase = gcnew MySqlCommand(query, conDB);
			cmdDatabase->Parameters->AddWithValue("@Name", ClientInfo->name);
			cmdDatabase->Parameters->AddWithValue("@Entries", ClientInfo->Entries);

			MySqlDataAdapter^ adapter = gcnew MySqlDataAdapter(cmdDatabase);   //adapter for table

			DataSet^ ds = gcnew DataSet();       
			adapter->Fill(ds, "ds");   
			dataGridView1->DataSource = ds;        //correctly pointing datagrid to table fetched from adapter
			dataGridView1->DataMember = "ds";


		}
		catch (Exception^ e) 
		{

			MessageBox::Show("Exception occured",
				"Exception", MessageBoxButtons::OK);
		}
		finally
		{
			conDB->Close();  //closing the connection
		}
	}
	

	private:System::Void Initialize_IdleWindowChart()     //initalizing idle window step line chart for selected client 
	{

		String^ connection = ConnectionString;
		MySqlConnection^ conDB = gcnew MySqlConnection(connection);

		try 
		{

			conDB->Open(); //connecting to database
			String^ query = "SELECT Date_and_Time,System_Idle_Window FROM(SELECT * FROM " + TableName + " where MachineName is not NULL and MachineName=@Name order by id DESC LIMIT @Entries)SUB ORDER by id ASC;";

			MySqlCommand^ cmdDatabase = gcnew MySqlCommand(query, conDB);
			cmdDatabase->Parameters->AddWithValue("@Name", ClientInfo->name);
			cmdDatabase->Parameters->AddWithValue("@Entries", ClientInfo->Entries);

			MySqlDataReader^ myReader = cmdDatabase->ExecuteReader();
			while (myReader->Read())
			{
				String^ time = myReader->GetString(ColDate_and_Time);  //xaxis is timestamp of data added
				int IdleTime = myReader->GetUInt64(1);               //0 base indexed where 1 means 2nd column which is of idle time in seconds
				

				this->IdleWindowChart->Series["Idle Time(sec)"]->Points->AddXY(time->Split(' ')[3], IdleTime); //xaxis is time stamp only time(no date) ,yaxis idle sec
				

				//System::Diagnostics::Debug::WriteLine(myReader[ColFreeRam]);
			}
			myReader->Close();
		}
		catch (Exception^ e) 
		{

			MessageBox::Show("Failed ",
				"Exception Occured", MessageBoxButtons::OK);
		}
		finally
		{
			conDB->Close();  //clsoing the connection
		}



	}


	private: System::Void ClientInfoForm_Load(System::Object^ sender, System::EventArgs^ e)  //this event occurs when client form first loads up  
	{													                                     //it initializes all the charts with selected clinet values					

		Initialize_CpuRamUsage_Chart();             //initializes cpu and ram usage line chart
		Initialize_RamChart();                     // initializes bar graph 
		Initialize_DiskPieChart();                 //initializes pie chart of disk space
		Initialize_DataGrid();                  // initializes table with selected number of last entries for selected cliet in dashboard
		Initialize_IdleWindowChart();              //initializes step line chart of idle window 

	}
};
}
