#include<iostream>
#include<string>
#include<chrono>
#include<mutex>
#include<memory>
#include<fstream>
#include<sstream>
#include<iomanip>
#include<concepts>
#include<vector>
#include<map>
using namespace std;

#define assert(x,y) if (!(x)) { assert_fail(#x,y, __FILE__, __LINE__); }

void assert_fail(const char *str, const char* msg,const char *file, int line)
{
  std::cerr << "Assertion : " << msg <<endl<<
               file << ":" << line <<" : "<<str<< std::endl;
  abort();
}

std::string return_current_time_and_date()
{
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);

    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
    return ss.str();
}

class Logger_End_Of_File{
    public:
        Logger_End_Of_File(){
            static bool condition = true;
            
            assert(condition , "Logger_End_Of_File must be initialised only once");
            
            condition = false;
        }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////
// HELPERS /////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////

class ERROR_Helper{
    public:
        ERROR_Helper(){
            static bool condition = true;
            
            assert(condition , "ERROR_Helper must be initialised only once");
            
            condition = false;
        }
};
class INFO_Helper{
    public:
        INFO_Helper(){
            static bool condition = true;
            
            assert(condition , "INFO_Helper must be initialised only once");
            
            condition = false;
        }
};
class WARNING_Helper{
    public:
        WARNING_Helper(){
            static bool condition = true;
            
            assert(condition , "WARNING_Helper must be initialised only once");
            
            condition = false;
        }
};
class DEBUG_Helper{
    public:
        DEBUG_Helper(){
            static bool condition = true;
            
            assert(condition , "DEBUG_Helper must be initialised only once");
            
            condition = false;
        }
};
class TRACE_Helper{
    public:
         //constinit static bool value = true;
        TRACE_Helper(){
            static bool condition = true;
            
            assert(condition , "TRACE_Helper must be initialised only once");
            
            condition = false;
        }


};



////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////VARIABLES//////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
ERROR_Helper ERROR;
INFO_Helper INFO;
WARNING_Helper WARNING;
DEBUG_Helper DEBUG;
TRACE_Helper TRACE;
Logger_End_Of_File lend;


////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////LOGGER////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////


class Logger_Info{
    string name;
    shared_ptr<mutex> lock;
    string output="";
    
    public:
        Logger_Info(string s,shared_ptr<mutex> l):name{s},lock{l}{
            //cout<<"Filename : "<<s<<endl;
        }
        Logger_Info(const Logger_Info& l):name{l.name},lock{l.lock},output{l.output}{}
        Logger_Info(Logger_Info&& l):name{move(l.name)},lock{move(l.lock)},output{move(l.output)}{}


        Logger_Info& operator<<(string s){
            //cout<<"S(TRACE) : "<<s<<endl;
            if(name!="")
                output+=s;
            return *this;
        }

        Logger_Info& operator<<(Logger_End_Of_File){
            if(name=="")
                return *this;
            ofstream file{name,ios::app};
            if(!file)
                throw name + " File not found";
            std::unique_lock mylock(*lock);
            file<<return_current_time_and_date()<<" : Logger Entry (INFO) \n\t"<<output<<endl;
            file.close();
            return *this;
        }


        template<integral Integer>
        Logger_Info& operator<<(Integer i){
            //cout << "i :"<<i<<endl;
            if(name!="")
                output+=to_string(i);
            return *this;    
        }


        Logger_Info& operator<<(bool l){
            //cout<<"ok"<<endl;
            if(name=="")
                return *this;
            if(l)
                output+="TRUE";
            else
                output+="FALSE";
            return *this;
        }

        Logger_Info& operator<<(const char* s){
            if(name!="")
                output+=s;
            return *this;
        }

};


class Logger_Warning{
    string name;
    shared_ptr<mutex> lock;
    string output="";
    
