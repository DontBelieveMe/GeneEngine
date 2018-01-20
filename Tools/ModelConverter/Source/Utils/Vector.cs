using System;
using System.Collections.Generic;
using System.Text;

namespace ModelConverter.Source.Utils
{
    class Vector3
    {
        public float X, Y, Z;

        public Vector3(float x, float y, float z)
        {
            X = x;
            Y = y;
            Z = z;
        }

        public Vector3()
        {
            X = 0;
            Y = 0;
            Z = 0;
        }

        public static Vector3 Cross(Vector3 a, Vector3 b)
        {
            float cx = (a.Y * b.Z) - (a.Z * b.Y);
            float cy = (a.Z * b.X) - (a.X * b.Z);
            float cz = (a.X * b.Y) - (a.Y * b.X);

            return new Vector3(cx, cy, cz);
        }

        public void Normalize()
        {
            float len = (float) Math.Sqrt((X * X) + (Y * Y) + (Z * Z));
            X /= len;
            Y /= len;
            Z /= len;
        }

        public static Vector3 operator-(Vector3 a, Vector3 b)
        {
            return new Vector3(a.X - b.X, a.Y - b.Y, a.Z - b.Z);
        }
    }

    class Vector2
    {
        public float X, Y;

        public Vector2(float x, float y)
        {
            X = x;
            Y = y;
        }

        public Vector2()
        {
            X = 0;
            Y = 0;
        }
    }
}
