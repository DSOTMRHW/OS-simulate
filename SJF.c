#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESS 5  // 最多进程数
#define MAX_TIME 30  // 最多时间片数

// 进程控制块结构体
typedef struct PCB {
	int id;  // 进程标识数 ID
	int priority;  // 进程优先数 PRIORITY
	int alltime;  // 进程运行所需 CPU总时间片数 ALLTIME
	int cputime;  // 已占用 CPU 时间片数 CPUTIME
	int startblock;  // 进程的待阻塞时间片数 STARTBLOCK
	int blocktime;  // 进程被阻塞的时间片数 BLOCKTIME
	int state;  // 进程状态 STATE
	struct PCB *next;  // 队列指针 NEXT，用来将 PCB 排成队列
} PCB;

PCB *head_ready = NULL;  // 就绪队列头指针
PCB *head_block = NULL;  // 阻塞队列头指针

// 创建进程控制块
PCB *create_pcb(int id, int priority, int alltime, int startblock, int blocktime) {
	PCB *pcb = (PCB*)malloc(sizeof(PCB));  // 为进程控制块分配内存
	pcb->id = id;  // 设置进程标识数
	pcb->priority = priority;  // 设置进程优先数
	pcb->alltime = alltime;  // 设置进程运行所需 CPU总时间片数
	pcb->cputime = 0;  // 初始化已占用 CPU 时间片数
	pcb->startblock = startblock;  // 设置进程的待阻塞时间片数
	pcb->blocktime = blocktime;  // 设置进程被阻塞的时间片数
	pcb->state = 0; // 初始化进程状态为就绪状态
	pcb->next = NULL; // 初始化队列指针
	return pcb; // 返回创建的进程控制块
}

// 将进程控制块插入就绪队列
void insert_ready_queue(PCB *pcb) {
	if (head_ready == NULL) { // 如果就绪队列为空，直接将进程控制块插入到头部
		head_ready = pcb;
	} else { // 否则，找到就绪队列的末尾并插入
		PCB *p = head_ready;
		while (p->next != NULL) {
			p = p->next;
		}
		p->next = pcb;
	}
}

// 将进程控制块从就绪队列中移除
void remove_ready_queue(PCB *pcb) {
	if (pcb == head_ready) { // 如果进程控制块在头部，将头部指针指向下一个进程控制块
		head_ready = pcb->next;
	} else { // 否则，找到该进程控制块的前一个进程控制块，将其指针指向下一个进程控制块
		PCB *p = head_ready;
		while (p != NULL && p->next != pcb) {
			p = p->next;
		}
		if (p != NULL) {
			p->next = pcb->next;
		}
	}
	pcb->next = NULL; // 将进程控制块的队列指针设置为空
}

// 将进程控制块插入阻塞队列
void insert_block_queue(PCB *pcb) {
	if (head_block == NULL) { // 如果阻塞队列为空，直接将进程控制块插入到头部
		head_block = pcb;
	} else { // 否则，找到阻塞队列的末尾并插入
		PCB *p = head_block;
		while (p->next != NULL) {
			p = p->next;
		}
		p->next = pcb;
	}
}

// 将进程控制块从阻塞队列中移除
void remove_block_queue(PCB *pcb) {
	if (pcb == head_block) { // 如果进程控制块在头部，将头部指针指向下一个进程控制块
		head_block = pcb->next;
	} else { // 否则，找到该进程控制块的前一个进程控制块，将其指针指向下一个进程控制块
		PCB *p = head_block;
		while (p != NULL && p->next != pcb) {
			p = p->next;
		}
		if (p != NULL) {
			p->next = pcb->next;
		}
	}
	pcb->next = NULL; // 将进程控制块的队列指针设置为空
}

// 打印就绪队列中的进程信息
void print_ready_queue() {
	printf("\n就绪队列中的进程：");
	PCB *p = head_ready;
	while (p != NULL) {
		printf("%d ", p->id);
		p = p->next;
	}
	printf("\n");
}

// 打印阻塞队列中的进程信息
void print_block_queue() {
	printf("阻塞队列中的进程：");
	PCB *p = head_block;
	while (p != NULL) {
		printf("%d ", p->id);
		p = p->next;
	}
	printf("\n");
}

