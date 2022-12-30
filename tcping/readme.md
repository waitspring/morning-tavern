# Tcping

### 一、使用说明

**Tcping** 小工具在 Github 开源社区有很多作者实现过, 但从使用体验的层面看始终存在各种小瑕疵  

**Tcping** 小工具由本人重构之后, 具备下述特点:

+ 支持在 Shell 脚本内, 配合 `IFS` 命令使用
+ 支持静默工作模式
+ 支持不同的返回码

### 二、使用方法

**Tcping** 小工具的安装方法说明如下:

```bash
$ gcc --std=c99 -o tcping tcping.c
$ chmod a+x tcping
$ cp tcping /usr/bin/tcping
```

**Tcping** 小工具的使用方法说明如下:

```bash
$ tcping [option...] socket

    -c, --count=TIMES                            # 配置命令发起 TIMES 次 TCP 连接, 默认值为 86400 (保持长 TCPING)
    -i, --interval=NUM                           # 配置两次连接中的停顿时间为 NUM 秒钟, 默认值为 1 秒钟
    -q, --quiet                                  # 开启静默执行模式, 命令屏蔽正常输出
    -h, --help                                   # 列出命令的帮助信息
    -v, --version                                # 列出命令的版本信息

```

