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

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "SbwcDecompService"

#include <android/binder_manager.h>
#include <android/binder_process.h>
#include <log/log.h>
#include <android-base/logging.h>

#include "SbwcDecompService.h"

using ::aidl::vendor::samsung_slsi::hardware::SbwcDecompService::SbwcDecompService;

int main() {
    ALOGD("SbwcDecompService start");
    ABinderProcess_setThreadPoolMaxThreadCount(0);
    std::shared_ptr<SbwcDecompService> service = ndk::SharedRefBase::make<SbwcDecompService>();

    const std::string instance = std::string() + SbwcDecompService::descriptor + "/default";
    binder_status_t status = AServiceManager_addService(service->asBinder().get(), instance.c_str());
    CHECK(status == STATUS_OK);

    ABinderProcess_joinThreadPool();
    return EXIT_FAILURE;  // should not reach
}
