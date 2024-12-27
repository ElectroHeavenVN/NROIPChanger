using System.Runtime.InteropServices;

namespace NROIPChanger.GUI.Desktop
{
    internal class NativeMethods
    {
        [DllImport("user32.dll")]
        internal static extern bool SetForegroundWindow(IntPtr hWnd);

        [DllImport("user32.dll")]
        internal static extern bool ShowWindowAsync(IntPtr hWnd, int nCmdShow);
    }
}
