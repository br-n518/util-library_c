extends KinematicBody

const GRAVITY_VECTOR:Vector3 = Vector3(0, -180, 0)
const TERM_VELOCITY:float = -240.0
const MIN_ATT_TIMEOUT:float = 0.15
const MAX_ATT_TIMEOUT:float = 3.35

signal damage_taken ()

onready var attack_timer:Timer = Timer.new()
onready var can_attack:bool = true
onready var can_jump:bool = false
onready var do_jump:bool = false

export(int) var hitpoints:int = 4 setget set_hp
export(int) var attack:int = 1
export(float) var attack_timeout:float = 1.0 setget set_attack_timeout

func _ready():
	add_child(attack_timer)
	attack_timer.connect("timeout", self, "_on_attack_timer_timeout")

func set_attack_timeout(n:float):
	if n < MIN_ATT_TIMEOUT:
		attack_timeout = MIN_ATT_TIMEOUT
	elif n > MAX_ATT_TIMEOUT:
		attack_timeout = MAX_ATT_TIMEOUT
	else:
		attack_timeout = n

func _on_attack_timer_timeout():
	can_attack = true

func queue_death():
	queue_free()


func jump():
	if can_jump:
		can_jump = false
		do_jump = true



func set_hp(val:int):
	var old:int = hitpoints
	hitpoints = val
	if val < old:
		emit_signal("damage_taken")
	if val <= 0:
		self.queue_death()


func damage(target):
	if can_attack and target.hitpoints > 0 and melee_range(translation, target.translation):
		can_attack = false
		attack_timer.wait_time = attack_timeout
		attack_timer.start()
		# damage target
		target.hitpoints -= attack
		return true
	return false


static func melee_range(a, b):
	if a.distance_squared_to(b) <= 5.0:
		return true
	return false
