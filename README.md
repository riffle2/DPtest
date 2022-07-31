# DPtest
这个Project是为了解答下面的智力题。
界面使用了MFC， 也用到STL的容器（vector，set）和算法（sort，random）
然后在解答的处理里用到了一下C++11的特性。 auto，constexpr，lambda函数


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