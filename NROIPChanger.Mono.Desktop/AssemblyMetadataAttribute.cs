using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace NROIPChanger.Mono.Desktop
{
    internal class AssemblyMetadataAttribute : Attribute
    {
        public AssemblyMetadataAttribute(string key, string value)
        {
            Key = key;
            Value = value;
        }
        public string Key { get; }
        public string Value { get; }
    }
}
