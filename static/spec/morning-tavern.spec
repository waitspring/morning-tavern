Name:          morning-tavern
Version:       1.0.2
Release:       1%{?dist}
Summary:       A good repository for bash tools

Group:         Development/Tools
License:       Apache 2.0
URL:           https://github.com/waitspring/morning-tavern
Source0:       %{name}-%{version}.tar.gz

BuildRequires: gcc, make
Requires:      bash
BuildArch:     x86_64

%description
A good repository for bash tools

%prep
%setup -q

%build

cd %{_builddir}/%{name}-%{version}/tcping
%configure
make CFLAGS=-std=c99 %{?_smp_mflags}
cd %{_builddir}/%{name}-%{version}/tcping6
%configure
make CFLAGS=-std=c99 %{?_smp_mflags}

%install
mkdir -p %{buildroot}%{_bindir}
install -m 0775 %{_builddir}/%{name}-%{version}/searchme/searchme %{buildroot}%{_bindir}/searchme
install -m 0775 %{_builddir}/%{name}-%{version}/tcping/tcping %{buildroot}%{_bindir}/tcping
install -m 0775 %{_builddir}/%{name}-%{version}/tcping6/tcping6 %{buildroot}%{_bindir}/tcping6
mkdir -p %{buildroot}%{_sysconfdir}
install -m 0664 %{_builddir}/%{name}-%{version}/searchme/searchme.conf %{buildroot}%{_sysconfdir}/searchme.conf

%files
%{_bindir}/searchme
%{_sysconfdir}/searchme.conf
%{_bindir}/tcping
%{_bindir}/tcping6

%changelog
* Fri Jan 07 2023 waitspring <newsfuxuanming@foxmail.com>
- Create the package for tcping6 command
- Create the package for tcping command
- Create the package for searchme command
* Fri Dec 30 2022 waitspring <newsfuxuanming@foxmail.com>
- Create the package for tcping command
- Create the package for searchme command
* Thu Dec 9 2021 waitspring <newsfuxuanming@foxmail.com>
- Create the package for searchme command

