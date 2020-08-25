#include <glog/logging.h>
#include <sys/types.h>
#include <sys/time.h>
#include <time.h>
#include <sys/syscall.h>
#include <sys/utsname.h>

extern "C" {
    pid_t getpid(void)
    {
        return 42;
    }

    int getpwuid_r(uid_t uid, struct passwd *pwd,
                   char *buf, size_t buflen, struct passwd **result)
    {
        return 42;
    }

    int gettimeofday(struct timeval *tv, struct timezone *tz)
    {
        tv->tv_sec = 42;
        tv->tv_usec = 42;
        return 0;
    }

    struct tm *localtime_r(const time_t *timep, struct tm *result)
    {
        result->tm_sec = 42;
        result->tm_min = 42;
        result->tm_hour = 22;
        result->tm_mday = 22;
        result->tm_mon = 11;
        result->tm_year = 42;
        result->tm_wday = 1;
        result->tm_yday = 222;
        result->tm_isdst = 0;
        return result;
    }

    // TODO: number should be long according to man page, but tis-kernel
    // header says int
    long syscall(int number, ...)
    {
        printf("TIS_syscall: %d\n", number);
        return 0;
    }

    int uname(struct utsname *buf) {
        struct utsname tis_uname = {
            "TIS system",
            "TIS nodename",
            "TIS release",
            "TIS version",
            "TIS machine"
        };
        *buf = tis_uname;
        return 0;
    }

}

int main(int argc, char* argv[]) {

    // Initialize Google's logging library.
    google::InitGoogleLogging(argv[0]);
    int num_cookies = 42;
    LOG(INFO) << "Found " << num_cookies << " cookies";
}
