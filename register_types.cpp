#include "register_types.h"

#include "gd_lowl.h"
#include "gd_lowl_error.h"
#include "gd_lowl_driver.h"
#include "gd_lowl_device.h"
#include "gd_lowl_node.h"
#include "gd_lowl_space.h"
#include "gd_lowl_audio_mixer.h"
#include "gd_lowl_audio_data.h"
#include "gd_lowl_audio_source.h"

#include <core/config/engine.h>

static GdLowl *gd_lowl = nullptr;

void initialize_gd_lowl_audio_module(ModuleInitializationLevel p_level) {

    if (p_level == MODULE_INITIALIZATION_LEVEL_CORE) {
        gd_lowl = memnew(GdLowl);
        ClassDB::register_class<GdLowl>();
        Engine::get_singleton()->add_singleton(Engine::Singleton("GdLowl", GdLowl::get_singleton()));

        ClassDB::register_class<GdLowlError>();

        ClassDB::register_class<GdLowlDriver>();
        ClassDB::register_class<GdLowlDevice>();

        ClassDB::register_abstract_class<GdLowlAudioSource>();
        ClassDB::register_class<GdLowlAudioMixer>();
        ClassDB::register_class<GdLowlAudioData>();

        ClassDB::register_class<GdLowlSpace>();

        ClassDB::register_class<GdLowlNode>();
    }
}

void uninitialize_gd_lowl_audio_module(ModuleInitializationLevel p_level) {
    if (p_level == MODULE_INITIALIZATION_LEVEL_CORE) {
        memdelete(gd_lowl);
    }
}
