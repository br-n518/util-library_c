extends Camera

const LOW_SPEED = 10
const HIGH_SPEED = 50

const LOWER_AIM_LIMIT:float = (-PI/2) + 0.1
const UPPER_AIM_LIMIT:float = (PI/2) - 0.1
const DEADZONE:float = 0.05
const GAMEPAD_SENS_LEVEL:float = 1.0

onready var direction_keys:Vector3 = Vector3()
onready var direction_matrix:Basis = Basis()
onready var analog_values:Vector2 = Vector2()

onready var speed = LOW_SPEED;

func _ready():
	add_to_group("player")

func _process(delta):
	rotate_camera(analog_values.x*delta, analog_values.y*delta)
	direction_keys.y = 0
	if direction_keys.z < 0:
		direction_keys.y = sin(rotation.x)
	elif direction_keys.z > 0:
		direction_keys.y = -sin(rotation.x)
	translation += ( direction_matrix.xform(direction_keys.normalized()) * speed ) *delta
	



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
			KEY_SHIFT:
				speed = HIGH_SPEED
	else: # not ev.is_pressed()
		match ev.scancode:
			KEY_W, KEY_S:
				direction_keys.z = 0
			KEY_A, KEY_D:
				direction_keys.x = 0
			KEY_SHIFT:
				speed = LOW_SPEED

func _unhandled_input(ev:InputEvent):
	if Input.get_mouse_mode() == Input.MOUSE_MODE_CAPTURED:
		# Mouse Motion
		if ev is InputEventMouseMotion:
			rotate_camera(deg2rad(ev.relative.x), deg2rad(ev.relative.y))
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
						analog_values.y = ev.axis_value * GAMEPAD_SENS_LEVEL
#						if _globals.INVERT_Y:
#							analog_values.y *= -1
					else:
						analog_values.y = 0.0
				JOY_ANALOG_RY:
					# Right Vertical
					if abs(ev.axis_value) > DEADZONE:
						analog_values.x = ev.axis_value * GAMEPAD_SENS_LEVEL
					else:
						analog_values.x = 0.0
		# Check buttons (presses only)
		elif ev.is_pressed():
			if ev is InputEventMouseButton:
				if ev.button_index == BUTTON_LEFT:
					pass
					#attack_melee_ray()
			elif ev is InputEventJoypadButton:
				# Check start button first
				if ev.button_index == JOY_START:
					#pause()
					pass
				else:
					# Check Joypad Buttons
					match ev.button_index:
						JOY_XBOX_A:
							#jump()
							pass
						# JOY_R2 == SONY_R1
						JOY_R2,JOY_R:
							#attack_melee_ray()
							pass
	# pressing button enables mouse capture
	else:
		if ev is InputEventMouseButton or ev is InputEventJoypadButton:
			Input.set_mouse_mode(Input.MOUSE_MODE_CAPTURED)

func rotate_camera(yaw:float, pitch:float):
	if yaw != 0.0 or pitch != 0.0:
		# YAW 
		direction_matrix = direction_matrix.rotated(Vector3.UP, -yaw).orthonormalized()
		
		# PITCH
		pitch = clamp(rotation.x - pitch, LOWER_AIM_LIMIT, UPPER_AIM_LIMIT)
		rotation = direction_matrix.get_euler()
		rotation.x = pitch
