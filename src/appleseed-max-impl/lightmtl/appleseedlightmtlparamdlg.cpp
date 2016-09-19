
//
// This source file is part of appleseed.
// Visit http://appleseedhq.net/ for additional information and resources.
//
// This software is released under the MIT license.
//
// Copyright (c) 2016 Francois Beaune, The appleseedhq Organization
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

// Interface header.
#include "appleseedlightmtlparamdlg.h"

// appleseed-max headers.
#include "lightmtl/appleseedlightmtl.h"

AppleseedLightMtlParamDlg::AppleseedLightMtlParamDlg(
    AppleseedLightMtl*  mtl,
    HWND                hwMtlEdit,
    IMtlParams*         imp)
  : m_mtl(mtl)
{
}

Class_ID AppleseedLightMtlParamDlg::ClassID()
{
    return AppleseedLightMtl::get_class_id();
}

void AppleseedLightMtlParamDlg::SetThing(ReferenceTarget* m)
{
    m_mtl = static_cast<AppleseedLightMtl*>(m);
}

ReferenceTarget* AppleseedLightMtlParamDlg::GetThing()
{
    return m_mtl;
}

void AppleseedLightMtlParamDlg::SetTime(TimeValue t)
{
}

void AppleseedLightMtlParamDlg::ReloadDialog()
{
}

void AppleseedLightMtlParamDlg::DeleteThis()
{
    delete this;
}

void AppleseedLightMtlParamDlg::ActivateDlg(BOOL onOff)
{
}