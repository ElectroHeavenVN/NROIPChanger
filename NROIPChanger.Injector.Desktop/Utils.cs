using System;
using System.Diagnostics;
using System.IO;

namespace NROIPChanger.Injector.Desktop
{
    internal static class Utils
    {
        internal static string GetBits(string path)
        {
            byte[] exeData = File.ReadAllBytes(path);
            for (int i = 0; i < exeData.Length - 4; i++)
            {
                if (BitConverter.ToInt32(exeData, i) == 0x00004550)
                {
                    i += 0x18;
                    short magic = BitConverter.ToInt16(exeData, i);
                    if (magic == 0x010b)
                        return "x86";
                    if (magic == 0x020b)
                        return "x64";
                }
            }
            return "";
        }

        internal static IInjector CreateInjector(Process process)
        {
            foreach (ProcessModule module in process.Modules)
            {
                if (module.ModuleName == "GameAssembly.dll")
                {
                    return new IL2CPPInjector(process);
                }
                if (module.ModuleName.StartsWith("mono", StringComparison.InvariantCultureIgnoreCase))
                {
                    return new MonoInjector(process);
                }
            }
            throw new NotSupportedException("The process is not an Unity game.");
        }
    }
}
