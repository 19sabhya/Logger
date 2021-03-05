# Logger

| [Tutorial](#Tutorial) | [Step 1](#Step-1) | [Step 2](#Step-2) | [Step 3](#Step-3) | [Step 4](#Step-4) | [Step 5](#Step-5) | [Step 6](#Step-6) | [Step 7](#Step-7) | [Output](#Output) |

**Logging** is the act of creating, updating, and maintaining the log file of a system or a software application. 
It may seem like an easy task as all one has to do is add some comments to the log file about the events related 
to the system or a software application but it may not always be the case.  *How to create a log file?* That's what 
we are going to learn today. 

<a name="Tutorial"></a>
<details open><summary>Tutorial</summary>
<p>

<a name="step1"></a>
<details open><summary>Step 1</summary>

<p>
    
The simplest interface that can be used is a class with a callable object.
<p font size= 10><b>

```Logger log{//body};```
</b>
</p>

The object **"log"** must have the access to the output file in order to update and make changes to it. Therefore, the
path to the output file should be passed to it in the body section. This would make the above statement look like this:

```Logger log {"path_of_output_file"};```

Now, just like in file handling, an exception must be thrown by `FILESYSTEM` if the output file cannot be created 
or updated. Thus, it is a good practice to wrap the code in a try-catch block. 
</p>
</details>

<a name="step2"></a>
<details open><summary>Step 2</summary>
</p>

Next, we know that there is no fixed format of a log file. It is a helper tool created for future reference by 
the developer, therefore, its structure is software application and developers' requirement specific. Generally,
as per definition, a log file contains information about the events that take place in a system or a software 
application. Therefore, at minimum, entries of *FILE INFORMATION, ERRORS, WARNINGS, DEBUGGING, and TRACE* are kept.
An additional entry is being used called *LEND (logger end of file)*, it represents the end of a log entry. These 
entries are referred to as severity levels. So let's just make a helper class for each of them such that, only 
one instance of the class can be instantiated. There are many ways to do it but the best method would be to make
a metaclass, such as:

```Singleton ERROR_Helper{};
Singleton WARNING_Helper{};
.... so on
```

Let's make an object of these helper classes. 

```ERROR_Helper ERROR;
WARNING_Helper WARNING;
... so on
```
</p>
</details>

<a name="step3"></a>
<details open><summary>Step 3</summary>
<p>

These singleton classes now must be accessible to the `class Logger`. The `class Logger` constructor must take 
the path to the output file as discussed earlier. We made the class Logger thread-safe using a mutex lock.
It is done in order to avoid deadlock conditions that may arise when two or more threads attempt to write 
in the log file, simultaneously.

```class Logger{
    private:
        string fileName;
        shared_ptr<mutex> lock =make_shared<mutex>();
    public:
        Logger(string f):fileName{f}{
            if(f=="")
                    throw string{"Filename cannot be empty"};

            ofstream file{fileName,ios::out};
            if(!file)
                    throw fileName + " Error opening file";
            file.close();
            }
};
```
</p>
</details>

<a name="step4"></a>
<details open><summary>Step 4</summary>
<p>

Now, we must set the severity level to define which entry is being made. We use the operator overloading 
on the operator `"()"` to set the severity level.

    auto operator()(ERROR_Helper){
           return Logger_Error{fileName, lock};
    }
    

The code above specifically shows that the entry made has a severity level of Error. Similarly, 
operator `"()"` will be overloaded for other severity levels. The above code returns the value of 
`Logger_Error{fileName, lock}`, so we must create a class representing it.

</p>
</details>

<a name="step5"></a>
<details open><summary>Step 5</summary>
<p>

The `class Logger_Error` is the class responsible for finally making the entry of the various severity 
levels in the specified output log file. Therefore, the constructor of the `class Logger_Error` takes 
two inputs: fileName, which specifies the name of the output file, and lock, which ensures thread 
safety. Now to write in the log file left shift operator `"<<"` are overloaded for various types of 
possible parameters such as - `bool`, `integer`, `string`, `Logger_End_Of_File`, and `const char*`. This data 
is then stored in the buffer "output" and whenever the object "lend" is encountered an entry is made 
in the log file and the contents of the buffer are cleared. The operator overloading function with 
parameter as lend is as following:

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

At this point, our code for the logger may look complete. It is thread-safe, is able to make log entries
in the log file of the specified name and at the specified path. If you look closely it is still incomplete
as we may want to make entry of only a certain part. Thus, we need certain conditions and variables to
represents those conditions. The conditions to be fulfilled are *Enable*, which excepts a boolean value, 
specifies whether an entry to the log file is to be made, and *Level*, which excepts an integer value, 
specifies till which level the entry has to be made in the log file. In the future, more conditions can 
be considered. 

<p>
</details>

<a name="step6"></a>
<details open><summary>Step 6</summary>
<p>

To match all these changes our code needs to be updated as follows:

In the `private` section of the `class Logger` following updates are required:
        
        
        bool loggerEnable = true;
        int level=0;
        
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

In the `public` section of `class Logger` the constructor will have the following updates:
        
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
        }

In the `public` section of `class Logger` the operator overloading function on operator `"()"` will have the following update:

```
auto operator()(ERROR_Helper){
            if(loggerEnable)
                return Logger_Error{fileName, lock};
            else
                return Logger_Error{"",lock};
        }
```

Now for the conditions

```
        auto If(Conditions c,ERROR_Helper){
            if(loggerEnable){
                if(c.getValue(getProperties())){
                    return Logger_Error{fileName,lock};
                }
                else{
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
```

Similarly, for other severity levels If blocks will be made.

</p>
</details>

<a name="step7"></a>
<details open><summary>Step 7</summary>
<p>

Now, our logger is almost complete. Let's make some entries through function `main()` and check the output.

```int main(){
    try{

        Logger l{"table.txt",enable = true,level=3};

        l(TRACE)<<"hello "<<"world "<<20<<true<<lend;
        l(DEBUG)<<"hello DEBUG"<<lend;
        
        l.If(enable == true ,  ERROR) << "If conditions check"<<lend;

        l.If(level > 2,ERROR) << "Level Checking"<<lend;
        l.If(enable == true && level > 2,ERROR) << "Logger and Level Checking"<<lend;

        l.If(true,ERROR)<<"General check"<<lend;

        l.If(enable == true && false,ERROR)<<"check"<<lend;

    }
    catch(string s){
        cout<<s<<endl;
    }
    return 0;
}
```

</p>
</details>

<a name="output"></a>
<details open><summary>Output</summary>
</p>
It gave the following output:

</p align = "centre">
<img src ="/output.jpg">
</p>
</p>
</details>
</p>
</details>
