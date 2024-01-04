#!/bin/bash

cd `dirname $0`

(mkdir -p build && cd build && cmake .. && make && cd ..)

export BUILDDIR=$(pwd)/build;


#sudo modprobe v4l2loopback
afb-binder --config=demo.config -vvv
#afb-binder --config=demo.config -vvv --tracereq=common --traceapi=common --traceevt=common --rpc-server unix:@CameraStream
