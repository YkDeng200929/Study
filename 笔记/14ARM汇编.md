# day1
## 上午
1. 汇编代码结构

		声明一个全局变量
		.global _start
		
		_start: 声明一个标签
			b stop	跳转到stop标签
		
		stop:
			b stop
			
2. 操作数的三种形式
	1. 立即数
		- 立即数判断方式
		- (ffff有效数, 什么是有效数?)
			- 如果一个数的反码是立即数, 那么这个数是立即数
	2. 寄存器
	3. 对寄存器的移位
3. 命令的组成
4. mov, mvn, lsl, add, 

## 下午
1. sub
2. cmp (**实际上是判断CPSR寄存器的NZCV位/条件位**)
	- N negative
	- Z zero
	- C
	- V
3. **影响NZCV位的另一种方式**
	- 在操作码后加上s
4. bl 下一条指令的地址存放在lr(link register)中
	- `mov pc, lr`可以执行bl的下一条指令
	- **或者 ldr pc, =<标签>**
5. 位运算指令

# day2
1. bic
2. ldr, str
	- 单寄存器数据传送
	- 30000000地址无法写入, 为什么
		- memorymap 30000000没有写入权限
		- 查看方式
			- asm.init文件
			- debug控件中查看
		- **低对低: 小端**

	- **基址变址寻址**
		- 前索引:[, #] (写到寄存器加上偏移量后的地址)
		- 后索引:[], #	(写到寄存器,然后地址加上偏移量)
		- 自动索引: [,#]! (也就是结合了以上两种: 写入寄存器加上偏移量后的地址后让地址再加上#)
3. ldm, stm
	- 多数据访问(stm, ldm)
		- **目标寄存器是否有感叹号的区别**
			- 加上感叹号: 目标寄存器数值会变化
			- 不加感叹号: 目标寄存器数值不会变化为操作后地址的值
		- **模式**
			- 先: 先赋值给目标地址后移动地址后再赋值
			- 后: 先移动地址后再给目标地址赋值, 然后重复直到赋值完毕
			- 规律(若目标寄存器使用!处理)
				- ib <--> da
				- ia <--> db
				- a最后指向空, b最后指向的地方有数据
		- **寄存器列表写法**
			- 若寄存器连续, 可以{r1-r5}, **寄存器号大应对应内存高地址, 且寄存器应从小到大写**
			- 可以用","隔开每个寄存器
		- 是否有^的区别
	- **栈操作:先设置sp的值**
		- 模式:arm默认满减栈(向下增长), 4的倍数的地址可以存储数据
		- 空堆栈与满堆栈
			- 满堆栈:sp指向最后压入堆栈的地方有数据
		- ***入栈***: `stmfd sp!, {Rm-Rn}`
		- 出栈: `ldmfd sp!, {Rm-Rn}`
4. mrs, msr
	- 含义
		- mrs: **Move to Register(通用寄存器)** from Special register
		- msr: **Move to Special register** from Register(当前程序状态寄存器)
	- 通过更改cpsr的第七位(T)可以更改arm模式或thumb模式
5. arm7采用三级流水线(fetch->decode->execute)

# day3
## 上午
1. 流水线
	- 最佳流水线(cpi = 1)
	- ldr流水线(cpi = 1.5)
		- 因为要访问内存, 所以在ldr访问内存时后面的指令会stall, 等待ldr执行完后再继续执行
		- 所以会少执行几条指令
		- 为了提高效率, 所以出现了多级流水线
	- 分支流水线
		- 跳转时lr会先保存pc的地址, 然后跳转到其他地址执行完指令后会对lr保存的地址进行一个调整
		- 当跳转的时候bl的下一条指令运行到解码阶段, 调整回来时又会重新执行一遍该过程, 所以会造成浪费
2. 伪指令(形似但不是的汇编指令, arm核无法识别, 需要编译器处理后才能识别)
	- 仿真的pc指向与实际pc指向不一样, 仿真pc指向当前执行的指令, 而实际是指向预取指令(当前执行指令地址 + 8, 因为三级流水线, 当前指令执行时下一条指令在解码, 间隔两个)
	- 链接地址与运行地址(理论上链接地址与运行地址一样)
		- 链接地址: 你默认设置的程序起始地址
		- 运行地址: 程序执行的起始地址, 可能是你规定的一个起始地址
		- 如果运行地址与链接地址不一样, 使用`ldr rd, =标签`方法获得标签地址的话, 会导致获得的标签地址值不正确, 所以有了`adr`
	- 有哪些伪指令(为什么ldr 不能替代 mov)
		1. `ldr Rd, =操作数`
		2. `ldr Rd, =标签` (会得到标签地址)， 写死到机器码中 `ldr, rd, [pc, #0x00000004]` 它下一个写死在机器码中
		3. `ldr Rd, 标签` (保存标签地址里的值)
		4. `adr Rd, 标签` (**准确**得到标签地址), 没有写死到机器码中 `add rd, pc, #0x00000004`
		5. `.word 0x12345678` 分配并直接将值写到内存中
## 下午
1. 参数传递
	- 函数的前4个参数通过r0 - r3来传递, 超过四个的参数通过栈来传递`stmfd sp!, {r0-rn}`
	- ***函数的返回值: 通过r0带回***
2. 为什么函数中的局部变量没有被清除
	- 通过反汇编能看到最后是用sub指令移动sp而非清零,所以值没被重写,若再调用其他函数后这些局部变量就会被复写为0
3. asm to c
	- 函数名就是一个标签
	- `volatile`:防止变量被编译器优化 (定义全局变量的时候需要加上volatile)
4. c with asm
	- 格式
		- "指令 \n"	
		- : 输出列表 0 "=r" (变量名)
		- : 输入列表 1, 2.. "r"(变量名1), "r"(变量名2)
		- : 修改列表 "发生修改的寄存器"

# day4
1. 软中断异常
	- arm的工作模式
	- arm的异常模式
		- 五种
			- 因为7种中有四种异常可以两两归类为一种异常
	- 中断向量表
	- 软中断
		- ^的含义
---
# 其他的重要部分
1. 异常处理
	- 异常产生时, ARM核会自动做的内容
		1. CPSR的值拷贝到异常模式的SPSR
		2. 设置CPSR相应位
			1. 进入ARM状态
			2. 进入对应的异常模式
			3. 禁止中断
		3. 保存pc的值到异常模式的1r
		4. 将pc设置异常向量表的相应位置
	- 程序员要做的事情
		1. 设置异常向量表（在异常向量表中写跳转指令，跳转指定异常处理函数）
		2. 告诉ARM核异常向量表的基地址
			1. cortex-A系列之前，异常向量表可以存放在0x0000，0000（低地址）或Oxffff，0000（高地址）cp15（协处理器）.c1（寄存器）决定异常向量存放在高地址还是低地址
			2. cortex-A系列之后，异常向量表可以存放在任意位置cp15（协处理器）.c12（寄存器）保存异常向量表的基地址
		3. 编写异常处理函数
			1. 设置sp寄存器
			2. 将通用的寄存器（x0-12）进行压栈保护
			3. 异常处理的事情
			4. 异常返回
				1. 恢复rO-r12(出栈)
				2. 恢复cpsr（spsr->cpsr）
				3. 恢复pc（1r->pc）