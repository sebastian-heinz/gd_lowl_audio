extends Node

class_name SoundSource

# Member variables
var space_id : int
var progress : ProgressBar
signal sound_source_event(sound_source : SoundSource, event : String, space_id : int, value)

func _init():
	pass

func _ready():
	progress = get_node("snd/progress")
	progress.min_value = 0;
	progress.max_value = 100;
	progress.value = 0;

func set_space_id(p_space_id):
	space_id = p_space_id
	
func get_space_id() -> int:
	return space_id
	
func set_progress(p_progress):
	progress.value = p_progress

func _on_play_pressed():
	emit_signal("sound_source_event", self, "play", space_id, 0)

func _on_stop_pressed():
	emit_signal("sound_source_event", self, "stop", space_id, 0)

func _on_pan_value_changed(value):
	print("pan: %f for %d" % [value, space_id])
	emit_signal("sound_source_event", self, "pan", space_id, value)

func _on_vol_value_changed(value):
	print("vol: %f for %d" % [value, space_id])
	emit_signal("sound_source_event", self, "vol", space_id, value)

func _on_progress_gui_input(event):
	if event is InputEventMouseButton:
		var button_index = event.get_button_index()
		if button_index == MOUSE_BUTTON_LEFT && event.is_pressed():
			var progress_max : float = progress.rect_size.x
			var progress_selected : float = event.position.x
			var percent : float = (progress_selected / progress_max) * 100
			print("pos: %f for %d" % [percent, space_id])
			emit_signal("sound_source_event", self, "pos", space_id, percent)
