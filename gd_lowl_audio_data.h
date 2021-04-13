#ifndef GD_LOWL_AUDIO_DATA_H
#define GD_LOWL_AUDIO_DATA_H

#include "core/object/class_db.h"
#include "core/object/reference.h"

#include "gd_lowl_error.h"
#include "gd_lowl_audio_source.h"

#include "lowl_audio_data.h"

#include <memory>

class GdLowlAudioData : public GdLowlAudioSource {
GDCLASS(GdLowlAudioData, GdLowlAudioSource);

private:
    std::shared_ptr<Lowl::AudioData> audio_data;

    static std::vector<Lowl::AudioFrame> convert_frames(Array p_audio_frames, int p_channel);

protected:
    static void _bind_methods();

public:
    std::shared_ptr<Lowl::AudioData> get_audio_data() const;

    GdLowlAudioData();

    GdLowlAudioData(std::shared_ptr<Lowl::AudioData> p_audio_data);

    GdLowlAudioData(Array p_audio_frames, double p_sample_rate, int p_channel);

    void cancel_read();

    void reset_read();

    ~GdLowlAudioData() = default;
};


#endif //GD_LOWL_AUDIO_DATA_H