    public:
        Logger_Warning(string s,shared_ptr<mutex> l):name{s},lock{l}{
            //cout<<"Filename : "<<s<<endl;
        }
        Logger_Warning(const Logger_Warning& l):name{l.name},lock{l.lock},output{l.output}{}
        Logger_Warning(Logger_Warning&& l):name{move(l.name)},lock{move(l.lock)},output{move(l.output)}{}


        Logger_Warning& operator<<(string s){
            cout<<"S(TRACE) : "<<s<<endl;
            if(name!="")
                output+=s;
            return *this;
        }

        Logger_Warning& operator<<(Logger_End_Of_File){
            if(name=="")
                return *this;
            ofstream file{name,ios::app};
            if(!file)
                throw name + " File not found";
            std::unique_lock mylock(*lock);
            file<<return_current_time_and_date()<<" : Logger Entry (WARNING) \n\t"<<output<<endl;
            file.close();
            return *this;
        }


        template<integral Integer>
        Logger_Warning& operator<<(Integer i){
            //cout << "i :"<<i<<endl;
            if(name!="")
                output+=to_string(i);
            return *this;    
        }


        Logger_Warning& operator<<(bool l){
            //cout<<"ok"<<endl;
            if(name=="")
                return *this;
            if(l)
                output+="TRUE";
            else
                output+="FALSE";
            return *this;
        }

        Logger_Warning& operator<<(const char* s){
            if(name!="")
                output+=s;
            return *this;
        }

};



class Logger_Debug{
    string name;
    shared_ptr<mutex> lock;
    string output="";
    
    public:
        Logger_Debug(string s,shared_ptr<mutex> l):name{s},lock{l}{
            //cout<<"Filename : "<<s<<endl;
        }
        Logger_Debug(const Logger_Debug& l):name{l.name},lock{l.lock},output{l.output}{}
        Logger_Debug(Logger_Debug&& l):name{move(l.name)},lock{move(l.lock)},output{move(l.output)}{}

        

        Logger_Debug& operator<<(string s){
            //cout<<"S(TRACE) : "<<s<<endl;
            if(name!="")
                output+=s;
            return *this;
        }

        Logger_Debug& operator<<(Logger_End_Of_File){
            if(name=="")
                return *this;
            ofstream file{name,ios::app};
            if(!file)
                throw name + " File not found";
            std::unique_lock mylock(*lock);
            file<<return_current_time_and_date()<<" : Logger Entry (DEBUG) \n\t"<<output<<endl;
            file.close();
            return *this;
        }


        template<integral Integer>
        Logger_Debug& operator<<(Integer i){
            //cout << "i :"<<i<<endl;
            if(name!="")
                output+=to_string(i);
            return *this;    
        }


        Logger_Debug& operator<<(bool l){
            //cout<<"ok"<<endl;
            if(name=="")
                return *this;
            if(l)
                output+="TRUE";
            else
                output+="FALSE";
            return *this;
        }

        Logger_Debug& operator<<(const char* s){
            if(name!="")
                output+=s;
            return *this;
        }

};












class Logger_Error{
    string name;
    shared_ptr<mutex> lock;
    string output="";
    
    public:
        Logger_Error(string s,shared_ptr<mutex> l):name{s},lock{l}{
            //cout<<"Filename : "<<s<<endl;
        }
        Logger_Error(const Logger_Error& l):name{l.name},lock{l.lock},output{l.output}{}
        Logger_Error(Logger_Error&& l):name{move(l.name)},lock{move(l.lock)},output{move(l.output)}{}


        Logger_Error& operator<<(string s){
            //cout<<"S(TRACE) : "<<s<<endl;
            if(name!="")
                output+=s;
            return *this;
        }

        Logger_Error& operator<<(Logger_End_Of_File){
            if(name=="")
                return *this;
            ofstream file{name,ios::app};
            if(!file)
                throw name + " File not found";
            std::unique_lock mylock(*lock);
            file<<return_current_time_and_date()<<" : Logger Entry (ERROR) \n\t"<<output<<endl;
            file.close();
            return *this;
        }


