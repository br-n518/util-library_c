extends Reference

var globals:Dictionary
var sections:Dictionary

func _init():
	globals = {}
	sections = {}

# get
func ini_get( sect:String, key:String ) -> String:
	if sections.has(sect):
		if sections[sect].has(key):
			return sections[sect][key]
	return ''

# get global
func ini_get_global( key:String ) -> String:
	if globals.has(key):
		return globals[key]
	return ''

# set
func ini_set( sect:String, key:String, value:String ):
	if not sections.has(sect):
		sections[sect] = {}
	sections[sect][key] = value

# set global
func ini_set_global( key:String, value:String ):
	globals[key] = value

# open
func ini_open( filename:String ):
	var f:File = File.new()
	if f.open( filename, File.READ ) == OK:
		var fdata:String = f.get_as_text()
		f.close()
		ini_parse( fdata )

# save
func ini_save( filename:String ):
	var f:File = File.new()
	if f.open( filename, File.WRITE ) == OK:
		f.store_string(ini_to_string())
		f.close()

# parse
func ini_parse( data:String ):
	var lines:PoolStringArray = data.split( "\n", false )
	
	var sect:String = ''
	
	for l in lines:
		
		if l.begins_with('['):
			var end_bracket = l.find(']') - 1
			if end_bracket < 1:
				end_bracket = len(l)
			# strip edges and inner whitespace
			sect = l.substr(1, end_bracket).strip_edges().replace(' ', '').replace('\t', '')
			if not sections.has(sect):
				sections[sect] = {}
		else:
			var eq:int = l.find('=')
			if eq > 0:
				# strip edges and inner whitespace
				var key = l.substr(0, eq).strip_edges().replace(' ', '').replace('\t', '')
				var val_end = l.find('#')
				# comment found, and it comes before the equals sign
				if val_end != -1 and val_end < eq:
					continue
				# comment not found, use whole line
				elif val_end == -1:
					val_end = len(l)
				# strip edges of value string
				var value = l.substr(eq+1, val_end).strip_edges()
				if len(sect) > 0:
					sections[sect][key] = value
				else:
					globals[key] = value

# to_string
func ini_to_string() -> String:
	var data:PoolStringArray = PoolStringArray()
	for k in globals.keys():
		data.append(str(k) + "=" + str(globals[k]))
	for s in sections.keys():
		data.append('[' + s + ']')
		for k in sections[s].keys():
			data.append(str(k) + "=" + str(sections[s][k]))
	return data.join('\n')








