/*
 * Copyright (c) 2021, the SerenityOS developers.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "qserenitystring.h"

#include <AK/StdLibExtraDetails.h>

AK::String QSerenityString::fromQString(QString const& str)
{
    // Use toStdString to retrieve guaranteed UTF-8 data (QString is UTF-16).
    auto const& std_string = str.toStdString();
    return AK::String::from_utf8({ std_string.data(), std_string.size() }).release_value();
}

QString QSerenityString::toQString(const AK::String& v)
{
    auto const utf8_bytes = v.bytes();
    // For some reason we can't safely cast fom u8 const* to char8_t const*...
    return QString::fromUtf8(AK::bit_cast<char8_t const*>(utf8_bytes.data()), utf8_bytes.size());
}
