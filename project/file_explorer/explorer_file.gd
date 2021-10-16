extends Label

class_name ExplorerFile

signal selected_event(explorer_file)
signal drop_event(explorer_file, position)

var m_is_active : bool
var m_is_file : bool
var m_is_folder : bool
var m_is_drag : bool
var m_path_name: String
var m_directory_path : String
var m_parent_directory_path : String
var m_original_position : Vector2
var m_drag_postion : Vector2
var m_drag_enabled : bool
var m_drag_pressed_pos : Vector2
var m_root : Node
var m_parent : Node
var m_index : int

static func is_pos_inside_target(p_position : Vector2i, p_target : Control) -> bool:
	var target_rect : Rect2i = Rect2(p_target.get_global_position(), p_target.rect_size)
	return target_rect.has_point(p_position)
	
func _init():
	m_is_file = false
	m_is_folder = false
	m_is_active = false
	m_drag_enabled = true
	m_drag_pressed_pos = Vector2.ZERO
	set_mouse_filter(Control.MOUSE_FILTER_PASS)
	self.mouse_entered.connect(Callable(self, "_on_mouse_entered"))
	self.mouse_exited.connect(Callable(self, "_on_mouse_exited"))
	var style : StyleBoxFlat = StyleBoxFlat.new()
	style.border_color = Color8(140, 140, 0, 50)
	style.set_border_width_all(2)
	style.bg_color= Color8(0, 0, 0, 0)
	set("theme_override_styles/normal", style)
	
func _ready():
	m_root = get_tree().get_root()  
	m_parent = get_parent()
	
func _input(event):

	if event is InputEventMouseButton:
		var button_index = event.get_button_index()
		if m_is_active && button_index == MOUSE_BUTTON_LEFT && event.is_double_click():
			emit_signal("selected_event", self)
			return
			
		if m_drag_enabled && button_index == MOUSE_BUTTON_LEFT && !event.is_pressed() && m_drag_pressed_pos != Vector2.ZERO:
			m_drag_pressed_pos = Vector2.ZERO 
			drag_stop()
			return
		
		if m_is_active && m_drag_enabled && button_index == MOUSE_BUTTON_LEFT && event.is_pressed():
			m_drag_pressed_pos = event.get_position()
			return
			
		if button_index == MOUSE_BUTTON_MASK_RIGHT && event.is_pressed():
			pass #open menu

	if m_drag_enabled && m_is_drag && event is InputEventMouseMotion:
		drag_update(event)
		return
		
	if m_drag_enabled && m_drag_pressed_pos != Vector2.ZERO && event is InputEventMouseMotion:
		var distance : float = m_drag_pressed_pos.distance_to(event.get_position()) 
		if distance > 10.0:
			drag_start()
			return
 

func drag_start():
	if m_is_drag:
		return
	m_original_position = get_position()
	m_drag_postion = m_original_position
	m_index = get_index()
	m_parent.remove_child(self)
	m_root.add_child(self)
	m_is_drag = true
	
func drag_update(p_event : InputEventMouseMotion):
	if !m_is_drag:
		return
	m_drag_postion = p_event.get_position()
	self.set_global_position(m_drag_postion - (self.get_rect().size / 2))
	
func drag_stop():
	if !m_is_drag:
		return
	m_is_drag = false
	_on_mouse_exited()
	m_root.remove_child(self)
	m_parent.add_child(self)
	m_parent.move_child(self, m_index)
	self.set_position(m_original_position)
	emit_signal("drop_event", self, m_drag_postion)
	
func is_drop_inside_target(p_target : Control) -> bool:
	return ExplorerFile.is_pos_inside_target(m_drag_postion, p_target)
	
func _on_mouse_entered():
	m_is_active = true 

func _on_mouse_exited():
	m_is_active = false 
	
func set_is_file(p_is_file : bool):
	m_is_file = p_is_file
	
func set_is_folder(p_is_folder : bool):
	m_is_folder = p_is_folder
	
func is_file()-> bool:
	return m_is_file
	
func is_folder() -> bool:
	return m_is_folder

func set_path_name(p_path_name : String):
	m_path_name = p_path_name

func get_path_name() -> String:
	return m_path_name
	
func set_directory_path(p_directory_path : String):
	m_directory_path = p_directory_path
	
func get_directory_path():
	return m_directory_path
		
func set_parent_directory_path(p_parent_directory_path : String):
	m_parent_directory_path = p_parent_directory_path
	
func get_parent_directory_path():
	return m_parent_directory_path
	
func get_full_path() -> String:
	return m_directory_path.plus_file(m_path_name)
	
func get_drag_position() -> Vector2:
	return m_drag_postion
	
func finish():
	var label : String = ""
	if m_is_folder:
		label += "[ ] "
	elif m_is_file:
		label += "    "
	label += m_path_name
	text = label
	
