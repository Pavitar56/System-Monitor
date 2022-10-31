

#include"LoginForm.h"
#include"Dashboard.h"

using namespace System;
using namespace System::Windows::Forms;

void main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	SystemMonitor::LoginForm loginForm;              //creates object of loginform

	loginForm.ShowDialog();                                         //opens login page
	User^ user = loginForm.user;
	//String^ client = user->name;
	
	if (user != nullptr && user ->name == "Pavitar" && user->password=="1234")
	{
		SystemMonitor::Dashboard mainForm;       
		Application::Run(% mainForm);             //if email pass is correct then open the dashboard
	
	}
	else {
		MessageBox::Show("Authentication Canceled",
			"Program.cpp", MessageBoxButtons::OK);
	}

}