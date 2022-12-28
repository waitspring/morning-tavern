/**********************************************************************************************************************
 *                                                                                                                    *
 * main.c                                                                                                             *
 * Fu Xuanming (2022-2023)                                                                                            *
 *                                                                                                                    *
 **********************************************************************************************************************
 * 
 * 
 */

#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <time.h>
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
    puts("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    puts("Examp: tcping -c 1 127.0.0.1:22");
    puts("       tcping -c 1 [::1]:22");
}

void version(void) {
    puts("");
    puts("command version: alpha 1.0.0");
    puts("created by FuXuanming (waitspring)");
    puts("");
}

void info(const char *func, const char *info) {
    char timestamp[64];
    time_t timepoint = time(NULL);
    struct tm *timeinfo = localtime(&timepoint);
    struct timeval tv;                           // 使用 sys/time.h/timeval 数据结构获取毫秒级时间戳

    gettimeofday(&tv, NULL);
    strftime(timestamp, sizeof timestamp, "%F %T", timeinfo);
    fprintf(stdout, "%s.%03d INFO [%s] %s\n", timestamp, tv.tv_usec/1000, func, info);
}

void warn(const char *func, const char *warn) {
    char timestamp[64];
    time_t timepoint = time(NULL);
    struct tm *timewarn = localtime(&timepoint);
    struct timeval tv;

    gettimeofday(&tv, NULL);
    strftime(timestamp, sizeof timestamp, "%F %T", timewarn);
    fprintf(stdout, "%s.%03d WARN [%s] %s\n", timestamp, tv.tv_usec/1000, func, warn);
}

void error(const char *func, const char *error) {
    char timestamp[64];
    time_t timepoint = time(NULL);
    struct tm *timerror = localtime(&timepoint);
    struct timeval tv;

    gettimeofday(&tv, NULL);
    strftime(timestamp, sizeof timestamp, "%F %T", timerror);
    fprintf(stderr, "%s.%03d ERROR [%s] %s\n", timestamp, tv.tv_usec/1000, func, error);
}



/**********************************************************************************************************************
 * Function                                                                                                           *
 **********************************************************************************************************************
 */
int judge_ip(char *ip) {
    /* todo: 分切套接字得到 IPv4/IPv6 地址
     * todo: 验证 IPv4/IPv6 地址是否符合书写规范
     */
    struct in_addr ipv4;
    struct in6_addr ipv6;
    const char tag = ':';
    const char sign[2] = {'[', ']'};
    
    ip[strlen(ip) - strlen(strrchr(ip, tag))] = '\0';
    if (strrchr(ip, sign[0])) {
        ip = &strrchr(ip, sign[0])[1];
    }
    if (strrchr(ip, sign[1])) {
        ip[strlen(ip) - strlen(strrchr(ip, sign[1]))] = '\0';
    }
    if (inet_pton(AF_INET, (char *)ip, &ipv4)) {
        return 1;
    }
    if (inet_pton(AF_INET6, (char *)ip, &ipv6)) {
        return 1;
    }

    error("judge_ip", "目标地址检查失败, 目标地址不符合 IPv4/ IPv6 的书写规范");
    return 0;
}

int judge_po(char *po) {
    const char tag = ':';

    po = &strrchr(po, tag)[1];
    for (int i = 0; i < strlen(po); i++) {
        if (po[i] >= '0' && po[i] <='9') {
            continue;
        } else {
            error("judge_po", "目标端口检查失败, 目标端口不符合书写规范");
            return 0;
        }
    }
    if (atoi(po) > 65535) {
        error("judge_po", "目标端口检查失败, 目标端口已超过取值范围");
        return 0;
    }

    return 1;
}



/**********************************************************************************************************************
 * Main Part                                                                                                          *
 **********************************************************************************************************************
 */
int main(int argc, char *argv[]) {
    int opt;
    int count = 999999;
    int interval = 0;                            // interval = 0 设置两次连接中的停顿时间为  0 秒钟
    int quiet = 0;                               // quiet = 0 关闭静默执行模式, quiet = 1 开启静默执行模式

    char *parameter;
    char ip[256];
    char po[256];

    struct sockaddr_in addr_info;

    while ((opt = getopt(argc, argv, "c:i:qhv")) != -1) {
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
                return 0;
            case 'v':
                version();
                return 0;
            case '?':                            // getopt 函数提供给用户捕获无效的命令选项
                error("main", "选项类型检查失败, 请使用 $ tcping -h 查阅命令的帮助信息");
                return 1;
        }
    }

    if ((argc - optind) != 1) {
        error("main", "参数数量检查失败, 请使用 $ tcping -h 查阅命令的帮助信息");
        return 1;
    } else {
        parameter = argv[optind];
        strcpy(ip, parameter);
        strcpy(po, parameter);
    }

    if (judge_ip(ip) == 0 || judge_po(po) == 0) {
        error("main", "参数赋值检查失败, 请使用 $ tcping -h 查阅命令的帮助信息");
        return 1;
    }

    for (int i = 0; i < count; i++) {
        double ms;
        struct timeval tv;
    }

    return 0;
}


