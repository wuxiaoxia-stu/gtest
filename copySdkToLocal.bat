
echo "copy sdk to local 执行依赖"


::	公共库
copy Z:\客户端SDK_new\include 		.\AyjPaicsClient\depends\sdk\include

copy Z:\客户端SDK_new\lib 			.\AyjPaicsClient\depends\sdk\lib

copy Z:\客户端SDK_new\bin\debug\AyjPaicsSdkLibDemo.exe 			.\Build\debug
copy Z:\客户端SDK_new\bin\release\AyjPaicsSdkLibDemo.exe 		.\Build\release

copy Z:\客户端SDK_new\bin\debug\AyjPaicsSdkLib.dll				.\Build\debug
copy Z:\客户端SDK_new\bin\release\AyjPaicsSdkLib.dll  			.\Build\release

copy Z:\客户端SDK_new\bin\debug\LPMPaicsAuthVerify.dll 			.\Build\debug
copy Z:\客户端SDK_new\bin\release\LPMPaicsAuthVerify.dll 		.\Build\release



echo 脚本执行完成

