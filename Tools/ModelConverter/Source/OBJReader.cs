using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Linq;
using ModelConverter.Source.Utils;

namespace ModelConverter.Source
{
    class OBJReader : IConverter
    {
        private string _filename;

        public OBJReader(string filename)
        {
            string extension = Path.GetExtension(filename);

            if(extension != "obj")
            {
                throw new ArgumentException("File specified is not a vaild OBJ model!");
            }

            _filename = filename;
        }

        public GeneModel ToGeneModel()
        {
            GeneModel model = new GeneModel();

            if (_filename == null) return null;

            string[] lines = File.ReadAllLines(_filename);
            
            foreach (string line in lines)
            {
                string id = line.Substring(0, 2);

                if(id == "v ")
                {
                    string[] data = line.Substring(2).Split(' ');
                    float x = Convert.ToSingle(data[0]);
                    float y = Convert.ToSingle(data[1]);
                    float z = Convert.ToSingle(data[2]);
                    model.Vertices.Add(new Vector3(x, y, z));
                }
                else if(id == "f ")
                {
                    string[] data = line.Substring(2).Split(' ');
                    int a = Convert.ToInt32(data[0]);
                    int b = Convert.ToInt32(data[1]);
                    int c = Convert.ToInt32(data[2]);
                    model.Indices.AddRange(new[] { a, b, c });
                }
            }

            model.Normals = Enumerable.Repeat(new Vector3(), model.Vertices.Count).ToList();

            for(int i = 0; i < model.Indices.Count; i += 3)
            {
                int ia = model.Indices[i];
                int ib = model.Indices[i + 1];
                int ic = model.Indices[i + 2];

                Vector3 q = model.Vertices[ib];
                Vector3 r = model.Vertices[ic];
                Vector3 p = model.Vertices[ia];

                Vector3 normal = Vector3.Cross(
                    q - p,
                    r - p
                );
                normal.Normalize();

                model.Normals[ia] = model.Normals[ib] = model.Normals[ic] = normal;
            }

            return model;
        }
    }
}