        template<integral Integer>
        Logger_Error& operator<<(Integer i){
            //cout << "i :"<<i<<endl;
            if(name!="")
                output+=to_string(i);
            return *this;    
        }


        Logger_Error& operator<<(bool l){
            //cout<<"ok"<<endl;
            if(name=="")
                return *this;
            if(l)
                output+="TRUE";
            else
                output+="FALSE";
            return *this;
        }

        Logger_Error& operator<<(const char* s){
            if(name!="")
                output+=s;
            return *this;
        }

};


class Logger_Trace{
    string name;
    shared_ptr<mutex> lock;
    string output="";
    
    public:
        Logger_Trace(string s,shared_ptr<mutex> l):name{s},lock{l}{
            //cout<<"Filename : "<<s<<endl;
        }
        Logger_Trace(const Logger_Trace& l):name{l.name},lock{l.lock},output{l.output}{}
        Logger_Trace(Logger_Trace&& l):name{move(l.name)},lock{move(l.lock)},output{move(l.output)}{}


        Logger_Trace& operator<<(string s){
            //cout<<"S(TRACE) : "<<s<<endl;
            if(name!="")
                output+=s;
            return *this;
        }

        Logger_Trace& operator<<(Logger_End_Of_File){
            if(name=="")
                return *this;
            ofstream file{name,ios::app};
            if(!file)
                throw name + " File not found";
            std::unique_lock mylock(*lock);
            file<<return_current_time_and_date()<<" : Logger Entry (TRACE) \n\t"<<output<<endl;
            file.close();
            return *this;
        }


        template<integral Integer>
        Logger_Trace& operator<<(Integer i){
            //cout << "i :"<<i<<endl;
            if(name!="")
                output+=to_string(i);
            return *this;    
        }


        Logger_Trace& operator<<(bool l){
            //cout<<"ok"<<endl;
            if(name=="")
                return *this;
            if(l)
                output+="TRUE";
            else
                output+="FALSE";
            return *this;
        }

        Logger_Trace& operator<<(const char* s){
            if(name!="")
                output+=s;
            return *this;
        }

};



///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////PROPERTIES//////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

class Enable{
        bool  value;
    public:
        Enable(bool b):value{b}{}
        string getValue()const{
            if(value)
                return "TRUE";
            else
                return "FALSE";
        }    
        string getName()const{
            return "ENABLE";
        }
};

class Level{
        int  value;
    public:
        Level(int b):value{b}{}
        string getValue()const{
            return to_string(value);
        }    
        string getName()const{
            return "LEVEL";
        }
};



template<typename t>
concept LoggerProperties = requires(t a){
    {a.getName()} -> same_as<string>;
    {a.getValue()} -> same_as<string>;
};

enum class RelationalOps{
    EQUALTO,
    NOTEQUALSTO,
    GREATERTHAN,
    LESSTHAN,
    GREATERTHANEQUALS,
    LESSTHANEQUALS
};

enum class LogicalOps{
    AND,
    OR,
    NOT
};

class Conditions;
class Union;

class Condition{
    string helper;
    RelationalOps op;
    string value;
    bool isSet=false;
    bool con=false;
    public:
        Condition()=default;
        template<typename lh>
        Condition(lh l,RelationalOps o,string v):helper{l.getName()},op{o},value{v}{}
        Condition(bool v):isSet{true},con{v}{}
        
        Condition(const Condition& c):
            helper{c.helper},
            op{c.op},
            value{c.value},
            isSet{c.isSet},
            con{c.con}
            {}
        
        Condition(Condition&& c):
            helper{move(c.helper)},
            op{move(c.op)},
            value{move(c.value)},
            isSet{c.isSet},
            con{c.con}
            {}
        

