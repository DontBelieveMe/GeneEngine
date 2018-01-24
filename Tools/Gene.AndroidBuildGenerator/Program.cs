using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;
using System.IO;

namespace Gene.AndroidBuildGenerator
{
    class Program
    {
        static void Main(string[] args)
        {
            string buildFile = Environment.CurrentDirectory + "/agnes.json";
            JsonTextReader reader = new JsonTextReader(new StringReader(File.ReadAllText(buildFile)));
            Project project = new ProjectReader().ReadProject(reader);
            Console.WriteLine(project.Name);
            project.SourceFiles.ForEach(a => Console.WriteLine("Source File: " + a));
            project.Libraries.ForEach(a => Console.WriteLine("Library File: " + a));

            Console.ReadLine();
        }
    }
}
