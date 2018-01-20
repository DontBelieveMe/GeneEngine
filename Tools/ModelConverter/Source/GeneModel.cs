using System;
using System.Collections.Generic;
using System.Text;
using ModelConverter.Source.Utils;

namespace ModelConverter.Source
{
    class GeneModel
    {
        public List<Vector3> Vertices = new List<Vector3>();
        public List<Vector3> Normals = new List<Vector3>();
        public List<Vector2> UVs = new List<Vector2>();
        public List<int> Indices = new List<int>();
    }
}