void sort_ready_queue() {
	PCB *p = head_ready; // 定义指针p指向就绪队列的头部
	PCB *q; // 定义指针q
	
	while (p != NULL) { // 循环遍历就绪队列
		q = p->next; // 让q指向p的下一个进程
		while (q != NULL) { // 再次循环遍历就绪队列
			if (p->alltime > q->alltime) { // 如果p的总时间大于q的总时间
				// 交换p和q的信息
				int temp_id = p->id;
				int temp_priority = p->priority;
				int temp_alltime = p->alltime;
				int temp_cputime = p->cputime;
				int temp_startblock = p->startblock;
				int temp_blocktime = p->blocktime;
				int temp_state = p->state;
				p->id = q->id;
				p->priority = q->priority;
				p->alltime = q->alltime;
				p->cputime = q->cputime;
				p->startblock = q->startblock;
				p->blocktime = q->blocktime;
				p->state = q->state;
				q->id = temp_id;
				q->priority = temp_priority;
				q->alltime = temp_alltime;
				q->cputime = temp_cputime;
				q->startblock = temp_startblock;
				q->blocktime = temp_blocktime;
				q->state = temp_state;
			}
			q = q->next; // 移动q到下一个进程
		}
		p = p->next; // 移动p到下一个进程
	}
}	//因为被指针绕晕了，只能采用交换数据这种方式进行，我写出来自认为完备的算法交换结果只进行一半。

int main() {
	printf("模拟进程调度（SJF算法） 作者黄家伟，HNU计科院OS课程设计\n\n");
	
	// 创建进程控制块并插入就绪队列
	PCB *pcb1 = create_pcb(1, 1, 6, 2, 3); //create_pcb(int id, int priority, int alltime, int startblock, int blocktime)
	insert_ready_queue(pcb1);
	PCB *pcb2 = create_pcb(2, 2, 4, 3, 1); //create_pcb(int id, int priority, int alltime, int startblock, int blocktime)
	insert_ready_queue(pcb2);
	PCB *pcb3 = create_pcb(3, 3, 8, 4, 1); //create_pcb(int id, int priority, int alltime, int startblock, int blocktime)
	insert_ready_queue(pcb3);
	PCB *pcb4 = create_pcb(4, 4, 5, 2, 3); //create_pcb(int id, int priority, int alltime, int startblock, int blocktime)
	insert_ready_queue(pcb4);
	PCB *pcb5 = create_pcb(5, 5, 7, 1, 2); //create_pcb(int id, int priority, int alltime, int startblock, int blocktime)
	insert_ready_queue(pcb5);
	
	PCB *running = NULL; // 当前正在运行的进程
	
	printf("更新SJF算法前的就绪队列：");
	print_ready_queue();
	printf("更新SJF算法后的就绪队列：");
	sort_ready_queue();
	print_ready_queue();
	
	for (int i = 0; i < MAX_TIME; i++) {
		printf("\n时间片%d：", i + 1);
		// 检查就绪队列中的进程是否有进入阻塞状态的
		PCB *p = running;
		while (p != NULL) {
			if (p->startblock == p->cputime) { // 如果进程运行了足够的时间片，将其从就绪队列中移除并插入阻塞队列
				p->state = 1; // 设置进程状态为阻塞状态
				//				remove_ready_queue(p); // 从就绪队列中移除**********
				running = NULL;
				insert_block_queue(p); // 插入阻塞队列
			}
			p = p->next;
		}
		// 检查阻塞队列中的进程是否有进入就绪状态的
		p = head_block;
		while (p != NULL) {
			if (p->blocktime == 0) {  // 如果进程阻塞的时间片已用完，将其从阻塞队列中移除并插入就绪队列
				p->state = 0;  // 设置进程状态为就绪状态
				remove_block_queue(p);  // 从阻塞队列中移除
				insert_ready_queue(p);  // 插入就绪队列
			} else {
				p->blocktime--;  // 如果进程阻塞的时间片还没用完，将其阻塞的时间片数减一
			}
			p = p->next;
		}
		
		
		// 如果有进程正在运行，将其运行时间片减一
		if (running != NULL) {
			printf("\n正在运行进程%d，", running->id);
			running->cputime++;  // 将进程的已占用 CPU 时间片数加一
			if (running->cputime == running->alltime) {  // 如果进程已经运行完毕，将其从就绪队列中移除
				running = NULL;
				printf("\n进程完毕！！！！");
			}
		}
		else{
			if (head_ready != NULL) {
				running = head_ready;
				printf("\n正在运行进程%d，", running->id);
				remove_ready_queue(running);
			}
			running->cputime++;  // 将进程的已占用 CPU 时间片数加一
			if (running->cputime == running->alltime) {  // 如果进程已经运行完毕，将其从就绪队列中移除
				running = NULL;
				printf("\n进程完毕！！！！");
			}
			else
				printf("\n没有进程正在运行，");
		}
		print_ready_queue();
		print_block_queue();
	}
	
	return 0;
}


