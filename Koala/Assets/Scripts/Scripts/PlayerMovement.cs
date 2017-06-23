using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Runtime.InteropServices;
using System.IO;
using System;

public class PlayerMovement : MonoBehaviour
{
	public StreamWriter log; 
    public Camera playerCamera;
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
	public struct surface {
		public double start_x;
		public double start_y;
		public double angle;
		public double limitation_x;
		public double mu;
	};
	public surface current_surface;

	[DllImport("TestCPPLibrary",CallingConvention = CallingConvention.Cdecl, EntryPoint="initialization_koef_model")]
	public static extern koef_of_model initialization_koef_of_model();
	public koef_of_model koef_model;

	[DllImport("TestCPPLibrary",CallingConvention = CallingConvention.Cdecl, EntryPoint="solve_step")]
	public static unsafe extern int solve_step(state_model* current_model, koef_of_model* koef_model, surface* current_surface, double* step_time, double* force);
	public state_model current_model;

	public Vector2 current_position;
	public double force_module = 10;

	public Vector2 bias_ray, vec_gravity;


    void Start()
    {
        if (playerCamera == null)
        {
            playerCamera = Camera.main;
        }
        playerCamera.transparencySortMode = TransparencySortMode.Orthographic;

		//initialization_koef_model
		koef_model = initialization_koef_of_model ();
		current_surface.limitation_x = 0.1;
		current_surface.mu = 1;

		current_position = this.transform.position;
		bias_ray.x = (float)current_surface.limitation_x;
		bias_ray.y = 0;
		vec_gravity.x = 0;
		vec_gravity.y = -1;

		//initialization start model
		current_model.Velocity.x = 0;
		current_model.Velocity.y = 0;
		current_model.Coord.x = System.Convert.ToDouble(current_position.x);
		current_model.Coord.y = System.Convert.ToDouble(current_position.y);

		current_surface.limitation_x = 0.1;
		current_surface.mu = 1;

		//log = new StreamWriter (@"log_unity.txt");
		//StreamWriter log = new StreamWriter(@"log_unity_start.txt");
		//log.WriteLine("current_position.x = " + current_position.x + "\ncurrent_position.y = " + current_position.y);
		//log.WriteLine("\n\ncurrent_model.Coord.x = " + current_model.Coord.x + "\ncurrent_model.Coord.y = " + current_model.Coord.y);
		//log.Close();
    }


	void Update(){
		this.transform.position = current_position;

		//After we move, adjust the camera to follow the player
		playerCamera.transform.position = new Vector3(transform.position.x, transform.position.y + 10, playerCamera.transform.position.z);

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
		double force;
		if (Input.GetKeyDown (KeyCode.RightArrow) || Input.GetKeyDown (KeyCode.LeftArrow) ) {
			if (Input.GetKeyDown (KeyCode.RightArrow)) force = force_module;
			if (Input.GetKeyDown (KeyCode.LeftArrow)) force = -force_module;
		} else {
			force = 0;
		}


		double step_time = (double)Time.deltaTime;
		int res_solve;
		/*state_model current_model;
		current_model.Velocity.x = 0;
		current_model.Velocity.y = 0;
		current_position = this.transform.position;
		current_model.Coord.x = System.Convert.ToDouble(current_position.x);
		current_model.Coord.y = System.Convert.ToDouble(current_position.y);*/
		unsafe{
			
			//state_model* ptr_current_model = &current_model;
			fixed(state_model* ptr_current_model = &current_model) {
				fixed(koef_of_model *ptr_koef_model = &koef_model) {
					fixed(surface *ptr_current_surface = &current_surface) {
						//log.WriteLine("\n2current_model.Coord.x = " + ptr_current_model->Coord.x + "\n1current_model.Coord.y = " + ptr_current_model->Coord.y);
						//log.WriteLine("\n\n!current_model.Coord.x = " + current_model.Coord.x + "\ncurrent_model.Coord.y = " + current_model.Coord.y);

						if (current_model.Velocity.x >= 0) learn_the_surface(ptr_current_surface, ptr_current_model, 1);
						else learn_the_surface(ptr_current_surface, ptr_current_model, -1);
						/*while ((res_solve = solve_step(ptr_current_model, ptr_koef_model, ptr_current_surface, &step_time, &force)) != 0){
							current_position.x = (float)current_model.Coord.x;
							current_position.y = (float)current_model.Coord.y;
							learn_the_surface(ptr_current_surface, ptr_current_model, res_solve);
						}*/
					}
				}
			}
		}
	}

	unsafe void learn_the_surface (surface* current_surface, state_model* current_model, int flag){
		double left_height = 100;
		double right_height = 100;
		if (flag == 1){
			//reycast right
			Raycasting(flag, &left_height, &right_height);
			current_surface->start_x = current_model->Coord.x;
			current_surface->start_y = current_model->Coord.y - left_height;
		}else{
			//reycast left
			Raycasting(flag, &left_height, &right_height);
			current_surface->start_x = current_model->Coord.x - current_surface->limitation_x;
			current_surface->start_y =current_model->Coord.y - right_height;
		}
		current_surface->angle = Math.Atan ((left_height - right_height) / current_surface->limitation_x);
	}

	public unsafe void Raycasting(int flag, double* left_height, double* right_height){
		RaycastHit hitSurfaceLeft;
		RaycastHit hitSurfaceRight;
		if (flag == 1) {
			Physics.Raycast (current_position, vec_gravity, out hitSurfaceLeft);
			Physics.Raycast (current_position + bias_ray, vec_gravity, out hitSurfaceRight);
			*left_height = hitSurfaceLeft.distance;
			*right_height = hitSurfaceRight.distance;
		} else {
			Physics.Raycast (current_position, vec_gravity, out hitSurfaceRight);
			Physics.Raycast (current_position - bias_ray, vec_gravity, out hitSurfaceLeft);
			*left_height = hitSurfaceLeft.distance;
			*right_height = hitSurfaceRight.distance;
		}
	}
}