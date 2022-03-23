#!/bin/bash

# Creator: VPR
# Created: December 14th, 2021
# Updated: March 22, 2022

# This script is intended to work with Pidjeon for a seamless injection process.

__game_name="DyingLightGame.exe"
__dll_path="./Lib/Release/daylight-savings.dll"

vpr-pidjeon_x64 "${__game_name}" "${__dll_path}" -i ManualMap
