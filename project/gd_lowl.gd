extends Node

class_name Daw

# Member variables
var space : GdLowlSpace
var selected_device : GdLowlDevice
var file_explorer : FileExplorer

func _init():
	pass

func _ready():
	file_explorer = get_node("file_explorer")
	file_explorer.file_drop_event.connect(Callable(self, "_on_file_drop_event"))
	init_gd();

func init_gd():
	# initialize GdLowl
	var err = GdLowl.init()
	if err != GdLowlError.NoError:
		push_error("GdLowl.init(): %s" % err)
		return
		
	# iterate available drivers and devices
	var available_devices = Array();
	for _driver in GdLowl.get_drivers():
		var driver : GdLowlDriver = _driver;
		print("driver: %s" % driver.get_name())
		err = driver.initialize()
		if err != GdLowlError.NoError:
			push_error("driver.initialize(): %s" % err)
			return
		for _device in driver.get_devices():
			var device : GdLowlDevice = _device;
			print("device: %s" % device.get_name())
			available_devices.push_back(device)
	
	# select desired device
	var selected_device_index = 0;
	if available_devices.size() <= 0:
		push_error("available_devices.size() <= 0")
		return
	if selected_device_index >= available_devices.size():
		push_error("selected_device_index >= available_devices.size()")
		return
	selected_device = available_devices[selected_device_index]
	space = GdLowl.create_space(2, 44100.0);

	err = selected_device.start(space)
	if err != GdLowlError.NoError:
		push_error("selected_device.start(): %s" % err)
		return
		
func _on_file_drop_event(p_explorer_file : ExplorerFile, p_position : Vector2):
	var target = get_node("src_ctr/src_scroll")
	if p_explorer_file.is_drop_inside_target(target):
		var path = p_explorer_file.get_full_path()
		var space_id : int = space.add_audio_path(path)
		if space_id == 0:
			return
		var sound_source_scene : PackedScene = load("res://sound_source/sound_source.tscn")
		var sound_source : SoundSource = sound_source_scene.instantiate()
		sound_source.set_space_id(space_id)
		sound_source.snd_event.connect(Callable(self, "_on_snd_ctr_event"))
		var container : VBoxContainer = get_node("src_ctr/src_scroll/src_scroll_container")
		container.add_child(sound_source)
	
func _on_snd_ctr_event(event, space_id, value):
	print("_on_snd_ctr_event: %s" % event)
	if(event == "play"):
		space.play_audio(space_id)
	if(event == "stop"):
		space.stop_audio(space_id)
	if(event == "pan"):
		space.set_audio_panning(space_id, value)
	if(event == "vol"):
		space.set_audio_volume(space_id, value)
