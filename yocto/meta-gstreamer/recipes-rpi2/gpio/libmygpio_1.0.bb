SUMMARY = "GPIO library for rpi2"
DESCRIPTION = "GPIO library for rpi2"

SECTION = "libs"

LICENSE = "GPLv2"
LIC_FILES_CHKSUM = "file://COPYING;md5=b234ee4d69f5fce4486a80fdaf4a4263"

SRC_URI = "file://libmygpio-1.0.tar.gz"

S = "${WORKDIR}/${PN}-${PV}"

EXTRA_OECONF += "--enable-shared"

inherit autotools

PROVIDES += "${PN}-staticdev"

FILES_${PN} = "${libdir}/*.so* ${bindir}/*"
FILES_${PN}-staticdev = "${includedir} ${datadir}"


