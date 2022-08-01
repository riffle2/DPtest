# DPtest
这个Project是为了解答下面的智力题。
界面使用了MFC， 也用到STL的容器（vector，set）和算法（sort，random）
然后在解答的处理里用到了一下C++11的特性（auto，constexpr，lambda函数）

---
智力题：
小明由于工作原因，经常到某地出差。当地的公共交通提供三种形式的交通卡:
1) 一日票。有效期1日，票价2元
2) 七日票。有效期7日，票价7元
3) 月票。有效期30日，票价25元

已知小明之后 M 天的行程，请帮助小明计算出最省钱的购票方式，给出最少需要花费的交通费。
注:1<= M<= 100.000
样例:
输入 : {1,3,5,6,8,9,29,30}
输出:13
注:第1天买一日票，第 3-9天买七日票，第 29天买一日票，第30天买一日票

---
运行的输出结果：

![运行结果图](https://github.com/riffle2/DPtest/blob/master/result.jpg)
Result:  Minimum Cost:13		(Calc Time:0ms,Search total routine :22)
Data:
1,3,5,6,8,9,29,30,
ticket Detail:
Day1, buy day ticket
Day3, buy week ticket
Day29, buy day ticket
Day30, buy day ticket

Result:  Minimum Cost:23305		(Calc Time:3344ms,Search total routine :44350)
Data:
1,2,3,5,6,7,9,11,12,13,14,16,17,19,21,22,23,24,26,27,29,30,33,36,39,40,41,42,45,47,49,50,52,53,54,
55,58,59,60,61,62,64,65,66,70,71,73,74,76,77,78,81,82,83,84,85,87,88,90,91,93,94,95,97,98,100,102,
...,29992,29993,29994,29995,29996,29997,29999,30000,
ticket Detail:
Day1, buy month ticket
Day33, buy day ticket
Day36, buy day ticket
Day39, buy week ticket
Day47, buy day ticket
Day49, buy month ticket
Day81, buy month ticket
...
Day29965, buy day ticket
Day29968, buy day ticket
Day29973, buy month ticket

---
从性能测试来看，3万天，60%的时间在当地。3.3秒的运行时间。
从性能测试图看，大部分的时间花在vector的存取上。函数DeleteHignCost的大部分时间也在vector的iterator
现在的结果是可以忍受，但还有很多的优化余地。 对Vector的使用稍加优化，可以得到很大的性能提升
![性能测试图](https://github.com/riffle2/DPtest/blob/master/performance.jpg)
