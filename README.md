# cubesolver
这个项目提供一个魔方从视觉识别到求解过程再到通过串口发送给单片机的方案。

之前我也写过一个解魔方的程序但是由于刚上大二，而且当初时间也比较紧迫。所以很多细节不是很完美。
所以准备把之前的代码重新写一遍。然后加强一些地方，就酱。希望看到的同学能够多多指正我的错误也十分欢迎和我交流。我的邮箱是herenzhie@gmail.com
因为大三在准备保研天天忙于刷绩点所以可能会更新的有点慢。但我会坚持写完的。

## 11.27更新

i first thought this would be the theme of the 2018 compitition. But i find that this year the compitition theme is the same as last year. SO cinsidering the fairness of the compitition， i delete some code. 

sorry :(

## 11.13更新
目前正在写算法部分

开发环境是win10＋VS2017

我使用的是kociemba算法 这个算法可以算出一个在21步左右的稳定的解。具体原理请参考[该链接](http://kociemba.org/download.htm)

Tip.在使用的时候需要注意自己电脑的系统和编译器的版本。

## 11.7更新
目前正在写视觉部分

开发环境是win10＋VS2017   opencv3.4 is also required

逻辑大概是这样：

1. 调用两个摄像头分别读取三个面
2. 图像预处理 直方图均衡化 模糊
3. 手动分割并提取RGBHSV六个值的平均值 这样三个面会有 27*6个值

4. 调用opencv ml库里面的SVM 预测值并返回（需要提前训练好模型）
5. 对收集的颜色进行三次检测 分别是总颜色 每个单独的颜色 以及魔方色块
6. 输出收集的颜色

