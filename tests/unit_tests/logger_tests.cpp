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

#undef NOX_ENABLE_LOGGING
#define NOX_ENABLE_LOGGING
#include "src/common/logger.h"

#include <gtest/gtest.h>

using namespace nox;

class LoggerTests : public ::testing::Test {
  protected:
    void TearDown() override {
        registerLogCallback(nullptr);
    }
};

TEST_F(LoggerTests, WhenRegisterLogCallbackIsCalledThenLogCallbackIsUsed) {
    LogLevel logLevel{};
    std::string channel{};
    std::string message{};
    auto logCallback = [&](LogLevel logLevel_, std::string_view channel_, std::string_view message_) -> void {
        logLevel = logLevel_;
        channel = channel_;
        message = message_;
    };
    registerLogCallback(logCallback);

    // Trace
    {
        constexpr auto expectedLogLevel = LogLevel::k_Trace;
        constexpr auto expectedChannel = "trace";
        constexpr auto expectedMessage = "0";

        NOX_LOG_TRACE(trace, "{}", static_cast<uint8_t>(expectedLogLevel));

        EXPECT_EQ(expectedLogLevel, logLevel);
        EXPECT_EQ(expectedChannel, channel);
        EXPECT_EQ(expectedMessage, message);
    }

    // Debug
    {
        constexpr auto expectedLogLevel = LogLevel::k_Debug;
        constexpr auto expectedChannel = "debug";
        constexpr auto expectedMessage = "1";

        NOX_LOG_DEBUG(debug, "{}", static_cast<uint8_t>(expectedLogLevel));

        EXPECT_EQ(expectedLogLevel, logLevel);
        EXPECT_EQ(expectedChannel, channel);
        EXPECT_EQ(expectedMessage, message);
    }

    // Info
    {
        constexpr auto expectedLogLevel = LogLevel::k_Info;
        constexpr auto expectedChannel = "info";
        constexpr auto expectedMessage = "2";

        NOX_LOG_INFO(info, "{}", static_cast<uint8_t>(expectedLogLevel));

        EXPECT_EQ(expectedLogLevel, logLevel);
        EXPECT_EQ(expectedChannel, channel);
        EXPECT_EQ(expectedMessage, message);
    }

    // Warn
    {
        constexpr auto expectedLogLevel = LogLevel::k_Warn;
        constexpr auto expectedChannel = "warn";
        constexpr auto expectedMessage = "3";

        NOX_LOG_WARN(warn, "{}", static_cast<uint8_t>(expectedLogLevel));

        EXPECT_EQ(expectedLogLevel, logLevel);
        EXPECT_EQ(expectedChannel, channel);
        EXPECT_EQ(expectedMessage, message);
    }

    // Error
    {
        constexpr auto expectedLogLevel = LogLevel::k_Error;
        constexpr auto expectedChannel = "error";
        constexpr auto expectedMessage = "4";

        NOX_LOG_ERROR(error, "{}", static_cast<uint8_t>(expectedLogLevel));

        EXPECT_EQ(expectedLogLevel, logLevel);
        EXPECT_EQ(expectedChannel, channel);
        EXPECT_EQ(expectedMessage, message);
    }
}

TEST_F(LoggerTests, WhenRegisterLogCallbackIsNotCalledThenLogCallbackIsNotUsed) {
    auto &logger = Logger::instance();
    bool logCallbackCalled = false;
    auto logCallback = [&logCallbackCalled](LogLevel logLevel_, std::string_view channel_, std::string_view message_) -> void {
        logCallbackCalled = true;
    };

    logger.log(LogLevel::k_Trace, "", "");

    EXPECT_FALSE(logCallbackCalled);
}

TEST_F(LoggerTests, WhenLoggerInstanceIsCalledThenTheSameLoggerInstanceIsReturned) {
    auto &logger1 = Logger::instance();
    auto &logger2 = Logger::instance();

    EXPECT_EQ(&logger1, &logger2);
}

TEST_F(LoggerTests, WhenLoggerLogIsCalledThenMessageIsFormattedCorrectly) {
    constexpr auto expectedFormat = "Formatted message: {}";
    constexpr auto expectedMessage = "Formatted message: 42";
    constexpr auto expectedParameter = 42;

    std::string message{};
    auto logCallback = [&message](LogLevel logLevel_, std::string_view channel_, std::string_view message_) -> void {
        message = message_;
    };
    registerLogCallback(logCallback);

    Logger::instance().log(LogLevel::k_Trace, "", expectedFormat, expectedParameter);

    EXPECT_EQ(expectedMessage, message);
}
