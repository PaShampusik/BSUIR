namespace Secure_app_lab_4_
{
    partial class Form1
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }


        private List<TextBox> loginFields = new();
        private List<TextBox> passwordsFields = new();
        private List<TextBox> messageFields = new();
        private List<Button> signInButtons = new();
        private List<Button> sendButtons = new();





        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        /// 
        private void InitializeComponent()
        {
            SignIn1 = new Button();
            Message1 = new TextBox();
            MessagesListBox = new ListBox();
            Message2 = new TextBox();
            SignIn2 = new Button();
            Message3 = new TextBox();
            SignIn3 = new Button();
            Login1 = new TextBox();
            Password1 = new TextBox();
            Login2 = new TextBox();
            Password2 = new TextBox();
            Login3 = new TextBox();
            Password3 = new TextBox();
            Send3 = new Button();
            Send2 = new Button();
            Send1 = new Button();
            AttackDefensesCheckedListBox = new CheckedListBox();
            SignOut3 = new Button();
            SignOut2 = new Button();
            SignOut1 = new Button();
            SuspendLayout();
            // 
            // SignIn1
            // 
            SignIn1.Location = new Point(135, 11);
            SignIn1.Name = "SignIn1";
            SignIn1.Size = new Size(82, 23);
            SignIn1.TabIndex = 2;
            SignIn1.Text = "Войти";
            SignIn1.UseVisualStyleBackColor = true;
            SignIn1.Click += SignIn_Click;
            // 
            // Message1
            // 
            Message1.Location = new Point(303, 26);
            Message1.Name = "Message1";
            Message1.Size = new Size(168, 23);
            Message1.TabIndex = 3;
            // 
            // MessagesListBox
            // 
            MessagesListBox.BackColor = SystemColors.Info;
            MessagesListBox.FormattingEnabled = true;
            MessagesListBox.ItemHeight = 15;
            MessagesListBox.Location = new Point(626, 26);
            MessagesListBox.Name = "MessagesListBox";
            MessagesListBox.Size = new Size(271, 139);
            MessagesListBox.TabIndex = 4;
            MessagesListBox.SelectedIndexChanged += MessagesListBox_SelectedIndexChanged;
            // 
            // Message2
            // 
            Message2.Location = new Point(303, 115);
            Message2.Name = "Message2";
            Message2.Size = new Size(168, 23);
            Message2.TabIndex = 8;
            // 
            // SignIn2
            // 
            SignIn2.Location = new Point(135, 100);
            SignIn2.Name = "SignIn2";
            SignIn2.Size = new Size(82, 23);
            SignIn2.TabIndex = 7;
            SignIn2.Text = "Войти";
            SignIn2.UseVisualStyleBackColor = true;
            SignIn2.Click += SignIn_Click;
            // 
            // Message3
            // 
            Message3.Location = new Point(303, 194);
            Message3.Name = "Message3";
            Message3.Size = new Size(168, 23);
            Message3.TabIndex = 12;
            // 
            // SignIn3
            // 
            SignIn3.Location = new Point(135, 179);
            SignIn3.Name = "SignIn3";
            SignIn3.Size = new Size(82, 23);
            SignIn3.TabIndex = 11;
            SignIn3.Text = "Войти";
            SignIn3.UseVisualStyleBackColor = true;
            SignIn3.Click += SignIn_Click;
            // 
            // Login1
            // 
            Login1.Location = new Point(17, 11);
            Login1.Name = "Login1";
            Login1.Size = new Size(100, 23);
            Login1.TabIndex = 0;
            // 
            // Password1
            // 
            Password1.Location = new Point(17, 40);
            Password1.Name = "Password1";
            Password1.Size = new Size(100, 23);
            Password1.TabIndex = 1;
            // 
            // Login2
            // 
            Login2.Location = new Point(17, 100);
            Login2.Name = "Login2";
            Login2.Size = new Size(100, 23);
            Login2.TabIndex = 5;
            // 
            // Password2
            // 
            Password2.Location = new Point(17, 129);
            Password2.Name = "Password2";
            Password2.Size = new Size(100, 23);
            Password2.TabIndex = 6;
            // 
            // Login3
            // 
            Login3.Location = new Point(17, 179);
            Login3.Name = "Login3";
            Login3.Size = new Size(100, 23);
            Login3.TabIndex = 9;
            // 
            // Password3
            // 
            Password3.Location = new Point(17, 208);
            Password3.Name = "Password3";
            Password3.Size = new Size(100, 23);
            Password3.TabIndex = 10;
            // 
            // Send3
            // 
            Send3.BackColor = Color.Pink;
            Send3.Location = new Point(487, 193);
            Send3.Name = "Send3";
            Send3.Size = new Size(82, 23);
            Send3.TabIndex = 27;
            Send3.Text = "Отправить";
            Send3.UseVisualStyleBackColor = false;
            Send3.Click += Send_Click;
            // 
            // Send2
            // 
            Send2.BackColor = Color.Pink;
            Send2.Location = new Point(487, 114);
            Send2.Name = "Send2";
            Send2.Size = new Size(82, 23);
            Send2.TabIndex = 26;
            Send2.Text = "Отправить";
            Send2.UseVisualStyleBackColor = false;
            Send2.Click += Send_Click;
            // 
            // Send1
            // 
            Send1.BackColor = Color.Pink;
            Send1.Location = new Point(487, 25);
            Send1.Name = "Send1";
            Send1.Size = new Size(82, 23);
            Send1.TabIndex = 25;
            Send1.Text = "Отправить";
            Send1.UseVisualStyleBackColor = false;
            Send1.Click += Send_Click;
            // 
            // AttackDefensesCheckedListBox
            // 
            AttackDefensesCheckedListBox.BackColor = SystemColors.MenuHighlight;
            AttackDefensesCheckedListBox.FormattingEnabled = true;
            AttackDefensesCheckedListBox.Items.AddRange(new object[] { "Минимизация привилегий", "Переполнение буфера", "DoS", "XSS" });
            AttackDefensesCheckedListBox.Location = new Point(626, 155);
            AttackDefensesCheckedListBox.Name = "AttackDefensesCheckedListBox";
            AttackDefensesCheckedListBox.Size = new Size(271, 76);
            AttackDefensesCheckedListBox.TabIndex = 31;
            AttackDefensesCheckedListBox.SelectedIndexChanged += AttackDefensesCheckedListBox_SelectedIndexChanged;
            // 
            // SignOut3
            // 
            SignOut3.Location = new Point(135, 208);
            SignOut3.Name = "SignOut3";
            SignOut3.Size = new Size(82, 23);
            SignOut3.TabIndex = 34;
            SignOut3.Text = "Выйти";
            SignOut3.UseVisualStyleBackColor = true;
            SignOut3.Click += SignOut_Click;
            // 
            // SignOut2
            // 
            SignOut2.Location = new Point(135, 129);
            SignOut2.Name = "SignOut2";
            SignOut2.Size = new Size(82, 23);
            SignOut2.TabIndex = 33;
            SignOut2.Text = "Выйти";
            SignOut2.UseVisualStyleBackColor = true;
            SignOut2.Click += SignOut_Click;
            // 
            // SignOut1
            // 
            SignOut1.Location = new Point(135, 40);
            SignOut1.Name = "SignOut1";
            SignOut1.Size = new Size(82, 23);
            SignOut1.TabIndex = 32;
            SignOut1.Text = "Выйти";
            SignOut1.UseVisualStyleBackColor = true;
            SignOut1.Click += SignOut_Click;
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            BackColor = Color.MediumOrchid;
            ClientSize = new Size(936, 270);
            Controls.Add(SignOut3);
            Controls.Add(SignOut2);
            Controls.Add(SignOut1);
            Controls.Add(AttackDefensesCheckedListBox);
            Controls.Add(Send3);
            Controls.Add(Send2);
            Controls.Add(Send1);
            Controls.Add(Message3);
            Controls.Add(SignIn3);
            Controls.Add(Password3);
            Controls.Add(Login3);
            Controls.Add(Message2);
            Controls.Add(SignIn2);
            Controls.Add(Password2);
            Controls.Add(Login2);
            Controls.Add(MessagesListBox);
            Controls.Add(Message1);
            Controls.Add(SignIn1);
            Controls.Add(Password1);
            Controls.Add(Login1);
            Name = "Form1";
            Text = "Form1";
            Load += Form1_Load;
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion
        private Button SignIn1;
        private TextBox Message1;
        private ListBox MessagesListBox;
        private TextBox Message2;
        private Button SignIn2;
        private TextBox Message3;
        private Button SignIn3;
        private TextBox Login1;
        private TextBox Password1;
        private TextBox Login2;
        private TextBox Password2;
        private TextBox Login3;
        private TextBox Password3;
        private Button Send3;
        private Button Send2;
        private Button Send1;
        private CheckedListBox AttackDefensesCheckedListBox;
        private Button SignOut3;
        private Button SignOut2;
        private Button SignOut1;
    }
}
