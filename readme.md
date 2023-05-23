这是一个供TrafficMonitor使用的插件。

用aida64共享内存功能，监测显卡和CPU的功耗，理论上只要Aida64支持的参数，都可以检测。
但由于TrafficMonitor已经提供了常见参数的检测，这里只增加了功耗的检测。

如需要其它参数请在**Aida64ShareMemory.cpp**中添加参数**AIDA64共享内存中的名字**、**标签**和**单位**，并确保AIDA64共享内存中有这个数据。

