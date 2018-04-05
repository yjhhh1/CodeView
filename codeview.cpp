#include<bits/stdc++.h>
using namespace std;
set<int>num;/**< 用来统计错误标识符的行号和对同一行多处错误的去重操作 */
char data[1024],temp[1024]= {'\0'};/**< 声明用来保存数据和临时数据的两个字符数组 */
void ErrorSlove(int linenum)/**< 统计错误标识符的行号及输出 */
{
    printf("LexicalError,");
    num.insert(linenum);
}
void ErrorCount()/**< 输出错误标识符的行号 */
{
    if(!num.empty())
    {
        printf("LexicalError(s) on line(s) ");
        for(set<int>::iterator it=num.begin(); it!=num.end(); ++it)
            printf("%d,",*it);
        num.clear();
    }
}
void ConstSolve(int&i,int line)/**< 常量的识别及处理 */
{
    do
    {
        temp[strlen(temp)]=data[i++];
    }
    while(isalnum(data[i])&&data[i]!='\0');
    temp[strlen(temp)]='\0';
    /**
     *对包含错误标识符的识别。
     */
    bool check=true;;
    for(int j=0; temp[j]!='\0'; ++j)
        if(!isdigit(temp[j]))
        {
            check=false;
            break;
        }
    if(check)
    {
        printf("<2,%s>,",temp);
    }
    else ErrorSlove(line);
    --i;
}
void TokenSelove(int &i)/**< 关键字和变量的判断和处理 */
{
    do
    {
        temp[strlen(temp)]=data[i++];
    }
    while(isalnum(data[i])&&data[i]!='\0');
    temp[strlen(temp)]='\0';
    if(!strcmp(temp,"void"))printf("<25,->,");
    else if(!strcmp(temp,"int"))printf("<26,->,");
    else if(!strcmp(temp,"float"))printf("<27,->,");
    else if(!strcmp(temp,"char"))printf("<28,->,");
    else if(!strcmp(temp,"if"))printf("<29,->,");
    else if(!strcmp(temp,"else"))printf("<30,->,");
    else if(!strcmp(temp,"while"))printf("<31,->,");
    else if(!strcmp(temp,"do"))printf("<32,->,");
    else if(!strcmp(temp,"return"))printf("<33,->,");
    else printf("<1,%s>,",temp);
    --i;
}
void OperatorSlove(int &i,int line)/**< 运算符判断和处理 */
{
    switch(data[i])
    {
    case '+':
        printf("<3,->,");
        break;
    case '-':
        printf("<4,->,");
        break;
    case '*':
        printf("<5,->,");
        break;
    case '/':
        if(data[i+1]=='/')
        {
            /**
             *处理注释标记，查找回车字符出现的位置
             */
            i=strchr(&data[i+2],'\n')-data;
            printf("\n");
        }
        else if(data[i+1]=='*')
        {
            i=strchr(&data[i+2],'/')-data+1;
            printf("\n");
        }
        else
            printf("<6,->,");
        break;
    case '%':
        printf("<7,->,");
        break;
    case '<':
        if(data[i+1]=='=')
        {
            ++i;
            printf("<9,->,");
        }
        else printf("<8,->,");
        break;
    case '>':
        if(data[i+1]=='=')
        {
            ++i;
            printf("<11,->,");
        }
        else printf("<10,->,");
        break;
    case '=':
        if(data[i+1]=='=')
        {
            ++i;
            printf("<12,->,");
        }
        else printf("<16,->,");
        break;
    case '!':
        if(data[i+1]=='=')
        {
            ++i;
            printf("<13,->,");
            break;
        }
    case '&':
        if(data[i+1]=='&')
        {
            ++i;
            printf("<14,->,");
            break;
        }
    case '|':
        if(data[i+1]=='|')
        {
            ++i;
            printf("<15,->,");
            break;
        }
    case '(':
        printf("<17,->,");
        break;
    case ')':
        printf("<18,->,");
        break;
    case '[':
        printf("<19,->,");
        break;
    case ']':
        printf("<20,->,");
        break;
    case '{':
        printf("<21,->,");
        break;
    case '}':
        printf("<22,->,");
        break;
    case ';':
        printf("<23,->,");
        break;
    case ',':
        printf("<24,->,");
        break;
    default:
        ErrorSlove(line);
    }
}
int main()
{
    cin.getline(data,1024,'#');
    for(int i=0,line=1; data[i]!='\0'; memset(temp,'\0',sizeof(temp)),++i)/**< 每次执行完操作后将temp数组中的所有元素设置为'\0'*/
        if(data[i]=='\n'&&data[i-1]!=' '&&data[i-1]!='\n')/**< 统计行号，并执行换行操作*/
        {
            line++;
            printf("\n");
        }
        else if(isspace(data[i]))continue;
        else if(isdigit(data[i]))ConstSolve(i,line);
        else if(isalpha(data[i]))TokenSelove(i);
        else OperatorSlove(i,line);
    ErrorCount();
    return 0;
}
