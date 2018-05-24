#pragma once
#include "DataManager.h"
#include "DotNetUtilities.h"


namespace Optimization {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// MyForm 的摘要
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			dataManager = new DataManager();
			//
			//TODO:  在此加入建構函式程式碼
			//
		}
	private: System::Windows::Forms::Label^  label1;
	public:
	private: System::Windows::Forms::ComboBox^  Algorithm;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::ComboBox^  FunctionList;

	private: System::Windows::Forms::FlowLayoutPanel^  flowLayoutPanel2;
	private: System::Windows::Forms::Label^  OutputText;
	private: System::Windows::Forms::TextBox^  Output;
	private: System::Windows::Forms::FlowLayoutPanel^  flowLayoutPanel3;
	private: System::Windows::Forms::Label^  label7;

	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::TextBox^  textBox3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::TextBox^  textBox4;
	private: System::Windows::Forms::FlowLayoutPanel^  flowLayoutPanel4;
	private: System::Windows::Forms::Label^  label6;

	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::TextBox^  textBox5;
	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::TextBox^  textBox6;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::FlowLayoutPanel^  flowLayoutPanel5;
	private: System::Windows::Forms::TextBox^  textBox7;
	private: System::Windows::Forms::TextBox^  textBox8;
	private: System::Windows::Forms::Button^  button3;



	protected:
		/// <summary>
		DataManager* dataManager;
		/// 清除任何使用中的資源。
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel1;
	protected:
	private: System::Windows::Forms::FlowLayoutPanel^  flowLayoutPanel1;
	private: System::Windows::Forms::Label^  InputText;
	private: System::Windows::Forms::TextBox^  Input;


	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  loadEquationsToolStripMenuItem;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;

	private:
		/// <summary>
		/// 設計工具所需的變數。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器修改
		/// 這個方法的內容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->flowLayoutPanel1 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->InputText = (gcnew System::Windows::Forms::Label());
			this->Input = (gcnew System::Windows::Forms::TextBox());
			this->flowLayoutPanel2 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->Algorithm = (gcnew System::Windows::Forms::ComboBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->FunctionList = (gcnew System::Windows::Forms::ComboBox());
			this->flowLayoutPanel3 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->textBox7 = (gcnew System::Windows::Forms::TextBox());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->flowLayoutPanel4 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->textBox8 = (gcnew System::Windows::Forms::TextBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->textBox5 = (gcnew System::Windows::Forms::TextBox());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->textBox6 = (gcnew System::Windows::Forms::TextBox());
			this->flowLayoutPanel5 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->OutputText = (gcnew System::Windows::Forms::Label());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->Output = (gcnew System::Windows::Forms::TextBox());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->loadEquationsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->tableLayoutPanel1->SuspendLayout();
			this->flowLayoutPanel1->SuspendLayout();
			this->flowLayoutPanel2->SuspendLayout();
			this->flowLayoutPanel3->SuspendLayout();
			this->flowLayoutPanel4->SuspendLayout();
			this->flowLayoutPanel5->SuspendLayout();
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->ColumnCount = 1;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel1->Controls->Add(this->flowLayoutPanel1, 0, 1);
			this->tableLayoutPanel1->Controls->Add(this->menuStrip1, 0, 0);
			this->tableLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel1->Location = System::Drawing::Point(0, 0);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 2;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 5)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 95)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(463, 654);
			this->tableLayoutPanel1->TabIndex = 0;
			// 
			// flowLayoutPanel1
			// 
			this->flowLayoutPanel1->Controls->Add(this->InputText);
			this->flowLayoutPanel1->Controls->Add(this->Input);
			this->flowLayoutPanel1->Controls->Add(this->flowLayoutPanel2);
			this->flowLayoutPanel1->Controls->Add(this->OutputText);
			this->flowLayoutPanel1->Controls->Add(this->button3);
			this->flowLayoutPanel1->Controls->Add(this->Output);
			this->flowLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->flowLayoutPanel1->Location = System::Drawing::Point(3, 35);
			this->flowLayoutPanel1->Name = L"flowLayoutPanel1";
			this->flowLayoutPanel1->Size = System::Drawing::Size(457, 616);
			this->flowLayoutPanel1->TabIndex = 0;
			// 
			// InputText
			// 
			this->InputText->AutoSize = true;
			this->InputText->Location = System::Drawing::Point(3, 0);
			this->InputText->Name = L"InputText";
			this->InputText->Size = System::Drawing::Size(30, 12);
			this->InputText->TabIndex = 0;
			this->InputText->Text = L"Input";
			// 
			// Input
			// 
			this->Input->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->Input->Location = System::Drawing::Point(3, 15);
			this->Input->Multiline = true;
			this->Input->Name = L"Input";
			this->Input->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->Input->Size = System::Drawing::Size(453, 81);
			this->Input->TabIndex = 1;
			// 
			// flowLayoutPanel2
			// 
			this->flowLayoutPanel2->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->flowLayoutPanel2->Controls->Add(this->label1);
			this->flowLayoutPanel2->Controls->Add(this->Algorithm);
			this->flowLayoutPanel2->Controls->Add(this->label2);
			this->flowLayoutPanel2->Controls->Add(this->FunctionList);
			this->flowLayoutPanel2->Controls->Add(this->flowLayoutPanel3);
			this->flowLayoutPanel2->Controls->Add(this->flowLayoutPanel4);
			this->flowLayoutPanel2->Controls->Add(this->flowLayoutPanel5);
			this->flowLayoutPanel2->Location = System::Drawing::Point(3, 102);
			this->flowLayoutPanel2->Name = L"flowLayoutPanel2";
			this->flowLayoutPanel2->Size = System::Drawing::Size(453, 95);
			this->flowLayoutPanel2->TabIndex = 6;
			// 
			// label1
			// 
			this->label1->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(3, 7);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(53, 12);
			this->label1->TabIndex = 5;
			this->label1->Text = L"Algorithm";
			// 
			// Algorithm
			// 
			this->Algorithm->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->Algorithm->FormattingEnabled = true;
			this->Algorithm->Items->AddRange(gcnew cli::array< System::Object^  >(5) {
				L"Powell’s Method", L"Steep Descent Method", L"Newton Method",
					L"Quasi-Newton Method", L"Conjugate Gradient Methods"
			});
			this->Algorithm->Location = System::Drawing::Point(62, 3);
			this->Algorithm->Name = L"Algorithm";
			this->Algorithm->Size = System::Drawing::Size(156, 20);
			this->Algorithm->TabIndex = 1;
			this->Algorithm->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::Algorithm_SelectedIndexChanged);
			// 
			// label2
			// 
			this->label2->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(224, 7);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(35, 12);
			this->label2->TabIndex = 5;
			this->label2->Text = L"Target";
			// 
			// FunctionList
			// 
			this->FunctionList->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->FunctionList->FormattingEnabled = true;
			this->FunctionList->Location = System::Drawing::Point(265, 3);
			this->FunctionList->Name = L"FunctionList";
			this->FunctionList->Size = System::Drawing::Size(180, 20);
			this->FunctionList->TabIndex = 1;
			this->FunctionList->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::FunctionList_SelectedIndexChanged);
			// 
			// flowLayoutPanel3
			// 
			this->flowLayoutPanel3->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->flowLayoutPanel3->Controls->Add(this->textBox7);
			this->flowLayoutPanel3->Controls->Add(this->label7);
			this->flowLayoutPanel3->Controls->Add(this->textBox1);
			this->flowLayoutPanel3->Controls->Add(this->label5);
			this->flowLayoutPanel3->Controls->Add(this->textBox3);
			this->flowLayoutPanel3->Controls->Add(this->label4);
			this->flowLayoutPanel3->Controls->Add(this->textBox4);
			this->flowLayoutPanel3->Enabled = false;
			this->flowLayoutPanel3->Location = System::Drawing::Point(3, 29);
			this->flowLayoutPanel3->Name = L"flowLayoutPanel3";
			this->flowLayoutPanel3->Size = System::Drawing::Size(150, 58);
			this->flowLayoutPanel3->TabIndex = 6;
			// 
			// textBox7
			// 
			this->textBox7->Location = System::Drawing::Point(3, 3);
			this->textBox7->Name = L"textBox7";
			this->textBox7->Size = System::Drawing::Size(30, 22);
			this->textBox7->TabIndex = 4;
			this->textBox7->Text = L"x";
			// 
			// label7
			// 
			this->label7->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(39, 8);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(59, 12);
			this->label7->TabIndex = 9;
			this->label7->Text = L"InitialPoint:";
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(104, 3);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(41, 22);
			this->textBox1->TabIndex = 4;
			// 
			// label5
			// 
			this->label5->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(3, 36);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(53, 12);
			this->label5->TabIndex = 2;
			this->label5->Text = L" Interval : ";
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(62, 31);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(26, 22);
			this->textBox3->TabIndex = 4;
			// 
			// label4
			// 
			this->label4->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(94, 36);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(11, 12);
			this->label4->TabIndex = 10;
			this->label4->Text = L"~";
			// 
			// textBox4
			// 
			this->textBox4->Location = System::Drawing::Point(111, 31);
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(34, 22);
			this->textBox4->TabIndex = 6;
			// 
			// flowLayoutPanel4
			// 
			this->flowLayoutPanel4->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->flowLayoutPanel4->Controls->Add(this->textBox8);
			this->flowLayoutPanel4->Controls->Add(this->label6);
			this->flowLayoutPanel4->Controls->Add(this->textBox2);
			this->flowLayoutPanel4->Controls->Add(this->label9);
			this->flowLayoutPanel4->Controls->Add(this->textBox5);
			this->flowLayoutPanel4->Controls->Add(this->label10);
			this->flowLayoutPanel4->Controls->Add(this->textBox6);
			this->flowLayoutPanel4->Enabled = false;
			this->flowLayoutPanel4->Location = System::Drawing::Point(159, 29);
			this->flowLayoutPanel4->Name = L"flowLayoutPanel4";
			this->flowLayoutPanel4->Size = System::Drawing::Size(143, 58);
			this->flowLayoutPanel4->TabIndex = 11;
			// 
			// textBox8
			// 
			this->textBox8->Location = System::Drawing::Point(3, 3);
			this->textBox8->Name = L"textBox8";
			this->textBox8->Size = System::Drawing::Size(28, 22);
			this->textBox8->TabIndex = 4;
			this->textBox8->Text = L"y";
			// 
			// label6
			// 
			this->label6->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(37, 8);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(65, 12);
			this->label6->TabIndex = 9;
			this->label6->Text = L"InitialPoint : ";
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(108, 3);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(28, 22);
			this->textBox2->TabIndex = 4;
			// 
			// label9
			// 
			this->label9->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(3, 36);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(50, 12);
			this->label9->TabIndex = 2;
			this->label9->Text = L"Interval : ";
			// 
			// textBox5
			// 
			this->textBox5->Location = System::Drawing::Point(59, 31);
			this->textBox5->Name = L"textBox5";
			this->textBox5->Size = System::Drawing::Size(26, 22);
			this->textBox5->TabIndex = 4;
			// 
			// label10
			// 
			this->label10->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(91, 36);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(11, 12);
			this->label10->TabIndex = 10;
			this->label10->Text = L"~";
			// 
			// textBox6
			// 
			this->textBox6->Location = System::Drawing::Point(108, 31);
			this->textBox6->Name = L"textBox6";
			this->textBox6->Size = System::Drawing::Size(28, 22);
			this->textBox6->TabIndex = 6;
			// 
			// flowLayoutPanel5
			// 
			this->flowLayoutPanel5->Anchor = System::Windows::Forms::AnchorStyles::Right;
			this->flowLayoutPanel5->Controls->Add(this->button1);
			this->flowLayoutPanel5->Controls->Add(this->button2);
			this->flowLayoutPanel5->Enabled = false;
			this->flowLayoutPanel5->Location = System::Drawing::Point(308, 29);
			this->flowLayoutPanel5->Name = L"flowLayoutPanel5";
			this->flowLayoutPanel5->Size = System::Drawing::Size(127, 58);
			this->flowLayoutPanel5->TabIndex = 14;
			// 
			// button1
			// 
			this->button1->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->button1->Location = System::Drawing::Point(3, 3);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(57, 55);
			this->button1->TabIndex = 12;
			this->button1->Text = L"CALC";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// button2
			// 
			this->button2->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			this->button2->Location = System::Drawing::Point(66, 4);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(53, 54);
			this->button2->TabIndex = 13;
			this->button2->Text = L"RESET";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// OutputText
			// 
			this->OutputText->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->OutputText->AutoSize = true;
			this->OutputText->Location = System::Drawing::Point(3, 206);
			this->OutputText->Name = L"OutputText";
			this->OutputText->Size = System::Drawing::Size(37, 12);
			this->OutputText->TabIndex = 7;
			this->OutputText->Text = L"Output";
			// 
			// button3
			// 
			this->button3->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->button3->Location = System::Drawing::Point(46, 203);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(66, 19);
			this->button3->TabIndex = 9;
			this->button3->Text = L"CLEAR";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			// 
			// Output
			// 
			this->Output->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->Output->Location = System::Drawing::Point(3, 228);
			this->Output->Multiline = true;
			this->Output->Name = L"Output";
			this->Output->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->Output->Size = System::Drawing::Size(453, 384);
			this->Output->TabIndex = 8;
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->fileToolStripMenuItem });
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(463, 24);
			this->menuStrip1->TabIndex = 1;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->loadEquationsToolStripMenuItem });
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(38, 20);
			this->fileToolStripMenuItem->Text = L"File";
			// 
			// loadEquationsToolStripMenuItem
			// 
			this->loadEquationsToolStripMenuItem->Name = L"loadEquationsToolStripMenuItem";
			this->loadEquationsToolStripMenuItem->Size = System::Drawing::Size(162, 22);
			this->loadEquationsToolStripMenuItem->Text = L"Load Equations";
			this->loadEquationsToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::loadEquationsToolStripMenuItem_Click);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			this->openFileDialog1->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &MyForm::openFileDialog1_FileOk);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(463, 654);
			this->Controls->Add(this->tableLayoutPanel1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"MyForm";
			this->Text = L"Optimization";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->tableLayoutPanel1->ResumeLayout(false);
			this->tableLayoutPanel1->PerformLayout();
			this->flowLayoutPanel1->ResumeLayout(false);
			this->flowLayoutPanel1->PerformLayout();
			this->flowLayoutPanel2->ResumeLayout(false);
			this->flowLayoutPanel2->PerformLayout();
			this->flowLayoutPanel3->ResumeLayout(false);
			this->flowLayoutPanel3->PerformLayout();
			this->flowLayoutPanel4->ResumeLayout(false);
			this->flowLayoutPanel4->PerformLayout();
			this->flowLayoutPanel5->ResumeLayout(false);
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) {

		/*Equation a("x^2+y^2");
		a.VariableChange.push_back(SubVariableintoEq("x", "x+0.5"));
		a.VariableChange.push_back(SubVariableintoEq("y", "0.5"));
		a.domainChange.push_back(SubVariableintoEq("x", "x-0.5"));
		a.domainChange.push_back(SubVariableintoEq("y", "inf*y-inf"));
		a.range.push_back(Range("x",0,1));
		a.range.push_back(Range("y", 0,1));

		std::cout << a.calc(std::vector<SubValueintoEq>{SubValueintoEq("x", 0.5), SubValueintoEq("y", 0.5)}) << std::endl;
		std::vector<SubValueintoEq> newPoints=a.goldenSection();*/

	}
	private: System::Void loadEquationsToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		openFileDialog1->ShowDialog();
	}
