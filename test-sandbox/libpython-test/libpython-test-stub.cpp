#undef NDEBUG
#include <cassert>
#include <cstdint>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <mach-o/dyld.h>
#include <string>

namespace fs = std::filesystem;

extern "C" void *__dso_handle;
extern "C" const char *dyld_image_path_containing_address(const void *addr);

static const char *get_self_path() {
    return dyld_image_path_containing_address(&__dso_handle);
}

static std::string get_exe_path() {
    char buf[8 * 1024];
    auto buf_sz    = (uint32_t)sizeof(buf);
    const auto res = _NSGetExecutablePath(buf, &buf_sz);
    assert(!res);
    return {buf};
}

static std::string read_python_version() {
    const auto exe_path            = fs::path{get_exe_path()};
    const auto python_version_path = exe_path.parent_path() / ".python-version-test";
    auto f                         = std::ifstream{python_version_path};
    std::string version;
    assert(std::getline(f, version));
    return version;
}

static fs::path get_python_lib_path() {
    const auto version = read_python_version();
    return fs::path{get_self_path()} / ("libpython-test-" + version + ".dylib");
}

__attribute__((constructor)) void libpython_test_stub_ctor() {
    printf("libpython-test-stub ctor\n");
    printf("get_self_path: %s\n", get_self_path());
    printf("get_exe_path: %s\n", get_exe_path().c_str());
    printf("python_lib_path: %s\n", get_python_lib_path().c_str());
    read_python_version();
}

#if 0
extern "C" const char *get_python_test_version() {
    return "I'm libpython-test-stub!";
}
#endif
