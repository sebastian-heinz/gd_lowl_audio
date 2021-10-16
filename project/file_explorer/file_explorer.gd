extends Control

class_name FileExplorer

signal file_drop_event(explorer_file, position)

var drives : OptionButton
var dir : Directory
var files : VBoxContainer
var label_path : Label
var text_filter : LineEdit
var current_directory_path : String
var current_disk_path : String
var drive_loaded : bool
var os_name : String 
var explorer_files: Array
	
func _init():
	os_name = OS.get_name()
	current_disk_path = ""
	current_directory_path = ""
	drive_loaded = false
	explorer_files = []
	
func _ready():
	label_path = get_node("path")
	files = get_node("scroll/container")
	drives = get_node("control/disk")
	text_filter = get_node("control/filter")
	if !drive_loaded:
		load_drives()

func load_drives():
	drives.clear()
	dir = Directory.new()

	if os_name == "Windows":
		var win_drives = ["A:", "B:", "C:", "D:", "E:", "F:", "G:", "H:", "I:", "J:", "K:", "L:", "M:", "N:", "O:", "P:", "Q:", "R:", "S:", "T:", "U:", "V:", "W:", "X:", "Y:", "Z:"]
		for dr in win_drives:
			var _result = dir.open(dr) 
	else:
		var _result = dir.open("/")
	var dc = dir.get_drive_count();
	if dc == 0:
		push_warning("No Drives")
	else:
		for i in range(0, dc):
			var d : String = dir.get_drive(i)
			drives.add_item(d)	
	var disk_index : int = dir.get_current_drive()
	drives.select(disk_index)
	_on_disk_item_selected(disk_index)
	drive_loaded = true

func _on_disk_item_selected(index):
	var dist_path : String = drives.get_item_text(index)
	current_disk_path = dist_path
	change_dir(dist_path)

func delete_children(node : Node):
	for n in node.get_children():
		node.remove_child(n)
		n.queue_free()

func change_dir(directory_path : String):
	dir.change_dir(directory_path)
	var result = dir.list_dir_begin(true, true)
	if result != OK:
		push_error("dir.list_dir_begin")
	
	explorer_files.clear()
	while true:
		var next_path: String = dir.get_next()
		if next_path.is_empty():
			break
		elif next_path == "." || next_path == "..":
			continue
		var explorer_file : ExplorerFile = ExplorerFile.new()
		explorer_file.selected_event.connect(Callable(self, "_on_selected_event"))
		explorer_file.drop_event.connect(Callable(self, "_on_drop_event"))
		explorer_file.set_parent_directory_path(directory_path)
		explorer_file.set_directory_path(directory_path)
		explorer_file.set_path_name(next_path)
		if dir.current_is_dir():
			explorer_file.set_is_folder(true)
		else:
			explorer_file.set_is_file(true)
		explorer_file.finish()
		explorer_files.append(explorer_file)
	
	explorer_files.sort_custom(Callable(self, "path_sort"))
	current_directory_path = directory_path
	label_path.text = directory_path
	text_filter.clear()
	delete_children(files)
	for explorer_file in explorer_files:
		files.add_child(explorer_file)
		
func _on_selected_event(explorer_file : ExplorerFile):
	if explorer_file.is_folder():
		var new_path : String = explorer_file.get_full_path()
		change_dir(new_path)
		
func _on_drop_event(p_explorer_file : ExplorerFile, p_position : Vector2):
	emit_signal("file_drop_event", p_explorer_file, p_position)
	
func _on_navigate_up_pressed():
	var parent_directory : String = get_parent_directory(current_directory_path)
	if !parent_directory.is_empty():
		change_dir(parent_directory)

func get_parent_directory(p_directory_path : String) -> String:
	var separators : Array[String] = ["/", "\\", "\\\\"]
	
	var parent_directory : String = ""
	for separator in separators:
		var parent : String = p_directory_path.trim_suffix(separator)
		var idx : int = parent.rfind(separator)
		if idx > -1:
			parent_directory = parent.substr(0, idx)
			if os_name != "Windows":
				parent_directory += separator
			break
		else:
			continue
	return parent_directory
	
static func path_sort(a, b):
	# if the given method returns true, element b will be after element a in the array.
	# true = ab | false = ba
	if !(a is ExplorerFile):
		return false
	if !(b is ExplorerFile):
		return false
	if a.is_folder() and !b.is_folder():
		return true
	if !a.is_folder() and b.is_folder():
		return false
	if a.is_folder() and b.is_folder():
		var test = a.get_path_name().casecmp_to(b.get_path_name())
		return test < 0
	if a.is_file() and b.is_file():
		var test = a.get_path_name().casecmp_to(b.get_path_name())
		return test < 0
	return true

func _on_filter_text_changed(p_filter : String):
	if p_filter.is_empty():
		for explorer_file in explorer_files:
			var explorer_file_t : ExplorerFile = explorer_file
			explorer_file_t.show()
		return
			
	var regex = RegEx.new()
	regex.compile(p_filter)
	for explorer_file in explorer_files:
		var explorer_file_t : ExplorerFile = explorer_file
		var result = regex.search(explorer_file_t.get_path_name())
		if result:
			explorer_file_t.show()
		else:
			explorer_file_t.hide()