void Reset(){
	Algorithm->ResetText();
	FunctionList->ResetText();

	textBox1->Text = "";
	textBox2->Text = "";
	textBox3->Text = "";
	textBox4->Text = "";
	textBox5->Text = "";
	textBox6->Text = "";

	flowLayoutPanel3->Enabled = false;
	flowLayoutPanel4->Enabled = false;
	flowLayoutPanel5->Enabled = false;

	dataManager->VarInfo.clear();
	Output->ResetText();
			 
}
private: System::Void openFileDialog1_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
	Reset();
	dataManager->EquationIndex = 0;

	for (Equation* e : dataManager->Equations)
	{
		delete e;
	}

	dataManager->Equations.clear();
	//在Dialog按下OK便會進入此函式
	//字串轉制string^ to string
	std::string tempFileName;
	MarshalString(openFileDialog1->FileName, tempFileName);
	//將檔案路徑名稱傳入dataManager
	dataManager->SetFileName(tempFileName);
	Input->Clear();
	FunctionList->Items->Clear();
	//從讀取讀取向量資料
	if (dataManager->LoadEquationData())
	{
		std::vector<Equation*> equations =dataManager->Equations;
		Output->Multiline = true;
		for (unsigned int i = 0; i < equations.size(); i++)
		{
			String^ FunctionName=gcnew String((std::to_string(equations[i]->EquationIndex) + " : "+ equations[i]->EquationString).c_str());
			Input->Text += FunctionName;
			Input->Text += Environment::NewLine;
			FunctionList->Items->Add(FunctionName);
		}
	}	
}

