extends Node

class_name SndCtr

# Member variables
var space_id : int
signal snd_event(event, space_id, value)

func _ready():
	pass

func set_space_id(p_space_id):
	space_id = p_space_id

func _on_play_pressed():
	emit_signal("snd_event", "play", space_id, 0)

func _on_stop_pressed():
	emit_signal("snd_event", "stop", space_id, 0)

func _on_pan_value_changed(value):
	print("pan: %f for %d" % [value, space_id])
	emit_signal("snd_event", "pan", space_id, value)

func _on_vol_value_changed(value):
	print("vol: %f for %d" % [value, space_id])
	emit_signal("snd_event", "vol", space_id, value)
