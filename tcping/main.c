/**********************************************************************************************************************
 *                                                                                                                    *
 * main.c                                                                                                             *
 * Fu Xuanming (2022-2023)                                                                                            *
 *                                                                                                                    *
 **********************************************************************************************************************
 * 
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


/**********************************************************************************************************************
 * Function                                                                                                           *
 **********************************************************************************************************************
 */
void usage(void) {
    puts("Usage: tcping [option...] socket");
    puts("    -c, --count=TIMES                  配置命令发起 TIMES 次 TCP 连接, 默认值为 -1 (保持长 TCPING)");
    puts("    -i, --interval=NUM                 配置两次连接中的停顿时间为 NUM 秒钟, 默认值为 0 秒钟");
    puts("    -q, --quiet                        开启静默执行模式, 命令屏蔽正常输出");
    puts("    -h, --help                         列出命令的帮助信息");
    puts("    -v, --version                      列出命令的版本信息");
}

void version(void) {
    puts("");
    puts("command version: alpha 1.0.0");
    puts("created by FuXuanming (waitspring)");
    puts("");
}


/**********************************************************************************************************************
 * Main Part                                                                                                          *
 **********************************************************************************************************************
 */
int main(int argc, char *argv[]) {
    int opt;
    int count = -1;
    int interval = 0;                            // interval = 0 设置两次连接中的停顿时间为  0 秒钟
    int quiet = 0;                               // quiet = 0 关闭静默执行模式, quiet = 1 开启静默执行模式

    while ((opt = getopt(argc, argv, "c:i:qh?v")) != -1) {
        switch (opt) {
            case 'c':
                count = atoi(optarg);
                break;
            case 'i':
                interval = atoi(optarg);
                break;
            case 'q':
                quiet = 1;
                break;
            case 'h':
                usage();
                break;
            case '?':
                usage();
                break;
            case 'v':
                version();
                break;
        }
    }

    return 0;
}


