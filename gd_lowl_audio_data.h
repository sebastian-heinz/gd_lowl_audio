#ifndef GD_LOWL_AUDIO_DATA_H
#define GD_LOWL_AUDIO_DATA_H

#include "core/object/class_db.h"
#include "core/object/reference.h"

#include "gd_lowl_error.h"

#include "lowl_audio_data.h"

#include <memory>

class GdLowlAudioData : public Reference {
GDCLASS(GdLowlAudioData, Reference);

private:
    std::unique_ptr<Lowl::AudioData> audio_data;

protected:
    static void _bind_methods();

public:
    GdLowlAudioData();

    ~GdLowlAudioData();

};


#endif //GD_LOWL_AUDIO_DATA_H
