$src = "src\main.c", "src\db_adapter.c", "src\inventory.c", "src\billing.c", "src\ui.c", "lib\sqlite3.c"
$out = "pos_app.exe"
$flags = "-I.\include", "-I.\lib"

Write-Host "Compiling..."
gcc $src -o $out $flags

if ($?) {
    Write-Host "Build Successful. Running..."
    .\pos_app.exe
}
else {
    Write-Host "Build Failed."
}
