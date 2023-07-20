function Force-Resolve-Path {
    param ([string] $FileName)
    $FileName = Resolve-Path $FileName -ErrorAction SilentlyContinue -ErrorVariable _frperror
    if (-not($FileName)) { $FileName = $_frperror[0].TargetObject }
    return $FileName
}

$Project = Force-Resolve-Path $PSScriptRoot/../../CMakeLists.txt
$Output = Force-Resolve-Path $PSScriptRoot/../../build/Web

emcmake cmake -G "Ninja" -DCMAKE_BUILD_TYPE=Debug $Project -B $Output/Normal
emcmake cmake -G "Ninja" -DCMAKE_TESTING=on -DCMAKE_BUILD_TYPE=Debug $Project -B $Output/Test