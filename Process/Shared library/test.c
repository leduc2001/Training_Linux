#include <stdio.h>
#include <dlfcn.h>
    
int main() {
    // Mở shared library
    void *handle = dlopen("/usr/lib/lib_hello.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "Error: %s\n", dlerror());
        return 1;
    }
    
    // Lấy con trỏ tới hàm hello_world từ thư viện
    void (*hello_world)();
    hello_world = dlsym(handle, "hello_world");
    
    // Kiểm tra lỗi khi lấy con trỏ
    char *error = dlerror();
    if (error != NULL) {
        fprintf(stderr, "Error: %s\n", error);
        return 1;
    }
    
    // Gọi hàm hello_world
    hello_world();
    
    // Đóng thư viện
    dlclose(handle);
    
    return 0;
}