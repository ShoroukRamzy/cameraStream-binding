Name: camera-demo
Version: 1.0.0
Release: 0%{?dist}
Summary: dummy camera demo

License: _TO_COMPLETE_
URL: https://github.com/jobol/CameraApp-redpesk.git
Source0: %{name}-%{version}.tar.gz

Requires: afb-binder
BuildRequires: cmake
BuildRequires: gcc gcc-c++
BuildRequires: pkgconfig(json-c)
BuildRequires: pkgconfig(afb-binding)

%description
Two microservices,
objectdeteciton that subscribes to 
camera stream

%package test
Requires: %{name} = %{version}
Requires: afb-test
Requires: jq
Summary: dummy camera demo (test package)

%description test
This is the test package for %{name}. 

%package redtest
Requires: %{name}-test = %{version}
Summary: dummy camera demo (redtest package)

%description redtest
This is the redtest package for %{name}. 

%prep
%autosetup -p 1

%build
%cmake .
%cmake_build

%install
%cmake_install

%files
%dir /usr/redpesk
%dir /usr/redpesk/%{name}
/usr/redpesk/%{name}/*
/usr/redpesk/%{name}/.rpconfig

%files test
%dir /usr/redpesk
%dir /usr/redpesk/%{name}-test
/usr/redpesk/%{name}-test/*
/usr/redpesk/%{name}-test/.rpconfig

%files redtest
%dir %{_libexecdir}/redtest/
%dir %{_libexecdir}/redtest/%{name}
%{_libexecdir}/redtest/%{name}/*




%changelog