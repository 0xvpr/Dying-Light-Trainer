#!/mnt/c/Windows/System32/WindowsPowerShell/v1.0/powershell.exe

$build_dir="Build"
$config="Release"

cmake -B ${build_dir}
cmake --build ${build_dir} --config ${config}
