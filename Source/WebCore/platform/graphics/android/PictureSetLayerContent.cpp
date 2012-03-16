#include "config.h"
#include "PictureSetLayerContent.h"

#include "SkPicture.h"

namespace WebCore {

PictureSetLayerContent::PictureSetLayerContent(const android::PictureSet& pictureSet)
{
    m_pictureSet.set(pictureSet);
}

PictureSetLayerContent::~PictureSetLayerContent()
{
    m_pictureSet.clear();
}

void PictureSetLayerContent::draw(SkCanvas* canvas)
{
    if (!m_pictureSet.isEmpty())
        m_pictureSet.draw(canvas);
}

void PictureSetLayerContent::serialize(SkWStream* stream)
{
    if (!stream)
           return;
    SkPicture picture;
    draw(picture.beginRecording(m_pictureSet.width(), m_pictureSet.height(),
                                SkPicture::kUsePathBoundsForClip_RecordingFlag));
    picture.endRecording();
    picture.serialize(stream);
}

} // namespace WebCore