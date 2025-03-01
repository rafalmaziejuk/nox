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
 * @brief Internal logging definitions
 */

#pragma once

#include <nox/log.h>

#include <format>

// clang-format off
#if defined(NOX_ENABLE_LOGGING)
    #define NOX_LOG_TRACE(channel, message, ...) nox::Logger::instance().log(nox::LogLevel::k_Trace, #channel, message, ##__VA_ARGS__)
    #define NOX_LOG_DEBUG(channel, message, ...) nox::Logger::instance().log(nox::LogLevel::k_Debug, #channel, message, ##__VA_ARGS__)
    #define NOX_LOG_INFO(channel, message, ...) nox::Logger::instance().log(nox::LogLevel::k_Info, #channel, message, ##__VA_ARGS__)
    #define NOX_LOG_WARN(channel, message, ...) nox::Logger::instance().log(nox::LogLevel::k_Warn, #channel, message, ##__VA_ARGS__)
    #define NOX_LOG_ERROR(channel, message, ...) nox::Logger::instance().log(nox::LogLevel::k_Error, #channel, message, ##__VA_ARGS__)
#else
    #define NOX_LOG_TRACE(channel, message, ...)
    #define NOX_LOG_DEBUG(channel, message, ...)
    #define NOX_LOG_INFO(channel, message, ...)
    #define NOX_LOG_WARN(channel, message, ...)
    #define NOX_LOG_ERROR(channel, message, ...)
#endif
// clang-format on 

namespace nox {

/**
 * @class Logger
 * @brief A singleton logger class that provides logging functionality for internal usage.
 * 
 * This class allows logging messages with different log levels and channels.
 * It is used in pair with logging macros.
 *
 * @note Requires a registered log callback before first use.
 * @see registerLogCallback
 */
class Logger {
  public:
    /**
     * @brief Gets the instance of the Logger.
     * 
     * @return Logger& Reference to the singleton instance of the Logger.
     */
    static Logger &instance();

    /**
     * @brief Invokes registered log callback with a specific log level, channel and formatted message.
     * 
     * @tparam Args Types of the arguments used for formatting the message
     * @param[in] logLevel Log level of the message
     * @param[in] channel Channel or category under which the log is recorded
     * @param[in] message Message to log, which may contain format specifiers
     * @param[in] args Arguments used to replace the format specifiers in the message
     */
    template <typename... Args>
    void log(LogLevel logLevel, std::string_view channel, std::string_view message, Args &&...args) {
        if (m_callback) {
            std::string formattedMessage = std::vformat(message, std::make_format_args(args...));
            m_callback(logLevel, channel, formattedMessage);
        }
    }

    /**
     * @brief Declares the `registerLogCallback` function as a friend to the Logger.
     */
    friend void registerLogCallback(LogCallback &&callback);

  public:
    Logger(Logger &&) = delete;
    Logger(const Logger &) = delete;
    Logger &operator=(Logger &&) = delete;
    Logger &operator=(const Logger &) = delete;

  private:
    Logger() = default;
    ~Logger() = default;

  private:
    LogCallback m_callback; ///< Callback function used for logging messages
};

} // namespace nox
