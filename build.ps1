#!/usr/bin/env powershell.exe

$build_dir="Build"
$config="Release"

cmake -B ${build_dir}
cmake --build ${build_dir} --config ${config}
