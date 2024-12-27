using System.Diagnostics;

namespace NROIPChanger.GUI.Desktop
{
    public partial class MainForm : Form
    {
        class ProcessItem
        {
            internal Process Process { get; set; }
            internal string Name { get; set; }
            public override string ToString() => Name;

            internal ProcessItem(Process process)
            {
                Process = process;
                Name = $"{process.ProcessName} [{process.Id}]";
            }
        }

        bool refreshing = false;

        public MainForm()
        {
            InitializeComponent();
        }

        void MainForm_Load(object sender, EventArgs e)
        {
            RefreshProcessList();
        }

        void btnRefresh_Click(object sender, EventArgs e)
        {
            RefreshProcessList();
        }

        void tbGamePath_TextChanged(object sender, EventArgs e)
        {
            if (!File.Exists(tbGamePath.Text) || Path.GetExtension(tbGamePath.Text) != ".exe")
            {
                tbGamePath.BackColor = Color.FromArgb(255, 128, 128);
                btnRun.Enabled = false;
            }
            else
            {
                tbGamePath.BackColor = Color.White;
                btnRun.Enabled = true;
            }
        }

        void btnBrowseGameFile_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog
            {
                Filter = "Executable files (*.exe)|*.exe",
                Title = "Chọn tệp .exe của game",
                InitialDirectory = Environment.GetFolderPath(Environment.SpecialFolder.UserProfile)
            };
            if (File.Exists(tbGamePath.Text))
                openFileDialog.InitialDirectory = Path.GetDirectoryName(tbGamePath.Text);
            if (openFileDialog.ShowDialog() == DialogResult.OK)
                tbGamePath.Text = openFileDialog.FileName;
        }

        void cbProcess_SelectedIndexChanged(object sender, EventArgs e)
        {
            ProcessItem? processItem = (ProcessItem?)cbProcess.SelectedItem;
            if (processItem == null || processItem.Process.HasExited)
            {
                btnInject.Enabled = false;
                return;
            }
            btnInject.Enabled = true;
        }

        void btnRun_Click(object sender, EventArgs e)
        {
            GetBits(tbGamePath.Text, out bool is32, out bool is64);
            if (!is32 && !is64)
            {
                MessageBox.Show("Không thể xác định kiến trúc của tệp .exe này.", "Lỗi", MessageBoxButtons.OK, MessageBoxIcon.Error, MessageBoxDefaultButton.Button1, (MessageBoxOptions)0x00040000);
                return;
            }
            Process gameProcess = Process.Start(tbGamePath.Text);
            if (gameProcess == null || gameProcess.HasExited)
            {
                MessageBox.Show("Không thể khởi chạy game.", "Lỗi", MessageBoxButtons.OK, MessageBoxIcon.Error, MessageBoxDefaultButton.Button1, (MessageBoxOptions)0x00040000);
                return;
            }
            if (is32)
                Process.Start("Injector/NROIPChanger.Injector.Desktop.x86.exe", $"{gameProcess.Id} {tbNewIP.Text}:{nudNewPort.Value} {cbDebugMode.Checked}");
            else if (is64)
                Process.Start("Injector/NROIPChanger.Injector.Desktop.x64.exe", $"{gameProcess.Id} {tbNewIP.Text}:{nudNewPort.Value} {cbDebugMode.Checked}");
        }

        void btnInject_Click(object sender, EventArgs e)
        {
            ProcessItem? processItem = (ProcessItem?)cbProcess.SelectedItem;
            if (processItem == null || processItem.Process.HasExited)
            {
                MessageBox.Show("Tiến trình đã kết thúc.", "Lỗi", MessageBoxButtons.OK, MessageBoxIcon.Error, MessageBoxDefaultButton.Button1, (MessageBoxOptions)0x00040000);
                return;
            }
            GetBits(processItem.Process.MainModule?.FileName ?? "", out bool is32, out bool is64);
            if (!is32 && !is64)
            {
                MessageBox.Show("Không thể xác định kiến trúc của tệp .exe này.", "Lỗi", MessageBoxButtons.OK, MessageBoxIcon.Error, MessageBoxDefaultButton.Button1, (MessageBoxOptions)0x00040000);
                return;
            }
            if (is32)
                Process.Start("Injector\\NROIPChanger.Injector.Desktop.x86.exe", $"{processItem.Process.Id} {tbNewIP.Text}:{nudNewPort.Value} {cbDebugMode.Checked}");
            else if (is64)
                Process.Start("Injector\\NROIPChanger.Injector.Desktop.x64.exe", $"{processItem.Process.Id} {tbNewIP.Text}:{nudNewPort.Value} {cbDebugMode.Checked}");
        }

        void tbGamePath_DragEnter(object sender, DragEventArgs e)
        {
            e.Effect = e.Data?.GetDataPresent(DataFormats.FileDrop) ?? false ? DragDropEffects.All : DragDropEffects.None;
        }

        void tbGamePath_DragDrop(object sender, DragEventArgs e)
        {
            tbGamePath.Text = ((string[]?)e.Data?.GetData(DataFormats.FileDrop))?[0] ?? "";
        }

        void RefreshProcessList()
        {
            new Thread(() =>
            {
                if (refreshing)
                    return;
                refreshing = true;
                Invoke(() => cbProcess.Enabled = false);
                Invoke(() => btnRefresh.Enabled = false);
                Invoke(cbProcess.Items.Clear);
                List<ProcessItem> processes = [];
                foreach (Process process in Process.GetProcesses().Where(FilterUnityGameProcesses))
                    processes.Add(new ProcessItem(process));
                Invoke(() => cbProcess.Items.AddRange(processes.ToArray()));
                Invoke(() => cbProcess.Enabled = true);
                Invoke(() => btnRefresh.Enabled = true);
                refreshing = false;
            })
            { IsBackground = true }.Start();
        }

        void GetBits(string path, out bool is32, out bool is64)
        {
            is32 = false;
            is64 = false;
            byte[] exeData = File.ReadAllBytes(path);
            for (int i = 0; i < exeData.Length - 4; i++)
            {
                if (BitConverter.ToInt32(exeData, i) == 0x00004550)
                {
                    i += 0x18;
                    short magic = BitConverter.ToInt16(exeData, i);
                    if (magic == 0x010b)
                    {
                        is32 = true;
                        return;
                    }
                    if (magic == 0x020b)
                    {
                        is64 = true;
                        return;
                    }
                }
            }
        }

        bool FilterUnityGameProcesses(Process process)
        {
            try
            {
                foreach (ProcessModule module in process.Modules)
                {
                    if (module.ModuleName == "UnityPlayer.dll" || module.ModuleName == "GameAssembly.dll" || module.ModuleName.StartsWith("mono", StringComparison.InvariantCultureIgnoreCase))
                        return true;
                }
            }
            catch { }
            return false;
        }
    }
}
