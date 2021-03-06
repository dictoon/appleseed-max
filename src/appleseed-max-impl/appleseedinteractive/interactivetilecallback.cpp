
//
// This source file is part of appleseed.
// Visit https://appleseedhq.net/ for additional information and resources.
//
// This software is released under the MIT license.
//
// Copyright (c) 2017-2018 Sergo Pogosyan, The appleseedhq Organization
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
#include "interactivetilecallback.h"

// 3ds Max headers.
#include "appleseed-max-common/_beginmaxheaders.h"
#include <bitmap.h>
#include <interactiverender.h>
#include <maxapi.h>
#include "appleseed-max-common/_endmaxheaders.h"

namespace asr = renderer;


//
// InteractiveTileCallback class implementation.
//

namespace
{
    const UINT WM_TRIGGER_CALLBACK = WM_USER + 4764;
}

InteractiveTileCallback::InteractiveTileCallback(
    Bitmap*                     bitmap,
    IIRenderMgr*                irender_manager,
    asr::IRendererController*   renderer_controller)
  : TileCallback(bitmap, nullptr)
  , m_bitmap(bitmap)
  , m_irender_manager(irender_manager)
  , m_renderer_controller(renderer_controller)
{
}

void InteractiveTileCallback::on_progressive_frame_update(
    const asr::Frame&           frame,
    const double                time,
    const std::uint64_t         samples,
    const double                samples_per_pixel,
    const std::uint64_t         samples_per_second)
{
    TileCallback::on_progressive_frame_update(
        frame,
        time,
        samples,
        samples_per_pixel,
        samples_per_second);

    // Wait until UI proc gets handled to ensure class object is valid.
    m_ui_promise = std::promise<void>();
    if (m_renderer_controller->get_status() == asr::IRendererController::ContinueRendering)
    {
        PostMessage(
            GetCOREInterface()->GetMAXHWnd(),
            WM_TRIGGER_CALLBACK,
            reinterpret_cast<UINT_PTR>(update_caller),
            reinterpret_cast<UINT_PTR>(this));
        m_ui_promise.get_future().wait();
    }
}

void InteractiveTileCallback::update_caller(UINT_PTR param_ptr)
{
    auto tile_callback = reinterpret_cast<InteractiveTileCallback*>(param_ptr);
    
    if (tile_callback->m_irender_manager->IsRendering())
        tile_callback->m_irender_manager->UpdateDisplay();

    tile_callback->m_ui_promise.set_value();
}
