// main5-1.cpp ����bo5-1.cpp��������
#include"c1.h"
typedef int ElemType;
#include"c5-1.h"
#include"bo5-1.cpp"

void main()
{
  Array A;
  int i,j,k,*p,dim=3,bound1=3,bound2=4,bound3=2; // a[3][4][2]����
  ElemType e,*p1;
  InitArray(A,dim,bound1,bound2,bound3); // ����3��4��2��3ά����A
  p=A.bounds;
  printf("A.bounds=");
  for(i=0;i<dim;i++) // ˳�����A.bounds
    printf("%d ",*(p+i));
  p=A.constants;
  printf("\nA.constants=");
  for(i=0;i<dim;i++) // ˳�����A.constants
    printf("%d ",*(p+i));
  printf("\n%dҳ%d��%d�о���Ԫ������:\n",bound1,bound2,bound3);
  for(i=0;i<bound1;i++)
  {
    for(j=0;j<bound2;j++)
    {
      for(k=0;k<bound3;k++)
      {
        Assign(A,i*100+j*10+k,i,j,k); // ��i*100+j*10+k��ֵ��A[i][j][k]
        Value(e,A,i,j,k); // ��A[i][j][k]��ֵ����e
        printf("A[%d][%d][%d]=%2d ",i,j,k,e); // ���A[i][j][k]
      }
      printf("\n");
    }
    printf("\n");
  }
  p1=A.base;
  printf("A.base=\n");
  for(i=0;i<bound1*bound2*bound3;i++) // ˳�����A.base
  {
    printf("%4d",*(p1+i));
    if(i%(bound2*bound3)==bound2*bound3-1)
      printf("\n");
  }
  DestroyArray(A);
}

