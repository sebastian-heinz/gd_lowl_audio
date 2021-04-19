#ifndef GD_LOWL_H
#define GD_LOWL_H

#include "core/object/class_db.h"

#include "gd_lowl_driver.h"
#include "gd_lowl_error.h"
#include "gd_lowl_audio_mixer.h"
#include "gd_lowl_audio_data.h"

#include <vector>

class GdLowl : public Object {
GDCLASS(GdLowl, Object);
OBJ_CATEGORY("Lowl Audio");

private:
    static GdLowl *singleton;

private:
    std::vector<Ref<GdLowlDriver>> drivers;

protected:
    static void _bind_methods();

public:
    static GdLowl *get_singleton();

public:
    Array get_drivers();

    GdLowlError::Code init();

    GdLowlError::Code finish();

    Ref<GdLowlAudioMixer> create_mixer(double p_sample_rate, int p_channel);

    Ref<GdLowlAudioData> create_data(Array p_audio_frames, double p_sample_rate, int p_channel);

    Ref<GdLowlAudioData> create_data_from_path(String p_audio_path);

    Ref<GdLowlDevice> get_default_device() const;

    GdLowl();

    ~GdLowl();
};


#endif