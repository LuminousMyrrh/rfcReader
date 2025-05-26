#pragma once
#include <spdlog/spdlog.h>
#include <spdlog/async.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h>
class Logger {
public:
    // Compile-time log level configuration
    static constexpr spdlog::level::level_enum CompileTimeLogLevel = spdlog::level::info;

    // Initialize the logger (called automatically on first use)
    static void init() {
        static bool initialized = false;
        if (initialized) return;

        // Create sinks
        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        console_sink->set_level(spdlog::level::trace); // Allow all levels to pass to sink
        console_sink->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%^%l%$] %v");

        // Rotating file sink: 5MB per file, max 3 files
        auto file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
            "logs/my_project.log", 1024 * 1024 * 5, 3);
        file_sink->set_level(spdlog::level::trace);
        file_sink->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%^%l%$] %v");

        // Create asynchronous logger with a thread pool
        spdlog::init_thread_pool(8192, 1); // Queue size: 8192, 1 thread
        auto logger = std::make_shared<spdlog::async_logger>(
            "my_project",
            std::initializer_list<spdlog::sink_ptr>{console_sink, file_sink},
            spdlog::thread_pool(),
            spdlog::async_overflow_policy::block // Block on queue full
        );

        logger->set_level(spdlog::level::trace); // Allow all levels to pass to logger
        spdlog::set_default_logger(logger);

        initialized = true;
    }

    // Log functions with compile-time level checking
    template<typename... Args>
    static void trace(fmt::format_string<Args...> fmt, Args&&... args) {
        if constexpr (CompileTimeLogLevel <= spdlog::level::trace) {
            init();
            spdlog::trace(fmt, std::forward<Args>(args)...);
        }
    }

    template<typename... Args>
    static void debug(fmt::format_string<Args...> fmt, Args&&... args) {
        if constexpr (CompileTimeLogLevel <= spdlog::level::debug) {
            init();
            spdlog::debug(fmt, std::forward<Args>(args)...);
        }
    }

    template<typename... Args>
    static void info(fmt::format_string<Args...> fmt, Args&&... args) {
        if constexpr (CompileTimeLogLevel <= spdlog::level::info) {
            init();
            spdlog::info(fmt, std::forward<Args>(args)...);
        }
    }

    template<typename... Args>
    static void warn(fmt::format_string<Args...> fmt, Args&&... args) {
        if constexpr (CompileTimeLogLevel <= spdlog::level::warn) {
            init();
            spdlog::warn(fmt, std::forward<Args>(args)...);
        }
    }

    template<typename... Args>
    static void error(fmt::format_string<Args...> fmt, Args&&... args) {
        if constexpr (CompileTimeLogLevel <= spdlog::level::err) {
            init();
            spdlog::error(fmt, std::forward<Args>(args)...);
        }
    }

    template<typename... Args>
    static void critical(fmt::format_string<Args...> fmt, Args&&... args) {
        if constexpr (CompileTimeLogLevel <= spdlog::level::critical) {
            init();
            spdlog::critical(fmt, std::forward<Args>(args)...);
        }
    }

    // Set runtime log level (overrides compile-time level for more verbosity)
    static void set_level(spdlog::level::level_enum level) {
        init();
        spdlog::set_level(level);
    }

private:
    Logger() = delete; // Prevent instantiation
};
