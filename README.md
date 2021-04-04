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


notes
```
scons platform=osx arch=x86_64 --jobs=6
scons --clean platform=osx arch=x86_64 --jobs=6
```