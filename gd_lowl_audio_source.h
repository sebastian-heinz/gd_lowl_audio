#ifndef GD_LOWL_AUDIO_SOURCE_H
#define GD_LOWL_AUDIO_SOURCE_H

#include "core/object/class_db.h"
#include "core/object/reference.h"

#include "lowl_sample_format.h"
#include "lowl_audio_source.h"

class GdLowlAudioSource : public Reference {
GDCLASS(GdLowlAudioSource, Reference);
OBJ_CATEGORY("Lowl Audio");

public:
    enum SampleFormat {
        Unknown = (int) Lowl::SampleFormat::Unknown,
        FLOAT_32 = (int) Lowl::SampleFormat::FLOAT_32,
        FLOAT_64 = (int) Lowl::SampleFormat::FLOAT_64,
        INT_32 = (int) Lowl::SampleFormat::INT_32,
        INT_24 = (int) Lowl::SampleFormat::INT_24,
        INT_16 = (int) Lowl::SampleFormat::INT_16,
        INT_8 = (int) Lowl::SampleFormat::INT_8,
        U_INT_8 = (int) Lowl::SampleFormat::U_INT_8,
    };

private:
    std::shared_ptr<Lowl::AudioSource> audio_source;

protected:
    static void _bind_methods();

public:
    static SampleFormat convert_sample_format(Lowl::SampleFormat sample_format);

    static Lowl::SampleFormat convert_sample_format(SampleFormat sample_format);

    SampleFormat get_sample_format() const;

    double get_sample_rate() const;

    int get_channel() const;

    std::shared_ptr<Lowl::AudioSource> get_audio_source() const;

    GdLowlAudioSource(std::shared_ptr<Lowl::AudioSource> p_audio_source);

    virtual ~GdLowlAudioSource() = default;
};

VARIANT_ENUM_CAST(GdLowlAudioSource::SampleFormat)

#endif //GD_LOWL_AUDIO_SOURCE_H
