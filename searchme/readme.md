# Searchme

### 一、拓扑说明

<div align="center">

![topology](https://github.com/waitspring/morning-tavern/raw/master/static/pic/searchme-topology.png)

</div>

**Searchme** 小工具配合 **Ansible** 软件的主机资产登记文件使用, 能够快速检索主机资产登记文件内的主机记录  

**Searchme** + **Ansible** + **CMDB** 可以形成一个完整的应用情境:

+ CMDB 软件基于事务控制集中管理环境资产信息, 并提供接口供外部软件查询主机数据
+ Ansible 软件使用短周期的定时任务 (例如每 3 分钟), 从 CMDB 的接口读取主机数据, 并同步结果到自身的主机资产登记文件
+ Searchme 小工具使用关键字检索 Ansible 软件的主机资产登记文件, 并返回检索结果

### 二、使用方法

**Searchme** 小工具的使用方法说明如下:

```bash
$ searchme [option...] [keyword]

    -a        --all                              # 回显全部主机记录
    -h        --help                             # 回显命令帮助信息
    -v        --version                          # 回显命令版本信息

```

**Searchme** 小工具的默认检索对象为 **Ansible** 软件的主机资产登记文件 `/etc/ansible/hosts/inventory`  
实际情况与此不同, 请更新 **Searchme** 小工具的配置文件 `/etc/searchme.conf`  

```bash
# /etc/searchme.conf
inventory=/path/to/inventory

```

