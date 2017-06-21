using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Runtime.InteropServices;
using System.IO;

public class BlockMove : MonoBehaviour {
	new private Rigidbody2D rigidbody;
	private Animator animator;
	private SpriteRenderer sprite;
	public struct double_Vector2{
		public double x;
		public double y;
	}
	public struct state_model{
		public double_Vector2 Coord;
		public double_Vector2 Velocity;
	}
	public struct koef_of_model{
		public double mass;
		public double gravity;
		public double radius;
	}

	[DllImport("TestCPPLibrary", EntryPoint="initialization_koef_model")]
	public static extern koef_of_model initialization_koef_of_model();

	[DllImport("TestCPPLibrary", EntryPoint="TestSum")]
	public static extern float TestSum_for_dll(float a, float b);
	[DllImport("TestCPPLibrary", EntryPoint="TestStruct")]
	public static extern state_model Test_struct();

	[DllImport("TestCPPLibrary", EntryPoint="TestUpdateStruct")]
	public static unsafe extern void TestUpdateStruct(state_model* ptr);

	public state_model test;

	private void Start ()
	{
		Vector3 position = this.transform.position;
		position.y = TestSum_for_dll(position.y, 5);
		this.transform.position = position;
		StreamWriter log = new StreamWriter(@"log_unity.txt");
		test = Test_struct ();
		log.WriteLine("Coord.x = " + test.Coord.x + "\nCoord.y = " + test.Coord.y + "\nVelocity.x = " + test.Velocity.x + "\nVelocity.y = " + test.Velocity.y);
		unsafe {
			fixed(state_model* ptr = &test) {
				TestUpdateStruct (ptr);
			}
		}
		log.WriteLine("\n\nCoord.x = " + test.Coord.x + "\nCoord.y = " + test.Coord.y + "\nVelocity.x = " + test.Velocity.x + "\nVelocity.y = " + test.Velocity.y);


		koef_of_model koef_model = initialization_koef_of_model ();
		log.WriteLine("\n\n\n\nkoef_model.mass = " + koef_model.mass + "\nkoef_model.gravity = " + koef_model.gravity + "\nkoef_model.radius = " + koef_model.radius);
		log.Close();
	}


	private void Awake()
	{
		animator = GetComponent<Animator> ();
		sprite=GetComponent<SpriteRenderer> ();
	}


	private void Update ()
	{
		if (Input.GetKey(KeyCode.LeftArrow))
		{
			Vector3 position = this.transform.position;
			position.x = TestSum_for_dll(position.x, -1);
			this.transform.position = position;
		}
		if (Input.GetKey(KeyCode.RightArrow))
		{
			Vector3 position = this.transform.position;
			position.x = TestSum_for_dll(position.x, 1);
			this.transform.position = position;
		}
		if (Input.GetKey(KeyCode.UpArrow))
		{
			Vector3 position = this.transform.position;
			position.y = TestSum_for_dll(position.y, 1);
			this.transform.position = position;
		}
		if (Input.GetKey(KeyCode.DownArrow))
		{
			Vector3 position = this.transform.position;
			position.y = TestSum_for_dll(position.y, -1);
			this.transform.position = position;
		}
	}
}
