using System;
using System.Net.Sockets;
using System.Text.RegularExpressions;
using HarmonyLib;

namespace NROIPChanger.Mono.Desktop
{
    internal static class Hook
    {
        internal static void Install()
        {
            new Harmony("NROIPChanger.Mono.Desktop").PatchAll();
        }

        [HarmonyPatch(typeof(TcpClient), nameof(TcpClient.Connect), typeof(string), typeof(int))]
        internal class TcpConnectHook
        {
            static void Prefix(ref string hostname, ref int port)
            {
                if (!Main.forceLocalhost && (hostname == "127.0.0.1" || hostname.Equals("localhost", StringComparison.OrdinalIgnoreCase)))
                {
                    AccessTools.Method("UnityEngine.Debug:Log", new Type[] { typeof(object) })?.Invoke(null, new object[] { $"[NROIPChanger.Mono.Desktop] Localhost" });
                    Console.WriteLine($"[NROIPChanger.Mono.Desktop] Localhost");
                    return;
                }
                Regex regex = new Regex("((^10\\.)|(^172\\.(1[6-9]|2[0-9]|3[0-1])\\.)|(^192\\.168\\.))");
                if (regex.IsMatch(hostname) || string.IsNullOrEmpty(Main.ipAndPort))
                {
                    AccessTools.Method("UnityEngine.Debug:Log", new Type[] { typeof(object) })?.Invoke(null, new object[] { $"[NROIPChanger.Mono.Desktop] {hostname}:{port}" });
                    Console.WriteLine($"[NROIPChanger.Mono.Desktop] {hostname}:{port}");
                    return;
                }
                AccessTools.Method("UnityEngine.Debug:Log", new Type[] { typeof(object) })?.Invoke(null, new object[] { $"[NROIPChanger.Mono.Desktop] {hostname}:{port} => {Main.ipAndPort}" });
                Console.WriteLine($"[NROIPChanger.Mono.Desktop] {hostname}:{port} => {Main.ipAndPort}");
                string[] ipAndPort = Main.ipAndPort.Split(':');
                hostname = ipAndPort[0];
                port = ushort.Parse(ipAndPort[1]);
            }
        }
    }
}
