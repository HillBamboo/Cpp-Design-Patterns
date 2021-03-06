class MainForm : public Form
{
    SplitterFactory*  factory;//工厂

public:
    
    MainForm(SplitterFactory*  factory){
        this->factory=factory;
    }
    
	void Button1_Click(){

		// 以下的两种方式都没有很好的解决具体类依赖的问题
		// BinarySplitter splitter = new BinarySplitter()
		// ISplitter * splitter = new BinarySplitter();//依赖具体类
        
        // factory 是哪一个ConcreteSplitterFactory，就会调用
        // 相应的CreateSplitter创建相应的 ConcreteSplitter（Product）
		ISplitter * splitter=
            factory->CreateSplitter(); //多态new
        
        splitter->split();

	}
};



