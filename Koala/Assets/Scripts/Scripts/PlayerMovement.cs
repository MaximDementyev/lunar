using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Runtime.InteropServices;
using System.IO;
using System;
using Utils;

public class PlayerMovement : MonoBehaviour
{
    public Camera playerCamera;
	public TextMesh model_text;

	public Surface current_surface;

	[DllImport("fiz2d",CallingConvention = CallingConvention.Cdecl, EntryPoint="initialization_koef_model")]
	public static extern Koef_of_model initialization_koef_of_model();
	public Koef_of_model koef_model;

	[DllImport("fiz2d",CallingConvention = CallingConvention.Cdecl, EntryPoint="solve_step")]
	public static unsafe extern int solve_step(ref State_model current_model, ref Koef_of_model koef_model, ref Surface current_surface, ref double step_time, double force);
	public State_model current_model;

	public Vector2 cur_pos_Wheel, cur_pos_body;
    public double mu = 0.5;
    public double limitation_x = 0.5;
    public double force_module;

	public Vector2 bias_ray, vec_gravity;
    public GameObject Wheel;
   
	
	public float body_lifting;
	int layerMask = 1 << 8;

    void Start()
    {
        if (playerCamera == null)
        {
            playerCamera = Camera.main;
        }
        playerCamera.transparencySortMode = TransparencySortMode.Orthographic;
		//initialization_koef_model
		koef_model = initialization_koef_of_model ();
		current_surface.limitation_x = limitation_x;
		current_surface.mu = mu;

		cur_pos_body = this.transform.position;
		bias_ray.x = (float)current_surface.limitation_x;
		bias_ray.y = 0;

		//initialization start model
		current_model.wheel.Velocity.x = current_model.body.Velocity.x = 0;
		current_model.wheel.Velocity.y = current_model.body.Velocity.y = 0;
		current_model.body.Coord.x = System.Convert.ToDouble(cur_pos_body.x);
		current_model.body.Coord.y = System.Convert.ToDouble(cur_pos_body.y);

        current_model.wheel.Coord.x = current_model.body.Coord.x;
        current_model.wheel.Coord.y = current_model.body.Coord.y - System.Convert.ToDouble(koef_model.wheel.position);

        layerMask = ~layerMask;
		//StreamWriter log = new StreamWriter(@"log_unity_start.txt");
		//log.WriteLine("current_position.x = " + current_position.x + "\ncurrent_position.y = " + current_position.y);
		//log.WriteLine("\n\ncurrent_model.Coord.x = " + current_model.Coord.x + "\ncurrent_model.Coord.y = " + current_model.Coord.y);
		//log.Close();
    }


	void Update(){
		GetComponent<Transform>().position = new Vector3(cur_pos_body.x, cur_pos_body.y, 0);
        Wheel.transform.position = new Vector3(cur_pos_Wheel.x, cur_pos_Wheel.y, 0); 
		//After we move, adjust the camera to follow the player
		playerCamera.transform.position = new Vector3(transform.position.x, transform.position.y + 10, playerCamera.transform.position.z);
		model_text.text = "coord.x      " + current_model.wheel.Coord.x + "\ncoord.y      " + current_model.wheel.Coord.y + 
			"\nvelocity.x   " + current_model.wheel.Velocity.x + "\nvelocity.y   " + current_model.wheel.Velocity.y +
			"\nangle         " + current_surface.angle;
	}
 
    void FixedUpdate()
	{   
		if (Input.GetKey(KeyCode.A))
		{
			++force_module;
		}

		if (Input.GetKey(KeyCode.Z))
		{
			if (force_module > 0) --force_module;
		}
		double force = 0;
		if (Input.GetKey (KeyCode.RightArrow) || Input.GetKey (KeyCode.LeftArrow) ) {
			if (Input.GetKey(KeyCode.RightArrow)) force = force_module;
			if (Input.GetKey (KeyCode.LeftArrow)) force = -force_module;
		}

		double step_time = System.Convert.ToDouble(Time.deltaTime);
		int res_solve;
		unsafe{
			if (current_model.wheel.Velocity.x >= 0) res_solve = 1;
			else res_solve = -1;
			learn_the_surface(ref current_surface, ref current_model, res_solve);
			while ((res_solve = solve_step(ref current_model, ref koef_model, ref current_surface, ref step_time, force)) != 0){
                cur_pos_Wheel.x = (float)current_model.wheel.Coord.x;
                cur_pos_Wheel.y = (float)current_model.wheel.Coord.y;
                cur_pos_body.x = (float)current_model.body.Coord.x;
                cur_pos_body.y = (float)current_model.body.Coord.y;
                learn_the_surface(ref current_surface, ref current_model, res_solve);
			}
            cur_pos_Wheel.x = (float)current_model.wheel.Coord.x;
            cur_pos_Wheel.y = (float)current_model.wheel.Coord.y;
            cur_pos_body.x = (float)current_model.body.Coord.x;
            cur_pos_body.y = (float)current_model.body.Coord.y;
        }
	}

	public unsafe void learn_the_surface (ref Surface current_surface, ref State_model current_model, int flag){
		double left_height = 0;
		double right_height = 0;
		if (flag == 1){
			//reycast right
			Raycasting(flag, ref left_height, ref right_height);
			current_surface.start_x = current_model.wheel.Coord.x;
			current_surface.start_y = current_model.wheel.Coord.y - left_height;
		}else{
			//reycast left
			Raycasting(flag, ref left_height, ref right_height);
			current_surface.start_x = current_model.wheel.Coord.x - current_surface.limitation_x;
			current_surface.start_y = current_model.wheel.Coord.y - left_height;
		}
		current_surface.angle = Math.Atan ((left_height - right_height) / current_surface.limitation_x);
		current_surface.left_height = left_height;
		current_surface.right_height = right_height;
	}

	public unsafe void Raycasting(int flag, ref double  left_height, ref double right_height){
		RaycastHit hitSurfaceLeft;
		RaycastHit hitSurfaceRight;
		if (flag == 1) {
			Physics.Raycast (cur_pos_Wheel - vec_gravity * body_lifting, vec_gravity, out hitSurfaceLeft, Mathf.Infinity, layerMask);
			Physics.Raycast (cur_pos_Wheel + bias_ray - vec_gravity * body_lifting, vec_gravity, out hitSurfaceRight, Mathf.Infinity, layerMask);
		} else {
			Physics.Raycast (cur_pos_Wheel - vec_gravity * body_lifting, vec_gravity, out hitSurfaceRight, Mathf.Infinity, layerMask);
			Physics.Raycast (cur_pos_Wheel - bias_ray - vec_gravity * body_lifting, vec_gravity, out hitSurfaceLeft, Mathf.Infinity, layerMask);
		}
		left_height = hitSurfaceLeft.distance + vec_gravity.y * body_lifting;
		right_height = hitSurfaceRight.distance + vec_gravity.y * body_lifting;
	}
}