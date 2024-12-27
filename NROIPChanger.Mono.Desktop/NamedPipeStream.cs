using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using static NROIPChanger.Mono.Desktop.NativeMethods;

namespace NROIPChanger.Mono.Desktop
{
    internal class NamedPipeStream : Stream
    {
        IntPtr _handle;
        FileAccess _mode;
        PeerType _peerType;

        protected NamedPipeStream()
        {
            _handle = IntPtr.Zero;
            _mode = 0;
            _peerType = PeerType.Server;
        }

        internal NamedPipeStream(string pipename, FileAccess mode)
        {
            _handle = IntPtr.Zero;
            _peerType = PeerType.Client;
            Open(pipename, mode);
        }
        internal NamedPipeStream(IntPtr handle, FileAccess mode)
        {
            _handle = handle;
            _mode = mode;
            _peerType = PeerType.Client;
        }

        internal void Open(string pipename, FileAccess mode)
        {
            if (!pipename.StartsWith(@"\\.\pipe\"))
                pipename = @"\\.\pipe\" + pipename;
            uint pipemode = 0;

            if ((mode & FileAccess.Read) > 0)
                pipemode |= GENERIC_READ;
            if ((mode & FileAccess.Write) > 0)
                pipemode |= GENERIC_WRITE;
            IntPtr handle = CreateFile(pipename, pipemode, 0, IntPtr.Zero, OPEN_EXISTING, 0, IntPtr.Zero);

            if (handle.ToInt32() == INVALID_HANDLE_VALUE)
            {
                int err = Marshal.GetLastWin32Error();
                throw new Win32Exception(err, string.Format("NamedPipeStream.Open failed, win32 error code {0}, pipename '{1}' ", err, pipename));
            }

            _mode = mode;
            _handle = handle;

        }

        internal static NamedPipeStream Create(string pipeName, ServerMode mode)
        {
            IntPtr handle = IntPtr.Zero;
            string name = @"\\.\pipe\" + pipeName;
            handle = CreateNamedPipe(name, (uint)mode, PIPE_TYPE_BYTE | PIPE_WAIT, PIPE_UNLIMITED_INSTANCES, 0, 1024, NMPWAIT_WAIT_FOREVER, IntPtr.Zero);
            if (handle.ToInt32() == INVALID_HANDLE_VALUE)
                throw new Win32Exception("Error creating named pipe " + name + " . Internal error: " + Marshal.GetLastWin32Error().ToString());
            NamedPipeStream self = new NamedPipeStream();
            self._handle = handle;
            switch (mode)
            {
                case ServerMode.InboundOnly:
                    self._mode = FileAccess.Read;
                    break;
                case ServerMode.OutboundOnly:
                    self._mode = FileAccess.Write;
                    break;
                case ServerMode.Bidirectional:
                    self._mode = FileAccess.ReadWrite;
                    break;
            }
            return self;
        }

        internal bool Listen()
        {
            if (_peerType != PeerType.Server)
                throw new Exception("Listen() is only for server-side streams");
            DisconnectNamedPipe(_handle);
            if (ConnectNamedPipe(_handle, IntPtr.Zero) != true)
            {
                uint lastErr = (uint)Marshal.GetLastWin32Error();
                if (lastErr == ERROR_PIPE_CONNECTED)
                    return true;
                return false;
            }
            return true;
        }

        internal void Disconnect()
        {
            if (_peerType != PeerType.Server)
                throw new Exception("Disconnect() is only for server-side streams");
            DisconnectNamedPipe(_handle);
        }

        internal bool IsConnected
        {
            get
            {
                if (_peerType != PeerType.Server)
                    throw new Exception("IsConnected() is only for server-side streams");

                if (ConnectNamedPipe(_handle, IntPtr.Zero) == false)
                {
                    if ((uint)Marshal.GetLastWin32Error() == ERROR_PIPE_CONNECTED)
                        return true;
                }
                return false;
            }
        }
        internal bool DataAvailable
        {
            get
            {
                uint bytesRead = 0, avail = 0, thismsg = 0;

                bool result = PeekNamedPipe(_handle,
                    null, 0, ref bytesRead, ref avail, ref thismsg);
                return result == true && avail > 0;
            }
        }

        public override bool CanRead
        {
            get { return (_mode & FileAccess.Read) > 0; }
        }

        public override bool CanWrite
        {
            get { return (_mode & FileAccess.Write) > 0; }
        }

        public override bool CanSeek
        {
            get { return false; }
        }

        public override long Length
        {
            get { throw new NotSupportedException("NamedPipeStream does not support seeking"); }
        }

        public override long Position
        {
            get { throw new NotSupportedException("NamedPipeStream does not support seeking"); }
            set { }
        }

        public override void Flush()
        {
            if (_handle == IntPtr.Zero)
                throw new ObjectDisposedException("NamedPipeStream", "The stream has already been closed");
            FlushFileBuffers(_handle);
        }

        public override int Read(byte[] buffer, int offset, int count)
        {
            if (buffer == null)
                throw new ArgumentNullException("buffer", "The buffer to read into cannot be null");
            if (buffer.Length < offset + count)
                throw new ArgumentException("Buffer is not large enough to hold requested data", "buffer");
            if (offset < 0)
                throw new ArgumentOutOfRangeException("offset", offset, "Offset cannot be negative");
            if (count < 0)
                throw new ArgumentOutOfRangeException("count", count, "Count cannot be negative");
            if (!CanRead)
                throw new NotSupportedException("The stream does not support reading");
            if (_handle == IntPtr.Zero)
                throw new ObjectDisposedException("NamedPipeStream", "The stream has already been closed");

            uint read = 0;

            byte[] buf = buffer;
            if (offset != 0)
            {
                buf = new byte[count];
            }
            bool f = ReadFile(_handle, buf, (uint)count, ref read, IntPtr.Zero);
            if (!f)
            {
                throw new Win32Exception(Marshal.GetLastWin32Error(), "ReadFile failed");
            }
            if (offset != 0)
            {
                for (int x = 0; x < read; x++)
                {
                    buffer[offset + x] = buf[x];
                }

            }
            return (int)read;
        }

        public override void Close()
        {
            CloseHandle(_handle);
            _handle = IntPtr.Zero;
        }

        public override void SetLength(long length)
        {
            throw new NotSupportedException("NamedPipeStream doesn't support SetLength");
        }

        public override void Write(byte[] buffer, int offset, int count)
        {
            if (buffer == null)
                throw new ArgumentNullException("buffer", "The buffer to write into cannot be null");
            if (buffer.Length < offset + count)
                throw new ArgumentException("Buffer does not contain amount of requested data", "buffer");
            if (offset < 0)
                throw new ArgumentOutOfRangeException("offset", offset, "Offset cannot be negative");
            if (count < 0)
                throw new ArgumentOutOfRangeException("count", count, "Count cannot be negative");
            if (!CanWrite)
                throw new NotSupportedException("The stream does not support writing");
            if (_handle == IntPtr.Zero)
                throw new ObjectDisposedException("NamedPipeStream", "The stream has already been closed");

            if (offset != 0)
            {
                byte[] buf = new byte[count];
                for (int x = 0; x < count; x++)
                {
                    buf[x] = buffer[offset + x];
                }
                buffer = buf;
            }
            uint written = 0;
            bool result = WriteFile(_handle, buffer, (uint)count, ref written, IntPtr.Zero);

            if (!result)
            {
                int err = Marshal.GetLastWin32Error();
                throw new Win32Exception(err, "Writing to the stream failed");
            }
            if (written < count)
                throw new IOException("Unable to write entire buffer to stream");
        }

        public override long Seek(long offset, SeekOrigin origin)
        {
            throw new NotSupportedException("NamedPipeStream doesn't support seeking");
        }
    }

}
