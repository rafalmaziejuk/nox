// Copyright 2025 Rafal Maziejuk
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/**
 * @file
 * @brief Logging definitions
 */

#pragma once

#include <cstdint>
#include <functional>
#include <string_view>

namespace nox {

/**
 * @enum LogLevel
 * @brief Represents different levels of logging.
 */
enum class LogLevel : uint8_t {
    k_Trace, ///< Tracing messages
    k_Debug, ///< Debugging messages
    k_Info,  ///< Informational messages
    k_Warn,  ///< Warning messages
    k_Error, ///< Error messages
};

/**
 * @typedef LogCallback
 * @brief Defines a callback function type for logging.
 *
 * @param[in] LogLevel Severity of the log
 * @param[in] std::string_view Channel name
 * @param[in] std::string_view Log message
 */
using LogCallback = std::function<void(LogLevel, std::string_view, std::string_view)>;

/**
 * @brief Registers a callback function for logging.
 *
 * @param[in] callback Function to be called whenever a log event occurs
 *
 * @note If `NOX_ENABLE_LOGGING` is `OFF` then registered callback will never be called.
 * @note Has to be called before any other NOX function.
 */
void registerLogCallback(LogCallback &&callback);

} // namespace nox
