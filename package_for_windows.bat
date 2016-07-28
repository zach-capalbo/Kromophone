set PATH=%PATH%;E:\Qt\5.7\mingw53_32\bin;E:\Qt\Tools\mingw530_32\bin
E:
cd E:\builds\build-Kromophone-Desktop_Qt_5_7_0_MinGW_32bit-Release
mkdir package
cd package
windeployqt ..\release\Kromophone.exe --dir . --release --qmldir E:\src\Kromophone\kromophone-ui
copy ..\release\Kromophone.exe .
cd E:\src\Kromophone
