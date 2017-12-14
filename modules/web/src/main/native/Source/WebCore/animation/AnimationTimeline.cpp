/*
 * Copyright (C) Canon Inc. 2016
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted, provided that the following conditions
 * are required to be met:
 *
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 * 3. Neither the name of Canon Inc. nor the names of
 * its contributors may be used to endorse or promote products derived
 * from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY CANON INC. AND ITS CONTRIBUTORS "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL CANON INC. AND ITS CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "config.h"
#include "AnimationTimeline.h"

#if ENABLE(WEB_ANIMATIONS)

#include "DocumentTimeline.h"

namespace WebCore {

AnimationTimeline::AnimationTimeline(ClassType classType)
    : m_classType(classType)
{
    // NOTE: We only have one type of subclass at the moment.
    ASSERT(classType == DocumentTimelineClass);
}

AnimationTimeline::~AnimationTimeline()
{
}

void AnimationTimeline::destroy()
{
    if (classType() == DocumentTimelineClass) {
        delete downcast<DocumentTimeline>(this);
        return;
    }

    ASSERT_NOT_REACHED();
}

void AnimationTimeline::attachAnimation(WebAnimation& animation)
{
    if (classType() == DocumentTimelineClass) {
        downcast<DocumentTimeline>(*this).attach(animation);
        return;
    }

    ASSERT_NOT_REACHED();
}

void AnimationTimeline::detachAnimation(WebAnimation& animation)
{
    if (classType() == DocumentTimelineClass) {
        downcast<DocumentTimeline>(*this).detach(animation);
        return;
    }

    ASSERT_NOT_REACHED();
}

} // namespace WebCore

#endif // ENABLE(WEB_ANIMATIONS)