        bool perform(string s)const{
            switch(op){
                case RelationalOps::EQUALTO:   return s == value;
                case RelationalOps::NOTEQUALSTO: return s != value;
                case RelationalOps::GREATERTHAN: return atoi(s.c_str()) > atoi(value.c_str());
                case RelationalOps::LESSTHAN: return atoi(s.c_str()) < atoi(value.c_str());
                case RelationalOps::GREATERTHANEQUALS: return atoi(s.c_str()) >= atoi(value.c_str());
                case RelationalOps::LESSTHANEQUALS: return atoi(s.c_str()) <= atoi(value.c_str());
            }
            return false;
        }

        bool getValue(string s)const{
            if(isSet)
                return con;
            return perform(s);
        }
        bool  getSet()const{
            return isSet;
        }
        bool getConValue()const{
            return con;
        }

        string getHelper()const{
            return helper;
        }

        Conditions operator&&(Condition);

};



class Conditions{
    mutable vector<Union> conditions;
    mutable vector<LogicalOps> ops;
    public:
        Conditions()=default;
        Conditions(Condition c,LogicalOps op,Condition d);
        Conditions(Condition c);

        Conditions(const Conditions& cs);
        Conditions(Conditions&& cs):conditions{move(cs.conditions)},ops{move(cs.ops)}{}


        bool getValue(map<string,string> properties) const;
};



class Union{
    bool con=true;
    Condition c;
    Conditions cs;

    public:
        Union(Condition a):c{a}{}
        Union(Conditions a):cs{a}{}

        Union(const Union& u):
            con{u.con},
            c{u.c},
            cs{u.cs}
            {}
        
        Union(Union&& u):
            con{move(u.con)},
            c{move(u.c)},
            cs{move(u.cs)}
            {}

        bool isCondition()const{
            return con;
        }

        const Condition& getCondition()const{
            return c;
        }

        bool getValue(string s)const{
            return c.getValue(s);
        }

        bool getValue(map<string,string> p)const{
            return cs.getValue(p);
        }
};

Conditions Condition::operator&&(Condition c){
    return Conditions{*this,LogicalOps::AND,c};
}

Conditions::Conditions(Condition c,LogicalOps op,Condition d){
            conditions.push_back(Union{c});
            conditions.push_back(Union{d});
            ops.push_back(op);
        }

Conditions::Conditions(Condition c){
            conditions.push_back(Union{c});
        }

Conditions::Conditions(const Conditions& cs){
            for(auto c : cs.conditions)
                conditions.push_back(c);
            
            for(auto o : cs.ops)
                ops.push_back(o);
        }

bool Conditions::getValue(map<string,string> properties)const{
            vector<bool> result ;
            //cout<<"Evaluating"<<endl;
            if(ops.size()==0){
                auto c = conditions[0].getCondition();
                //cout<<"Ops size : 0"<<endl;
                return c.getValue(properties[c.getHelper()]);
            }
            //cout<<"Ops size : "<<ops.size()<<endl;
            while(ops.size()!=0){
                auto o = ops.back();
                ops.pop_back();


                switch(o){
                    case LogicalOps::NOT  : 
                        if(conditions.size()!=0){
                            auto b = conditions.back();
                            conditions.pop_back();
                            if(b.isCondition())
                                result.push_back(!b.getValue(properties[b.getCondition().getHelper()]));
                        }
                        else{
                            auto r = result.back();
                            result.pop_back();
                            result.push_back(!r);
                        }
                    break; 
                    case LogicalOps::AND  : 
                        //cout<<"And operator found"<<endl;
                        if(conditions.size()==0){
                            //cout<<"Conditions size : 0"<<endl;
                            auto a = result.back();
                            result.pop_back();
                            auto b = result.back();
                            result.pop_back();


                            result.push_back(a && b);
                        }
                        else{
                            bool a;
                            if(result.size()!=0){
                                a = result.back();
                                result.pop_back();
                            }
                            else{
                                auto c = conditions.back();
                                if(c.isCondition())
                                    a = c.getValue(properties[c.getCondition().getHelper()]);
                                else
                                    a = c.getValue(properties);
                            }
                            
                            auto u = conditions.back();
                            conditions.pop_back();
                            
                            if(u.isCondition()){
                                auto cond = u.getCondition();
                                auto helper = cond.getHelper();
                                auto property = properties[helper];
                                auto value = u.getValue(property);
                                result.push_back(a && value);
                            }
                            else
                                result.push_back(a && u.getValue(properties));
                        }
                    break; 
                    case LogicalOps::OR  : 
                        //cout<<"And operator found"<<endl;
                        if(conditions.size()==0){
                            //cout<<"Conditions size : 0"<<endl;
                            auto a = result.back();
                            result.pop_back();
                            auto b = result.back();
                            result.pop_back();


                            result.push_back(a || b);
                        }
                        else{
                            bool a;
                            if(result.size()!=0){
                                a = result.back();
                                result.pop_back();
                            }
                            else{
                                auto c = conditions.back();
                                if(c.isCondition())
                                    a = c.getValue(properties[c.getCondition().getHelper()]);
                                else
                                    a = c.getValue(properties);
                            }
                            
                            auto u = conditions.back();
                            conditions.pop_back();
                            
                            if(u.isCondition()){
                                auto cond = u.getCondition();
                                auto helper = cond.getHelper();
                                auto property = properties[helper];
                                auto value = u.getValue(property);
                                result.push_back(a || value);
                            }
                            else
                                result.push_back(a || u.getValue(properties));
                        }
                    break; 
                }
            }

            return result[0];
        }

class Enable_helper{
    public:
        Enable_helper(){
            static bool condition = true;
            assert(condition , "Enable_helper must be initialised only once");
            condition = false;
        }
        Enable operator=(bool b){
            return Enable{b};
        }


