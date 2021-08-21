#!/usr/bin/env bash

set -euo pipefail

cd $(dirname $0)/..

environment="esp_wroom_02"

# determine version
gcc -o ver hack/printversion.c
version="$(./ver)"
rm ver

# setup
remoteDirectory="infrastructure/data/monitor/ota-1/froy"
remoteFilename="$remoteDirectory/froy-$version.bin"
remoteHost="xrstf.de"

# create directory
ssh "$remoteHost" "mkdir -p $remoteDirectory"

# check if this version already exists
if ssh "$remoteHost" "test -e $remoteFilename"; then
  echo "A release with this version ($version) already exists, refusing to overwrite."
  exit 1
fi

# build project
echo "Compiling..."
pio run --silent --environment "$environment" --target clean
pio run --silent --environment "$environment"

echo "Uploading version $version ..."
scp ".pio/build/$environment/firmware.bin" "$remoteHost:$remoteFilename"
