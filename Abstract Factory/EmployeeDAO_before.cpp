// 员工信息被存在某个数据库中，我们需要将其取出并做某些查询操作
// 如果我们现在使用的数据库是SQLServer, 没问题，我们已经实现了相应的类，但如果我们将数据库迁移至MySQL，我们就要做多少的低效操作？
// 改 SqlConnection， SqlCommand的类定义，然后改下面的代码，$_$人生苦短
class EmployeeDAO{
    
public:
    vector<EmployeeDAO> GetEmployees(){
        // 下面是三个类被关联在一起： SQLServer有自己的SqlConnection，SqlCommand，SqlDataReader
        // 如果我们将数据迁移至MySQL，相应的也要有自己的SqlConnection，SqlCommand，SqlDataReader
        // 1 - 新建一个SqlConnection对象
        SqlConnection* connection = new SqlConnection();
        connection->ConnectionString = "...";

        // 2 - 新建一个SqlCommand对象并连接 SqlConnection
        SqlCommand* command = new SqlCommand();
        command->CommandText="...";
        command->SetConnection(connection);

        // 3 - 做相应的查询操作
        SqlDataReader* reader = command->ExecuteReader();
        while (reader->Read()){}
    }
};
