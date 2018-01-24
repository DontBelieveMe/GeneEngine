using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Gene.AndroidBuildGenerator
{
    class NameConstants
    {
        public const string ProjectName = "projectName";
        public const string SourceFiles = "sourceFiles";
        public const string Libs = "libs";

    }

    class ProjectReader
    {
        public Project ReadProject(JsonReader reader)
        {
            Project project = new Project();

            while(reader.Read())
            {
                IfPropertyNameIs(reader, NameConstants.ProjectName, () => {
                    string projectName = reader.ReadAsString();
                    project.Name = projectName;
                });

                IfPropertyNameIs(reader, NameConstants.SourceFiles, () => {
                    project.SourceFiles = ReadStringArray(reader);
                });

                IfPropertyNameIs(reader, NameConstants.Libs, () => {
                    project.Libraries = ReadStringArray(reader);
                });
            }

            return project;
        }

        private List<string> ReadStringArray(JsonReader reader)
        {
            List<string> strings = new List<string>();
            while(reader.TokenType != JsonToken.EndArray)
            {
                reader.Read();
                if (reader.TokenType == JsonToken.String)
                {
                    strings.Add(reader.Value.ToString());
                }
            }
            return strings;
        }

        private void IfPropertyNameIs(JsonReader reader, string name, Action doThis)
        {
            if (reader.TokenType != JsonToken.PropertyName)
                return;

            if(reader.Value.ToString() == name)
            {
                doThis();
            }
        }
    }
}
