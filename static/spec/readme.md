# RPM 仓库结构

`/srv/morning-tavern-1.0.3` 的目录结构如下:

```
/srv/morning-tavern-1.0.3
    │
    ├──── searchme
    │     ├──── searchme
    │     └──── searchme.conf
    ├──── tcping
    │     ├──── aclocal.m4
    │     ├──── config.h.in
    │     ├──── configure
    │     ├──── configure.ac
    │     ├──── Makefile.am
    │     ├──── Makefile.in
    │     └──── src
    │           ├──── tcping
    │           └──── tcping.c
    └──── tcping6
          ├──── aclocal.m4
          ├──── config.h.in
          ├──── configure
          ├──── configure.ac
          ├──── Makefile.am
          ├──── Makefile.in
          └──── src
                ├──── tcping6
                └──── tcping6.c

```

`/root/rpmbuild` 的目录结构如下:

```
/root/rpmbuild
    │
    ├──── BUILD
    ├──── BUILDROOT
    ├──── RPMS
    ├──── SOURCES
    │     └──── morning-tavern-1.0.3.tar.gz
    ├──── SPECS
    │     └──── morning-tavern.spec
    └──── SRPMS

```