        string getName()const{
            return "ENABLE";
        }

        Condition operator==(bool b){
            if(b)
                return Condition{*this,RelationalOps::EQUALTO,"TRUE"};
            else
                return Condition{*this,RelationalOps::EQUALTO,"FALSE"};
        }

        Condition operator!=(bool b){
            if(b)
                return Condition{*this,RelationalOps::NOTEQUALSTO,"TRUE"};
            else
                return Condition{*this,RelationalOps::NOTEQUALSTO,"FALSE"};
        }
};


class Level_helper{
public:
        Level_helper(){
            static bool condition = true;
            assert(condition , "Level_helper must be initialised only once");
            condition = false;
        }
        Level operator=(int b){
            return Level{b};
        }


        string getName()const{
            return "LEVEL";
        }

        Condition operator==(int b){
            return Condition{*this,RelationalOps::EQUALTO,to_string(b)};
        }

        Condition operator!=(bool b){
            return Condition{*this,RelationalOps::NOTEQUALSTO,to_string(b)};
        }
        
        Condition operator>(int b){
            return Condition{*this,RelationalOps::GREATERTHAN,to_string(b)};
        }

        Condition operator<(bool b){
            return Condition{*this,RelationalOps::LESSTHAN,to_string(b)};
        }
        
        Condition operator>=(int b){
            return Condition{*this,RelationalOps::GREATERTHANEQUALS,to_string(b)};
        }

        Condition operator<=(bool b){
            return Condition{*this,RelationalOps::LESSTHANEQUALS,to_string(b)};
        }
};


Enable_helper enable;
Level_helper level;

class Logger{
    public:

    private:
        string fileName;
        bool loggerEnable = true;
        int level=0;
        shared_ptr<mutex> lock =make_shared<mutex>();
    
        void setPropertyByName(string p,string v){
            if(p=="ENABLE"){
                if(v=="TRUE")
                    loggerEnable = true;
                else
                    loggerEnable = false;
            }
            else if(p=="LEVEL")
                level = atoi(v.c_str());
        }

