namespace Log {
    typedef enum {
        INFO = 0, WARNING = 1, FATAL = 2
    } LogLevel;

    void Log(LogLevel level, const char* format, ...);
    void LogWinApi(LogLevel level);
    void LogCal3d(LogLevel level);
    void PrintBuffer(char* buffer, int size);
}
