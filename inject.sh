#!/bin/bash

__game_name="DyingLightGame.exe"
__dll_path="./bin/daylight-savings.dll"

export PATH=$PATH:~/.toolkit/

pidjeon_x64.exe "${__game_name}" "${__dll_path}" -i ManualMap
