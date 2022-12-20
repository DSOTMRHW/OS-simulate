# My-OSproject
含页面置换算法和模拟进程调度 两个模拟实现


模拟进程调度要求如下
（1）对5个进程分别采用
高响应比优先、
先来先服务算法、
短进程优先算法、
时间片轮转调度算法、
动态优先级调度算法共5种算法执行调度模拟。
（2）每个用来标识进程的进程控制块 PCB 可用结构来描述，包括以下字段（具体
字段及数量可根据需要自行定义，此处仅供参考）：(a) 进程标识数 ID。(b) 进程优
先数 PRIORITY，并规定优先数越大的进程，其优先权越高。(c) 进程运行所需
CPU总时间片数ALLTIME，已占用 CPU 时间片数 CPUTIME。当进程运行完毕时
，ALLTIME 变为 0。(d) 进程的待阻塞时间片数 STARTBLOCK，表示当进程再运
行 STARTBLOCK个时间片后，进程将进入阻塞状态。(e) 进程被阻塞的时间片数
BLOCKTIME ，表示已阻塞的进程再等待 BLOCKTIME 个时间片后，将转换成就
绪状态。(f) 进程状态 STATE。(g) 队列指针 NEXT，用来将 PCB 排成队列。
（3）优先数改变的原则：进程在就绪队列中呆一个时间片，优先数增加 1。 进程
每运行一个时间片，优先数减 3（这一规则主要用于动态优先级调度算法）。
（4）为了观察每个进程的调度过程，程序应将每个时间片内的进程的情况显示出
来，包括正在运行的进程，处于就绪 队列中的进程和处于阻塞队列中的进程。



个人解释：模拟进程调度按照C17标准编写，命名基本符合软件工程要求



关于DPS算法：
抢占式动态优先级调度算法和非抢占式动态优先级调度算法是两种调度算法，它们的主要区别在于进程之间是否可以抢占 CPU 资源。

抢占式动态优先级调度算法允许进程在运行过程中被抢占，也就是说，当另一个进程的优先级比当前正在运行的进程高时，调度算法会立即抢占当前正在运行的进程，让优先级较高的进程获得 CPU 资源。这种调度算法在处理实时进程时非常有用，因为实时进程的时间要求通常比较严格，如果不能立即响应，就会对系统的正常运行造成影响。

非抢占式动态优先级调度算法不允许进程在运行过程中被抢占，也就是说，即使有更高优先级的进程到来，也不会中断当前正在运行的进程。这种调度算法通常用于处理非实时进程，因为非实时进程的时间要求通常不是很严格，可以容忍一定的延迟。

总的来说，抢占式动态优先级调度算法更适合处理实时进程，而非抢占式动态优先级调度算法更适合处理非实时进程。但是，这两种调度算法都是动态优先级调度算法，也就是说，它们都会根据进程的运行情况动态地调整进程的优先级。

在抢占式动态优先级调度算法中，当一个进程被抢占时，它的优先级会提高。这样，当前正在运行的进程就有可能被抢占，从而让优先级更高的进程获得 CPU 资源。

在非抢占式动态优先级调度算法中，当一个进程被中断或者完成时，它的优先级会提高。这样，当前正在运行的进程就不会被抢占，而是等到它自己的运行时间用完之后才让出 CPU 资源。
