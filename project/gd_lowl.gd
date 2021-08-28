extends Node

class_name Daw

# Member variables
var space : GdLowlSpace
var selected_device : GdLowlDevice

func _ready():
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

func _on_add_src_button_pressed():
	var fd : FileDialog = get_node("src_ctr/add_src_button/select_sound_dlg")
	fd.popup_centered(Vector2i(800,800))

func _on_select_sound_dlg_file_selected(path):
	var space_id : int = space.add_audio_path(path)
	print("space_id: %d" % space_id)
	if space_id == 0:
		return
	var snd_ctr_res : PackedScene = load("res://test/daw/snd_ctr.tscn")
	var snd_ctr : SndCtr = snd_ctr_res.instantiate()
	snd_ctr.set_space_id(space_id)
	snd_ctr.snd_event.connect(Callable(self, "_on_snd_ctr_event"))
	var container : VBoxContainer = get_node("src_ctr/src_scroll/src_scroll_container")
	container.add_child(snd_ctr)

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
