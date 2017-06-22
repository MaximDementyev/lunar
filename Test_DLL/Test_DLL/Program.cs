using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.IO;
using System;



namespace Test_DLL
{
    class Program
    {
        public struct Vector2
        {
            public double x;
            public double y;
        };

        public struct state_model
        {
            public Vector2 Coord;
            public Vector2 Velocity;
        };

        public struct koef_of_model
        {
            public double mass;
            public double gravity;
            public double radius;
        };

        public struct surface
        {
            public double start_x;
            public double srart_y;
            public double angle;
            public double limitation_x;
            public double mu;
        };

        [DllImport("TestCPPLibrary", CallingConvention = CallingConvention.Cdecl, EntryPoint = "solve_step")]
        public static unsafe extern int solve_step(state_model* current_model, koef_of_model* koef_model, surface* current_surface, double* step_time, double* force);

        static void Main(string[] args)
        {
            surface current_surface;
            state_model current_model;
            koef_of_model koef_model;

            koef_model.gravity = 10;
            koef_model.mass = 1;
            koef_model.radius = 0;

            current_model.Coord.x = 0;
            current_model.Coord.y = 1;
            current_model.Velocity.x = 0.05;
            current_model.Velocity.y = 0;

            current_surface.limitation_x = 1;
            current_surface.angle = 0;
            current_surface.mu = 1;
            current_surface.start_x = 0;
            current_surface.srart_y = 0;

            double force = 0;
            double step_time = 10; ;
            unsafe
            {
                int a = solve_step(&current_model, &koef_model, &current_surface, &step_time, &force);
            }
            force += 1;
        }

    }
}
