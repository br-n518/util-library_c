extends "res://scripts/BattleCharacter.gd"


const LOWER_AIM_LIMIT:float = (-PI/2) + deg2rad(45)
const UPPER_AIM_LIMIT:float = (PI/2) - deg2rad(22.5)
const DEADZONE:float = 0.05

onready var direction_keys:Vector3 = Vector3()
onready var direction_matrix:Basis = Basis()
onready var analog_values:Vector2 = Vector2()



func _ready():
	add_to_group("player")
	Input.set_mouse_mode(Input.MOUSE_MODE_CAPTURED)
	#connect("damage_taken", self, "got_hurt")
	# For init, Don't call $HUD/Container.update_hp
	#$HUD/Container/VBoxContainer/HPDisplay.update_hp(hitpoints)
	
	#WeaponMount.add_child(preload("res://scenes/weapons/Sword.tscn").instance())

#func got_hurt():
#	$HUD/Container.update_hp(hitpoints)



func queue_death():
	set_process(false)
	set_physics_process(false)
	set_process_unhandled_input(false)
	set_process_unhandled_key_input(false)
	Input.set_mouse_mode(Input.MOUSE_MODE_VISIBLE)


# check melee ray for collision
func attack_melee_ray():
	if can_attack:
		var hit:bool = false
		if $Camera/MeleeRayCast.is_colliding():
			var coll = $Camera/MeleeRayCast.get_collider()
			if coll is preload("res://scripts/BattleCharacter.gd") and damage(coll):
				hit = true
				if coll.hitpoints <= 0:
					# KILLED ENEMY
					self.attack_timeout -= 0.05


#func interact():
#	if $Camera/MeleeRayCast.is_colliding():
#		var coll = $Camera/MeleeRayCast.get_collider()
#		coll.interact('shovel')


func _process(delta):
	rotate_camera(analog_values.x*delta, analog_values.y*delta)

var coll:KinematicCollision
onready var vert_vel:Vector3 = GRAVITY_VECTOR
func _physics_process(delta):
	# Apply gravity
	vert_vel.y += (GRAVITY_VECTOR.y * delta)
	# Limit to terminal velocity
	if vert_vel.y < TERM_VELOCITY:
		vert_vel.y = TERM_VELOCITY
	# Move player vertically2
	coll = move_and_collide(vert_vel * delta)
	if coll:
		# can_jump = true iff player is on the ground
		can_jump = (coll.normal.y > 0.2)
		if can_jump:
			vert_vel.y = 0
	# Move player horizontally
	move_and_slide( direction_matrix.xform(direction_keys.normalized()) * 8)



func _unhandled_key_input(ev:InputEventKey):
	if ev.pressed:
		match ev.scancode:
			# movement
			KEY_W:
				direction_keys.z = -1
			KEY_S:
				direction_keys.z = 1
			KEY_A:
				direction_keys.x = -1
			KEY_D:
				direction_keys.x = 1
			# jump
			KEY_SPACE:
				jump()
			KEY_ESCAPE:
				pause()
			
	else: # not ev.is_pressed()
		match ev.scancode:
			KEY_W, KEY_S:
				direction_keys.z = 0
			KEY_A, KEY_D:
				direction_keys.x = 0

func _unhandled_input(ev:InputEvent):
	if Input.get_mouse_mode() == Input.MOUSE_MODE_CAPTURED:
		# Mouse Motion
		if ev is InputEventMouseMotion:
			rotate_camera(deg2rad(ev.relative.x)*_globals.MOUSE_SENS_LEVEL/2.0, deg2rad(ev.relative.y)*_globals.MOUSE_SENS_LEVEL/2.0)
		# Gamepad Motion
		elif ev is InputEventJoypadMotion:
			match ev.axis:
				JOY_ANALOG_LX:
					direction_keys.x = 0
					if ev.axis_value > DEADZONE:
						direction_keys.x = 1
					elif ev.axis_value < -DEADZONE:
						direction_keys.x = -1
				JOY_ANALOG_LY:
					# Left Vertical
					direction_keys.z = 0
					if ev.axis_value > DEADZONE:
						direction_keys.z = 1
					elif ev.axis_value < -DEADZONE:
						direction_keys.z = -1
				JOY_ANALOG_RX:
					# Right Horizontal
					if abs(ev.axis_value) > DEADZONE:
						analog_values.y = ev.axis_value * _globals.GAMEPAD_SENS_LEVEL
						if _globals.INVERT_Y:
							analog_values.y *= -1
					else:
						analog_values.y = 0.0
				JOY_ANALOG_RY:
					# Right Vertical
					if abs(ev.axis_value) > DEADZONE:
						analog_values.x = ev.axis_value * _globals.GAMEPAD_SENS_LEVEL
					else:
						analog_values.x = 0.0
		# Check buttons (presses only)
		elif ev.is_pressed():
			if ev is InputEventMouseButton:
				if ev.button_index == BUTTON_LEFT:
					attack_melee_ray()
			elif ev is InputEventJoypadButton:
				# Check start button first
				if ev.button_index == JOY_START:
					pause()
				else:
					# Check Joypad Buttons
					match ev.button_index:
						JOY_XBOX_A:
							jump()
						# JOY_R2 == SONY_R1
						JOY_R2,JOY_R:
							attack_melee_ray()
	# pressing button enables mouse capture
	else:
		if ev is InputEventMouseButton or ev is InputEventJoypadButton:
			Input.set_mouse_mode(Input.MOUSE_MODE_CAPTURED)

func rotate_camera(yaw:float, pitch:float):
	if yaw != 0.0 or pitch != 0.0:
		# YAW 
		direction_matrix = direction_matrix.rotated(Vector3.UP, -yaw).orthonormalized()
		
		# PITCH
		pitch = clamp($Camera.rotation.x - pitch, LOWER_AIM_LIMIT, UPPER_AIM_LIMIT)
		$Camera.rotation = direction_matrix.get_euler()
		$Camera.rotation.x = pitch


func jump():
	if can_jump:
		can_jump = false
		vert_vel.y = 33



func pause():
	Input.set_mouse_mode(Input.MOUSE_MODE_VISIBLE)



