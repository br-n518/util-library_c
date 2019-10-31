extends Node

# warning-ignore:unused_class_variable
onready var MOUSE_SENS_LEVEL:int = 2
# warning-ignore:unused_class_variable
onready var GAMEPAD_SENS_LEVEL:int = 5
# warning-ignore:unused_class_variable
onready var INVERT_Y:bool = false

# warning-ignore:unused_class_variable
onready var world_seed = ' '




func _input(event):
	if event is InputEventKey and event.is_pressed():
		match event.scancode:
			KEY_ESCAPE:
				Input.set_mouse_mode(Input.MOUSE_MODE_VISIBLE)
			KEY_F11:
				OS.set_window_fullscreen( not OS.window_fullscreen)
				get_viewport().size = OS.window_size


func next_map():
# warning-ignore:return_value_discarded
	get_tree().reload_current_scene()

