 // algo3-7.cpp ���ʽ��ֵ(��ΧΪint����,���븺��Ҫ��(0-����)��ʾ)
 typedef int SElemType; // ջԪ������Ϊ����,�Ľ��㷨3.4
 #include"c1.h"
 #include"c3-1.h"
 #include"bo3-1.cpp"

 SElemType Precede(SElemType t1,SElemType t2) // ͬalgo3-6.cpp
 { // ���ݽ̿����3.1���ж������ŵ����ȹ�ϵ
   SElemType f;
   switch(t2)
   {
     case '+':
     case '-':if(t1=='('||t1=='=')
                f='<';
              else
                f='>';
              break;
     case '*':
     case '/':if(t1=='*'||t1=='/'||t1==')')
                f='>';
              else
                f='<';
              break;
     case '(':if(t1==')')
              {
                printf("ERROR1\n");
                exit(ERROR);
              }
              else
                f='<';
              break;
     case ')':switch(t1)
              {
                case '(':f='=';
                         break;
                case '=':printf("ERROR2\n");
                         exit(ERROR);
                default: f='>';
              }
              break;
     case '=':switch(t1)
              {
                case '=':f='=';
                         break;
                case '(':printf("ERROR2\n");
                         exit(ERROR);
                default: f='>';
              }
   }
   return f;
 }

 Status In(SElemType c) // ������algo3-6.cpp��ͬ
 { // �ж�c�Ƿ�Ϊ�����
   switch(c)
   {
     case'+':
     case'-':
     case'*':
     case'/':
     case'(':
     case')':
     case'=':return TRUE; // �˾䲻ͬ��algo3-6.cpp
     default:return FALSE;
   }
 }

 SElemType Operate(SElemType a,SElemType theta,SElemType b) // �иĶ�
 {
   SElemType c;
   switch(theta)
   {
     case'+':c=a+b;
             break;
     case'-':c=a-b;
             break;
     case'*':c=a*b;
             break;
     case'/':c=a/b;
   }
   return c;
 }

 SElemType EvaluateExpression() // �иĶ�
 { // �������ʽ��ֵ����������㷨����OPTR��OPND�ֱ�Ϊ�����ջ��������ջ
   SqStack OPTR,OPND;
   SElemType a,b,d,x,theta;
   char c; // ����ɼ��̽��յ��ַ���
   char z[6]; // ��������ַ���
   int i;
   InitStack(OPTR); // ��ʼ�������ջ
   Push(OPTR,'='); // =�Ǳ��ʽ������־
   InitStack(OPND); // ��ʼ��������ջ
   c=getchar();
   GetTop(OPTR,x);
   while(c!='='||x!='=')
   {
     if(In(c)) // ��7�������֮һ
       switch(Precede(x,c))
       {
         case'<':Push(OPTR,c); // ջ��Ԫ������Ȩ��
                 c=getchar();
                 break;
         case'=':Pop(OPTR,x); // �����Ų�������һ�ַ�
                 c=getchar();
                 break;
         case'>':Pop(OPTR,theta); // ��ջ������������ջ
                 Pop(OPND,b);
                 Pop(OPND,a);
                 Push(OPND,Operate(a,theta,b));
       }
     else if(c>='0'&&c<='9') // c�ǲ�����
     {
       i=0;
       do
       {
         z[i]=c;
         i++;
         c=getchar();
       }while(c>='0'&&c<='9');
       z[i]=0;
       d=atoi(z); // ���ַ�������תΪ���ʹ���d
       Push(OPND,d);
     }
     else // c�ǷǷ��ַ�
     {
       printf("ERROR3\n");
       exit(ERROR);
     }
     GetTop(OPTR,x);
   }
   GetTop(OPND,x);
   return x;
 }

 void main() // �иĶ�
 {
   printf("�������������ʽ,����Ҫ��(0-����)��ʾ,����=����\n");
   printf("%d\n",EvaluateExpression());
 }