private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {

 	Equation* Poly=(dataManager->Equations.at(dataManager->currentEq));
	dataManager->VarInfo.clear();
	Poly->range.clear();

	std::string tempString;
	double t1, t2, t3;

	if (Poly->degree() >= 1)
	{
		MarshalString(textBox7->Text, tempString);
		MarshalString(textBox1->Text, t1);
		MarshalString(textBox3->Text, t2);
		MarshalString(textBox4->Text, t3);

		Poly->range.push_back(Range(tempString,t2,t3));
		dataManager->VarInfo.push_back(SubValueintoEq(tempString, t1));
	}	
	if (Poly->degree() >= 2)
	{
		MarshalString(textBox8->Text, tempString);
		MarshalString(textBox2->Text, t1);
		MarshalString(textBox5->Text, t2);
		MarshalString(textBox6->Text, t3);

		Poly->range.push_back(Range(tempString, t2, t3));
		dataManager->VarInfo.push_back(SubValueintoEq(tempString, t1));
	}

	switch (Algorithm->SelectedIndex)
	{
	case 0:
		Output->Text+=gcnew String(Poly->Powell(dataManager->VarInfo).c_str());
		Output->Text += Environment::NewLine;
		break;
	case 1:
		Output->Text += gcnew String(Poly->SteepDescent(dataManager->VarInfo).c_str());
		Output->Text += Environment::NewLine;
		break;
	case 2:
	case 3:
	case 4:

	default:
		break;
	}


}
private: System::Void Algorithm_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
	dataManager->currentMethod=Algorithm->SelectedIndex;
}
private: System::Void FunctionList_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
	
		
	dataManager->currentEq = FunctionList->SelectedIndex;
	Equation* Poly = (dataManager->Equations.at(dataManager->currentEq));

	//show Equation Degree
	//Input->Text+=dataManager->GetEquations().at(dataManager->currentEq).degree();

	if (Poly->degree() >= 1)
		flowLayoutPanel3->Enabled = true;
	else
		flowLayoutPanel3->Enabled = false;

	if(Poly->degree()>=2)
		flowLayoutPanel4->Enabled = true;
	else
		flowLayoutPanel4->Enabled = false;

	flowLayoutPanel5->Enabled = true;
}

private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
	Reset();
}
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
	Output->Clear();
}
};
}
