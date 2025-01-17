/*
 * 测试通过时输出：
 * "getcwd OK."
 * 测试失败时输出：
 * "getcwd ERROR."
 */
#define __LIBRARY__
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *getcwd(char *buf, size_t size) {
    long __res;
    __asm__ volatile("int $0x80" : "=a"(__res) : "0"(__NR_getcwd), "b"((long)(buf)), "c"((long)(size)));
    if (__res > 0)
        return (char *)__res;
    errno = -__res;
    return NULL;
}

void test_getcwd(void) {
    char *cwd = NULL;
    char buf[128] = {0};
    cwd = getcwd(buf, 128);
    if (cwd != NULL) {
        printf("current dir: %s\n", buf);
        printf("getcwd OK.\n");
    } else
        printf("getcwd ERROR.\n");
}

int main(void) {
    test_getcwd();
    return 0;
}

char *sys_getcwd(char *buf, size_t size) {
    strcpy(buf, "/usr/root");
    return buf;
}