using System;
using System.Runtime.InteropServices;

namespace NROIPChanger.Injector.Desktop
{
    internal class NativeMethods
    {
        internal const int PROCESS_CREATE_THREAD = 0x0002;
        internal const int PROCESS_QUERY_INFORMATION = 0x0400;
        internal const int PROCESS_VM_OPERATION = 0x0008;
        internal const int PROCESS_VM_WRITE = 0x0020;
        internal const int PROCESS_VM_READ = 0x0010;

        internal const uint MEM_COMMIT = 0x1000;
        internal const uint MEM_RESERVE = 0x2000;
        internal const uint MEM_DECOMMIT = 0x4000;
        internal const uint MEM_RELEASE = 0x8000;

        internal const uint PAGE_NOACCESS = 0x1;
        internal const uint PAGE_READONLY = 0x2;
        internal const uint PAGE_READWRITE = 0x4;
        internal const uint PAGE_WRITECOPY = 0x8;
        internal const uint PAGE_EXECUTE = 0x10;
        internal const uint PAGE_EXECUTE_READ = 0x20;
        internal const uint PAGE_EXECUTE_READWRITE = 0x40;
        internal const uint PAGE_EXECUTE_WRITECOPY = 0x80;
        internal const uint PAGE_GUARD = 0x100;
        internal const uint PAGE_NOCACHE = 0x200;
        internal const uint PAGE_WRITECOMBINE = 0x400;

        internal const uint GENERIC_READ = 0x80000000;
        internal const uint GENERIC_WRITE = 0x40000000;

        internal const int INVALID_HANDLE_VALUE = -1;

        internal const uint FILE_FLAG_OVERLAPPED = 0x40000000;
        internal const uint FILE_FLAG_NO_BUFFERING = 0x20000000;

        [StructLayout(LayoutKind.Sequential)]
        internal struct CLIENT_ID
        {
            internal IntPtr UniqueProcess;
            internal IntPtr UniqueThread;
        }

        [StructLayout(LayoutKind.Sequential, Pack = 0)]
        internal struct OBJECT_ATTRIBUTES
        {
            internal int Length;
            internal IntPtr RootDirectory;
            internal IntPtr ObjectName;
            internal uint Attributes;
            internal IntPtr SecurityDescriptor;
            internal IntPtr SecurityQualityOfService;
        }

        internal struct IMAGE_DOS_HEADER
        {
            internal short e_magic;
            internal short e_cblp;
            internal short e_cp;
            internal short e_crlc;
            internal short e_cparhdr;
            internal short e_minalloc;
            internal short e_maxalloc;
            internal short e_ss;
            internal short e_sp;
            internal short e_csum;
            internal short e_ip;
            internal short e_cs;
            internal short e_lfarlc;
            internal short e_ovno;
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 4)]
            internal short[] e_res;  // 4
            internal short e_oemid;
            internal short e_oeminfo;
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 10)]
            internal short[] e_res2; // 10
            internal long e_lfanew;
        }

        internal struct IMAGE_FILE_HEADER
        {
            internal short Machine;
            internal short NumberOfSections;
            internal int TimeDateStamp;
            internal int PointerToSymbolTable;
            internal int NumberOfSymbols;
            internal short SizeOfOptionalHeader;
            internal short Characteristics;
        }

        [DllImport("kernel32.dll")]
        internal static extern IntPtr OpenProcess(int dwDesiredAccess, bool bInheritHandle, int dwProcessId);

        [DllImport("kernel32.dll", CharSet = CharSet.Auto)]
        internal static extern IntPtr GetModuleHandle(string lpModuleName);

        [DllImport("kernel32", CharSet = CharSet.Ansi, ExactSpelling = true, SetLastError = true)]
        internal static extern IntPtr GetProcAddress(IntPtr hModule, string procName);

        [DllImport("kernel32.dll", SetLastError = true, ExactSpelling = true)]
        internal static extern IntPtr VirtualAllocEx(IntPtr hProcess, IntPtr lpAddress, uint dwSize, uint flAllocationType, uint flProtect);

        [DllImport("kernel32.dll", SetLastError = true)]
        internal static extern bool WriteProcessMemory(IntPtr hProcess, IntPtr lpBaseAddress, byte[] lpBuffer, uint nSize, out UIntPtr lpNumberOfBytesWritten);

        [DllImport("kernel32.dll")]
        internal static extern IntPtr CreateRemoteThread(IntPtr hProcess, IntPtr lpThreadAttributes, uint dwStackSize, IntPtr lpStartAddress, IntPtr lpParameter, uint dwCreationFlags, IntPtr lpThreadId);

        [DllImport("kernel32.dll", SetLastError = true)]
        internal static extern uint WaitForSingleObject(IntPtr hObject, int dwTimeout);

        [DllImport("kernel32.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        internal static extern bool GetExitCodeThread(IntPtr hThread, out uint lpExitCode);

        [DllImport("kernel32.dll", EntryPoint = "CreateFile", SetLastError = true)]
        internal static extern IntPtr CreateFile(string lpFileName, uint dwDesiredAccess, uint dwShareMode, IntPtr lpSecurityAttributes, uint dwCreationDisposition, uint dwFlagsAndAttributes, IntPtr hTemplateFile);

        [DllImport("kernel32.dll", SetLastError = true)]
        internal static extern IntPtr CreateNamedPipe(string lpName, uint dwOpenMode, uint dwPipeMode, uint nMaxInstances, uint nOutBufferSize, uint nInBufferSize, uint nDefaultTimeOut, IntPtr pipeSecurityDescriptor);
        
        [DllImport("kernel32.dll", SetLastError = true)]
        internal static extern bool DisconnectNamedPipe(IntPtr hHandle);
        
        [DllImport("kernel32.dll", SetLastError = true)]
        internal static extern bool ConnectNamedPipe(IntPtr hHandle, IntPtr lpOverlapped);
        
        [DllImport("kernel32.dll", EntryPoint = "PeekNamedPipe", SetLastError = true)]
        internal static extern bool PeekNamedPipe(IntPtr handle, byte[] buffer, uint nBufferSize, ref uint bytesRead, ref uint bytesAvail, ref uint BytesLeftThisMessage);
        
        [DllImport("kernel32.dll", SetLastError = true)]
        internal static extern bool ReadFile(IntPtr handle, byte[] buffer, uint toRead, ref uint read, IntPtr lpOverLapped);
        
        [DllImport("kernel32.dll", SetLastError = true)]
        internal static extern bool WriteFile(IntPtr handle, byte[] buffer, uint count, ref uint written, IntPtr lpOverlapped);
        
        [DllImport("kernel32.dll", SetLastError = true)]
        internal static extern bool CloseHandle(IntPtr handle);
        
        [DllImport("kernel32.dll", SetLastError = true)]
        internal static extern bool FlushFileBuffers(IntPtr handle);

        [DllImport("ntdll.dll")]
        internal static extern uint NtOpenProcess(ref IntPtr ProcessHandle, uint DesiredAccess, ref OBJECT_ATTRIBUTES ObjectAttributes, ref CLIENT_ID processId);

        [DllImport("ntdll.dll")]
        internal static extern bool NtReadVirtualMemory(IntPtr hProcess, IntPtr lpBaseAddress, [Out] byte[] lpBuffer, int dwSize, out IntPtr lpNumberOfBytesRead);

        [DllImport("ntdll.dll", SetLastError = true)]
        internal static extern uint NtQueryInformationProcess(IntPtr processHandle, int processInformationClass, IntPtr pbi, uint processInformationLength, out uint returnLength);
    }
}
