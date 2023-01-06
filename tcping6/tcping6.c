/**********************************************************************************************************************
 *                                                                                                                    *
 *                                         ______                         __                                          *
 *                                        (_) |          o               /                                            *
 *                                            | __    _      _  _    __,| __                                          *
 *                                          _ |/    |/ \_|  / |/ |  /  ||/  \                                         *
 *                                         (_/ \___/|__/ |_/  |  |_/\_/|/\__/                                         *
 *                                                 /|                 /|                                              *
 *                                                 \|                 \|                                              *
 *                                                                                                                    *
 **********************************************************************************************************************
 * 文件名称: tcping6.c
 * 编译方法: gcc --std=c99 -o /usr/bin/tcping6 /path/to/tcping6.c
 * 作者信息: Fu Xuanming (2023)
 */

#include <arpa/inet.h>
#include <getopt.h>
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
    puts("Usage: tcping6 [option...] socket");
    puts("");
    puts("    -c, --count=NUM                    make NUM times TCP connection, default 86400");
    puts("    -i, --interval=NUM                 pause time for two connections as NUM seconds, default 1");
    puts("    -q, --quiet                        enable the silent execution mode");
    puts("    -h, --help                         list this help information");
    puts("    -v, --version                      list this command version information");
    puts("");
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
int judge_ip(char *ip, char **ipp, struct sockaddr_in6 *addr6) {
    /* Todo: 分切套接字得到 IPv6 地址, 验证 IPv6 地址是否符合书写规范
     * Todo: 已经验证通过的 IPv6 地址, 赋予 sockaddr_in6.sin6_addr.s6_addr 数据字段
     * Todo: 已经验证通过的 IPv6 地址, 赋予 ipp 字符串指针
     * Todo: 如果传入参数为 IPv4 地址, 抛出错误信息
     * Return: IPv6 地址校验成功返回值为 1, IPv6 地址校验失败返回值为 0
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
        error("judge_ip", "check target address error");
        error("judge_ip", "target address is IPv4 address, maybe you can use tcping command");
        return 0;
    }
    if (inet_pton(AF_INET6, (char *)ip, &ipv6)) {
        addr6->sin6_family = AF_INET6;
        inet_pton(AF_INET6, (char *)ip, &(addr6->sin6_addr));
        *ipp = ip;
        return 1;
    }

    error("judge_ip", "check target address error");
    error("judge_ip", "target address does not conform to the IPv6 writing specification");
    return 0;
}

int judge_po(char *po, char **pop, struct sockaddr_in6 *addr6) {
    /* Todo: 分切套接字得到端口号, 验证端口号是否符合书写规范
     * Todo: 已经验证通过的端口号, 赋予 sockaddr_in6.sin6_port 数据字段
     * Todo: 已经验证通过的端口号, 赋予 pop 字符串指针
     * Return: 端口号校验成功返回值为 1, 端口号校验失败返回值为 0
     */
    const char tag = ':';

    po = &strrchr(po, tag)[1];
    for (int i = 0; i < strlen(po); i++) {
        if (po[i] >= '0' && po[i] <='9') {
            continue;
        } else {
            error("judge_po", "check target port error");
            error("judge_po", "target port does not conform to the port writing specification");
            return 0;
        }
    }
    if (atoi(po) > 65535) {
        error("judge_po", "check target port error");
        error("judge_po", "target port has exceeded the value range");
        return 0;
    }

    addr6->sin6_port = htons(atoi(po));
    *pop = po;
    return 1;
}

int connect_to(struct timeval *begin, struct timeval *end, struct sockaddr_in6 *addr6) {
    /* Todo: 创建套接字, 并发起 TCP 连接 (默认 10 秒钟超时)
     * Todo: 针对上述过程计时, 返回计时结果, 若连接失败则计时结果为 0
     * Notice: 套接字的非阻塞工作模式无法适应内网的 TCP 连接
     */
    int sock;
    int connect_result;
    int ms;
    int timeout = 10;

    gettimeofday(begin, NULL);
    sock = socket(addr6->sin6_family, SOCK_STREAM, 0);
    setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout, sizeof(int));
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(int));
    connect_result = connect(sock, (struct sockaddr *)addr6, sizeof(*addr6));
    close(sock);
    gettimeofday(end, NULL);
    if (connect_result == 0) {
        ms = (1000000 * (end->tv_sec - begin->tv_sec) + (end->tv_usec - begin->tv_usec)) / 1000;
        if (ms == 0) {
            /* Todo: 建立本机的 TCP 连接时, 因数据精度不够, 可能导致计时为 0 毫秒, 人工将其重置为 1 毫秒
             */
            ms = 1;
        }
        return ms;
    } else {
        return 0;
    }
}

