using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NROIPChanger.Injector.Desktop
{
    internal interface IInjector
    {
        Process Process { get; }

        string GetScriptingBackend();
        bool Inject();
        bool SetIP(string hostname, ushort port, bool debugMode = false);
    }
}
