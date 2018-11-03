// 以下使用抽象工厂实现重构
//数据库访问有关的基类
class IDBConnection{};
class IDBCommand{};
class IDataReader{};

class IDBFactory{
public:
    virtual IDBConnection* CreateDBConnection()=0;
    virtual IDBCommand* CreateDBCommand()=0;
    virtual IDataReader* CreateDataReader()=0;
};


//支持SQL Server
class SqlConnection: public IDBConnection{};
class SqlCommand: public IDBCommand{};
class SqlDataReader: public IDataReader{};


class SqlDBFactory:public IDBFactory{
public:
    virtual IDBConnection* CreateDBConnection()=0;
    virtual IDBCommand* CreateDBCommand()=0;
    virtual IDataReader* CreateDataReader()=0;
 
};

//支持Oracle
class OracleConnection: public IDBConnection{};
class OracleCommand: public IDBCommand{};
class OracleDataReader: public IDataReader{};


class EmployeeDAO{
    IDBFactory* dbFactory;
    
public:
    vector<EmployeeDAO> GetEmployees(){
        // 1 - 新建一个IDBConnection对象
        IDBConnection* connection = dbFactory->CreateDBConnection();
        connection->ConnectionString("...");

        // 2 - 新建一个IDBCommand对象并连接相应的IDBConnection
        IDBCommand* command = dbFactory->CreateDBCommand();
        command->CommandText("...");
        command->SetConnection(connection); //关联性

        // 3 - 做相应的查询操作
        IDBDataReader* reader = command->ExecuteReader(); //关联性
        while (reader->Read()){}
    }
};
