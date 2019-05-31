/*
 * Copyright (C) 2004, 2005, 2006, 2007 Nikolas Zimmermann <zimmermann@kde.org>
 * Copyright (C) 2004, 2005, 2006 Rob Buis <buis@kde.org>
 * Copyright (C) 2006 Samuel Weinig <sam.weinig@gmail.com>
 * Copyright (C) 2009 Dirk Schulze <krit@webkit.org>
 * Copyright (C) Research In Motion Limited 2010. All rights reserved.
 * Copyright (C) 2014 Adobe Systems Incorporated. All rights reserved.
 * Copyright (C) 2018 Apple Inc. All rights reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include "config.h"
#include "SVGFilterElement.h"

#include "RenderSVGResourceFilter.h"
#include "SVGFilterBuilder.h"
#include "SVGFilterPrimitiveStandardAttributes.h"
#include "SVGNames.h"
#include "SVGParserUtilities.h"
#include <wtf/IsoMallocInlines.h>
#include <wtf/NeverDestroyed.h>

namespace WebCore {

WTF_MAKE_ISO_ALLOCATED_IMPL(SVGFilterElement);

inline SVGFilterElement::SVGFilterElement(const QualifiedName& tagName, Document& document)
    : SVGElement(tagName, document)
    , SVGExternalResourcesRequired(this)
    , SVGURIReference(this)
{
    // Spec: If the x/y attribute is not specified, the effect is as if a value of "-10%" were specified.
    // Spec: If the width/height attribute is not specified, the effect is as if a value of "120%" were specified.
    ASSERT(hasTagName(SVGNames::filterTag));
    registerAttributes();
}

Ref<SVGFilterElement> SVGFilterElement::create(const QualifiedName& tagName, Document& document)
{
    return adoptRef(*new SVGFilterElement(tagName, document));
}

const AtomicString& SVGFilterElement::filterResXIdentifier()
{
    static NeverDestroyed<AtomicString> s_identifier("SVGFilterResX", AtomicString::ConstructFromLiteral);
    return s_identifier;
}

const AtomicString& SVGFilterElement::filterResYIdentifier()
{
    static NeverDestroyed<AtomicString> s_identifier("SVGFilterResY", AtomicString::ConstructFromLiteral);
    return s_identifier;
}

void SVGFilterElement::setFilterRes(unsigned filterResX, unsigned filterResY)
{
    m_filterResX.setValue(filterResX);
    m_filterResY.setValue(filterResY);

    if (RenderObject* object = renderer())
        object->setNeedsLayout();
}

void SVGFilterElement::registerAttributes()
{
    auto& registry = attributeRegistry();
    if (!registry.isEmpty())
        return;
    registry.registerAttribute<SVGNames::filterUnitsAttr, SVGUnitTypes::SVGUnitType, &SVGFilterElement::m_filterUnits>();
    registry.registerAttribute<SVGNames::primitiveUnitsAttr, SVGUnitTypes::SVGUnitType, &SVGFilterElement::m_primitiveUnits>();
    registry.registerAttribute<SVGNames::xAttr, &SVGFilterElement::m_x>();
    registry.registerAttribute<SVGNames::yAttr, &SVGFilterElement::m_y>();
    registry.registerAttribute<SVGNames::widthAttr, &SVGFilterElement::m_width>();
    registry.registerAttribute<SVGNames::heightAttr, &SVGFilterElement::m_height>();
    registry.registerAttribute<SVGNames::filterResAttr,
        &SVGFilterElement::filterResXIdentifier, &SVGFilterElement::m_filterResX,
        &SVGFilterElement::filterResYIdentifier, &SVGFilterElement::m_filterResY>();
}

void SVGFilterElement::parseAttribute(const QualifiedName& name, const AtomicString& value)
{
    SVGParsingError parseError = NoError;

    if (name == SVGNames::filterUnitsAttr) {
        SVGUnitTypes::SVGUnitType propertyValue = SVGPropertyTraits<SVGUnitTypes::SVGUnitType>::fromString(value);
        if (propertyValue > 0)
            m_filterUnits.setValue(propertyValue);
    } else if (name == SVGNames::primitiveUnitsAttr) {
        SVGUnitTypes::SVGUnitType propertyValue = SVGPropertyTraits<SVGUnitTypes::SVGUnitType>::fromString(value);
        if (propertyValue > 0)
            m_primitiveUnits.setValue(propertyValue);
    } else if (name == SVGNames::xAttr)
        m_x.setValue(SVGLengthValue::construct(LengthModeWidth, value, parseError));
    else if (name == SVGNames::yAttr)
        m_y.setValue(SVGLengthValue::construct(LengthModeHeight, value, parseError));
    else if (name == SVGNames::widthAttr)
        m_width.setValue(SVGLengthValue::construct(LengthModeWidth, value, parseError));
    else if (name == SVGNames::heightAttr)
        m_height.setValue(SVGLengthValue::construct(LengthModeHeight, value, parseError));
    else if (name == SVGNames::filterResAttr) {
        float x, y;
        if (parseNumberOptionalNumber(value, x, y)) {
            m_filterResX.setValue(x);
            m_filterResY.setValue(y);
        }
    }

    reportAttributeParsingError(parseError, name, value);

    SVGElement::parseAttribute(name, value);
    SVGURIReference::parseAttribute(name, value);
    SVGExternalResourcesRequired::parseAttribute(name, value);
}

void SVGFilterElement::svgAttributeChanged(const QualifiedName& attrName)
{
    if (isAnimatedLengthAttribute(attrName)) {
        InstanceInvalidationGuard guard(*this);
        invalidateSVGPresentationAttributeStyle();
        return;
    }

    if (isKnownAttribute(attrName) || SVGURIReference::isKnownAttribute(attrName)) {
        if (auto* renderer = this->renderer())
            renderer->setNeedsLayout();
        return;
    }

    SVGElement::svgAttributeChanged(attrName);
    SVGExternalResourcesRequired::svgAttributeChanged(attrName);
}

void SVGFilterElement::childrenChanged(const ChildChange& change)
{
    SVGElement::childrenChanged(change);

    if (change.source == ChildChangeSource::Parser)
        return;

    if (RenderObject* object = renderer())
        object->setNeedsLayout();
}

RenderPtr<RenderElement> SVGFilterElement::createElementRenderer(RenderStyle&& style, const RenderTreePosition&)
{
    return createRenderer<RenderSVGResourceFilter>(*this, WTFMove(style));
}

bool SVGFilterElement::childShouldCreateRenderer(const Node& child) const
{
    if (!child.isSVGElement())
        return false;

    const SVGElement& svgElement = downcast<SVGElement>(child);

    static NeverDestroyed<HashSet<QualifiedName>> allowedChildElementTags;
    if (allowedChildElementTags.get().isEmpty()) {
        allowedChildElementTags.get().add(SVGNames::feBlendTag);
        allowedChildElementTags.get().add(SVGNames::feColorMatrixTag);
        allowedChildElementTags.get().add(SVGNames::feComponentTransferTag);
        allowedChildElementTags.get().add(SVGNames::feCompositeTag);
        allowedChildElementTags.get().add(SVGNames::feConvolveMatrixTag);
        allowedChildElementTags.get().add(SVGNames::feDiffuseLightingTag);
        allowedChildElementTags.get().add(SVGNames::feDisplacementMapTag);
        allowedChildElementTags.get().add(SVGNames::feDistantLightTag);
        allowedChildElementTags.get().add(SVGNames::feDropShadowTag);
        allowedChildElementTags.get().add(SVGNames::feFloodTag);
        allowedChildElementTags.get().add(SVGNames::feFuncATag);
        allowedChildElementTags.get().add(SVGNames::feFuncBTag);
        allowedChildElementTags.get().add(SVGNames::feFuncGTag);
        allowedChildElementTags.get().add(SVGNames::feFuncRTag);
        allowedChildElementTags.get().add(SVGNames::feGaussianBlurTag);
        allowedChildElementTags.get().add(SVGNames::feImageTag);
        allowedChildElementTags.get().add(SVGNames::feMergeTag);
        allowedChildElementTags.get().add(SVGNames::feMergeNodeTag);
        allowedChildElementTags.get().add(SVGNames::feMorphologyTag);
        allowedChildElementTags.get().add(SVGNames::feOffsetTag);
        allowedChildElementTags.get().add(SVGNames::fePointLightTag);
        allowedChildElementTags.get().add(SVGNames::feSpecularLightingTag);
        allowedChildElementTags.get().add(SVGNames::feSpotLightTag);
        allowedChildElementTags.get().add(SVGNames::feTileTag);
        allowedChildElementTags.get().add(SVGNames::feTurbulenceTag);
    }

    return allowedChildElementTags.get().contains<SVGAttributeHashTranslator>(svgElement.tagQName());
}

}
