#ifndef GD_LOWL_SPACE_H
#define GD_LOWL_SPACE_H

#include "core/object/class_db.h"
#include "core/object/reference.h"

#include "gd_lowl_audio_mixer.h"
#include "gd_lowl_error.h"
#include "gd_lowl_audio_data.h"

#include "lowl_space.h"

#include <memory>

class GdLowlSpace : public Reference {
GDCLASS(GdLowlSpace, Reference);
OBJ_CATEGORY("Lowl Audio");

private:
    std::unique_ptr<Lowl::Space> space;
    Ref<GdLowlAudioMixer> mixer;
    GdLowlError::Code error;

protected:
    static void _bind_methods();

public:
    void play(Lowl::SpaceId p_id);

    void stop(Lowl::SpaceId p_id);

    GdLowlError::Code get_error();

    Lowl::SpaceId add_audio_path(const String &p_path);

    Lowl::SpaceId add_audio_data(const Ref<GdLowlAudioData> &p_audio_data);

    void load();

    void set_sample_rate(Lowl::SampleRate p_sample_rate);

    void set_channel(uint16_t p_channel);

    Ref<GdLowlAudioMixer> get_mixer();

    GdLowlSpace();

    ~GdLowlSpace();
};


#endif //GD_LOWL_NODE_H
