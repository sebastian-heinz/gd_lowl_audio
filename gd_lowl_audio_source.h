#ifndef GD_LOWL_AUDIO_SOURCE_H
#define GD_LOWL_AUDIO_SOURCE_H

#include "core/object/class_db.h"
#include "core/object/ref_counted.h"

#include "audio/lowl_audio_sample_format.h"
#include "audio/lowl_audio_source.h"

#include <memory>

class GdLowlAudioSource : public RefCounted {
GDCLASS(GdLowlAudioSource, RefCounted);
OBJ_CATEGORY("Lowl Audio");

public:
    enum SampleFormat {
        Unknown = (int) Lowl::Audio::SampleFormat::Unknown,
        FLOAT_32 = (int) Lowl::Audio::SampleFormat::FLOAT_32,
        FLOAT_64 = (int) Lowl::Audio::SampleFormat::FLOAT_64,
        INT_32 = (int) Lowl::Audio::SampleFormat::INT_32,
        INT_24 = (int) Lowl::Audio::SampleFormat::INT_24,
        INT_16 = (int) Lowl::Audio::SampleFormat::INT_16,
        INT_8 = (int) Lowl::Audio::SampleFormat::INT_8,
        U_INT_8 = (int) Lowl::Audio::SampleFormat::U_INT_8,
    };

private:
    std::shared_ptr<Lowl::Audio::AudioSource> audio_source;

protected:
    static void _bind_methods();

public:
    static SampleFormat convert_sample_format(Lowl::Audio::SampleFormat sample_format);

    static Lowl::Audio::SampleFormat convert_sample_format(SampleFormat sample_format);

    SampleFormat get_sample_format() const;

    double get_sample_rate() const;

    int get_channel() const;

    void set_volume(double p_volume);

    double get_volume();

    void set_panning(double p_panning);

    double get_panning();

    void pause();

    bool is_pause();

    void play();

    bool is_play();

    int get_frames_remaining();

    int get_frame_position();

    std::shared_ptr<Lowl::Audio::AudioSource> get_audio_source() const;

    GdLowlAudioSource(std::shared_ptr<Lowl::Audio::AudioSource> p_audio_source);

    virtual ~GdLowlAudioSource() = default;
};

VARIANT_ENUM_CAST(GdLowlAudioSource::SampleFormat)

#endif //GD_LOWL_AUDIO_SOURCE_H
