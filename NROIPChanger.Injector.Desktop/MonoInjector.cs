using System;
using System.Diagnostics;
using System.IO;
using System.IO.Pipes;

namespace NROIPChanger.Injector.Desktop
{
    internal class MonoInjector : IInjector
    {
        internal MonoInjector(Process process)
        {
            _process = process;
        }

        Process _process;
        public Process Process => _process;

        public string GetScriptingBackend() => "Mono";

        public bool Inject()
        {
            if (_process == null)
                return false;
            SharpMonoInjector.Injector injector = new SharpMonoInjector.Injector(_process.Id);
            byte[] assembly = File.ReadAllBytes(Path.Combine(Path.GetDirectoryName(Path.GetDirectoryName(typeof(Program).Assembly.Location)), "Lib", "NROIPChanger.Mono.Desktop.dll"));
            byte[] harmonyLib = File.ReadAllBytes(Path.Combine(Path.GetDirectoryName(Path.GetDirectoryName(typeof(Program).Assembly.Location)), "Lib", "0Harmony.dll"));
            injector.Inject(harmonyLib);
            IntPtr monoAssembly = injector.Inject(assembly, "NROIPChanger.Mono.Desktop", "Main", "Initialize");
            return monoAssembly != IntPtr.Zero;
        }

        public bool SetIP(string hostname, ushort port, bool debugMode = false, bool forceLocalhost = false)
        {
            if (_process == null)
                return false;
            NamedPipeServerStream pipe = new NamedPipeServerStream($"NROIPChanger.Mono.Desktop+{_process.Id}", PipeDirection.Out, 1, PipeTransmissionMode.Byte, PipeOptions.WriteThrough);
            pipe.WaitForConnection();
            StreamWriter writer = new StreamWriter(pipe);
            writer.WriteLine($"{hostname}:{port}");
            writer.WriteLine(debugMode);
            writer.WriteLine(forceLocalhost);
            writer.Flush();
            writer.Close();
            pipe.Close();
            return true;
        }
    }
}
