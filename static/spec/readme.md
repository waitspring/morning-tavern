# RPM 仓库结构

`/srv/morning-tavern-1.0.1` 的目录结构如下:

```
/srv/morning-tavern-1.0.1
    │
    ├──── searchme
    │     ├──── searchme
    │     └──── searchme.conf
    └──── tcping
          ├──── aclocal.m4
          ├──── config.h.in
          ├──── configure
          ├──── configure.ac
          ├──── Makefile.am
          ├──── Makefile.in
          └──── src
                ├──── tcping
                └──── tcping.c

```

`/root/rpmbuild` 的目录结构如下:

```
/root/rpmbuild
    │
    ├──── BUILD
    ├──── BUILDROOT
    ├──── RPMS
    ├──── SOURCES
    │     └──── morning-tavern-1.0.1.tar.gz
    ├──── SPECS
    │     └──── morning-tavern.spec
    └──── SRPMS

```

