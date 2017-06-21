using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Runtime.InteropServices;
using System.IO;
using System;



public class PlayerMovement : MonoBehaviour
{
	
    public Camera playerCamera;
	
    /*public float speed = 12.0F;
    public float jumpSpeed = 8.0F;
    public float gravity = 20.0F;
    private Vector3 moveDirection = Vector3.zero;*/


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
		public double limitation_x = 1; //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		public double mu = 1;
	};
	public surface current_surface;

	[DllImport("TestCPPLibrary", EntryPoint="initialization_koef_model")]
	public static extern koef_of_model initialization_koef_of_model();
	public koef_of_model koef_model;

	[DllImport("TestCPPLibrary", EntryPoint="solve_step")]
	public static unsafe extern int solve_step(state_model* current_model, koef_of_model* koef_model, surface* current_surface, double* step_time, double* force);
	public state_model current_model;


	public Vector2 current_position;
	public int force_module = 1;

    void Start()
    {
        if (playerCamera == null)
        {
            playerCamera = Camera.main;
        }
        playerCamera.transparencySortMode = TransparencySortMode.Orthographic;

		koef_model = initialization_koef_of_model ();//initialization_koef_model
		//initialization start model
		current_model.Velocity.x = current_model.Velocity.y = 0;
		//coord !!!!!!!!!!
		// !!!!!!!!current_position = position
    }


	void Update(){
		//!!!!!position = current_position

		//After we move, adjust the camera to follow the player
		playerCamera.transform.position = new Vector3(transform.position.x, transform.position.y + 10, playerCamera.transform.position.z);

	}

    void FixUpdate()
    {    
		/*if (Input.GetKey(KeyCode.LeftArrow))
		{
			Vector3 position = this.transform.position;
			position.x--;
			this.transform.position = position;
		}
		if (Input.GetKey(KeyCode.RightArrow))
		{
			Vector3 position = this.transform.position;
			position.x++;
			this.transform.position = position;
		}
		if (Input.GetKey(KeyCode.UpArrow))
		{
			Vector3 position = this.transform.position;
			position.y++;
			this.transform.position = position;
		}
        CharacterController controller = GetComponent<CharacterController>();
        if (controller.isGrounded)
        {
            moveDirection = new Vector3(1, 0, Input.GetAxis("Vertical"));
            moveDirection = transform.TransformDirection(moveDirection);
            //moveDirection *= speed;
            if (Input.GetButton("Jump"))
            {
                moveDirection.y = jumpSpeed; 
            }
            if (Input.touchCount > 0)
            {
                moveDirection.y = jumpSpeed;
            }
           
        }
        moveDirection.y -= gravity * Time.smoothDeltaTime;
        controller.Move(moveDirection * Time.smoothDeltaTime);*/


        


		//__________________________________________________________
		if (Input.GetKey(KeyCode.A))
		{
			++force_module;
		}

		if (Input.GetKey(KeyCode.Z))
		{
			if (force_module > 0) --force_module;
		}
		int force;
		//!!!!!!!!!!!!!! force = Input.KeyCode.UpArrow/KeyCode.DownArrow
		//!!!!!!!!!!!!!! If the button is pressed the value is. Button not pressed - value 0;



		int step_time = 1; //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! time one step unity
		int res_solve;
		unsafe{
			fixed(state_model* ptr_current_model = &current_model) {
				fixed(koef_of_model *ptr_koef_model = &koef_model) {
					fixed(surface *ptr_current_surface = &current_surface) {
						double left_height;
						double right_height;
						if (current_model.Velocity.x >= 0){
							//reycast +!!!!!!!!!!!!!!!!!
							current_surface.start_x = 0; //=position.x
							current_surface.start_y = 0; //=position.y - left_height
						}else{
							//reycast -!!!!!!!!!!!!!!!!!
							current_surface.start_x = 0; //=position.x-current_surface.limitation_x
							current_surface.start_y = 0; //=position.y - right_height
						}
						current_surface.angle = Math.Atan ((left_height - right_height) / current_surface.limitation_x) * Math.PI / 180;
						while ((res_solve = solve_step(ptr_current_model, ptr_koef_model, ptr_current_surface, &step_time, &force) != 0)){
							//!!!!!position = current_model.Coord    in(float)
							if (res_solve == 1){
								//reycast +!!!!!!!!!!!!!!!!!
								current_surface.start_x = 0; //=position.x
								current_surface.start_y = 0; //=position.y - left_height
							}else{
								//reycast -!!!!!!!!!!!!!!!!!
								current_surface.start_x = 0; //=position.x-current_surface.limitation_x
								current_surface.start_y = 0; //=position.y - right_height
							}
						}
					}
				}
			}
		}
	}
}
