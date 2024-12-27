using System;
using System.Diagnostics;
using System.Threading;

namespace NROIPChanger.Injector.Desktop
{
    internal class Program
    {
        static int Main(string[] args)
        {
            if (args.Length != 2 && args.Length != 3)
            {
                Console.WriteLine("Usage: NROIPChanger.Injector.Desktop.exe <pid> <hostname:port> [debug]");
                return 1;
            }
            int processID = int.Parse(args[0]);
            string hostname = args[1];
            ushort port = ushort.Parse(hostname.Split(':')[1]);
            bool debugMode = false;
            if (args.Length == 3)
                debugMode = bool.Parse(args[2]);
            hostname = hostname.Split(':')[0];

            Process process = Process.GetProcessById(processID);
            if (process == null)
            {
                Console.WriteLine("Process not found.");
                return 1;
            }
            try
            {
                while (process.MainWindowHandle == IntPtr.Zero)
                    Thread.Sleep(100);
                IInjector injector = Utils.CreateInjector(process);
                Console.WriteLine($"Scripting backend type: {injector.GetScriptingBackend()}");
                injector.Inject();
                injector.SetIP(hostname, port, debugMode);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
                if (!(ex is NotSupportedException))
                    Console.WriteLine(ex.StackTrace);
                Console.ReadLine();
                return 1;
            }
            Console.WriteLine("Success.");
            return 0;
        }
    }
}
