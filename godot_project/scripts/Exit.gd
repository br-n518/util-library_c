extends Spatial


func _on_Area_body_entered(body):
	var players = get_tree().get_nodes_in_group("player")
	for p in players:
		if p == body:
			_globals.next_map()
