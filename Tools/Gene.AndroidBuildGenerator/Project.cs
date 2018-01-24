using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Gene.AndroidBuildGenerator
{
    class Project
    {
        public string Name;
        public List<string> SourceFiles;
        public List<string> Libraries;

        public Project()
        {
            Name = string.Empty;
            SourceFiles = new List<string>();
            Libraries = new List<string>();
        }
    }
}
