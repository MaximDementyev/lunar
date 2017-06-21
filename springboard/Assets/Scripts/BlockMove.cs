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

	[DllImport("TestCPPLibrary", EntryPoint="TestSum")]
	public static extern float TestSum_for_dll(float a, float b);
	[DllImport("TestCPPLibrary", EntryPoint="TestStruct")]
	public static extern double_Vector2 Test_struct();

	[DllImport("TestCPPLibrary", EntryPoint="TestUpdateStruct")]
	public static unsafe extern void TestUpdateStruct(double_Vector2* res);

	private void Start ()
	{
		Vector3 position = this.transform.position;
		position.y = TestSum_for_dll(position.y, 5);
		this.transform.position = position;
		StreamWriter log = new StreamWriter(@"log_unity.txt");
		double_Vector2 test = Test_struct ();
		log.WriteLine("Vector2.x = " + test.x + "\nVector2.y = " + test.y);
		unsafe {
			TestUpdateStruct (&test);
		}
		log.WriteLine("\n\nVector2.x = " + test.x + "\nVector2.y = " + test.y);
		log.Close();
	}


	private void Awake()
	{
		animator = GetComponent<Animator> ();
		sprite=GetComponent<SpriteRenderer> ();
	}


	private void Update ()
	{
		int step = 1;
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
