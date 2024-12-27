using System;
using System.Diagnostics;
using System.IO;
using System.Text;
using System.Threading;
using HarmonyLib;
using static NROIPChanger.Mono.Desktop.NativeMethods;

namespace NROIPChanger.Mono.Desktop
{
    internal class Main
    {
        internal static string ipAndPort;
        internal static bool debugMode;

        internal static void Initialize()
        {
            try
            {
                Hook.Install();
                new Thread(ReceiveIP) { IsBackground = true }.Start();
            }
            catch (Exception ex)
            {
                try
                {
                    AccessTools.Method("UnityEngine.Debug:Log", new Type[] { typeof(object) })?.Invoke(null, new object[] { "[NROIPChanger.Mono.Desktop] " + ex });
                }
                catch { }
            }
        }

        static void ReceiveIP()
        {
            Thread.Sleep(1000);
            NamedPipeStream pipe = new NamedPipeStream($"NROIPChanger.Mono.Desktop+{Process.GetCurrentProcess().Id}", FileAccess.Read);
            StreamReader reader = new StreamReader(pipe);
            while (!pipe.DataAvailable)
                Thread.Sleep(100);
            ipAndPort = reader.ReadLine();
            debugMode = bool.Parse(reader.ReadLine());
            if (debugMode)
                OpenConsole();
            reader.Close();
            pipe.Close();
        }

#pragma warning disable CS0618 // Type or member is obsolete
        static void OpenConsole()
        {
            AllocConsole();
            IntPtr stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
            FileStream fileStream = new FileStream(stdHandle, FileAccess.Write);
            Console.SetOut(new StreamWriter(fileStream, Encoding.UTF8) { AutoFlush = true });
            Console.WriteLine();
            Console.WriteLine("Debug mode enabled! Log messages will be displayed here.");
            Console.WriteLine("Don't close this window, it will close the game.");
        }
#pragma warning restore CS0618 // Type or member is obsolete
    }
}
