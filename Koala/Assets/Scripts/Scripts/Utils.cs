namespace Utils
{
    using System;
    [Serializable]
    public struct Vec2
    {
        public double x, y;
    }


    [Serializable]
    public struct GObject
    {
        public Vec2 Coord;
        public Vec2 Velocity;
        public Vec2 Acceleration;
        public Vec2 Force;
    };



    [Serializable]
    public struct State_model
    {
        public GObject body;
        public GObject wheel;
    }

    [Serializable]
    public struct Kwheel
    {
        public double mass;
        public double radius;
        public double position;
        public double rigidity_suspension;
    };
    [Serializable]
    public struct Kbody
    {
        public double mass;
    };
    [Serializable]
    public struct Kworld
    {
        public double gravity;
    };
    [Serializable]
    public struct Koef_of_model
    {
        public Kwheel wheel;
        public Kbody body;
        public Kworld world;
    }
    [Serializable]
    public struct Surface
    {
        public double start_x;
        public double start_y;
        public double left_height;
        public double right_height;
        public double angle;
        public double limitation_x;
        public double mu;
    };
}