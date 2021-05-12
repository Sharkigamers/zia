############################
#                          #
# WINDOWS SCRIPT FOR BABEL #
#                          #
############################

Write-Output "Windows script for compiling Babel project"
if (Test-Path -LiteralPath "./build") {
    Write-Output "Removing './build' folder ..."
    Remove-Item -Confirm:$false -Force -Recurse "./build"
    Write-Output "Done"
}
if (Test-Path -LiteralPath "./client/build-clientUI-Desktop-Debug") {
    Write-Output "Removing './client/build-clientUI-Desktop-Debug' folder ..."
    Remove-Item -Confirm:$false -Force -Recurse "./client/build-clientUI-Desktop-Debug"
    Write-Output "Done"
}

Write-Output "Creating './build' folder"
mkdir "./build"
Write-Output "Done"

Write-Output "Moving into './build' folder"
cd "./build"
Write-Output "Done"

Write-Output "Downloading conan dependencies ..."
conan install .. --build missing
Write-Output "Done"

Write-Output "Building project with conan ..."
conan build ..
Write-Output "Done"

Write-Output "Moving into root repository"
cd .. 
Write-Output "Done"