# 计算机图形学

## 题目

实现一个画曲线软件，能显示点坐标和曲线方程（要求能显示点坐标和曲线方程，能选择样条曲线的次数，能画多段曲线）   
[码云仓库](https://gitee.com/liulu1998/CGproject)
## 实现
基于```MFC```, 使用 ```C++``` 语言, ```Visual Studio 2019``` 构建项目

## 功能

- 绘制不同次数的 ```Bezier 曲线``` 和 ```B 样条曲线``` 

- 添加、删除曲线

- 添加、删除控制点

- 保存曲线信息，从文件加载曲线信息

## 成员

- [韩继锋](https://gitee.com/h453)

- [刘崇鹏](https://github.com/amberOoO)

- [刘俊](https://gitee.com/flare_wing)

- [刘陆](https://github.com/liulu1998)

## 仓库文件结构

```
.
├── CurveCG         // 本组 vs 工程
└── README.md
```

## 分支说明

- backup 使用 基于基函数的曲线点生成算法 的分支, 仅做存档

- master 主分支, 使用 基于矩阵的曲线点生成算法, 性能有提升