int max(int *num, int size) {
    int max = num[0];

    for (int i = 0; i < size; i++) {
        if (max < num[i] && num[i] != 0) {
            max = num[i];
        }
    }

    return max;
}

int min(int *num, int size) {
    int min = num[0];

    for (int i = 0; i < size; i++) {
        if (min > num[i] && num[i] != 0) {
            min = num[i];
        }
    }

    return min;
}

int avg(int *num, int size, int counts) {
    int total = 0;

    for (int i = 0; i < size; i++) {
        if (num[i] != 0) {
            total += num[i];
        }
    }

    if (counts != 0) {
        return total / counts;
    } else {
        return 0;
    }
}



/**********************************************************************************************************************
 * Main Part                                                                                                          *
 **********************************************************************************************************************
 */
int main(int argc, char *argv[]) {
    int opt;
    int count = 86400;                           // count = 86400 设置连接次数, 默认为 86400 次连接 (24小时不间断)
    int interval = 1;                            // interval = 1 设置两次连接中的停顿时间为  1 秒钟
    int quiet = 0;                               // quiet = 0 关闭静默执行模式, quiet = 1 开启静默执行模式

    char *parameter;
    char  ip[256];
    char  po[256];
    char *ipp;                                   // 指向清洗过的 IPv6 地址
    char *pop;                                   // 指向清洗过的端口号

    struct sockaddr_in6 addr6;
    memset(&addr6, 0, sizeof(addr6));            // 使用数值 0 填充数据结构 sockaddr_in6 的每个字节

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
                error("main", "option type check error");
                error("main", "exeute $ tcping6 -h find help information");
                return 1;
        }
    }

    if ((argc - optind) != 1) {
        error("main", "option number check error");
        error("main", "exeute $ tcping6 -h find help information");
        return 1;
    } else {
        parameter = argv[optind];
        strcpy(ip, parameter);
        strcpy(po, parameter);
    }

    if (judge_ip(ip, &ipp, &addr6) == 0 || judge_po(po, &pop, &addr6) == 0) {
        /* judge_ip() 执行结束时, 字符数组变量 ip 仍然存储完整的目标套接字 (:port 部分被切割)
         * judge_po() 执行结束时, 字符数组变量 po 仍然存储完整的目标套接字
         */
        error("main", "option value check error");
        error("main", "exeute $ tcping6 -h find help information");
        return 1;
    }

    int ms[count];
    int max_ms = 0;
    int min_ms = 0;
    int avg_ms = 0;
    int counts = 0;                              // 统计成功次数 (count success)
    int counte = 0;                              // 统计失败次数 (count error)

    for (int i = 0; i < count; i++) {
        struct timeval begin;
        struct timeval end;

        ms[i] = connect_to(&begin, &end, &addr6);
        if (ms[i] == 0) {
            counte++;
            if (quiet == 0) {
                printf("Ping tcp://%s:%s - error\n", ipp, pop);
            }
        } else {
            counts++;
            if (quiet == 0) {
                printf("Ping tcp://%s:%s - success: timepay %d(ms)\n", ipp, pop, ms[i]);
            }
        }
        sleep(interval);
    }

    max_ms = max(ms, count);
    min_ms = min(ms, count);
    avg_ms = avg(ms, count, counts);
    if (quiet == 0) {
        printf("\n");
        printf("Tcping6 statistics tcp://%s:%s\n", ipp, pop);
        printf("    %d times request success, %d times request error\n", counts, counte);
        printf("Approximate trip times:\n");
        printf("    Maximum = %d(ms), Minimum = %d(ms), Average = %d(ms)\n", max_ms, min_ms, avg_ms);
        printf("\n");
    }

    if (counte == count) {
        return 2;
    }
    if (counte != 0) {
        return 1;
    }
    return 0;
}


