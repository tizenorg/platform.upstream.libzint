Name:      zint
Version:   2.4.3
Release:   10
Summary:   Barcode generator library
License:   BSD-2.0
URL:       http://www.zint.org.uk
Source:    %{name}-%{version}.tar.gz
Group:     Development/Libraries

BuildRequires: cmake
BuildRequires: libpng-devel
#BuildRequires: zlib-devel

%description
Zint is a C library for encoding data in several barcode variants. The
bundled command-line utility provides a simple interface to the library.
Features of the library:
- Over 50 symbologies including all ISO/IEC standards, like QR codes.
- Unicode translation for symbologies which support Latin-1 and
  Kanji character sets.
- Full GS1 support including data verification and automated insertion of
  FNC1 characters.
- Support for encoding binary data including NULL (ASCII 0) characters.
- Health Industry Barcode (HIBC) encoding capabilities.
- Output in PNG, EPS and SVG formats with user adjustable sizes and colors.
- Verification stage for SBN, ISBN and ISBN-13 data.



%package devel
Summary:       Library and header files for %{name}
Group:         Development/Libraries
Requires:      %{name} = %{version}-%{release}

%description devel
C library and header files needed to develop applications that use
the Zint library. The API documentation can be found on the project website:
http://www.zint.org.uk/zintSite/Manual.aspx

%prep
%setup -q


%build
MAJORVER=`echo %{version} | awk 'BEGIN {FS="."}{print $1}'`
cmake . -DCMAKE_INSTALL_PREFIX=/usr -DFULLVER=%{version} -DMAJORVER=${MAJORVER}
make VERBOSE=1


%install
rm -rf %{buildroot}
make install DESTDIR=%{buildroot}
#rm -rf %{buildroot}/%{_datadir}/cmake


%clean
rm -rf $RPM_BUILD_ROOT


%post -p /sbin/ldconfig
%postun -p /sbin/ldconfig


%files
%defattr(-,root,root,-)
#%doc COPYING readme
%{_libdir}/libzint.so.*
%{_datadir}/%{name}/LICENSE


%files devel
%defattr(-,root,root,-)
%{_includedir}/%{name}.h
%{_libdir}/libzint.so
%{_datadir}/%{name}/LICENSE
%exclude %{_datadir}/cmake/Modules/FindZint.cmake
