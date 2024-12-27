using System;
using System.Diagnostics;
using System.IO;
using System.IO.Pipes;
using System.Runtime.InteropServices;
using System.Text;
using static NROIPChanger.Injector.Desktop.NativeMethods;

namespace NROIPChanger.Injector.Desktop
{
    internal class IL2CPPInjector : IInjector
    {
        internal IL2CPPInjector(Process process)
        {
            _process = process;
        }

        Process _process;
        public Process Process => _process;

        public string GetScriptingBackend() => "IL2CPP";

        public bool Inject()
        {
            if (_process == null)
                return false;
            string dllPath = Path.Combine(Path.GetDirectoryName(Path.GetDirectoryName(typeof(Program).Assembly.Location)), "Lib", $"NROIPChanger.IL2CPP.Desktop.{Utils.GetBits(_process.MainModule.FileName)}.dll");
            return LoadLibrary(_process, dllPath);
        }

        public bool SetIP(string hostname, ushort port, bool debugMode = false)
        {
            if (_process == null)
                return false;
            NamedPipeServerStream pipe = new NamedPipeServerStream($"NROIPChanger.IL2CPP.Desktop+{_process.Id}", PipeDirection.Out, 1, PipeTransmissionMode.Byte, PipeOptions.WriteThrough);
            pipe.WaitForConnection();
            string ip = $"{hostname}:{port}";
            pipe.Write(BitConverter.GetBytes(ip.Length), 0, sizeof(int));
            pipe.Write(Encoding.Unicode.GetBytes(ip), 0, ip.Length * sizeof(char));
            pipe.Write(BitConverter.GetBytes(debugMode), 0, sizeof(bool));
            pipe.Flush();
            pipe.Close();
            return true;
        }

        internal static bool LoadLibrary(Process targetProcess, string dllFullPath)
        {
            dllFullPath = Path.GetFullPath(dllFullPath);
            IntPtr procHandle = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ, false, targetProcess.Id);
            IntPtr loadLibraryAddress = GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryA");
            IntPtr allocMemAddress = VirtualAllocEx(procHandle, IntPtr.Zero, (uint)((dllFullPath.Length + 1) * Marshal.SizeOf(typeof(char))), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
            WriteProcessMemory(procHandle, allocMemAddress, Encoding.Default.GetBytes(dllFullPath), (uint)((dllFullPath.Length + 1) * Marshal.SizeOf(typeof(char))), out _);
            uint exitCode = RunThread(procHandle, loadLibraryAddress, allocMemAddress);
            return exitCode != 0 && exitCode != uint.MaxValue;
        }

        static uint RunThread(IntPtr hProcess, IntPtr lpStartAddress, IntPtr lpParam, int timeout = 1000)
        {
            uint maxValue = uint.MaxValue;
            IntPtr intPtr = CreateRemoteThread(hProcess, IntPtr.Zero, 0, lpStartAddress, lpParam, 0, IntPtr.Zero);
            if (intPtr != IntPtr.Zero && WaitForSingleObject(intPtr, timeout) == 0UL)
                GetExitCodeThread(intPtr, out maxValue);
            return maxValue;
        }
    }
}
