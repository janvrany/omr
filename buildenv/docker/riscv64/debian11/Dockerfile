# Copyright IBM Corp. and others 2022
#
# This program and the accompanying materials are made available under
# the terms of the Eclipse Public License 2.0 which accompanies this
# distribution and is available at https://www.eclipse.org/legal/epl-2.0/
# or the Apache License, Version 2.0 which accompanies this distribution and
# is available at https://www.apache.org/licenses/LICENSE-2.0.
#
# This Source Code may also be made available under the following
# Secondary Licenses when the conditions for such availability set
# forth in the Eclipse Public License, v. 2.0 are satisfied: GNU
# General Public License, version 2 with the GNU Classpath
# Exception [1] and GNU General Public License, version 2 with the
# OpenJDK Assembly Exception [2].
#
# [1] https://www.gnu.org/software/classpath/license.html
# [2] https://openjdk.org/legal/assembly-exception.html
#
# SPDX-License-Identifier: EPL-2.0 OR Apache-2.0 OR GPL-2.0 WITH Classpath-exception-2.0 OR LicenseRef-GPL-2.0 WITH Assembly-exception

# Create the OMR build environment with Debian 11.7.

FROM debian:11.7-slim AS base

# Workaround for a hang during docker build.
ENV TZ=America/Toronto
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

RUN apt-get update && apt-get install -y \
	tzdata \
        python3 \
        git \
        cmake \
        bison \
        flex \
        libelf-dev \
        libdwarf-dev \
        gdb \
        vim \
        ninja-build \
        ccache \
	pkg-config \
	libglib2.0-dev \
	build-essential \
	wget \
	gcc-riscv64-linux-gnu \
	g++-riscv64-linux-gnu \
	qemu-user-static \
	lsb-release \
	mmdebstrap \
	binfmt-support \
        && rm -rf /var/lib/apt/lists/*

# Add user home and copy authorized_keys and known_hosts.
RUN groupadd -r jenkins \
&& useradd -rm -u 1000 -g jenkins jenkins \
&& mkdir -p /home/jenkins/.ssh \
&& echo "Host git.eclipse.org*\n\tStrictHostKeyChecking no\n" > /home/jenkins/.ssh/config \
&& chown -R jenkins:jenkins /home/jenkins

RUN wget -O /usr/local/include/riscv.h 'https://sourceware.org/git/gitweb.cgi?p=binutils-gdb.git;a=blob_plain;f=include/opcode/riscv.h;hb=2f973f134d7752cbc662ec65da8ad8bbe4c6fb8f' \
&& wget -O /usr/local/include/riscv-opc.h 'https://sourceware.org/git/gitweb.cgi?p=binutils-gdb.git;a=blob_plain;f=include/opcode/riscv-opc.h;hb=2f973f134d7752cbc662ec65da8ad8bbe4c6fb8f'

RUN cd /opt \ 
&& git clone https://gitlab.com/qemu-project/qemu.git qemu_src \
&& git -C qemu_src checkout v7.2.0 \
&& mkdir qemu_bld \
&& cd qemu_bld \
&& ../qemu_src/configure --prefix=/opt/qemu-v7.2.0 --target-list=riscv64-linux-user --static \
&& make -j4 \
&& make install \
&& /opt/qemu-v7.2.0/bin/qemu-riscv64 --version \
&& rm -rf /opt/qemu_bld /opt/qemu_src

# this needs to be setup on the host such that the sysroot creation in the job works, and this copy from the host succeeds
#RUN mkdir -p /root/.gnupg \
#&& chmod 600 /root/.gnupg \
#&& gpg --no-default-keyring --primary-keyring /root/.gnupg/pubring.kbx --keyserver keyserver.ubuntu.com --recv-key B523E5F3FC4E5F2C \
#&& gpg --no-default-keyring --primary-keyring /root/.gnupg/pubring.kbx --keyserver keyserver.ubuntu.com --recv-key 8D69674688B6CB36 \
#&& gpg --no-default-keyring --primary-keyring /root/.gnupg/pubring.kbx --export B523E5F3FC4E5F2C > /etc/apt/trusted.gpg.d/debian-B523E5F3FC4E5F2C.gpg \
#&& gpg --no-default-keyring --primary-keyring /root/.gnupg/pubring.kbx --export 8D69674688B6CB36 > /etc/apt/trusted.gpg.d/debian-8D69674688B6CB36.gpg \
#&& mmdebstrap --variant=minbase --architectures=riscv64 --include="debian-ports-archive-keyring,build-essential,libdwarf-dev,libelf-dev,libx11-dev,libxext-dev,libxrender-dev,libxrandr-dev,libxtst-dev,libxt-dev,libasound2-dev,libcups2-dev,libfontconfig1-dev" bullseye "${WORKSPACE}/sysroot" "deb http://deb.debian.org/debian-ports/ sid main" "deb http://deb.debian.org/debian-ports/ unreleased main"

COPY sysroot /opt/

# USER jenkins
