# Godot Lowl Audio


## Setup:
### via submodule
- open a terminal inside the godot source folder and run the following commands:  
  `cd modules`  
  `git submodule add https://github.com/sebastian-heinz/gd_lowl_audio.git`  
  `git submodule update --init --recursive`  


## Usage

### In GDScript

### In other modules
To use lowl_audio as a c++ lib directly in another module, add the following to your modules `SCsub`-file
```
module_env.Prepend(CPPPATH=["#modules/gd_lowl_audio/lowl_audio/include"])
module_env.Prepend(CPPPATH=["#modules/gd_lowl_audio/lowl_audio/third_party/readerwriterqueue"])
module_env.Prepend(CPPPATH=["#modules/gd_lowl_audio/lowl_audio/third_party/concurrentqueue"])
module_env.Prepend(CPPPATH=["#modules/gd_lowl_audio/lowl_audio/third_party/dr_libs"])
module_env.Prepend(CPPPATH=["#modules/gd_lowl_audio/lowl_audio/third_party/portaudio/include"])
module_env.Prepend(CPPPATH=["#modules/gd_lowl_audio/lowl_audio/third_party/r8brain-free-src"])
```

### Space
```gdscript
extends Node

class_name GdLowlSpaceTest

func _ready():
	
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
	var selected_device : GdLowlDevice = available_devices[selected_device_index]
	
	# setup the space
	var space : GdLowlSpace = GdLowlSpace.new()
	var audio_1 : int = space.add_audio_path("/Users/railgun/Downloads/CantinaBand60.wav")
	var audio_2 : int = space.add_audio_path("/Users/railgun/Downloads/StarWars60.wav")
	space.load()
	var space_mixer : GdLowlAudioMixer = space.get_mixer()
	
	# register it with the device
	err = selected_device.start_mixer(space_mixer)
	if err != GdLowlError.NoError:
		push_error("selected_device.start_mixer(): %s" % err)
		return
		
	# space is ready to play loaded sounds
	space.play(audio_1)
	space.play(audio_2)
		
	# wait for 10 seconds
	var time = 10
	while time >= 0:
		OS.delay_msec(1000)
		time = time - 1
		
	# when done, stop the device
	err = selected_device.stop()
	if err != GdLowlError.NoError:
		push_error("selected_device.stop(): %s" % err)
		return
```

notes
```
scons platform=osx arch=x86_64 --jobs=6
scons --clean platform=osx arch=x86_64 --jobs=6
```