        template<LoggerProperties... P>
        void setProperty(P... p){
            std::apply([&](auto&&... args) {((setPropertyByName(args.getName(),args.getValue())), ...);}, tuple{p...});
        }

        map<string,string> getProperties()const{
            return {
                {"ENABLE",(loggerEnable)?"TRUE":"FALSE"},
                {"LEVEL",to_string(level)}
            };
        }


    public:

        template<LoggerProperties ... Properties>
        Logger(string f,Properties... properties):fileName{f}{
            setProperty(properties...);
            if(loggerEnable){
                if(f=="")
                    throw string{"Filename cannot be empty"};

                ofstream file{fileName,ios::out};
                if(!file)
                    throw fileName + " Error opening file";
                file.close();
            }
            else
                fileName="";
            //cout << "loggerEnable : "<<loggerEnable<<endl;
        }

        auto operator()(ERROR_Helper){
            if(loggerEnable)
                return Logger_Error{fileName,lock};
            else
                return Logger_Error{"",lock};
        }

        
        auto operator()(WARNING_Helper){
            if(loggerEnable)
                return Logger_Warning{fileName,lock};
            else
                return Logger_Warning{"",lock};
        }
        
        auto operator()(INFO_Helper){
            if(loggerEnable)
                return Logger_Info{fileName,lock};
            else
                return Logger_Info{"",lock};
        }

        
        auto operator()(DEBUG_Helper){
            if(loggerEnable)
                return Logger_Debug{fileName,lock};
            else
                return Logger_Debug{"",lock};
        }

        auto operator()(TRACE_Helper){
            if(loggerEnable)
                return Logger_Trace{fileName,lock};
            else
                return Logger_Trace{"",lock};
        }


        

        auto If(Conditions c,ERROR_Helper){
            if(loggerEnable){
                if(c.getValue(getProperties())){
                    return Logger_Error{fileName,lock};
                }
                else{
                	   //cout<<"Condition was not true"<<endl;
                    return Logger_Error{"",lock};
                }
            }
            return Logger_Error{"",lock};
        }

        auto If(bool c,ERROR_Helper){
            if(loggerEnable && c){
                return Logger_Error{fileName,lock};
            }
            return Logger_Error{"",lock};
        }

        auto If(Conditions c,TRACE_Helper){
            if(loggerEnable){
                if(c.getValue(getProperties())){
                    return Logger_Trace{fileName,lock};
                }
                else{
                	   //cout<<"Condition was not true"<<endl;
                    return Logger_Trace{"",lock};
                }
            }
            return Logger_Trace{"",lock};
        }

        auto If(bool c,TRACE_Helper){
            if(loggerEnable && c){
                return Logger_Trace{fileName,lock};
            }
            return Logger_Trace{"",lock};
        }

        auto If(Conditions c,DEBUG_Helper){
            if(loggerEnable){
                if(c.getValue(getProperties())){
                    return Logger_Debug{fileName,lock};
                }
                else{
                	   //cout<<"Condition was not true"<<endl;
                    return Logger_Debug{"",lock};
                }
            }
            return Logger_Debug{"",lock};
        }

        auto If(bool c,DEBUG_Helper){
            if(loggerEnable && c){
                return Logger_Debug{fileName,lock};
            }
            return Logger_Debug{"",lock};
        }

        auto If(Conditions c,INFO_Helper){
            if(loggerEnable){
                if(c.getValue(getProperties())){
                    return Logger_Info{fileName,lock};
                }
                else{
                	   //cout<<"Condition was not true"<<endl;
                    return Logger_Info{"",lock};
                }
            }
            return Logger_Info{"",lock};
        }

        auto If(bool c,INFO_Helper){
            if(loggerEnable && c){
                return Logger_Info{fileName,lock};
            }
            return Logger_Info{"",lock};
        }
        
};
