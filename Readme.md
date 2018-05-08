* 编程语言：C++

* 编译工具：Apple LLVM version 7.0.2 (clang-700.1.81)

* 测试环境：Mac OS X High Sierra 10.13.1

* 额外使用的库：无

* 编译方式：在src路径下运行make，生成可执行文件hw2

* 运行方式：在src路径下建立文本文件`in.txt`，并运行可执行文件hw2。输出数据将写入同目录下的文件文本文件`out.txt`中。

* 输入格式：

	包含n+1行。
	
	第1行为输入点的个数n；  
	第2~n+1行每行输入两个小数：第i+1行前后两个数分别代表第i号点的经度和纬度（仅可输入度数，不支持输入分数和秒数，忽略度数符号）
	
* 输出格式：
	
	包含n行，每行一个数字。其中第 i 行的数字表示 i 号点与某号点之间有无线回传连接。若这个数字是0，表示这个点是宿主点。

