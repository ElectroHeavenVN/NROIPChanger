using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

namespace NROIPChanger.Mono.Desktop
{
    internal static class NativeMethods
    {
        internal const uint GENERIC_READ = 0x80000000;
        internal const uint GENERIC_WRITE = 0x40000000;

        internal const int INVALID_HANDLE_VALUE = -1;

        internal const uint FILE_FLAG_OVERLAPPED = 0x40000000;
        internal const uint FILE_FLAG_NO_BUFFERING = 0x20000000;

        internal const uint OPEN_EXISTING = 3;
        internal const uint PIPE_ACCESS_OUTBOUND = 0x00000002;
        internal const uint PIPE_ACCESS_DUPLEX = 0x00000003;
        internal const uint PIPE_ACCESS_INBOUND = 0x00000001;
        internal const uint PIPE_WAIT = 0x00000000;
        internal const uint PIPE_NOWAIT = 0x00000001;
        internal const uint PIPE_READMODE_BYTE = 0x00000000;
        internal const uint PIPE_READMODE_MESSAGE = 0x00000002;
        internal const uint PIPE_TYPE_BYTE = 0x00000000;
        internal const uint PIPE_TYPE_MESSAGE = 0x00000004;
        internal const uint PIPE_CLIENT_END = 0x00000000;
        internal const uint PIPE_SERVER_END = 0x00000001;
        internal const uint PIPE_UNLIMITED_INSTANCES = 255;
        internal const uint NMPWAIT_WAIT_FOREVER = 0xffffffff;
        internal const uint NMPWAIT_NOWAIT = 0x00000001;
        internal const uint NMPWAIT_USE_DEFAULT_WAIT = 0x00000000;

        internal const ulong ERROR_PIPE_CONNECTED = 535;

        internal const int STD_OUTPUT_HANDLE = -11;

        internal enum ServerMode
        {
            InboundOnly = (int)PIPE_ACCESS_INBOUND,
            OutboundOnly = (int)PIPE_ACCESS_OUTBOUND,
            Bidirectional = (int)(PIPE_ACCESS_INBOUND + PIPE_ACCESS_OUTBOUND)
        };

        internal enum PeerType
        {
            Client = 0,
            Server = 1
        };

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

        [DllImport("kernel32.dll", SetLastError = true)]
        internal static extern bool AllocConsole();

        [DllImport("kernel32.dll")]
        internal static extern IntPtr GetStdHandle(int nStdHandle);
    }
}
