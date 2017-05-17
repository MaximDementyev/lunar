using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Runtime.InteropServices;
using System.IO;

public class BlockMove : MonoBehaviour {
	new private Rigidbody2D rigidbody;
	private Animator animator;
	private SpriteRenderer sprite;

	//[DllImport("TestCPPLibrary", EntryPoint="TestDivide")]
	//public static extern float StraightFromDllTestDivide(float a, float b);

	private void Start ()
	{
		Vector3 position = this.transform.position;
		position.y = TestCSharpLibrary.TestCSharpLibrary.TestSum(position.y, 5);
		this.transform.position = position;

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
			position.x = TestCSharpLibrary.TestCSharpLibrary.TestSum(position.x, -1);
			this.transform.position = position;
		}
		if (Input.GetKey(KeyCode.RightArrow))
		{
			Vector3 position = this.transform.position;
			position.x = TestCSharpLibrary.TestCSharpLibrary.TestSum(position.x, 1);
			this.transform.position = position;
		}
		if (Input.GetKey(KeyCode.UpArrow))
		{
			Vector3 position = this.transform.position;
			position.y = TestCSharpLibrary.TestCSharpLibrary.TestSum(position.y, 1);
			this.transform.position = position;
		}
		if (Input.GetKey(KeyCode.DownArrow))
		{
			Vector3 position = this.transform.position;
			position.y = TestCSharpLibrary.TestCSharpLibrary.TestSum(position.y, -1);
			this.transform.position = position;
		}
	}
}
