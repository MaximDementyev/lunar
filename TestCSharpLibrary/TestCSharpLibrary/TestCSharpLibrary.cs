using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

namespace TestCSharpLibrary
{
    public class TestCSharpLibrary
    {
        // From c++ Dll (unmanaged)
        [DllImport("TestCPPLibrary")]
        public static extern float TestMultiply(float a, float b);

        // From c++ Dll (unmanaged)
        [DllImport("TestCPPLibrary")]
        public static extern float TestDivide(float a, float b);

        [DllImport("TestCPPLibrary")]
        public static extern float TestSum(float a, float b);


        public static float SharpMultiply(float a, float b)
        {
            return (a * b);
        }

        public static float SharpDivide(float a, float b)
        {
            if (b == 0)
            {
                return 0;
            }

            return (a / b);
        }
        public static float SharpSum(float a, float b)
        {
            return (a + b);
        }
    }
}
