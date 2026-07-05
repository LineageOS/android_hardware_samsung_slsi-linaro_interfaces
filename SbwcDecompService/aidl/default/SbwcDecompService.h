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

#pragma once

#include <aidl/vendor/samsung_slsi/hardware/SbwcDecompService/BnSbwcDecompService.h>

namespace aidl {
namespace vendor {
namespace samsung_slsi {
namespace hardware {
namespace SbwcDecompService {

class SbwcDecompService : public BnSbwcDecompService {
    private:
        int32_t decodeWithCropAndFpsInternal(const aidl::android::hardware::common::NativeHandle &srcHandle, const aidl::android::hardware::common::NativeHandle &dstHandle, int32_t attr, int32_t cropWidth, int32_t cropHeight, int32_t framerate);
        int32_t decodeWithFramerateInternal(const aidl::android::hardware::common::NativeHandle &srcHandle, const aidl::android::hardware::common::NativeHandle &dstHandle, int32_t attr, int32_t framerate);

    public:
        ndk::ScopedAStatus decode(const aidl::android::hardware::common::NativeHandle &srcHandle, const aidl::android::hardware::common::NativeHandle &dstHandle, int32_t attr, int32_t* _aidl_return) override;
        ndk::ScopedAStatus decodeWithFramerate(const aidl::android::hardware::common::NativeHandle &srcHandle, const aidl::android::hardware::common::NativeHandle &dstHandle, int32_t attr, int32_t framerate, int32_t* _aidl_return) override;
        ndk::ScopedAStatus decodeWithCrop(const aidl::android::hardware::common::NativeHandle &srcHandle, const aidl::android::hardware::common::NativeHandle &dstHandle, int32_t attr, int32_t cropWidth, int32_t cropHeight, int32_t* _aidl_return) override;
        ndk::ScopedAStatus decodeWithCropAndFps(const aidl::android::hardware::common::NativeHandle &srcHandle, const aidl::android::hardware::common::NativeHandle &dstHandle, int32_t attr, int32_t cropWidth, int32_t cropHeight, int32_t framerate, int32_t* _aidl_return) override;
};

}  // namespace SbwcDecompService
}  // namespace hardware
}  // namespace samsung_slsi
}  // namespace vendor
}  // namespace aidl
