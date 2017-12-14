/*
 * Copyright (C) 2009 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "config.h"
#include "JSExceptionBase.h"

#include "JSDOMCoreException.h"
#include "JSEventException.h"
#include "JSRangeException.h"
#include "JSSQLException.h"
#include "JSSVGException.h"
#include "JSXMLHttpRequestException.h"
#include "JSXPathException.h"
#include "SQLException.h"

namespace WebCore {

ExceptionBase* toExceptionBase(JSC::JSValue value)
{
    if (DOMCoreException* domException = JSDOMCoreException::toWrapped(value))
        return reinterpret_cast<ExceptionBase*>(domException);
    if (RangeException* rangeException = JSRangeException::toWrapped(value))
        return reinterpret_cast<ExceptionBase*>(rangeException);
    if (EventException* eventException = JSEventException::toWrapped(value))
        return reinterpret_cast<ExceptionBase*>(eventException);
    if (XMLHttpRequestException* xmlHttpException = JSXMLHttpRequestException::toWrapped(value))
        return reinterpret_cast<ExceptionBase*>(xmlHttpException);
    if (SVGException* svgException = JSSVGException::toWrapped(value))
        return reinterpret_cast<ExceptionBase*>(svgException);
    if (XPathException* pathException = JSXPathException::toWrapped(value))
        return reinterpret_cast<ExceptionBase*>(pathException);
    if (SQLException* pathException = JSSQLException::toWrapped(value))
        return reinterpret_cast<ExceptionBase*>(pathException);

    return 0;
}

} // namespace WebCore
