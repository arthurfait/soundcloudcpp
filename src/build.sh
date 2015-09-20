#!/bin/bash

# set -o nounset # for debug
set -o errexit


BUILD_START=$(date +%s)

#default
BUILD_TYPE=MinSizeRel


PARAM=$(echo $1 | tr "[:lower:]" "[:upper:]")
while [[ _$PARAM != _ ]]; do
   case "$PARAM" in
      D ) BUILD_TYPE="Debug" ;;
      G ) BUILD_TYPE="RelWithDebInfo" ;;
      S ) BUILD_TYPE="Release" ;;
      CLEAN ) CLEAN="true"  ;;
      PRJ ) export GEN_PROJ="ON" ;;
      * ) echo "ERROR: Unknow parameter '$PARAM'"; exit 1 ;;
   esac
   shift
   PARAM=$(echo $1 | tr "[:lower:]" "[:upper:]")
done



#use host path
export ABSOLUTE_PATH=$(cd `dirname "${BASH_SOURCE[0]}"` && pwd)
if [[ "$CORRECT" == "yes" ]]; then
	PRODUCTS_DIR="$ABSOLUTE_PATH/../build"
else
	PRODUCTS_DIR="$ABSOLUTE_PATH/build"
fi	

if [[ "$CLEAN" == "true" ]]; then
    rm -R -f "$PRODUCTS_DIR"
fi

mkdir -p $PRODUCTS_DIR
cd $PRODUCTS_DIR

echo "STAGE: <<<<< Configuring >>>>>"
echo

# If project already configured we will skip configuration
if [[ ! -e "Makefile" ]]; then
    if [[ "$GEN_PROJ" == "ON" ]]; then
        echo "Generating Eclipse CDT4 project files..."
        cmake -G "Eclipse CDT4 - Unix Makefiles" -DCMAKE_BUILD_TYPE=$BUILD_TYPE  "$ABSOLUTE_PATH/" 
    else
        cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE "$ABSOLUTE_PATH/" 
    fi
fi

echo "STAGE: <<<<< Building >>>>>"
echo "BUILD_TYPE: $BUILD_TYPE"

CPU_NUM=$(cat /proc/cpuinfo | grep processor | wc -l)
echo "Parallel build: $CPU_NUM CPU(s)"


make --jobs=$CPU_NUM 


if (( ${PIPESTATUS[0]} != 0 )); then
   BUILDRESULT=FAIL
   EXITCODE=1
else
   BUILDRESULT=OK
   EXITCODE=0
fi

if [[ "$BUILDRESULT" = "OK" ]]; then
   echo "BUILD SUCCEEDED"
else
   echo "BUILD FAILED"
fi

let BUILD_TIME=$(date +%s)-$BUILD_START

printf "Total build time: %dh %dm %ds\n" $(($BUILD_TIME/3600)) $(($BUILD_TIME%3600/60)) $(($BUILD_TIME%60))

exit $EXITCODE
