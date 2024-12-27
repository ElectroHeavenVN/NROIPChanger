using System.Diagnostics;
using System.Reflection;

namespace NROIPChanger.GUI.Desktop
{
    internal static class Program
    {
        static Mutex mutex = new Mutex(true, "<NROIPChanger.GUI.Desktop>{0c2a83ce-7edb-4299-a742-7850fe63902a}");

        /// <summary>
        ///  The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            if (!mutex.WaitOne(TimeSpan.Zero, true))
            {
                Process? otherInstance = Process.GetProcessesByName(Assembly.GetEntryAssembly().GetName().Name).FirstOrDefault((Process p) => p.MainWindowHandle != IntPtr.Zero);
                if (otherInstance != null)
                {
                    NativeMethods.ShowWindowAsync(otherInstance.MainWindowHandle, 9);
                    NativeMethods.SetForegroundWindow(otherInstance.MainWindowHandle);
                }
                return;
            }
            if (Environment.CurrentDirectory.Contains("AppData\\Local\\Temp"))
            {
                MessageBox.Show("Please extract the file before running!\r\nVui lòng giải nén file trước!", "NROIPChanger.GUI.Desktop", MessageBoxButtons.OK, MessageBoxIcon.Hand, MessageBoxDefaultButton.Button1, (MessageBoxOptions)0x00040000);
                mutex.ReleaseMutex();
                return;
            }
            // To customize application configuration such as set high DPI settings or default font,
            // see https://aka.ms/applicationconfiguration.
            ApplicationConfiguration.Initialize();
            Application.Run(new MainForm());
        }
    }
}