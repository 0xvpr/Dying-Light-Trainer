#!/bin/bash

# Creator: VPR
# Created: December 14th, 2021
# Updated: December 14th, 2021

# This script is intended to work with Pidjeon for a seamless injection process.

__game_name="DyingLightGame.exe"
#__dll_path="./bin/daylight-savings.dll"
__dll_path="./bin/Release/daylight-savings.dll"
__pidjeon_path="~/.toolkit" # Change as necessary

export PATH=$PATH:"${__pidjeon_path}"

pidjeon_x64.exe "${__game_name}" "${__dll_path}" -i ManualMap
