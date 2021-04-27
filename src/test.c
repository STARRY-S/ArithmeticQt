/*用于记录符号的优先级，这里浪费了一些内存，可以优化*/
static char priority[128] = {0};
void priorityInit()
{
    /*初始化优先级，值越小，优先级越高*/
    priority['+'] = 4;
    priority['-'] = 4;
    priority['*'] = 3;
    priority['/'] = 3;
    priority['('] = 1;
    priority[')'] = 1;


}
/*比较运算符的优先级,op1优先级大于op2时，返回大于0的值*/
int priorityCompare(char op1,char op2)
{
    return priority[op2] - priority[op1];
}
/*出栈操作符和操作数进行计算*/
int calcOp(StackInfo_st *nums,StackInfo_st *ops,int nowOp)
{
    int a ,b,op;
    stack_pop(ops,&op);
    printf("op %c is <= %c\n",nowOp,op);
    printf("get op from stack %c\n",op);
    if(SUCCESS != stack_pop(nums,&b))
    {
        printf("pop failed\n");
        return -1;
    }
    if(SUCCESS != stack_pop(nums,&a))
    {
        printf("pop failed\n");
        return 0;
    }
    printf("get b from stack %d\n",b);

    printf("get a from stack %d\n",a);
    switch(op)
    {
        case '+':
        {
            printf("push %d into stack\n",a+b);
            stack_push(nums,a+b);
            break;
        }
        case '-':
        {
            stack_push(nums,a-b);
            break;
        }
        case '*':
        {
            printf("push %d into stack\n",a*b);
            stack_push(nums,a*b);
            break;
        }
        case '/':
        {
            printf("push %d into stack\n",a/b);
            stack_push(nums,a/b);
            break;
        }
    }
    return 1;
}
int calc(const char* exp,int *result)
{
    if(NULL == exp || NULL == result)
        return FAILURE;
    /*创建栈，用于保存数*/
    StackInfo_st nums;
    nums.topOfStack = TOP_OF_STACK;

    /*用于保存操作符*/
    StackInfo_st ops;
    ops.topOfStack = TOP_OF_STACK;
    int index = 0;
    /*用于标记，判断上一个是否为数字*/
    int flag = 0;
    int temp = 0;
    int op ;
    while(0 != *exp)
    {
        /*如果是数字*/
        if(isdigit(*exp))
        {
            printf("char is %c\n",*exp);
             /*如果上一个还是数字，则取出栈顶数据*/
            if(1 == flag)
               {

                stack_pop(&nums,&temp);
                printf("pop from stack num %d\n",temp);
                }
            else
                temp = 0;
            flag = 1;
            temp = 10 * temp + *exp-'0';
            printf("push %d to stack\n",temp);
            stack_push(&nums,temp);
        }
        /*如果是操作符*/
        else if('/' == *exp || '*' == *exp || '+' == *exp || '-' == *exp)
        {
            flag = 0;
            printf("OP is %c\n",*exp);
            while((ops.topOfStack > TOP_OF_STACK )&&(SUCCESS == stack_top(&ops,&op))&&'(' != op && ')'!=op&&(priorityCompare(*exp,op) <= 0))
            {
                calcOp(&nums, &ops,*exp);
            }
            printf("push %c to stack ops\n",*exp);
            stack_push(&ops,*exp);
        }
        /*左括号直接入栈*/
        else if('(' == *exp )
        {
            printf("push ( to stack ops\n");
            flag = 0;
            stack_push(&ops,*exp);
        }
        /*右括号，计算*/
        else if(')' ==*exp )
        {
            printf("deal with  ) in ops\n");
            flag = 0;
            /*右括号时，不断计算，直到遇见左括号*/
            while(SUCCESS == stack_top(&ops,&op) && '(' != op)
            {
                calcOp(&nums, &ops,*exp);
            }
            stack_pop(&ops,&op);
        }
        else
        {
            flag=0;
        }
        printf("flag is %d\n\n",flag);
        exp++;
    }
    /*计算剩余两个栈的内容*/
    while((!stack_is_empty(&ops)) && (!stack_is_empty(&nums)))
    {
        if(!calcOp(&nums, &ops,0))
        printf("exp is error\n");
    }
    stack_pop(&nums,&temp);
    /*如果栈中还有内容，说明表达式错误*/
    if((!stack_is_empty(&ops)) || (!stack_is_empty(&nums)))
        printf("\n\nexp is ok\n\n");

    if(SUCCESS == stack_pop(&nums,&temp))
        printf("result is %d\n",temp);
    *result = temp;
    return 0;
}
