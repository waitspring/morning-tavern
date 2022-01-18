# Hostinit

### 一、背景说明

公有云服务自带的 RHEL7 (CentOS7) 镜像都是以最小化模式安装的操作系统

+ 更新 OpenSSH 欢迎语句
+ 安装下述软件包:
  * bash-completion.noarch
  * dos2unix.x86_64
  * telnet.x86_64
  * tree.x86_64
  * unzip.x86_64
  * xorg-x11-apps.x86_64
  * xorg-x11-xauth.x86_64

### 二、使用办法

```bash
$ sh hostinit.sh 
```
