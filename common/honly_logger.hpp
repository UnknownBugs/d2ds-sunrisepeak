#ifndef __LOGGER_HPP__HONLY
#define __LOGGER_HPP__HONLY

#include <cstdio>

#ifndef HONLY_LOGGER_TAG
#define HONLY_LOGGER_TAG "HONLY"
#endif

#define LOG_ENABLE true
#define _HONLY_LOG(fd, ...) if (LOG_ENABLE) fprintf (fd, __VA_ARGS__); fprintf (fd, "\033[0m\n")
#define HONLY_LOGI(...) fprintf (stdout, "\033[32m[%s LOGI]: \t%s: %s:%d - ", HONLY_LOGGER_TAG, __func__, __FILE__, __LINE__); _HONLY_LOG(stdout, __VA_ARGS__)
#define HONLY_LOGD(...) fprintf (stdout, "\033[37m[%s LOGD]: \t%s: %s:%d - ", HONLY_LOGGER_TAG, __func__, __FILE__, __LINE__); _HONLY_LOG(stdout, __VA_ARGS__)
#define HONLY_LOGW(...) fprintf (stdout, "\033[33m[%s LOGW]: \t%s: %s:%d - ", HONLY_LOGGER_TAG, __func__, __FILE__, __LINE__); _HONLY_LOG(stdout, __VA_ARGS__)
#define HONLY_LOGE(...) fprintf (stderr, "\033[31m[%s LOGE]: \t%s: %s:%d - ", HONLY_LOGGER_TAG, __func__, __FILE__, __LINE__); _HONLY_LOG(stderr, __VA_ARGS__)

#endif