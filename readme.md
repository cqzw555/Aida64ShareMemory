# Aida64ShareMemory

这是一个供TrafficMonitor使用的插件。

用aida64共享内存功能，监测显卡和CPU的功耗，理论上只要Aida64支持的参数，都可以检测。
但由于TrafficMonitor已经提供了常见参数的检测，这里只增加了功耗的检测。

如需要其它参数请在**Aida64ShareMemory.cpp**中添加参数**AIDA64共享内存中的名字**、**标签**和**单位**，并确保AIDA64共享内存中有这个数据。

# 用法
- 将这个Aida64ShareMemory.vcxproj添加到TrafficMonitorPlugins的解决方案里面编译,自行修改
- 直接在TrafficMonitor的plugins中添加realse的dll文件，只能监测功耗

# 注意事项
- AIDA64版本：测试使用的版本是6.88.6400，可以检测功耗，
    6.00.5100只能监测显卡功耗的GPU TDP%，其他版本请自行确认