// bo5-1.cpp ˳��洢����(�洢�ṹ��c5-1.h����)�Ļ�������(5��)
Status InitArray(Array &A,int dim,...)
{ // ��ά��dim�͸�ά���ȺϷ���������Ӧ������A��������OK��ͼ5-2��
  int elemtotal=1,i; // elemtotal��Ԫ����ֵ
  va_list ap;
  if(dim<1||dim>MAX_ARRAY_DIM)
    return ERROR;
  A.dim=dim;
  A.bounds=(int *)malloc(dim*sizeof(int));
  if(!A.bounds)
    exit(OVERFLOW);
  va_start(ap,dim);
  for(i=0;i<dim;++i)
  {
    A.bounds[i]=va_arg(ap,int);
    if(A.bounds[i]<0)
      return UNDERFLOW; // ��math.h�ж���Ϊ4
    elemtotal*=A.bounds[i];
  }
  va_end(ap);
  A.base=(ElemType *)malloc(elemtotal*sizeof(ElemType));
  if(!A.base)
    exit(OVERFLOW);
  A.constants=(int *)malloc(dim*sizeof(int));
  if(!A.constants)
    exit(OVERFLOW);
  A.constants[dim-1]=1;
  for(i=dim-2;i>=0;--i)
    A.constants[i]=A.bounds[i+1]*A.constants[i+1];
  return OK;
}

Status DestroyArray(Array &A)
{ // ��������A��ͼ5-3��
  if(A.base)
  {
    free(A.base);
    A.base=NULL;
  }
  else
    return ERROR;
  if(A.bounds)
  {
    free(A.bounds);
    A.bounds=NULL;
  }
  else
    return ERROR;
  if(A.constants)
  {
    free(A.constants);
    A.constants=NULL;
  }
  else
    return ERROR;
  return OK;
}

Status Locate(Array A,va_list ap,int &off) // Value()��Assign()���ô˺���
{ // ��apָʾ�ĸ��±�ֵ�Ϸ����������Ԫ����A�е���Ե�ַoff
  int i,ind;
  off=0;
  for(i=0;i<A.dim;i++)
  {
    ind=va_arg(ap,int);
    if(ind<0||ind>=A.bounds[i])
      return OVERFLOW;
    off+=A.constants[i]*ind;
  }
  return OK;
}

Status Value(ElemType &e,Array A,...) // ��VC++�У�...֮ǰ���ββ�������������
{ // ...����Ϊ��ά���±�ֵ�������±�Ϸ�����e����ֵΪA����Ӧ��Ԫ��ֵ
  va_list ap;
  Status result;
  int off;
  va_start(ap,A);
  if((result=Locate(A,ap,off))==OVERFLOW) // ����Locate()
    return result;
  e=*(A.base+off);
  return OK;
}

Status Assign(Array &A,ElemType e,...)
{ // ...����Ϊ��ά���±�ֵ�������±�Ϸ�����e��ֵ����A��ָ����Ԫ��
  va_list ap;
  Status result;
  int off;
  va_start(ap,e);
  if((result=Locate(A,ap,off))==OVERFLOW) // ����Locate()
    return result;
  *(A.base+off)=e;
  return OK;
}

