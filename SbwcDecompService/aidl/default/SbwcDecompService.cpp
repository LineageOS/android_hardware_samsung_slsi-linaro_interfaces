/*
 * Copyright Samsung Electronics Co.,LTD.
 * Copyright (C) 2016 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <aidlcommonsupport/NativeHandle.h>
#include <memory>
#include <mutex>

#define ATRACE_TAG ATRACE_TAG_GRAPHICS
#include <utils/Trace.h>

#include <ExynosGraphicBuffer.h>
#include <hardware/exynos/sbwcwrapper.h>
#include "SbwcDecompService.h"

#define DEFAULT_FRAMERATE   1000

namespace aidl {
namespace vendor {
namespace samsung_slsi {
namespace hardware {
namespace SbwcDecompService {

using ::vendor::graphics::ExynosGraphicBufferMeta;

int32_t SbwcDecompService::decodeWithCropAndFpsInternal(const aidl::android::hardware::common::NativeHandle &srcHandle, const aidl::android::hardware::common::NativeHandle &dstHandle,
                                                           int32_t attr, int32_t cropWidth, int32_t cropHeight, int32_t framerate)
{
    static std::mutex mDecompMutex;

    ATRACE_CALL();

    std::lock_guard<std::mutex> lock(mDecompMutex);

    static SbwcWrapper *decoder;

    if (!decoder) {
        decoder = new SbwcWrapper();
        if (!decoder)
            return ::android::NO_MEMORY;
    }

    native_handle_t *srcBH = ::android::makeFromAidl(srcHandle);
    if (!srcBH)
        return ::android::BAD_VALUE;

    native_handle_t *dstBH = ::android::makeFromAidl(dstHandle);
    if (!dstBH) {
        native_handle_delete(srcBH);
        return ::android::BAD_VALUE;
    }

    bool ret = decoder->decode(static_cast<void*>(srcBH), static_cast<void*>(dstBH), attr, cropWidth, cropHeight, framerate);

    native_handle_delete(srcBH);
    native_handle_delete(dstBH);

    if (!ret) {
        ALOGE("decode is failed");
        return ::android::BAD_VALUE;
    }

    return ::android::NO_ERROR;
}

int32_t SbwcDecompService::decodeWithFramerateInternal(const aidl::android::hardware::common::NativeHandle &srcHandle, const aidl::android::hardware::common::NativeHandle &dstHandle,
                                                       int32_t attr, int32_t framerate)
{
    native_handle_t *nh = ::android::makeFromAidl(srcHandle);

    if (!nh)
        return ::android::BAD_VALUE;

    buffer_handle_t srcBH = static_cast<buffer_handle_t>(nh);

    int32_t ret = decodeWithCropAndFpsInternal(srcHandle, dstHandle, attr,
                                static_cast<unsigned int>(ExynosGraphicBufferMeta::get_width(srcBH)),
                                static_cast<unsigned int>(ExynosGraphicBufferMeta::get_height(srcBH)), framerate);
    
    native_handle_delete(nh);
    return ret;
}

ndk::ScopedAStatus SbwcDecompService::decode(const aidl::android::hardware::common::NativeHandle &srcHandle, const aidl::android::hardware::common::NativeHandle &dstHandle,
                                          int32_t attr, int32_t* _aidl_return)
{
    *_aidl_return = decodeWithFramerateInternal(srcHandle, dstHandle, attr, DEFAULT_FRAMERATE);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus SbwcDecompService::decodeWithFramerate(const aidl::android::hardware::common::NativeHandle &srcHandle, const aidl::android::hardware::common::NativeHandle &dstHandle,
                                                       int32_t attr, int32_t framerate, int32_t* _aidl_return)
{
    *_aidl_return = decodeWithFramerateInternal(srcHandle, dstHandle, attr, framerate);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus SbwcDecompService::decodeWithCrop(const aidl::android::hardware::common::NativeHandle &srcHandle, const aidl::android::hardware::common::NativeHandle &dstHandle,
                                                    int32_t attr, int32_t cropWidth, int32_t cropHeight, int32_t* _aidl_return)
{
    *_aidl_return = decodeWithCropAndFpsInternal(srcHandle, dstHandle, attr, cropWidth, cropHeight, DEFAULT_FRAMERATE);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus SbwcDecompService::decodeWithCropAndFps(const aidl::android::hardware::common::NativeHandle &srcHandle, const aidl::android::hardware::common::NativeHandle &dstHandle,
                                                           int32_t attr, int32_t cropWidth, int32_t cropHeight, int32_t framerate, int32_t* _aidl_return)
{
    *_aidl_return = decodeWithCropAndFpsInternal(srcHandle, dstHandle, attr, cropWidth, cropHeight, framerate);
    return ndk::ScopedAStatus::ok();
}

}  // namespace SbwcDecompService
}  // namespace hardware
}  // namespace samsung_slsi
}  // namespace vendor
}  // namespace aidl
