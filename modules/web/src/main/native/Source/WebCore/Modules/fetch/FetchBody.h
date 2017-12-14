/*
 * Copyright (C) 2016 Canon Inc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted, provided that the following conditions
 * are required to be met:
 *
 * 1.  Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 * 2.  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 * 3.  Neither the name of Canon Inc. nor the names of
 *     its contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
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

#pragma once

#if ENABLE(FETCH_API)

#include "Blob.h"
#include "FetchBodyConsumer.h"
#include "FetchLoader.h"
#include "FormData.h"
#include "JSDOMPromise.h"
#include "URLSearchParams.h"
#include <wtf/Optional.h>
#include <wtf/Variant.h>

namespace JSC {
class ExecState;
class JSValue;
};

namespace WebCore {

class FetchBodyOwner;
class FetchResponseSource;
class ScriptExecutionContext;

class FetchBody {
public:
    void arrayBuffer(FetchBodyOwner&, Ref<DeferredPromise>&&);
    void blob(FetchBodyOwner&, Ref<DeferredPromise>&&, const String&);
    void json(FetchBodyOwner&, Ref<DeferredPromise>&&);
    void text(FetchBodyOwner&, Ref<DeferredPromise>&&);
    void formData(FetchBodyOwner&, Ref<DeferredPromise>&& promise) { promise.get().reject(0); }

#if ENABLE(READABLE_STREAM_API)
    void consumeAsStream(FetchBodyOwner&, FetchResponseSource&);
#endif

    bool isBlob() const { return WTF::holds_alternative<Ref<const Blob>>(m_data); }
    bool isFormData() const { return WTF::holds_alternative<Ref<FormData>>(m_data); }
    bool isArrayBuffer() const { return WTF::holds_alternative<Ref<const ArrayBuffer>>(m_data); }
    bool isArrayBufferView() const { return WTF::holds_alternative<Ref<const ArrayBufferView>>(m_data); }
    bool isURLSearchParams() const { return WTF::holds_alternative<Ref<const URLSearchParams>>(m_data); }
    bool isText() const { return WTF::holds_alternative<String>(m_data); }
    bool isReadableStream() const { return m_isReadableStream; }

    static std::optional<FetchBody> extract(ScriptExecutionContext&, JSC::ExecState&, JSC::JSValue, String&);
    static FetchBody loadingBody() { return { }; }

    void loadingFailed();
    void loadingSucceeded();

    RefPtr<FormData> bodyForInternalRequest(ScriptExecutionContext&) const;

    FetchBodyConsumer& consumer() { return m_consumer; }

    void consumeOnceLoadingFinished(FetchBodyConsumer::Type, Ref<DeferredPromise>&&);
    void cleanConsumePromise() { m_consumePromise = nullptr; }

    FetchBody clone() const;

private:
    explicit FetchBody(Ref<const Blob>&& data) : m_data(WTFMove(data)) { }
    explicit FetchBody(Ref<const ArrayBuffer>&& data) : m_data(WTFMove(data)) { }
    explicit FetchBody(Ref<const ArrayBufferView>&& data) : m_data(WTFMove(data)) { }
    explicit FetchBody(Ref<FormData>&& data) : m_data(WTFMove(data)) { }
    explicit FetchBody(String&& data) : m_data(WTFMove(data)) { }
    explicit FetchBody(Ref<const URLSearchParams>&& data) : m_data(WTFMove(data)) { }
    explicit FetchBody(const FetchBodyConsumer& consumer) : m_consumer(consumer) { }
    FetchBody() = default;

    void consume(FetchBodyOwner&, Ref<DeferredPromise>&&);

    void consumeArrayBuffer(Ref<DeferredPromise>&&);
    void consumeArrayBufferView(Ref<DeferredPromise>&&);
    void consumeText(Ref<DeferredPromise>&&, const String&);
    void consumeBlob(FetchBodyOwner&, Ref<DeferredPromise>&&);

    const Blob& blobBody() const { return WTF::get<Ref<const Blob>>(m_data).get(); }
    FormData& formDataBody() { return WTF::get<Ref<FormData>>(m_data).get(); }
    const FormData& formDataBody() const { return WTF::get<Ref<FormData>>(m_data).get(); }
    const ArrayBuffer& arrayBufferBody() const { return WTF::get<Ref<const ArrayBuffer>>(m_data).get(); }
    const ArrayBufferView& arrayBufferViewBody() const { return WTF::get<Ref<const ArrayBufferView>>(m_data).get(); }
    String& textBody() { return WTF::get<String>(m_data); }
    const String& textBody() const { return WTF::get<String>(m_data); }
    const URLSearchParams& urlSearchParamsBody() const { return WTF::get<Ref<const URLSearchParams>>(m_data).get(); }

    Variant<std::nullptr_t, Ref<const Blob>, Ref<FormData>, Ref<const ArrayBuffer>, Ref<const ArrayBufferView>, Ref<const URLSearchParams>, String> m_data { nullptr };

    FetchBodyConsumer m_consumer { FetchBodyConsumer::Type::None };
    RefPtr<DeferredPromise> m_consumePromise;

    // FIXME: We probably want to keep the stream as a specific field in m_data when we will support stream data upload.
    bool m_isReadableStream { false };
};

} // namespace WebCore

#endif // ENABLE(FETCH_API)
