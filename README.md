RTOS_LM3S_Keil
==============


http://hmean.github.io/RTOS_LM3S_Keil/ 为使用doxygen输出的ucos文档,包括函数静态调用图，数据结构等.
出于学习目的,没有很好的掩藏代码信息，部分图片会比较大。

[main的callee图](http://hmean.github.io/RTOS_LM3S_Keil/docbydoxygen/app_8c_a840291bc02cba5474a4cb46a9b9566fe_cgraph.png)
展示了main都调用了哪些函数.
![main的callee图](http://hmean.github.io/RTOS_LM3S_Keil/docbydoxygen/app_8c_a840291bc02cba5474a4cb46a9b9566fe_cgraph.png)

[OS_SchedNew的caller图](http://hmean.github.io/RTOS_LM3S_Keil/docbydoxygen/os__core_8c_a4c012d2e7a886885bd6f80ca15b295b8_icgraph.png)
把操作系统何时可能导致上下文切换展现得比较清晰。
![OS_SchedNew的caller图](http://hmean.github.io/RTOS_LM3S_Keil/docbydoxygen/os__core_8c_a4c012d2e7a886885bd6f80ca15b295b8_icgraph.png)

ucos ii port to TI lm3s1968（cortex m3，this project aim at rtos  learning. anyone use in commercial, please visit Micrium website
for license info.


