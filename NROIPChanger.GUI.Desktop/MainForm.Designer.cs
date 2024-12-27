namespace NROIPChanger.GUI.Desktop
{
    partial class MainForm
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

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainForm));
            tbNewIP = new TextBox();
            lbNewIP = new Label();
            lbNewPort = new Label();
            nudNewPort = new NumericUpDown();
            cbProcess = new ComboBoxWithBorder();
            lbProcess = new Label();
            btnInject = new Button();
            tbGamePath = new TextBox();
            lbGamePath = new Label();
            btnBrowseGameFile = new Button();
            btnRun = new Button();
            btnRefresh = new Button();
            cbDebugMode = new CheckBox();
            ((System.ComponentModel.ISupportInitialize)nudNewPort).BeginInit();
            SuspendLayout();
            // 
            // tbNewIP
            // 
            tbNewIP.Anchor = AnchorStyles.Top | AnchorStyles.Left | AnchorStyles.Right;
            tbNewIP.BorderStyle = BorderStyle.FixedSingle;
            tbNewIP.Location = new Point(12, 48);
            tbNewIP.Name = "tbNewIP";
            tbNewIP.Size = new Size(308, 34);
            tbNewIP.TabIndex = 0;
            // 
            // lbNewIP
            // 
            lbNewIP.AutoSize = true;
            lbNewIP.Location = new Point(6, 9);
            lbNewIP.Name = "lbNewIP";
            lbNewIP.Size = new Size(296, 28);
            lbNewIP.TabIndex = 1;
            lbNewIP.Text = "Tên miền/địa chỉ IP máy chủ mới:";
            // 
            // lbNewPort
            // 
            lbNewPort.AutoSize = true;
            lbNewPort.Location = new Point(6, 90);
            lbNewPort.Name = "lbNewPort";
            lbNewPort.Size = new Size(102, 28);
            lbNewPort.TabIndex = 2;
            lbNewPort.Text = "Cổng mới:";
            // 
            // nudNewPort
            // 
            nudNewPort.Anchor = AnchorStyles.Top | AnchorStyles.Left | AnchorStyles.Right;
            nudNewPort.Location = new Point(12, 126);
            nudNewPort.Margin = new Padding(8);
            nudNewPort.Maximum = new decimal(new int[] { 65535, 0, 0, 0 });
            nudNewPort.Name = "nudNewPort";
            nudNewPort.Size = new Size(308, 34);
            nudNewPort.TabIndex = 3;
            // 
            // cbProcess
            // 
            cbProcess.Anchor = AnchorStyles.Top | AnchorStyles.Left | AnchorStyles.Right;
            cbProcess.DropDownStyle = ComboBoxStyle.DropDownList;
            cbProcess.FormattingEnabled = true;
            cbProcess.Location = new Point(12, 242);
            cbProcess.Name = "cbProcess";
            cbProcess.Size = new Size(190, 36);
            cbProcess.TabIndex = 4;
            cbProcess.SelectedIndexChanged += cbProcess_SelectedIndexChanged;
            // 
            // lbProcess
            // 
            lbProcess.AutoSize = true;
            lbProcess.Location = new Point(6, 205);
            lbProcess.Name = "lbProcess";
            lbProcess.Size = new Size(98, 28);
            lbProcess.TabIndex = 5;
            lbProcess.Text = "Tiến trình:";
            // 
            // btnInject
            // 
            btnInject.Anchor = AnchorStyles.Top | AnchorStyles.Right;
            btnInject.BackColor = Color.White;
            btnInject.Enabled = false;
            btnInject.FlatStyle = FlatStyle.Flat;
            btnInject.Font = new Font("Segoe UI", 10.2F, FontStyle.Regular, GraphicsUnit.Point, 163);
            btnInject.Location = new Point(236, 242);
            btnInject.Name = "btnInject";
            btnInject.Size = new Size(84, 36);
            btnInject.TabIndex = 6;
            btnInject.Text = "Inject";
            btnInject.UseVisualStyleBackColor = false;
            btnInject.Click += btnInject_Click;
            // 
            // tbGamePath
            // 
            tbGamePath.AllowDrop = true;
            tbGamePath.Anchor = AnchorStyles.Top | AnchorStyles.Left | AnchorStyles.Right;
            tbGamePath.BorderStyle = BorderStyle.FixedSingle;
            tbGamePath.Location = new Point(12, 321);
            tbGamePath.Name = "tbGamePath";
            tbGamePath.Size = new Size(192, 34);
            tbGamePath.TabIndex = 7;
            tbGamePath.TextChanged += tbGamePath_TextChanged;
            tbGamePath.DragDrop += tbGamePath_DragDrop;
            tbGamePath.DragEnter += tbGamePath_DragEnter;
            // 
            // lbGamePath
            // 
            lbGamePath.AutoSize = true;
            lbGamePath.Location = new Point(6, 284);
            lbGamePath.Name = "lbGamePath";
            lbGamePath.Size = new Size(169, 28);
            lbGamePath.TabIndex = 8;
            lbGamePath.Text = "Đường dẫn game:";
            // 
            // btnBrowseGameFile
            // 
            btnBrowseGameFile.Anchor = AnchorStyles.Top | AnchorStyles.Right;
            btnBrowseGameFile.BackColor = Color.White;
            btnBrowseGameFile.FlatStyle = FlatStyle.Flat;
            btnBrowseGameFile.Font = new Font("Segoe UI", 10.2F, FontStyle.Regular, GraphicsUnit.Point, 163);
            btnBrowseGameFile.Location = new Point(203, 321);
            btnBrowseGameFile.Name = "btnBrowseGameFile";
            btnBrowseGameFile.Size = new Size(34, 34);
            btnBrowseGameFile.TabIndex = 9;
            btnBrowseGameFile.Text = "...";
            btnBrowseGameFile.UseVisualStyleBackColor = false;
            btnBrowseGameFile.Click += btnBrowseGameFile_Click;
            // 
            // btnRun
            // 
            btnRun.Anchor = AnchorStyles.Top | AnchorStyles.Right;
            btnRun.BackColor = Color.White;
            btnRun.Enabled = false;
            btnRun.FlatStyle = FlatStyle.Flat;
            btnRun.Font = new Font("Segoe UI", 10.2F, FontStyle.Regular, GraphicsUnit.Point, 163);
            btnRun.Location = new Point(236, 321);
            btnRun.Name = "btnRun";
            btnRun.Size = new Size(84, 34);
            btnRun.TabIndex = 10;
            btnRun.Text = "Chạy";
            btnRun.UseVisualStyleBackColor = false;
            btnRun.Click += btnRun_Click;
            // 
            // btnRefresh
            // 
            btnRefresh.Anchor = AnchorStyles.Top | AnchorStyles.Right;
            btnRefresh.BackColor = Color.White;
            btnRefresh.FlatStyle = FlatStyle.Flat;
            btnRefresh.Font = new Font("Segoe UI", 10.2F, FontStyle.Regular, GraphicsUnit.Point, 163);
            btnRefresh.Location = new Point(201, 242);
            btnRefresh.Name = "btnRefresh";
            btnRefresh.Size = new Size(36, 36);
            btnRefresh.TabIndex = 11;
            btnRefresh.Text = "⟳";
            btnRefresh.UseVisualStyleBackColor = false;
            btnRefresh.Click += btnRefresh_Click;
            // 
            // cbDebugMode
            // 
            cbDebugMode.Anchor = AnchorStyles.Top | AnchorStyles.Left | AnchorStyles.Right;
            cbDebugMode.CheckAlign = ContentAlignment.MiddleRight;
            cbDebugMode.Location = new Point(6, 162);
            cbDebugMode.Name = "cbDebugMode";
            cbDebugMode.Size = new Size(314, 43);
            cbDebugMode.TabIndex = 12;
            cbDebugMode.Text = "Chế độ gỡ lỗi";
            cbDebugMode.UseVisualStyleBackColor = true;
            // 
            // MainForm
            // 
            AllowDrop = true;
            AutoScaleDimensions = new SizeF(11F, 28F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(332, 373);
            Controls.Add(cbDebugMode);
            Controls.Add(btnRefresh);
            Controls.Add(btnRun);
            Controls.Add(btnBrowseGameFile);
            Controls.Add(lbGamePath);
            Controls.Add(tbGamePath);
            Controls.Add(btnInject);
            Controls.Add(lbProcess);
            Controls.Add(cbProcess);
            Controls.Add(nudNewPort);
            Controls.Add(lbNewPort);
            Controls.Add(lbNewIP);
            Controls.Add(tbNewIP);
            Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 163);
            Icon = (Icon)resources.GetObject("$this.Icon");
            Margin = new Padding(4);
            MinimumSize = new Size(350, 420);
            Name = "MainForm";
            Text = "NROIPChanger Desktop";
            Load += MainForm_Load;
            ((System.ComponentModel.ISupportInitialize)nudNewPort).EndInit();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private TextBox tbNewIP;
        private Label lbNewIP;
        private Label lbNewPort;
        private NumericUpDown nudNewPort;
        private ComboBoxWithBorder cbProcess;
        private Label lbProcess;
        private Button btnInject;
        private TextBox tbGamePath;
        private Label lbGamePath;
        private Button btnBrowseGameFile;
        private Button btnRun;
        private Button btnRefresh;
        private CheckBox cbDebugMode;
    }
}
