# MiniConda 安装与使用

下载官方安装包安装miniconda



常用指令

1. 查看版本： conda --version

 2.	查看已安装包：conda --list
 3.	安装包：conda install numpy
 4.	卸载包：conda uninstall numpy
 5.	配置独立开发环境：conda create -n learn  python=3
 6.	切换环境 ： source active learn


通过修改.condarc 以更新anaconda的仓库地址



conda在指定目录下创建虚拟环境

conda create --prefix=//// python=3

