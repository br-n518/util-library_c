extends "res://scripts/BattleCharacter.gd"

export(NodePath) var ANIM_PLAYER = "AnimationPlayer"
export(String) var PLAYER_GROUP = "player"
export(String) var ENEMY_GROUP = "enemy"

onready var anim_player:AnimationPlayer = get_node(ANIM_PLAYER)

const IDLE_STATE = 1
const ATTACK_STATE = 2

var state setget set_state

var target_player = null
var target:Vector3 = Vector3.ZERO

func _ready():
	add_to_group(ENEMY_GROUP)
	target = self.translation + Vector3.FORWARD.rotated(Vector3.UP, randf()*PI*2)
	self.state = IDLE_STATE


func _process(delta):
	check_state()
	if state == ATTACK_STATE and target_player != null and damage(target_player):
		anim_player.play("attack")

func _physics_process(delta):
	var target_direction:Vector3 = (target - self.translation)
	target_direction.y = 0
	target_direction = target_direction.normalized()
	self.rotation.y = atan2(target_direction.x, target_direction.z)
	var coll = move_and_collide(target_direction * delta)
	if coll and target_player == null:
			target = target_direction.bounce(coll.normal) * target.distance_to(translation)


func check_state():
	match state:
		IDLE_STATE:
			for p in get_tree().get_nodes_in_group(PLAYER_GROUP):
				if p.translation.distance_squared_to(self.translation) < 20:
					target_player = p
					self.state = ATTACK_STATE
					return
			target_player = null
			if  (target - translation).length_squared() < 0.5:
				var r = (randi()%5) + 1
				target = self.translation + (Vector3.FORWARD.rotated(Vector3.UP, randf()*PI*2) * r)
		ATTACK_STATE:
			if target.distance_squared_to(self.translation) > 25:
				self.state = IDLE_STATE
			else:
				target = target_player.translation
				

func set_state(s):
	state = s
	match state:
		IDLE_STATE:
			anim_player.play("walk-loop")
			target = self.translation + (Vector3.FORWARD.rotated(Vector3.UP, randf()*PI*2) * 2)
		ATTACK_STATE:
			target = target_player.translation



func _on_AnimationPlayer_animation_finished(anim_name):
	if anim_name == "attack":
		anim_player.play("walk-loop")

