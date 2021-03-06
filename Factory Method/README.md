# Factory Method

## 动机（Motivation）
+ 在软件系统中，经常面临着创建对象的工作；由于需求的变化，需要创建的对象的具体类型经常变化。
+ 如何应对这种变化？如何绕过常规的对象创建方法(new)，提供一种“封装机制”来避免客户程序和这种“具体对象创建工作”的紧耦合？

## 模式定义
定义一个用于创建对象的接口，让子类决定实例化哪一个类。Factory Method使得一个类的实例化延迟（目的：解耦，手段：虚函数）到子类。
——《设计模式》GoF

## 要点总结
+ Factory Method模式用于隔离类对象的使用者和具体类型之间的耦合关系。面对一个经常变化的具体类型，紧耦合关系(new)会导致软件的脆弱。
+ Factory Method模式通过面向对象的手法，将所要创建的具体对象工作延迟到子类，从而实现一种扩展（而非更改）的策略，较好地解决了这种紧耦合关系。
+ Factory Method模式解决“单个对象”的需求变化。缺点在于要求创建方法/参数相同。

## 代码
+ FileSplitter.cpp -- 变化部分
+ ISplitterFactory.cpp -- 稳定部分
+ MainForm.cpp -- 注释包含使用设计模式之前，没注释的是使用了设计模式之后

## 通俗讲解
看下面这串代码：
A a = new A()

A 是具体类，依赖于具体类并不能很好的应对变化，如果日后功能扩展，我们要new 出来一个不同的对象呢？
画出类图是这样的：

a <-----  A

尝试使用多态解决这一问题，写出如下的代码：

IA a = new A()

其中IA是一个虚方法，A 继承了 IA， 画出类图是这样的：
		  IA （稳定）
		  +
		  |
		  |	
a <------ A   (不稳定) 

仍然不好，因为我们还要依据具体的A来创建实例a,也就是我们仍然依赖于一个不稳定的东西

多做几个类，用多态new,类图是这样子的：


		  IA -----------》AFactory（稳定）
		  +		  			+
		  |		  			|
		  |		  			|
a <------ A <------------ ACreator (不稳定) 

这样，使用多态new，我们就能实现解耦
IA a = (new ACreator())->createA()

用的时候，传入某个XCreator，调用自身的createX方法，就会返回一个X，这个X恰好是IA的子类，多态用的漂亮！

然而，我们应该看出工厂模式的*缺陷*：如果我们想这个工厂能生产出*新产品*，只有打破-----------》，接下来要做的就是IA派生出新的子类X，AFactory派生出新的子类XCreator,再利用多态性在运行时实现 XCreator()-> createX()

Notes：

a <------ A： 类A创建了对象a
a -------》 A: A中包含了a
a ——————+ A: A是父类， a是子类

比喻

张三能造剪刀，李四能造锤子，如果我想要剪刀，叫张三帮我造，想要锤子就叫李四帮我造。但是张三，李四不靠谱，经常不见人影（相知小兔子一样经常变化），怎么解决？找一工厂A，让他雇佣（派生）张三，李四，再与工厂A签订协议（协议<=>代码<=>编译时行为），约定A需要我们造工具，工具可以是剪刀和锤子（对应工具派生出剪刀，锤子，签订协议意味着工厂A中有一指针指向工具类），剪刀需要张三为我造，锤子需要李四为我造。签订协议后的某一天，我想要一工具X，如果我告知工厂A我需要张三为我干活，依据协议，A也就知道其实我需要的是剪刀，同理我要李四为我干活A就会知道我需要的是锤子。这种我不直接告诉A我需要啥，而是告诉他我需要谁为我干活类似于多态机制。

当然，这种方式的缺点显然：协议已经签订，不应该再改。但是如果哪一天我想要镰刀，那该咋整？只有撕毁协议，再签一个新的协议（类似于要打破-----------》）。原则上一个设计模式中稳定的部分不应该被打破，一旦来了某种新的变化使得该模式不得不打破原有结构时（稳定部分也要变化），就是该模式不能handle的地方，自然也是该模式的缺陷。

类图如下
工具-----------》工厂A
  +				   +
  |				   |
  |				   |
锤子  剪刀<----张三  李四
 ^					   |			
 |---------------------|
