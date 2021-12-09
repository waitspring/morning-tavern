Name:		morning-tavern
Version:	1.0.0
Release:	1%{?dist}
Summary:	A good repository for bash tools

Group:		Development/Tools
License:	Apache 2.0
URL:		https://github.com/waitspring/morning-tavern
Source0:	%{name}-%{version}.tar.gz

Requires:	bash
BuildArch:      noarch

%description
A good repository for bash tools

%prep
%setup -q

%build

%install
mkdir -p %{buildroot}%{_bindir}
install -m 0775 %{_builddir}/%{name}-%{version}/searchme/searchme %{buildroot}%{_bindir}/searchme
mkdir -p %{buildroot}%{_sysconfdir}
install -m 0664 %{_builddir}/%{name}-%{version}/searchme/searchme.conf %{buildroot}%{_sysconfdir}/searchme.conf

%files
%{_bindir}/searchme
%{_sysconfdir}/searchme.conf

%changelog
* Thu Dec 9 2021 waitspring <newsfuxuanming@foxmail.com>
- Create the package for searchme command
