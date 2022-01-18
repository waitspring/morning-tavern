# Hostinit

### 一、功能说明

AWS, 阿里云, 华为云, 腾讯云在内的公有云服务, 其自带镜像都是以最小化模式安装的操作系统, 使用起来存在诸多不便  
Hostinit 小工具用于一键式的执行公有云主机的初始化服务, 具体包括:

+ 更新用户会话的欢迎语句
+ 更新主机名称
+ 更新虚拟终端的命令行提示符, 更新格式如下:
  * 普通权限用户 `username@hostname:~$ `
  * 超级权限用户 `[env][username@hostname ~]# `
+ 安装国内可用的 EPEL 源
+ 安装国内可用的 PIP 源
+ 解除文件句柄与网络句柄的阈值限制
+ 解除用户会话的指纹校验
+ 创建业务进程使用的群组用户, 配置免密码超级权限
+ 创建业务进程使用的基础目录, 默认配置为 `/opt/{application,applog,middleware}`
+ 安装 OpenJDK8 运行环境
+ 安装 MySQL 数据库的客户端软件环境
+ 安装软件包如下:
  * bash-completion.noarch
  * bash-completion-extras.noarch
  * bind-utils.x86_64
  * dos2unix.x86_64
  * figlet.x86_64
  * gcc.x86_64
  * gcc-c++.x86_64
  * lrzsz.x86_64
  * nc.x86_64
  * nmap.x86_64
  * nmap-ncat.x86_64
  * procps-ng.x86_64
  * psmisc.x86_64
  * telnet.x86_64
  * tree.x86_64
  * unzip.x86_64
  * wget.x86_64
  * xorg-x11-apps.x86_64
  * xorg-x11-xauth.x86_64

### 二、使用办法

Hostinit 小工具的使用方法说明如下:

```
$ sh hostinit.sh [option ...]

              --directory /path/to/dir           # 业务系统使用的基础目录, 默认值为 /opt
              --domain ipaddr,...                # 更新主机的域名解析服务器, 默认值为空 (沿用公有云原有的域名解析服务器)
              --env environment                  # 更新主机的环境标签, 默认值为 prd
              --host hostname                    # 更新主机的名称
              --string str                       # 用户会话的欢迎语句, 默认为空值
              --help                             # 回显命令帮助信息
              --version                          # 回显命令版本信息
```

