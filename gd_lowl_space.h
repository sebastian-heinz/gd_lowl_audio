#ifndef GD_LOWL_SPACE_H
#define GD_LOWL_SPACE_H

#include "core/object/class_db.h"
#include "core/object/ref_counted.h"

#include "gd_lowl_audio_mixer.h"
#include "gd_lowl_error.h"
#include "gd_lowl_audio_data.h"

#include "lowl_space.h"

#include <memory>

class GdLowlSpace : public GdLowlAudioSource {
GDCLASS(GdLowlSpace, GdLowlAudioSource);
OBJ_CATEGORY("Lowl Audio");

private:
    std::shared_ptr<Lowl::Space> space;

protected:
    static void _bind_methods();

public:
    void play_audio_ex(Lowl::SpaceId p_id, double p_volume, double p_panning);

    void play_audio(Lowl::SpaceId p_id);

    void stop_audio(Lowl::SpaceId p_id);

    Lowl::SpaceId add_audio_path(const String &p_path);

    Lowl::SpaceId add_audio_data(const Ref<GdLowlAudioData> &p_audio_data);

    void set_audio_volume(Lowl::SpaceId p_id, double p_volume);
    
    void set_audio_panning(Lowl::SpaceId p_id, double p_panning);

    void reset_audio(Lowl::SpaceId p_id);

    void seek_audio_time(Lowl::SpaceId p_id, double p_seconds);

    void seek_audio_frame(Lowl::SpaceId p_id, int p_frame);

    virtual int get_audio_frames_remaining(Lowl::SpaceId p_id) const;

    virtual int get_audio_frame_position(Lowl::SpaceId p_id) const;

    GdLowlSpace();

    GdLowlSpace(int p_channel, double p_sample_rate);

    ~GdLowlSpace() = default;
};


#endif //GD_LOWL_NODE_H
