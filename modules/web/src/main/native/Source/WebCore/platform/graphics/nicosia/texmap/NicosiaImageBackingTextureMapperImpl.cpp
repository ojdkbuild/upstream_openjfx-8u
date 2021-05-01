/*
 * Copyright (C) 2018 Metrological Group B.V.
 * Copyright (C) 2018 Igalia S.L.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above
 *    copyright notice, this list of conditions and the following
 *    disclaimer in the documentation and/or other materials provided
 *    with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "config.h"
#include "NicosiaImageBackingTextureMapperImpl.h"

#if USE(TEXTURE_MAPPER)

namespace Nicosia {

auto ImageBackingTextureMapperImpl::createFactory() -> Factory
{
    return Factory(
        [](ImageBacking&) {
            return makeUnique<ImageBackingTextureMapperImpl>();
        });
}

ImageBackingTextureMapperImpl::ImageBackingTextureMapperImpl() = default;
ImageBackingTextureMapperImpl::~ImageBackingTextureMapperImpl() = default;

void ImageBackingTextureMapperImpl::flushUpdate()
{
    LockHolder locker(m_update.lock);

    // If the update happens for the same image and there's no buffer, keep the current one
    // so it can be received by the CoordinatedGraphicsScene. In that case we only need to update
    // the isVisible flag.
    if ((m_layerState.update.nativeImageID == m_update.update.nativeImageID) && !m_layerState.update.buffer) {
        m_update.update.isVisible = m_layerState.update.isVisible;
        return;
    }

    m_update.update = WTFMove(m_layerState.update);
}

auto ImageBackingTextureMapperImpl::takeUpdate() -> Update
{
    LockHolder locker(m_update.lock);
    return WTFMove(m_update.update);
}

} // namespace Nicosia

#endif
